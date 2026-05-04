#ifndef REMOTEIMAGETEXTBROWSER_H
#define REMOTEIMAGETEXTBROWSER_H

#include <QNetworkAccessManager>
#include <QSet>
#include <QTextBrowser>
#include <QUrl>

class RemoteImageTextBrowser : public QTextBrowser
{
    Q_OBJECT
public:
    explicit RemoteImageTextBrowser(QWidget *parent = nullptr);
    void setAllowRemoteImageLoad(bool allow);

protected:
    QVariant loadResource(int type, const QUrl &name) override;

private:
    bool m_allowRemote = false;
    QNetworkAccessManager *m_nam = nullptr;
    QSet<QUrl> m_loadingUrls;
    QMap<QUrl, QImage> m_resourceCache;
};

#endif // REMOTEIMAGETEXTBROWSER_H
