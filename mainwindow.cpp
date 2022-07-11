#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    connect(ui -> actionQuit, SIGNAL(triggered()), this, SLOT(closeApplication()));

    connect(ui->horizontalSliderAmplitude, SIGNAL(valueChanged(int)), ui -> plotterWidget, SLOT(setAmplitude(int)));
    connect(ui->horizontalSliderAmplitude, SIGNAL(valueChanged(int)), this, SLOT(updateLcdNumberAmplitude(int)));

    connect(ui->horizontalSliderFrequency, SIGNAL(valueChanged(int)), ui -> plotterWidget, SLOT(setFrequency(int)));
    connect(ui->horizontalSliderFrequency, SIGNAL(valueChanged(int)), this, SLOT(updateLcdNumberFrequency(int)));

    connect(ui->horizontalSliderSpeed, SIGNAL(valueChanged(int)), ui -> plotterWidget, SLOT(setSpeed(int)));
    connect(ui->horizontalSliderSpeed, SIGNAL(valueChanged(int)), this, SLOT(updateLcdNumberSpeed(int)));

    connect(ui->actionSin, SIGNAL(triggered()), ui -> plotterWidget, SLOT(updateCurveTypeToSine()));
    connect(ui->actionCos, SIGNAL(triggered()), ui -> plotterWidget, SLOT(updateCurveTypeToCos()));
    connect(ui->actionTan, SIGNAL(triggered()), ui -> plotterWidget, SLOT(updateCurveTypeToTan()));
}

MainWindow::~MainWindow(){ delete ui; }

void MainWindow::closeApplication(){ exit(0); }
void MainWindow::updateLcdNumberAmplitude(int amplitude_){ ui -> lcdNumberAmplitude -> display(amplitude_); }
void MainWindow::updateLcdNumberFrequency(int frequency_){ ui -> lcdNumberFrequency -> display(frequency_); }
void MainWindow::updateLcdNumberSpeed(int speed_){ ui -> lcdNumberSpeed -> display(speed_); }
void MainWindow::bindPlotterWidget(){ ui -> lcdNumberAmplitude -> display(0); }