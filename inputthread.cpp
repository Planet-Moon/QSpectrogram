#include "inputthread.h"
#include <QCoreApplication>
#include <QDebug>
#include <QRandomGenerator>

#define RAW_BUFFER_SIZE 128

InputThread::InputThread(unsigned int _sampleRate, unsigned int _bufferSize):
    sampleRate(_sampleRate), bufferSize(_bufferSize)
{
    buffer = std::make_unique<std::vector<float>>();
    copyBuffer = std::make_unique<std::vector<float>>();

    stopped = true;
}

InputThread::~InputThread() {

}

void InputThread::run() {
    stopped = false;
    int error = 0;
    std::vector<float> rawBuffer(bufferSize, 0);

    qint32 seed = QRandomGenerator::system()->generate();
    QRandomGenerator generator(seed);
    generator.bounded(1,101);

    while(!stopped){
        for(int i = 0; i < bufferSize; i++){
            rawBuffer[i] = generator->generate();
        }
        QThread::msleep(1000*(1/sampleRate)*bufferSize);
        *copyBuffer = *buffer;
        emit bufferFilled(copyBuffer, bufferSize);
    }
}

void InputThread::stop() {
    stopped = true;
}
