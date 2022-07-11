#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void closeApplication();
    void updateLcdNumberAmplitude(int amplitude_);
    void updateLcdNumberFrequency(int frequency_);
    void updateLcdNumberSpeed(int speed_);
    void bindPlotterWidget();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
