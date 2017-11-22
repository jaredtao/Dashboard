#pragma once
#include <QObject>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QTimer>
class Dashboard : public QQuickPaintedItem {
    Q_OBJECT
    //起始角度。3点钟方向为0度，正数表示逆时针方向的角度，负数表示顺时针方向的角度
    Q_PROPERTY(qreal startAngle READ startAngle WRITE setStartAngle NOTIFY startAngleChanged)
    //张角 起始角度+张角=终止角度。3点钟方向为0度，正数表示逆时针方向的角度，负数表示顺时针方向的角度
    Q_PROPERTY(qreal spanAngle READ spanAngle WRITE setSpanAngle NOTIFY spanAngleChanged)
    //表示的最小刻度数值
    Q_PROPERTY(qreal minValue READ minValue WRITE setMinValue NOTIFY minValueChanged)
    //表示的最大刻度数值
    Q_PROPERTY(qreal maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged)
    //当前刻度值
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged)
    //张角等分成多少个区间
    Q_PROPERTY(int divisor READ divisor WRITE setDivisor NOTIFY divisorChanged)
    //每个区间再细分成多少小格
    Q_PROPERTY(int precision READ precision WRITE setPrecision NOTIFY precisionChanged)
    //区间中间是否需要中分线。precision必须为偶数时此变量为true才生效。因为奇数个区间是不能画中分线的。
    Q_PROPERTY(bool divisorSplit READ divisorSplit WRITE setDivisorSplit NOTIFY divisorSplitChanged)
public:
    Dashboard(QQuickPaintedItem *parent = nullptr);

    void paint(QPainter *painter) override;

    qreal startAngle() const;

    qreal spanAngle() const;

    qreal minValue() const;

    qreal maxValue() const;

    qreal value() const;

    int divisor() const;

    int precision() const;

    bool divisorSplit() const;

public slots:
    void timeoutSlot();

    void setStartAngle(qreal startAngle);

    void setSpanAngle(qreal spanAngle);

    void setMinValue(qreal minValue);

    void setMaxValue(qreal maxValue);

    void setValue(qreal value);

    void setDivisor(int divisor);

    void setPrecision(int precision);

    void setDivisorSplit(bool divisorSplit);

signals:
    void startAngleChanged(qreal startAngle);

    void spanAngleChanged(qreal spanAngle);

    void minValueChanged(qreal minValue);

    void maxValueChanged(qreal maxValue);

    void valueChanged(qreal value);

    void divisorChanged(int divisor);

    void precisionChanged(int precision);

    void divisorSplitChanged(bool divisorSplit);

private:
    QTimer mTimer;
    QPen mPen;
    QBrush mBrush;

    qreal mStartAngle = 0.0f;
    qreal mSpanAngle = 0.0f;
    qreal mMinValue = 0.0f;
    qreal mMaxValue = 0.0f;
    qreal mValue = 0.0f;
    int mDivisor = 0;
    int mPrecision = 0;
    bool mDivisorSplit = false;
};
