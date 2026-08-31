#include "thumbnailprovider.hpp"
#include <QFile>
#include <QDir>
#include <QStandardPaths>

namespace stowaway::core {

QHash<QString, QImage> ThumbnailImageProvider::s_cache;
QMutex ThumbnailImageProvider::s_mutex;

ThumbnailImageProvider::ThumbnailImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image) {}

QImage ThumbnailImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize) {
    QImage img = getImage(id);
    if (img.isNull()) {
        QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + QStringLiteral("/thumbnails");
        QString filePath = cacheDir + QStringLiteral("/") + id + QStringLiteral(".png");
        if (QFile::exists(filePath)) {
            img.load(filePath);
            cacheImage(id, img);
        }
    }

    if (!img.isNull()) {
        if (size) *size = img.size();
        if (requestedSize.isValid() && requestedSize != img.size()) {
            return img.scaled(requestedSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        return img;
    }

    return QImage();
}

void ThumbnailImageProvider::cacheImage(const QString& id, const QImage& image) {
    QMutexLocker locker(&s_mutex);
    s_cache.insert(id, image);
}

QImage ThumbnailImageProvider::getImage(const QString& id) {
    QMutexLocker locker(&s_mutex);
    return s_cache.value(id);
}

} // namespace stowaway::core
