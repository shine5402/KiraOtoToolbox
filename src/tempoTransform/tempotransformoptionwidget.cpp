#include "tempotransformoptionwidget.h"
#include "kira/lib_helper/fplus_qt_adapter.h"
#include "ui_tempotransformoptionwidget.h"
#include <QMessageBox>

TempoTransformOptionWidget::TempoTransformOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::TempoTransformOptionWidget)
{
    ui->setupUi(this);

    connect(ui->offsetDoubleSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->fromDoubleSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->toDoubleSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &ToolOptionWidget::userSettingsChanged);

    connect(ui->guessSrcTempoButton, &QPushButton::clicked, this, [this](){
        emit askOtoData(guessTempoAskId);
    });
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

void TempoTransformOptionWidget::setOptions(const OptionContainer& options)
{
    ui->offsetDoubleSpinBox->setValue(options.getOption("offset").toDouble());
    ui->fromDoubleSpinBox->setValue(options.getOption("fromTempo", 120).toDouble());
    ui->toDoubleSpinBox->setValue(options.getOption("toTempo", 120).toDouble());
}

QJsonObject TempoTransformOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject json;

    json.insert("offset", options.getOption("offset").toDouble());
    json.insert("fromTempo", options.getOption("fromTempo").toDouble());
    json.insert("toTempo", options.getOption("toTempo").toDouble());

    return json;
}

OptionContainer TempoTransformOptionWidget::jsonToOptions(const QJsonObject& json) const
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


void TempoTransformOptionWidget::askOtoDataCallback(int askId, const QVector<OtoEntryList>& contents)
{
    if (askId == guessTempoAskId)
    {
        auto absolutePre = [](const OtoEntry& entry)->double{
            return entry.left() + entry.preUtterance();
        };

        auto stdSrc = std::vector(contents[0].begin(), contents[0].end());

        auto most_frequent_distance = fplus::maximum_by([](std::pair<int, std::size_t> lhs, std::pair<int, std::size_t> rhs) -> bool{
            return lhs.second < rhs.second;
                          },fplus::transform_and_concat([&](const std::vector<OtoEntry> entries) -> std::vector<std::pair<int, std::size_t>>{
            return fplus::map_to_pairs(
            fplus::count_occurrences_by<int(double)>(fplus::floor,
            fplus::transform([&](std::pair<OtoEntry, OtoEntry> pair)->double{
                return absolutePre(pair.second) - absolutePre(pair.first);
            },
            fplus::zipWithNext(entries))));
        } ,fplus::group_by([](const OtoEntry& lhs, const OtoEntry& rhs)->bool{
            return lhs.fileName() == rhs.fileName();
        }, stdSrc))).first;

        if (most_frequent_distance <= 0)
            QMessageBox::critical(this,{}, tr("We can not guess tempo from the given data."));

        // Divided by 10 then muliply by 10 means tempos like 122 -> 120.
        auto guessedTempo = fplus::round(60000.0 / most_frequent_distance / 10) * 10;
        ui->fromDoubleSpinBox->setValue(guessedTempo);
    }
}
