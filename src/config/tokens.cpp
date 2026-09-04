#include "tokens.hpp"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QPointF>
#include <QTimer>

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

void SizeTokens::loadJson(const QJsonObject& json) {
    if (json.contains("stowaway")) {
        auto st = json["stowaway"].toObject();
        if (st.contains("width")) m_stowaway->set_width(st["width"].toInt(m_stowaway->width()));
        if (st.contains("height")) m_stowaway->set_height(st["height"].toInt(m_stowaway->height()));
    } else if (json.contains("clipboard")) {
        auto cb = json["clipboard"].toObject();
        if (cb.contains("width")) m_stowaway->set_width(cb["width"].toInt(m_stowaway->width()));
        if (cb.contains("height")) m_stowaway->set_height(cb["height"].toInt(m_stowaway->height()));
    }
}

TokensSingleton::TokensSingleton(QObject* parent)
    : QObject(parent)
    , m_rounding(new RoundingTokens(this))
    , m_spacing(new SpacingTokens(this))
    , m_padding(new PaddingTokens(this))
    , m_anim(new AnimCurves(this))
    , m_font(new FontTokens(this))
    , m_sizes(new SizeTokens(this)) {
    reload();

    QString home = QDir::homePath();
    QString configDir = home + "/.config/caelestia";
    QString tokensFile = configDir + "/shell-tokens.json";
    QString shellFile = configDir + "/shell.json";

    if (QFile::exists(tokensFile)) m_watcher.addPath(tokensFile);
    if (QFile::exists(shellFile)) m_watcher.addPath(shellFile);

    auto onConfigChange = [this, configDir, tokensFile, shellFile]() {
        QTimer::singleShot(20, this, [this, configDir, tokensFile, shellFile]() {
            if (QFile::exists(tokensFile) && !m_watcher.files().contains(tokensFile)) {
                m_watcher.addPath(tokensFile);
            }
            if (QFile::exists(shellFile) && !m_watcher.files().contains(shellFile)) {
                m_watcher.addPath(shellFile);
            }
            reload();
        });
    };

    connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, onConfigChange);
    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this, onConfigChange);
}

TokensSingleton* TokensSingleton::instance() {
    static TokensSingleton inst;
    return &inst;
}

void TokensSingleton::reload() {
    QString home = QDir::homePath();
    QString tokensFile = home + "/.config/caelestia/shell-tokens.json";
    QString shellFile = home + "/.config/caelestia/shell.json";
    QString legacyTokens = home + "/.local/state/caelestia/tokens.json";

    if (QFile::exists(tokensFile)) {
        loadTokensFile(tokensFile);
    } else if (QFile::exists(legacyTokens)) {
        loadTokensFile(legacyTokens);
    }
    if (QFile::exists(shellFile)) {
        loadShellConfigFile(shellFile);
    }
}

void TokensSingleton::loadTokensFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return;

    auto doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject()) return;

    auto obj = doc.object();
    if (obj.contains("appearance")) {
        auto app = obj["appearance"].toObject();
        if (app.contains("rounding")) m_rounding->loadJson(app["rounding"].toObject());
        if (app.contains("spacing")) m_spacing->loadJson(app["spacing"].toObject());
        if (app.contains("padding")) m_padding->loadJson(app["padding"].toObject());
        if (app.contains("animDurations")) m_anim->durations()->loadJson(app["animDurations"].toObject());
        if (app.contains("curves")) m_anim->loadJson(app["curves"].toObject());
    } else {
        if (obj.contains("rounding")) m_rounding->loadJson(obj.value("rounding").toObject());
        if (obj.contains("spacing")) m_spacing->loadJson(obj.value("spacing").toObject());
        if (obj.contains("padding")) m_padding->loadJson(obj.value("padding").toObject());
        if (obj.contains("anim")) m_anim->loadJson(obj.value("anim").toObject());
    }

    if (obj.contains("sizes")) {
        m_sizes->loadJson(obj.value("sizes").toObject());
    }
}

void TokensSingleton::loadShellConfigFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return;

    auto doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject()) return;

    auto root = doc.object();
    if (root.contains("appearance")) {
        auto app = root["appearance"].toObject();
        if (app.contains("rounding")) {
            auto r = app["rounding"].toObject();
            if (r.contains("scale")) m_rounding->setScale(r["scale"].toDouble(1.0));
        }
        if (app.contains("spacing")) {
            auto s = app["spacing"].toObject();
            if (s.contains("scale")) m_spacing->setScale(s["scale"].toDouble(1.0));
        }
        if (app.contains("padding")) {
            auto p = app["padding"].toObject();
            if (p.contains("scale")) m_padding->setScale(p["scale"].toDouble(1.0));
        }
    }

    if (root.contains("stowaway")) {
        auto st = root["stowaway"].toObject();
        if (st.contains("width")) m_sizes->stowaway()->set_width(st["width"].toInt(m_sizes->stowaway()->width()));
        if (st.contains("height")) m_sizes->stowaway()->set_height(st["height"].toInt(m_sizes->stowaway()->height()));
    }
}

} // namespace stowaway::config
