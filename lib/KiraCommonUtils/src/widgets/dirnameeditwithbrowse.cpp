#include <kira/widgets/dirnameeditwithbrowse.h>
#include <QFileDialog>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDragEnterEvent>
#include <QMimeData>

DirNameEditWithBrowse::DirNameEditWithBrowse(QWidget *parent) : QWidget(parent)
{
    setAcceptDrops(true);

    auto layout = new QHBoxLayout(this);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
    layout->setMargin(0);
#else
    layout->setContentsMargins(0, 0, 0, 0);
#endif

    dirNameEdit = new QLineEdit(this);
    layout->addWidget(dirNameEdit);

    browseButton = new QPushButton(tr("Browse"), this);
    layout->addWidget(browseButton);

    connect(browseButton, &QPushButton::clicked, this, &DirNameEditWithBrowse::onBrowse);
}

QString DirNameEditWithBrowse::dirName() const
{
    return dirNameEdit->text();
}

void DirNameEditWithBrowse::setDirName(const QString& value)
{
    dirNameEdit->setText(value);
}

QString DirNameEditWithBrowse::getCaption() const
{
    return caption;
}

void DirNameEditWithBrowse::setCaption(const QString& value)
{
    caption = value;
}

QFileDialog::Options DirNameEditWithBrowse::getOptions() const
{
    return options;
}

void DirNameEditWithBrowse::setOptions(const QFileDialog::Options& value)
{
    options = value;
}

void DirNameEditWithBrowse::onBrowse()
{
    auto result = QFileDialog::getExistingDirectory(this, caption, dirName(), options);
    if (!result.isEmpty())
    {
        dirNameEdit->setText(result);
        emit browseTriggered();
    }
}

void DirNameEditWithBrowse::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasUrls()){
        event->setDropAction(Qt::LinkAction);
        event->accept();
    }
}


void DirNameEditWithBrowse::dropEvent(QDropEvent* event)
{
    if (event->mimeData()->hasUrls()){
        QFileInfo fileInfo{event->mimeData()->urls().value(0).toLocalFile()};
        QString result;
        if (fileInfo.isDir())
            result = fileInfo.absoluteFilePath();
        else
            result = fileInfo.absoluteDir().absolutePath();
        dirNameEdit->setText(result);
        emit dropTriggered();
        event->setDropAction(Qt::LinkAction);
        event->accept();
    }
}

void DirNameEditWithBrowse::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        browseButton->setText(tr("Browse"));
    }
}
