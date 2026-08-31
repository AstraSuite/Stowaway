#pragma once

#include <QQuickImageProvider>
#include <QHash>
#include <QImage>
#include <QMutex>

namespace stowaway::core {

class ThumbnailImageProvider : public QQuickImageProvider {
public:
    ThumbnailImageProvider();

    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;

    static void cacheImage(const QString& id, const QImage& image);
    static QImage getImage(const QString& id);

private:
    static QHash<QString, QImage> s_cache;
    static QMutex s_mutex;
};

} // namespace stowaway::core
