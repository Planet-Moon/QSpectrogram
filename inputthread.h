#ifndef INPUTTHREAD_H
#define INPUTTHREAD_H

#include <QThread>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <memory>

class InputThread: public QThread {
    Q_OBJECT
public:
    InputThread(unsigned int _sampleRage, unsigned int _bufferSize);
    ~InputThread();
    void stop();

    unsigned int sampleRate;
    unsigned int bufferSize;

signals:
    void bufferFilled(float *outputBufferLeft, unsigned int bufferLength);

protected:
    void run();

private:
    volatile bool stopped;
    std::unique_ptr<std::vector<float>> buffer;
    std::unique_ptr<std::vector<float>> copyBuffer;
};

#endif // INPUTTHREAD_H
