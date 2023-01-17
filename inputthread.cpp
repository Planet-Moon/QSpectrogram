#include "inputthread.h"
#include <QCoreApplication>
#include <QDebug>
#include <QRandomGenerator>
#include <QDateTime>

#define RAW_BUFFER_SIZE 128
#define M_PI 3.14159265358979323846

template<typename T, typename U>
U linearInterpolate(T x, T x0, T x1, U y0, U y1)
{
    static_assert(
        std::is_arithmetic<T>::value && std::is_arithmetic<U>::value, "Both types must be numbers");
    const U x_x0 = static_cast<U>(x-x0);
    const U x1_x0 = static_cast<U>(x1-x0);
    const U left = y0*(1-x_x0/x1_x0);

    const U x1_x = static_cast<U>(x1-x);
    const U right = y1*(1-x1_x/x1_x0);
    const U result = left + right;
    return result;
}

InputThread::InputThread(unsigned int _sampleRate, unsigned int _bufferSize):
    sampleRate(_sampleRate), bufferSize(_bufferSize)
{
    buffer = std::make_unique<std::vector<float>>(bufferSize, 0);
    copyBuffer = std::make_unique<std::vector<float>>(bufferSize, 0);

    stopped = true;
}

InputThread::~InputThread() {

}

void InputThread::run() {
    stopped = false;
    int error = 0;
    std::vector<float> rawBuffer(bufferSize, 0);

    qint32 seed = QRandomGenerator::system()->generate();
    std::unique_ptr<QRandomGenerator> generator = std::make_unique<QRandomGenerator>(seed);
    generator->bounded(1,101);
    const quint32 min = generator->min();
    const quint32 max = generator->max();

    const quint32 _period = 50;
    const double frequency = 1/static_cast<double>(_period);
    const double _amplitude = 1;

    while(!stopped){
        qint64 start_time = QDateTime::currentMSecsSinceEpoch();
        qint64 time = -1;
        const double time_step_ms = 1000/static_cast<float>(sampleRate);

        for(int i = 0; i < bufferSize; i++){
            const quint32 _random = generator->generate();
            const float random = linearInterpolate(_random,min,max,0.f,100.f);


            const double delta_t = i*time_step_ms;
            time = start_time + delta_t;
            const double fraction = (time % _period) / static_cast<double>(_period);
            const double signal = _amplitude * sin(2 * M_PI * fraction);

            rawBuffer[i] = 0.0*random + 1*signal;
        }
        *buffer = rawBuffer;
        const unsigned long sleep_time = 1'000'000*bufferSize/sampleRate;
        QThread::usleep(sleep_time);
        *copyBuffer = *buffer;
        emit bufferFilled(copyBuffer->data(), bufferSize);
    }
}

void InputThread::stop() {
    stopped = true;
}
