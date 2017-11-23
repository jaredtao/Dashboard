#include "Ringboard.h"
#include <QtMath>
#include <QtGlobal>
#include <QRadialGradient>

Ringboard::Ringboard() {
    connect(&mTimer, &QTimer::timeout, this, &Ringboard::timeoutSlot);
    mTimer.start(1000 / 60);
    //红橙黄绿青蓝紫
    mColors << QColor(255,   0, 0)
            << QColor(255, 125, 0)
            << QColor(255, 255, 0)
            << QColor(  0, 255, 0)
            << QColor(  0,   0, 255)
            << QColor(  0, 255, 255)
            << QColor(255,   0, 255);
}

void Ringboard::paint(QPainter *painter) {
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);

    const qreal cx = width() / 2.0;
    const qreal cy = height() / 2.0;
    QPainterPath path;
    //起点
    path.arcMoveTo(cx - radiusOuter(), cy - radiusOuter(),
                   radiusOuter() * 2, radiusOuter() * 2,
                   startAngle());
    //画外圆弧
    path.arcTo(cx - radiusOuter(), cy - radiusOuter(),
               radiusOuter() * 2, radiusOuter() * 2,
               startAngle(), spanAngle() );
    if (roundConer()) {
        //外弧到内弧的圆角
        auto radius = (radiusOuter() - radiusInner()) / 2;
        auto rx = cx + (radiusInner() + radius) * cos(qDegreesToRadians(startAngle() + spanAngle()));
        auto ry = cy - (radiusInner() + radius) * sin(qDegreesToRadians(startAngle() + spanAngle()));
        path.arcTo(rx - radius, ry - radius,
                   radius * 2, radius * 2,
                   startAngle() + spanAngle(), -180);
    }
    //内弧，方向与外弧相反
    path.arcTo(cx - radiusInner(), cy - radiusInner(),
               radiusInner() * 2, radiusInner() * 2,
               startAngle() + spanAngle(), - spanAngle());
    //闭合path
    path.closeSubpath();

    //    QBrush brush;
    //    brush.setColor(Qt::green);
    //    brush.setStyle(Qt::SolidPattern);

    QRadialGradient gradiant;
    gradiant.setCenter(cx, cy);
    gradiant.setCenterRadius(radiusInner());
    gradiant.setRadius(radiusOuter());
    gradiant.setFocalPoint(cx, cy);
    qreal len = radiusOuter() - radiusInner();
    int colorCount = mColors.count();
    qreal percentStep = (len / radiusOuter()) / colorCount;
    for (int i = 0; i < colorCount; ++i) {
        gradiant.setColorAt(1.0 - i * percentStep, mColors.at(i));
    }
    QBrush brush(gradiant);
    painter->fillPath(path, brush);
    painter->restore();
}

qreal Ringboard::startAngle() const {
    return mStartAngle;
}

qreal Ringboard::spanAngle() const {
    return mSpanAngle;
}

qreal Ringboard::radiusInner() const {
    return mRadiusInner;
}

qreal Ringboard::radiusOuter() const {
    return mRadiusOuter;
}

bool Ringboard::roundConer() const {
    return mRoundConer;
}

void Ringboard::timeoutSlot() {
    update();
}

void Ringboard::setStartAngle(qreal startAngle) {
    if (qFuzzyCompare(mStartAngle, startAngle))
        return;

    mStartAngle = startAngle;
    emit startAngleChanged(mStartAngle);
}

void Ringboard::setSpanAngle(qreal spanAngle) {
    if (qFuzzyCompare(mSpanAngle, spanAngle))
        return;

    mSpanAngle = spanAngle;
    emit spanAngleChanged(mSpanAngle);
}

void Ringboard::setRadiusInner(qreal radiusInner) {
    if (qFuzzyCompare(mRadiusInner, radiusInner))
        return;

    mRadiusInner = radiusInner;
    emit radiusInnerChanged(mRadiusInner);
}

void Ringboard::setRadiusOuter(qreal radiusOuter) {
    if (qFuzzyCompare(mRadiusOuter, radiusOuter))
        return;

    mRadiusOuter = radiusOuter;
    emit radiusOuterChanged(mRadiusOuter);
}

void Ringboard::setRoundConer(bool roundConer) {
    if (mRoundConer == roundConer)
        return;

    mRoundConer = roundConer;
    emit roundConerChanged(mRoundConer);
}