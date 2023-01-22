#include "mainwindow.h"
#include <QDebug>
#include <QKeyEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    spectrogram = std::make_unique<Spectrogram>(44100, 44100 * 60, 256, 8192);

    spectrogramWidget = std::make_unique<QSpectrogram>(spectrogram.get(), this);
    setCentralWidget(spectrogramWidget.get());

    resize(1024, 600);

    inputThread = std::make_unique<InputThread>(44100, 1024);
    inputThread->start();

    connect(inputThread.get(), &InputThread::bufferFilled,
            spectrogramWidget.get(), &QSpectrogram::processData);
}

void
MainWindow::keyPressEvent(QKeyEvent *event) {
    qDebug("keyPress %d", event->key());

    switch (event->key()) {
    case Qt::Key_F1:
        spectrogramWidget->setMinAmpl(0.0001);
        break;
    case Qt::Key_F2:
        spectrogramWidget->setMinAmpl(0.001);
        break;
    case Qt::Key_F3:
        spectrogramWidget->setMinAmpl(0.01);
        break;
    case Qt::Key_F4:
        spectrogramWidget->setMaxAmpl(0.1);
        break;
    case Qt::Key_F5:
        spectrogramWidget->setMaxAmpl(1.0);
        break;
    case Qt::Key_F6:
        spectrogramWidget->setMaxAmpl(10.0);
        break;
    }
}

MainWindow::~MainWindow() {
    if(inputThread){
        inputThread->stop();
        inputThread->wait();
    }
}
