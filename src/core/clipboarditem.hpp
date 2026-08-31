#pragma once

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QImage>
#include <QJsonObject>
#include <qqmlintegration.h>

namespace stowaway::core {

enum class ClipboardType {
    Text = 0,
    Code,
    Url,
    Color,
    Image
};

class ClipboardItem : public QObject {
    Q_OBJECT
    QML_ANONYMOUS

    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(int type READ typeInt NOTIFY typeChanged)
    Q_PROPERTY(QString typeName READ typeName NOTIFY typeChanged)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(QString previewText READ previewText NOTIFY previewTextChanged)
    Q_PROPERTY(QString previewLine1 READ previewLine1 NOTIFY previewTextChanged)
    Q_PROPERTY(QString previewLine2 READ previewLine2 NOTIFY previewTextChanged)
    Q_PROPERTY(QString imagePath READ imagePath NOTIFY imagePathChanged)
    Q_PROPERTY(int imageWidth READ imageWidth NOTIFY imagePathChanged)
    Q_PROPERTY(int imageHeight READ imageHeight NOTIFY imagePathChanged)
    Q_PROPERTY(qint64 byteSize READ byteSize NOTIFY byteSizeChanged)
    Q_PROPERTY(int lineCount READ lineCount NOTIFY contentChanged)
    Q_PROPERTY(int charCount READ charCount NOTIFY contentChanged)
    Q_PROPERTY(QDateTime timestamp READ timestamp NOTIFY timestampChanged)
    Q_PROPERTY(QString timeAgo READ timeAgo NOTIFY timestampChanged)
    Q_PROPERTY(bool pinned READ pinned WRITE setPinned NOTIFY pinnedChanged)
    Q_PROPERTY(QString colorHex READ colorHex NOTIFY colorHexChanged)

public:
    explicit ClipboardItem(QObject* parent = nullptr);
    ClipboardItem(const QString& id, ClipboardType type, const QString& content,
                  const QDateTime& time = QDateTime::currentDateTime(), bool pinned = false,
                  QObject* parent = nullptr);

    QString id() const { return m_id; }
    void setId(const QString& id) { m_id = id; }

    ClipboardType type() const { return m_type; }
    int typeInt() const { return static_cast<int>(m_type); }
    QString typeName() const;
    void setType(ClipboardType type);

    QString content() const { return m_content; }
    void setContent(const QString& c);

    QString previewText() const { return m_previewText; }
    void setPreviewText(const QString& pt);
    QString previewLine1() const {
        if (m_previewText.isEmpty()) return QString();
        int nl = m_previewText.indexOf(QLatin1Char('\n'));
        return nl >= 0 ? m_previewText.left(nl).trimmed() : m_previewText;
    }
    QString previewLine2() const {
        int nl = m_previewText.indexOf(QLatin1Char('\n'));
        if (nl < 0 || nl + 1 >= m_previewText.size()) return QString();
        return m_previewText.mid(nl + 1).trimmed().left(200);
    }

    QString imagePath() const { return m_imagePath; }
    void setImagePath(const QString& p);

    int imageWidth() const { return m_imageWidth; }
    void setImageWidth(int w) { m_imageWidth = w; }

    int imageHeight() const { return m_imageHeight; }
    void setImageHeight(int h) { m_imageHeight = h; }

    qint64 byteSize() const { return m_byteSize; }
    void setByteSize(qint64 s) { m_byteSize = s; emit byteSizeChanged(); }

    int lineCount() const { return m_lineCount; }
    int charCount() const { return m_charCount; }

    QDateTime timestamp() const { return m_timestamp; }
    void setTimestamp(const QDateTime& dt);
    QString timeAgo() const;

    bool pinned() const { return m_pinned; }
    void setPinned(bool p);

    QString colorHex() const { return m_colorHex; }
    void setColorHex(const QString& hex);

    QJsonObject toJson() const;
    static ClipboardItem* fromJson(const QJsonObject& obj, QObject* parent = nullptr);

signals:
    void typeChanged();
    void contentChanged();
    void previewTextChanged();
    void imagePathChanged();
    void byteSizeChanged();
    void timestampChanged();
    void pinnedChanged();
    void colorHexChanged();

private:
    QString m_id;
    ClipboardType m_type = ClipboardType::Text;
    QString m_content;
    QString m_previewText;
    QString m_imagePath;
    int m_imageWidth = 0;
    int m_imageHeight = 0;
    qint64 m_byteSize = 0;
    int m_lineCount = 1;
    int m_charCount = 0;
    QDateTime m_timestamp;
    bool m_pinned = false;
    QString m_colorHex;

    void updateDerivedFields();
};

} // namespace stowaway::core
