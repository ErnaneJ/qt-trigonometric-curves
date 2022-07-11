#include "plotter.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <cmath>
#include <QString>
#include <QMainWindow>

#define PI 3.1415

Plotter::Plotter(QWidget *parent) : QWidget{parent} {
    frequency = 1; amplitude = 0.5;
    angle = 0; speed = 0.01;
    startTimer(100); // 100 ms
    showSin = showCos = showTan = false;
}

void Plotter::timerEvent(QTimerEvent *event){
    if(showSin == false && showCos == false && showTan == false) return;
    angle = angle + speed;
    if(angle >= 2*PI){ angle = 0; }
    repaint();
}

void Plotter::paintEvent(QPaintEvent *event){
   QPainter painter(this);
   brush.setColor(QColor(47, 52, 56));
   brush.setStyle(Qt::SolidPattern);

   pen.setWidth(2);

   painter.setBrush(brush);
   painter.setPen(pen);
   painter.drawRect(0, 0,width(), height());

   // Line center
   painter.setPen(QPen(QColor(255,255,255, 60), 2, Qt::DashLine, Qt::RoundCap));

   painter.drawLine(0, height()/2, width(), height()/2);
   painter.drawLine(2, 0, 2, height());

   pen.setColor(QColor(255, 255, 255));
   painter.setPen(pen);

   drawTrigonometricFunction(&painter, QColor(249, 246, 11), 0); // sin
   drawTrigonometricFunction(&painter, QColor(228, 33, 49), 1); // cos
   drawTrigonometricFunction(&painter, QColor(41, 153, 203), 2); // tan

   printActiveCurves(&painter);

   pen.setColor(QColor(255, 255, 255));
   painter.setPen(pen);

   painter.drawText(QRect(10, height()-60, width(), 50), 0,
    QString("\n ● Angle: ")+QString::number((float)angle, 'f', 2)+QString(" rad")+
    QString("          ● Speed: ")+QString::number((float)speed, 'f', 2)+QString(" rad/s\n")+
    QString(" ● Frequency: ")+QString::number((float)frequency, 'f', 2)+QString(" Hz")+
    QString("   ● Amplitude: ")+QString::number((float)amplitude, 'f', 2)
   );
}

void Plotter::drawTrigonometricFunction(QPainter *painter, QColor color, int curveType){
    if(curveType == 0 && showSin == false) return;
    if(curveType == 1 && showCos == false) return;
    if(curveType == 2 && showTan == false) return;

    int x1, x2, y1, y2;
    pen.setColor(color);
    painter -> setPen(pen);

    x1 = 0;
    y1 = height()/2;
    for(int i=1; i< width(); i++){
        x2 = i;
        y2 = (height()/2) * (1 - amplitude * functionResult(x2, curveType));
        painter -> drawLine(x1, y1, x2, y2);
        x1 = x2;
        y1 = y2;
    }
}

void Plotter::printActiveCurves(QPainter *painter){
    int added = 2;
    if(showSin){
        pen.setColor(QColor(249, 246, 11));
        painter -> setPen(pen);
        painter -> drawText(QRect(10, height() - 120 + 20 * added, width(), 50), 0, QString("\n ● Sine"));
        added--;
    }
    if(showCos){
        pen.setColor(QColor(228, 33, 49));
        painter -> setPen(pen);
        painter -> drawText(QRect(10, height() - 120 + 20 * added, width(), 50), 0, QString("\n ● Cosine"));
        added--;
    };
    if(showTan){
        pen.setColor(QColor(41, 153, 203));
        painter -> setPen(pen);
        painter -> drawText(QRect(10, height() - 120 + 20 * added, width(), 50), 0, QString("\n ● Tangent"));
        added--;
    };
}

void Plotter::setAmplitude(int amplitude_){ amplitude = (float)amplitude_/100.0; repaint(); }
void Plotter::setFrequency(int frequency_){ frequency = (float)frequency_; repaint(); }
void Plotter::setSpeed(int speed_){ speed = (float)speed_/100.0; repaint();}

void Plotter::updateCurveTypeToSine(){ showSin = !showSin; repaint(); }
void Plotter::updateCurveTypeToCos(){ showCos = !showCos; repaint(); }
void Plotter::updateCurveTypeToTan(){ showTan = !showTan; repaint(); }
double Plotter::functionResult(double x, int curveType){
    if(curveType == 0){ return std::sin(2 * PI * frequency * x/width()+angle); } //sin
    if(curveType == 1){ return std::cos(2 * PI * frequency * x/width()+angle); } //cos
    if(curveType == 2){ return std::tan(2 * PI * frequency * x/width()+angle); } //tg
    return 0;
}
