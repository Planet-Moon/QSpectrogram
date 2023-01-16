#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "spectrogram.h"
#include "qspectrogram.h"
#include "inputthread.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    std::unique_ptr<InputThread> inputThread;
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    std::unique_ptr<Spectrogram> spectrogram;
    std::unique_ptr<QSpectrogram> spectrogramWidget;
};

#endif // MAINWINDOW_H
