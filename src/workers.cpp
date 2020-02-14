#include "../include/workers.h"

#include <QDebug>
#include <QTimer>

static std::default_random_engine generator;

Worker::Worker(QObject *parent) : QObject(parent)
{}

Worker::~Worker()
{
    disconnect(m_timer.data(), &QTimer::timeout, this, &Worker::genNewValue);
    m_timer->stop();
}

void Worker::run()
{
    m_generator = std::uniform_real_distribution<double>(m_min, m_max);
    m_timer.reset(new QTimer);
    connect(m_timer.data(), &QTimer::timeout, this, &Worker::genNewValue);
    m_timer->setInterval(100);
    m_timer->start();
}

void Worker::setMax(const double max)
{
    m_max = max;
}

void Worker::setMin(const double min)
{
    m_min = min;
}

void Worker::genNewValue()
{
    auto newGenValue = m_generator(generator);
    emit newValue(newGenValue);
    qDebug() << QThread::currentThread() << ":" << newGenValue;
}
