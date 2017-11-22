#include "Dashboard.h"
#include <QPen>
#include <QBrush>
#include <QtMath>
#include <QDebug>

const int PEN_WIDTH = 3;
const int DIVISOR_LENGTH = 16;
const int PRECISION_LENGTH = DIVISOR_LENGTH / 2;
const int NUMBER_TO_RING_DISTANCE = 30;

class PainterUser {
public:
    PainterUser(QPainter *painter) : mPainter(painter) {
        mPainter->save();
    }
    ~PainterUser() {
        mPainter->restore();
    }
private:
    Q_DISABLE_COPY(PainterUser)
    QPainter *mPainter;
};
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
    PainterUser paintUser(painter);

    painter->setPen(mPen);
    painter->setBrush(mBrush);
    painter->setRenderHint(QPainter::Antialiasing, true);
    //半径
    const qreal radius = width() / 2.0 - PEN_WIDTH;
    //圆心
    const qreal cx = width() / 2.0;
    const qreal cy = height() / 2.0;

    //画圆弧
    painter->drawArc(PEN_WIDTH, PEN_WIDTH,
                     width() - PEN_WIDTH, height() - PEN_WIDTH,
                     startAngle() * 16 , spanAngle() * 16);
    //每个区间的张角
    qreal divisorAngle = spanAngle() / divisor();
    //区间小格的张角
    qreal precisionAngle = divisorAngle / precision();
    //总共要分成小格数
    int gap = divisor() * precision();
    int gapNumber = (int)fabs(maxValue() - minValue()) / divisor();
    for (int i = 0; i <= gap; ++i) {
        auto angle = qDegreesToRadians(startAngle() + i * precisionAngle);
        auto divisorStartX = cx + radius * cos(angle);
        auto divisorStartY = cy - radius * sin(angle);
        auto divisorEndX = 0;
        auto divisorEndY = 0;
        if (0 == i % precision()) {
            divisorEndX = cx + (radius - DIVISOR_LENGTH) * cos(angle);
            divisorEndY = cy - (radius - DIVISOR_LENGTH) * sin(angle);

            auto numberX = cx + (radius - NUMBER_TO_RING_DISTANCE) * cos(angle);
            auto numberY = cy - (radius - NUMBER_TO_RING_DISTANCE) * sin(angle);
            auto number = QString("%1").arg(i / precision() * gapNumber + minValue());
            //cos值符号为正，即角度在-90至90度这个区间，文字应该左偏移
            if (!qFuzzyCompare(angle, 0) &&  0 == signbit(cos(angle))) {
                numberX -= number.length() * 8;
            }
            painter->drawLine(divisorStartX, divisorStartY, divisorEndX, divisorEndY);
            painter->drawText(numberX, numberY, number);
        } else {
            divisorEndX = cx + (radius - PRECISION_LENGTH) * cos(angle);
            divisorEndY = cy - (radius - PRECISION_LENGTH) * sin(angle);
            painter->drawLine(divisorStartX, divisorStartY, divisorEndX, divisorEndY);
        }
    }
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

