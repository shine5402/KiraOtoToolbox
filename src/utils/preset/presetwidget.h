#ifndef PRESETWIDGET_H
#define PRESETWIDGET_H

#include <QWidget>
#include <QAbstractItemView>
class QStandardItemModel;

namespace Ui {
    class PresetWidget;
}

class PresetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PresetWidget(QAbstractItemView* contentView, QWidget *parent = nullptr);
    ~PresetWidget();

    void changeContentView(QAbstractItemView* newView);
    QAbstractItemView* getContentView() const;

    //QStringList getPresetNames() const;
    //void setPresetNames(const QStringList& value);

    QString getCurrentPresetName() const;
    QVariant getCurrentPresetContent() const;
    bool isCurrentPresetModified() const;

    QStandardItemModel* getPresetNameModel() const;
    void setPresetNameModel(QStandardItemModel* value);


private:
    Ui::PresetWidget *ui;
    QAbstractItemView* contentView = nullptr;
    //QStringList presetNames;

signals:
    void presetSwitched(int id);
    void presetRenameAsked(int id);
    void presetCopyAsked(int id);
    void presetRemoveAsked(int id);
    void presetSaveAsked(int id, QVariant content);
    void extendEditAsked(int index);
};

#endif // PRESETWIDGET_H
