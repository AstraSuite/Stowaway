#include "clipboarditem.hpp"
#include <QUuid>
#include <QRegularExpression>
#include <QColor>

namespace stowaway::core {

ClipboardItem::ClipboardItem(QObject* parent)
    : QObject(parent)
    , m_id(QUuid::createUuid().toString(QUuid::WithoutBraces))
    , m_timestamp(QDateTime::currentDateTime()) {}

ClipboardItem::ClipboardItem(const QString& id, ClipboardType type, const QString& content,
                             const QDateTime& time, bool pinned, QObject* parent)
    : QObject(parent)
    , m_id(id.isEmpty() ? QUuid::createUuid().toString(QUuid::WithoutBraces) : id)
    , m_type(type)
    , m_content(content)
    , m_timestamp(time)
    , m_pinned(pinned) {
    updateDerivedFields();
}

QString ClipboardItem::typeName() const {
    switch (m_type) {
        case ClipboardType::Code: return QStringLiteral("Code");
        case ClipboardType::Url: return QStringLiteral("URL");
        case ClipboardType::Color: return QStringLiteral("Color");
        case ClipboardType::Image: return QStringLiteral("Image");
        case ClipboardType::Text:
        default: return QStringLiteral("Text");
    }
}

void ClipboardItem::setType(ClipboardType type) {
    if (m_type != type) {
        m_type = type;
        emit typeChanged();
    }
}

void ClipboardItem::setContent(const QString& c) {
    if (m_content != c) {
        m_content = c;
        updateDerivedFields();
        emit contentChanged();
    }
}

void ClipboardItem::setPreviewText(const QString& pt) {
    if (m_previewText != pt) {
        m_previewText = pt;
        emit previewTextChanged();
    }
}

void ClipboardItem::setImagePath(const QString& p) {
    if (m_imagePath != p) {
        m_imagePath = p;
        emit imagePathChanged();
    }
}

void ClipboardItem::setTimestamp(const QDateTime& dt) {
    if (m_timestamp != dt) {
        m_timestamp = dt;
        emit timestampChanged();
    }
}

void ClipboardItem::setPinned(bool p) {
    if (m_pinned != p) {
        m_pinned = p;
        emit pinnedChanged();
    }
}

void ClipboardItem::setColorHex(const QString& hex) {
    if (m_colorHex != hex) {
        m_colorHex = hex;
        emit colorHexChanged();
    }
}

void ClipboardItem::updateDerivedFields() {
    m_charCount = m_content.length();
    m_lineCount = m_content.isEmpty() ? 0 : m_content.count(QLatin1Char('\n')) + 1;

    if (m_type != ClipboardType::Image) {
        m_byteSize = m_content.toUtf8().size();
        QString trimmed = m_content.trimmed();
        if (trimmed.length() > 300) {
            m_previewText = trimmed.left(297) + QStringLiteral("...");
        } else {
            m_previewText = trimmed;
        }

        // Color detection: #RGB, #RRGGBB, #RRGGBBAA, rgb(), rgba()
        static const QRegularExpression hexRegex(QStringLiteral("^#([0-9a-fA-F]{3}|[0-9a-fA-F]{6}|[0-9a-fA-F]{8})$"));
        if (hexRegex.match(trimmed).hasMatch()) {
            QColor col(trimmed);
            if (col.isValid()) {
                m_type = ClipboardType::Color;
                m_colorHex = col.name(col.alpha() < 255 ? QColor::HexArgb : QColor::HexRgb);
            }
        } else if (trimmed.startsWith(QLatin1String("http://")) || trimmed.startsWith(QLatin1String("https://")) || trimmed.startsWith(QLatin1String("ftp://"))) {
            m_type = ClipboardType::Url;
        } else if (m_lineCount > 2 || m_content.contains(QLatin1String("{")) || m_content.contains(QLatin1String("function")) ||
                   m_content.contains(QLatin1String("const ")) || m_content.contains(QLatin1String("let ")) ||
                   m_content.contains(QLatin1String("#include")) || m_content.contains(QLatin1String("import ")) ||
                   m_content.contains(QLatin1String("def ")) || m_content.contains(QLatin1String("class ")) ||
                   m_content.contains(QLatin1String("return ")) || m_content.contains(QLatin1String("=>"))) {
            m_type = ClipboardType::Code;
        }
    }
}

QString ClipboardItem::timeAgo() const {
    qint64 secs = m_timestamp.secsTo(QDateTime::currentDateTime());
    if (secs < 60) return QStringLiteral("Just now");
    if (secs < 3600) return QStringLiteral("%1m ago").arg(secs / 60);
    if (secs < 86400) return QStringLiteral("%1h ago").arg(secs / 3600);
    if (secs < 604800) return QStringLiteral("%1d ago").arg(secs / 86400);
    return m_timestamp.toString(QStringLiteral("MMM d"));
}

QJsonObject ClipboardItem::toJson() const {
    QJsonObject obj;
    obj[QStringLiteral("id")] = m_id;
    obj[QStringLiteral("type")] = static_cast<int>(m_type);
    obj[QStringLiteral("content")] = m_content;
    obj[QStringLiteral("previewText")] = m_previewText;
    obj[QStringLiteral("imagePath")] = m_imagePath;
    obj[QStringLiteral("imageWidth")] = m_imageWidth;
    obj[QStringLiteral("imageHeight")] = m_imageHeight;
    obj[QStringLiteral("byteSize")] = m_byteSize;
    obj[QStringLiteral("timestamp")] = m_timestamp.toString(Qt::ISODateWithMs);
    obj[QStringLiteral("pinned")] = m_pinned;
    obj[QStringLiteral("colorHex")] = m_colorHex;
    return obj;
}

ClipboardItem* ClipboardItem::fromJson(const QJsonObject& obj, QObject* parent) {
    auto* item = new ClipboardItem(parent);
    item->setId(obj.value(QStringLiteral("id")).toString());
    item->setType(static_cast<ClipboardType>(obj.value(QStringLiteral("type")).toInt(0)));
    item->setContent(obj.value(QStringLiteral("content")).toString());
    item->setPreviewText(obj.value(QStringLiteral("previewText")).toString());
    item->setImagePath(obj.value(QStringLiteral("imagePath")).toString());
    item->setImageWidth(obj.value(QStringLiteral("imageWidth")).toInt(0));
    item->setImageHeight(obj.value(QStringLiteral("imageHeight")).toInt(0));
    item->setByteSize(obj.value(QStringLiteral("byteSize")).toInteger(0));
    item->setTimestamp(QDateTime::fromString(obj.value(QStringLiteral("timestamp")).toString(), Qt::ISODateWithMs));
    item->setPinned(obj.value(QStringLiteral("pinned")).toBool(false));
    item->setColorHex(obj.value(QStringLiteral("colorHex")).toString());
    item->updateDerivedFields();
    return item;
}

} // namespace stowaway::core
