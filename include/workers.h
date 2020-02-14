#ifndef WORKERS_H
#define WORKERS_H

#include <QThread>
#include <QSharedPointer>
#include <random>

class QTimer;
class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();
    void run();
    void setMin(const double);
    void setMax(const double);

signals:
    void newValue(double);

private slots:
    void genNewValue();

private:
    double m_min;
    double m_max;

    QSharedPointer<QTimer> m_timer;
    std::uniform_real_distribution<double> m_generator;
};

#endif // WORKERS_H
