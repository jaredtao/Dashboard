#include "Dashboard.h"
#include <QPen>
#include <QBrush>
#include <QtMath>
const int PEN_WIDTH = 3;
const int DIVISOR_LENGTH = 10;
const int PRECISION_LENGTH = DIVISOR_LENGTH / 2;
Dashboard::Dashboard(QQuickPaintedItem *parent) : QQuickPaintedItem(parent) {
    connect(&mTimer, &QTimer::timeout, this, &Dashboard::timeoutSlot);
    mTimer.start(1000 / 60);
    mPen.setColor(QColor("red"));
    mPen.setWidth(PEN_WIDTH);
    mBrush.setColor(QColor("blue"));
}

void Dashboard::timeoutSlot() {
    update();
}

void Dashboard::paint(QPainter *painter) {
    painter->save();

    painter->setPen(mPen);
    painter->setBrush(mBrush);
    painter->setRenderHint(QPainter::Antialiasing, true);
    //半径
    const qreal radius = width() / 2.0 - PEN_WIDTH;
    //圆心
    const qreal cx = width() / 2.0;
    const qreal cy = height() / 2.0;

    painter->drawArc(PEN_WIDTH, PEN_WIDTH,
                     width() - PEN_WIDTH, height() - PEN_WIDTH,
                     startAngle() * 16 , spanAngle() * 16);
    //每个区间的张角
    qreal divisorAngle = spanAngle() / divisor();
    //区间小格的张角
    qreal precisionAngle = divisorAngle / precision();
    //总共要分成小格数
    int gap = divisor() * precision();
    for (int i = 0; i <= gap; ++i) {
        auto angle = qDegreesToRadians(startAngle() + i * precisionAngle);
        auto divisorStartX = cx + radius * sin(angle);
        auto divisorStartY = cy + radius * cos(angle);
        auto divisorEndX = 0;
        auto divisorEndY = 0;
        if (0 == i % precision()) {
            divisorEndX = cx + (radius - DIVISOR_LENGTH) * sin(angle);
            divisorEndY = cy + (radius - DIVISOR_LENGTH) * cos(angle);
        } else {
            divisorEndX = cx + (radius - PRECISION_LENGTH) * sin(angle);
            divisorEndY = cy + (radius - PRECISION_LENGTH) * cos(angle);
        }
        painter->drawLine(divisorStartX, divisorStartY, divisorEndX, divisorEndY);
    }

    painter->restore();
}

qreal Dashboard::startAngle() const {
    return mStartAngle;
}

qreal Dashboard::spanAngle() const {
    return mSpanAngle;
}

qreal Dashboard::minValue() const {
    return mMinValue;
}

qreal Dashboard::maxValue() const {
    return mMaxValue;
}

qreal Dashboard::value() const {
    return mValue;
}

int Dashboard::divisor() const {
    return mDivisor;
}

int Dashboard::precision() const {
    return mPrecision;
}

bool Dashboard::divisorSplit() const {
    return mDivisorSplit;
}

void Dashboard::setStartAngle(qreal startAngle) {
    if (qFuzzyCompare(mStartAngle, startAngle))
        return;

    mStartAngle = startAngle;
    emit startAngleChanged(mStartAngle);
}

void Dashboard::setSpanAngle(qreal spanAngle) {
    if (qFuzzyCompare(mSpanAngle, spanAngle))
        return;

    mSpanAngle = spanAngle;
    emit spanAngleChanged(mSpanAngle);
}

void Dashboard::setMinValue(qreal minValue) {
    if (qFuzzyCompare(mMinValue, minValue))
        return;

    mMinValue = minValue;
    emit minValueChanged(mMinValue);
}

void Dashboard::setMaxValue(qreal maxValue) {
    if (qFuzzyCompare(mMaxValue, maxValue))
        return;

    mMaxValue = maxValue;
    emit maxValueChanged(mMaxValue);
}

void Dashboard::setValue(qreal value) {
    if (qFuzzyCompare(mValue, value))
        return;

    mValue = value;
    emit valueChanged(mValue);
}

void Dashboard::setDivisor(int divisor) {
    if (mDivisor == divisor)
        return;

    mDivisor = divisor;
    emit divisorChanged(mDivisor);
}

void Dashboard::setPrecision(int precision) {
    if (mPrecision == precision)
        return;

    mPrecision = precision;
    emit precisionChanged(mPrecision);
}

void Dashboard::setDivisorSplit(bool divisorSplit) {
    if (mDivisorSplit == divisorSplit)
        return;

    mDivisorSplit = divisorSplit;
    emit divisorSplitChanged(mDivisorSplit);
}

