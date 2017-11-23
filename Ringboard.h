#pragma once

#include <QTimer>
#include <QObject>
#include <QPainter>
#include <QQuickPaintedItem>
class Ringboard : public QQuickPaintedItem {
    Q_OBJECT

    //起始角度。3点钟方向为0度，正数表示逆时针方向的角度，负数表示顺时针方向的角度
    Q_PROPERTY(qreal startAngle READ startAngle WRITE setStartAngle NOTIFY startAngleChanged)
    //张角 起始角度+张角=终止角度。3点钟方向为0度，正数表示逆时针方向的角度，负数表示顺时针方向的角度
    Q_PROPERTY(qreal spanAngle READ spanAngle WRITE setSpanAngle NOTIFY spanAngleChanged)

    //内半径
    Q_PROPERTY(qreal radiusInner READ radiusInner WRITE setRadiusInner NOTIFY radiusInnerChanged)
    //外半径
    Q_PROPERTY(qreal radiusOuter READ radiusOuter WRITE setRadiusOuter NOTIFY radiusOuterChanged)
    //是否使用圆角
    Q_PROPERTY(bool roundConer READ roundConer WRITE setRoundConer NOTIFY roundConerChanged)

    Q_PROPERTY(Gradient gradient READ gradient WRITE setGradient NOTIFY gradientChanged)
public:
    enum Gradient {
        NoGradient = 0,
        RadialGradiant,
        ConicalGradiant
    };
    Q_ENUMS(Gradient)

    Ringboard();

    void paint(QPainter *painter) override;

    qreal startAngle() const;

    qreal spanAngle() const;

    qreal radiusInner() const;

    qreal radiusOuter() const;

    bool roundConer() const;

    Gradient gradient() const;

public slots:
    void timeoutSlot();

    void setStartAngle(qreal startAngle);

    void setSpanAngle(qreal spanAngle);

    void setRadiusInner(qreal radiusInner);

    void setRadiusOuter(qreal radiusOuter);

    void setRoundConer(bool roundConer);

    void setGradient(Gradient gradient);

signals:
    void startAngleChanged(qreal startAngle);

    void spanAngleChanged(qreal spanAngle);

    void radiusInnerChanged(qreal radiusInner);

    void radiusOuterChanged(qreal radiusOuter);

    void roundConerChanged(bool roundConer);

    void gradientChanged(Gradient gradient);

private:
    QTimer mTimer;
    qreal mStartAngle;
    qreal mSpanAngle;
    qreal mRadiusInner;
    qreal mRadiusOuter;
    bool mRoundConer = false;
    QList<QColor> mColors;
    Gradient mGradient = NoGradient;
};

