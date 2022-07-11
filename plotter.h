#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QPen>

class Plotter : public QWidget
{
    Q_OBJECT
private:
    float amplitude, frequency, speed, angle;
    bool showSin, showCos, showTan;
    QBrush brush;
    QPen pen;
public:
    explicit Plotter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
signals:

public slots:
    void setAmplitude(int amplitude_);
    void setFrequency(int frequency_);
    void setSpeed(int speed_);
    
    void updateCurveTypeToSine();
    void updateCurveTypeToCos();
    void updateCurveTypeToTan();
   
    void printActiveCurves(QPainter *painter);
    void drawTrigonometricFunction(QPainter *painter, QColor color, int curveType);
    
    double functionResult(double x, int curveType);
};

#endif // PLOTTER_H
