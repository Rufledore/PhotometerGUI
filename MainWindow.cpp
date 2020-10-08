#include <iostream>
#include <QThread>
#include <QDebug>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "daqmx/include/NIDAQmx.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TaskHandle taskHandle = nullptr;

    int errorCode = 0;
    char errorString[200];

    errorCode = DAQmxCreateTask("task", &taskHandle);
    if (errorCode) {
        DAQmxGetErrorString(errorCode, errorString, 200);
        qDebug() << errorCode << ": " << errorString;
    }

    errorCode = DAQmxCreateAOVoltageChan(taskHandle, "Dev1/ao0", "channel", 0, 3, DAQmx_Val_Volts, "");
    if (errorCode) {
        DAQmxGetErrorString(errorCode, errorString, 200);
        qDebug() << errorCode << ": " << errorString;
    }

    errorCode = DAQmxStartTask(taskHandle);
    if (errorCode) {
        DAQmxGetErrorString(errorCode, errorString, 200);
        qDebug() << errorCode << ": " << errorString;
    }

    errorCode = DAQmxWriteAnalogScalarF64(taskHandle, true, -1, 2.5, NULL);
    if (errorCode) {
        DAQmxGetErrorString(errorCode, errorString, 200);
        qDebug() << errorCode << ": " << errorString;
    }

    QThread::sleep(5);

    DAQmxStopTask(taskHandle);
    DAQmxClearTask(taskHandle);

}

MainWindow::~MainWindow()
{
    delete ui;
}

