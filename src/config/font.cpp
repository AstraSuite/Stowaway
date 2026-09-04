#include "font.hpp"
#include <QFontDatabase>

namespace stowaway::config {

FontBuilders::FontBuilders(const FontStyleBase* style, QObject* parent)
    : QObject(parent)
    , m_style(style) {}

FontBuilder FontBuilders::extraLarge() const {
    return FontBuilder(m_style->extraLarge());
}

FontBuilder FontBuilders::large() const {
    return FontBuilder(m_style->large());
}

FontBuilder FontBuilders::medium() const {
    return FontBuilder(m_style->medium());
}

FontBuilder FontBuilders::small() const {
    return FontBuilder(m_style->small());
}

FontStyleBase::FontStyleBase(const QString& family, int smallSize, int mediumSize, int largeSize, int extraLargeSize,
                             QFont::Weight defaultWeight, QObject* parent)
    : QObject(parent)
    , m_family(family)
    , m_smallSize(smallSize)
    , m_mediumSize(mediumSize)
    , m_largeSize(largeSize)
    , m_extraLargeSize(extraLargeSize)
    , m_defaultWeight(defaultWeight)
    , m_builders(new FontBuilders(this, this)) {
    rebuild();
}

void FontStyleBase::setFamily(const QString& family) {
    if (m_family != family) {
        m_family = family;
        rebuild();
    }
}

void FontStyleBase::setScale(qreal scale) {
    if (!qFuzzyCompare(m_scale, scale)) {
        m_scale = scale;
        rebuild();
    }
}

void FontStyleBase::setSizes(int smallSize, int mediumSize, int largeSize, int extraLargeSize) {
    m_smallSize = smallSize;
    m_mediumSize = mediumSize;
    m_largeSize = largeSize;
    m_extraLargeSize = extraLargeSize;
    rebuild();
}

QFont FontStyleBase::makeFont(int baseSize, QFont::Weight weight) {
    QFont font(m_family);
    font.setPointSize(static_cast<int>(baseSize * m_scale));
    font.setWeight(weight);
    return font;
}

void FontStyleBase::rebuild() {
    m_small = makeFont(m_smallSize, m_defaultWeight);
    m_medium = makeFont(m_mediumSize, m_defaultWeight);
    m_large = makeFont(m_largeSize, m_defaultWeight);
    m_extraLarge = makeFont(m_extraLargeSize, m_defaultWeight);
    emit fontsChanged();
    emit m_builders->buildersChanged();
}

IconFontStyle::IconFontStyle(const QString& family, QObject* parent)
    : FontStyleBase(family, 16, 20, 24, 32, QFont::Normal, parent) {}

FontBuilder IconFontStyle::size(int pointSize) {
    return FontBuilder(makeFont(pointSize, m_defaultWeight));
}

FontTokens::FontTokens(QObject* parent)
    : QObject(parent) {
    QString regularFamily = QStringLiteral("Google Sans Flex");
    QString monoFamily = QStringLiteral("monospace");
    QString iconFamily = QStringLiteral("Material Symbols Rounded");

    m_headline = new FontStyle(regularFamily, 24, 28, 32, 36, QFont::Bold, this);
    m_title = new FontStyle(regularFamily, 14, 16, 18, 22, QFont::DemiBold, this);
    m_body = new FontStyle(regularFamily, 11, 13, 15, 17, QFont::Normal, this);
    m_label = new FontStyle(regularFamily, 10, 11, 12, 14, QFont::Medium, this);
    m_mono = new FontStyle(monoFamily, 10, 11, 13, 15, QFont::Normal, this);
    m_icon = new IconFontStyle(iconFamily, this);
}

void FontTokens::setFamily(const QString& family) {
    m_headline->setFamily(family);
    m_title->setFamily(family);
    m_body->setFamily(family);
    m_label->setFamily(family);
}

void FontTokens::setIconFamily(const QString& family) {
    m_icon->setFamily(family);
}

void FontTokens::setScale(qreal scale) {
    m_headline->setScale(scale);
    m_title->setScale(scale);
    m_body->setScale(scale);
    m_label->setScale(scale);
    m_mono->setScale(scale);
    m_icon->setScale(scale);
}

} // namespace stowaway::config
