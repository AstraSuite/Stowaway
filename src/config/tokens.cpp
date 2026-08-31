#include "tokens.hpp"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QPointF>

namespace stowaway::config {

QEasingCurve AnimCurves::makeBezier(qreal p1x, qreal p1y, qreal p2x, qreal p2y) {
    QEasingCurve curve(QEasingCurve::BezierSpline);
    curve.addCubicBezierSegment(QPointF(p1x, p1y), QPointF(p2x, p2y), QPointF(1.0, 1.0));
    return curve;
}

AnimCurves::AnimCurves(QObject* parent)
    : QObject(parent)
    , m_durations(new AnimDurationTokens(this))
    , m_emphasized(makeBezier(0.05, 0.7, 0.1, 1.0))
    , m_emphasizedAccel(makeBezier(0.3, 0.0, 0.8, 0.15))
    , m_emphasizedDecel(makeBezier(0.05, 0.7, 0.1, 1.0))
    , m_standard(makeBezier(0.2, 0.0, 0.0, 1.0))
    , m_standardAccel(makeBezier(0.3, 0.0, 1.0, 1.0))
    , m_standardDecel(makeBezier(0.0, 0.0, 0.0, 1.0))
    , m_expressiveFastSpatial(makeBezier(0.25, 0.1, 0.25, 1.0))
    , m_expressiveDefaultSpatial(makeBezier(0.2, 0.0, 0.0, 1.0))
    , m_expressiveSlowSpatial(makeBezier(0.2, 0.0, 0.0, 1.0))
    , m_expressiveFastEffects(makeBezier(0.4, 0.0, 0.2, 1.0))
    , m_expressiveDefaultEffects(makeBezier(0.4, 0.0, 0.2, 1.0))
    , m_expressiveSlowEffects(makeBezier(0.4, 0.0, 0.2, 1.0)) {}

void RoundingTokens::loadJson(const QJsonObject& json) {
    if (json.contains("scale")) m_scale = json.value("scale").toDouble(1.0);
    emit valuesChanged();
}

void SpacingTokens::loadJson(const QJsonObject& json) {
    if (json.contains("scale")) m_scale = json.value("scale").toDouble(1.0);
    emit valuesChanged();
}

void PaddingTokens::loadJson(const QJsonObject& json) {
    if (json.contains("scale")) m_scale = json.value("scale").toDouble(1.0);
    emit valuesChanged();
}

void AnimDurationTokens::loadJson(const QJsonObject& json) {
    if (json.contains("scale")) m_scale = json.value("scale").toDouble(1.0);
    emit valuesChanged();
}

void AnimCurves::loadJson(const QJsonObject& json) {
    if (json.contains("durations")) {
        m_durations->loadJson(json.value("durations").toObject());
    }
    emit curvesChanged();
}

TokensSingleton::TokensSingleton(QObject* parent)
    : QObject(parent)
    , m_rounding(new RoundingTokens(this))
    , m_spacing(new SpacingTokens(this))
    , m_padding(new PaddingTokens(this))
    , m_anim(new AnimCurves(this))
    , m_font(new FontTokens(this)) {
    reload();
}

TokensSingleton* TokensSingleton::instance() {
    static TokensSingleton inst;
    return &inst;
}

void TokensSingleton::reload() {
    QString home = QDir::homePath();
    QString tokensPath = home + "/.local/state/caelestia/tokens.json";
    if (QFile::exists(tokensPath)) {
        loadTokensFile(tokensPath);
    }
}

void TokensSingleton::loadTokensFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return;

    auto doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject()) return;

    auto obj = doc.object();
    if (obj.contains("rounding")) m_rounding->loadJson(obj.value("rounding").toObject());
    if (obj.contains("spacing")) m_spacing->loadJson(obj.value("spacing").toObject());
    if (obj.contains("padding")) m_padding->loadJson(obj.value("padding").toObject());
    if (obj.contains("anim")) m_anim->loadJson(obj.value("anim").toObject());
}

} // namespace stowaway::config
