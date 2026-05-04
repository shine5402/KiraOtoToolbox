#include "utils/widgets/RemoteImageTextBrowser.h"

#include <QAbstractTextDocumentLayout>
#include <QDebug>
#include <QNetworkReply>
#include <QNetworkRequest>

RemoteImageTextBrowser::RemoteImageTextBrowser(QWidget *parent) : QTextBrowser(parent)
{
}

void RemoteImageTextBrowser::setAllowRemoteImageLoad(bool allow)
{
    m_allowRemote = allow;
    if (allow && !m_nam) {
        m_nam = new QNetworkAccessManager(this);
    }
}

QVariant RemoteImageTextBrowser::loadResource(int type, const QUrl &name)
{
    if (type == QTextDocument::ImageResource && m_allowRemote && m_nam) {
        if (name.scheme().startsWith("http")) { // http or https
            // Check our internal cache
            if (m_resourceCache.contains(name)) {
                return m_resourceCache.value(name);
            }

            // Avoid duplicate downloads
            if (!m_loadingUrls.contains(name)) {
                m_loadingUrls.insert(name);
                QNetworkRequest request(name);
                request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);

                QNetworkReply *reply = m_nam->get(request);
                connect(reply, &QNetworkReply::finished, this, [this, reply, name]() {
                    if (reply->error() == QNetworkReply::NoError) {
                        QByteArray data = reply->readAll();
                        QImage image;
                        if (image.loadFromData(data)) {
                            m_resourceCache.insert(name, image);
                            // Trigger layout update so the view calls loadResource again
                            emit document()->documentLayout()->update();
                        }
                    }
                    m_loadingUrls.remove(name);
                    reply->deleteLater();
                });
            }
            // Return null variant while loading
            return QVariant();
        }
    }
    return QTextBrowser::loadResource(type, name);
}
