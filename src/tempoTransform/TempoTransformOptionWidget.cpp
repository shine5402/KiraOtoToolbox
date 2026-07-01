#include "TempoTransformOptionWidget.h"
#include "ui_TempoTransformOptionWidget.h"

#include <QMessageBox>

#include <algorithm>
#include <cmath>
#include <map>

TempoTransformOptionWidget::TempoTransformOptionWidget(QWidget *parent)
    : ToolOptionWidget(parent), ui(new Ui::TempoTransformOptionWidget)
{
    ui->setupUi(this);

    connect(ui->offsetDoubleSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this,
            &ToolOptionWidget::userSettingsChanged);
    connect(ui->fromDoubleSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this,
            &ToolOptionWidget::userSettingsChanged);
    connect(ui->toDoubleSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this,
            &ToolOptionWidget::userSettingsChanged);

    connect(ui->guessSrcTempoButton, &QPushButton::clicked, this, [this]() { emit askOtoData(guessTempoAskId); });
}

TempoTransformOptionWidget::~TempoTransformOptionWidget()
{
    delete ui;
}

OptionContainer TempoTransformOptionWidget::getOptions() const
{
    OptionContainer options;

    options.setOption("offset", ui->offsetDoubleSpinBox->value());
    options.setOption("fromTempo", ui->fromDoubleSpinBox->value());
    options.setOption("toTempo", ui->toDoubleSpinBox->value());

    return options;
}

void TempoTransformOptionWidget::setOptions(const OptionContainer &options)
{
    ui->offsetDoubleSpinBox->setValue(options.getOption("offset").toDouble());
    ui->fromDoubleSpinBox->setValue(options.getOption("fromTempo", 120).toDouble());
    ui->toDoubleSpinBox->setValue(options.getOption("toTempo", 120).toDouble());
}

QJsonObject TempoTransformOptionWidget::optionsToJson(const OptionContainer &options) const
{
    QJsonObject json;

    json.insert("offset", options.getOption("offset").toDouble());
    json.insert("fromTempo", options.getOption("fromTempo").toDouble());
    json.insert("toTempo", options.getOption("toTempo").toDouble());

    return json;
}

OptionContainer TempoTransformOptionWidget::jsonToOptions(const QJsonObject &json) const
{
    OptionContainer options;

    options.setOption("offset", json.value("offset").toDouble());
    options.setOption("fromTempo", json.value("fromTempo").toDouble(120));
    options.setOption("toTempo", json.value("toTempo").toDouble(120));

    return options;
}

int TempoTransformOptionWidget::optionJsonVersion() const
{
    return 1;
}

void TempoTransformOptionWidget::askOtoDataCallback(int askId, const QVector<OtoEntryList> &contents)
{
    if (askId == guessTempoAskId) {
        auto absolutePre = [](const OtoEntry &entry) -> double {
            return entry.left() + entry.preUtterance();
        };

        auto stdSrc = std::vector(contents[0].begin(), contents[0].end());

        // Group by fileName
        std::vector<std::vector<OtoEntry>> groups;
        for (std::size_t i = 0; i < stdSrc.size();) {
            std::size_t j = i + 1;
            while (j < stdSrc.size() && stdSrc[j].fileName() == stdSrc[i].fileName())
                ++j;
            groups.emplace_back(stdSrc.begin() + i, stdSrc.begin() + j);
            i = j;
        }

        // Collect (floor_distance, count) across all groups
        std::vector<std::pair<int, std::size_t>> allCounts;
        for (const auto &entries : groups) {
            std::map<int, std::size_t> countMap;
            for (std::size_t i = 1; i < entries.size(); ++i) {
                const auto &a = entries[i - 1];
                const auto &b = entries[i];
                auto distance = absolutePre(b) - absolutePre(a);
                ++countMap[static_cast<int>(std::floor(distance))];
            }
            for (const auto &kv : countMap)
                allCounts.emplace_back(kv.first, kv.second);
        }

        if (allCounts.empty()) {
            QMessageBox::critical(this, {}, tr("We can not guess tempo from the given data."));
            return;
        }

        auto most_frequent_distance =
            std::ranges::max_element(allCounts, {}, &std::pair<int, std::size_t>::second)->first;

        if (most_frequent_distance <= 0)
            QMessageBox::critical(this, {}, tr("We can not guess tempo from the given data."));

        auto guessedTempo = std::round(60000.0 / most_frequent_distance / 10) * 10;
        ui->fromDoubleSpinBox->setValue(guessedTempo);
    }
}
