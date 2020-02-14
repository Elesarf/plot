#include "../include/vm.h"

#include <QThread>
#include <QTime>
#include <workers.h>

vm::vm(QObject *parent) : QObject(parent)
{
    m_workerA.reset(new Worker());
    m_workerB.reset(new Worker());
    m_workerC.reset(new Worker());

    m_workerA->setMin(3);
    m_workerA->setMax(7);
    m_workerB->setMin(1);
    m_workerB->setMax(3);
    m_workerC->setMin(1);
    m_workerC->setMax(10);

    m_threadA.reset(new QThread());
    m_threadB.reset(new QThread());
    m_threadC.reset(new QThread());

    m_workerA->moveToThread(m_threadA.data());
    m_workerB->moveToThread(m_threadB.data());
    m_workerC->moveToThread(m_threadC.data());

    connect(m_threadA.data(), &QThread::started, m_workerA.data(), &Worker::run);
    connect(m_threadB.data(), &QThread::started, m_workerB.data(), &Worker::run);
    connect(m_threadC.data(), &QThread::started, m_workerC.data(), &Worker::run);

    connect(m_workerA.data(), &Worker::newValue, this, [this](const double a){
        m_a = a;
        recalc();
    });

    connect(m_workerB.data(), &Worker::newValue, this, [this](const double b){
        m_b = b;
        recalc();
    });

    connect(m_workerC.data(), &Worker::newValue, this, [this](const double c){
        m_c = c;
        recalc();
    });

    m_threadA->start();
    m_threadB->start();
    m_threadC->start();
}

QList<double> vm::dots() const
{
    return m_dotsList;
}

void vm::recalc()
{
    m_dotsList.clear();
    for(int i = 0; i < 100; ++i)
    {
        auto value = m_a + m_b * sin(m_c * i);
        m_dotsList.append(value);
        m_dotsList.append(i);
    }
}
