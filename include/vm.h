#ifndef VM_H
#define VM_H

#include <QObject>
#include <QList>
#include <QVariantMap>
#include <QSharedPointer>

class Worker;
class QThread;

struct dotType
{
    dotType(){}
    dotType(const double &_x, const double &_y) :
        x(_x),
        y(_y)
    {}

    dotType(const QVariantMap &v_map) :
        x(v_map["x"].toDouble()),
        y(v_map["y"].toDouble())
    {}

    QVariantMap toVariant() const
    {
        return
        {
            {"x", QVariant::fromValue(x)}
            , {"y", QVariant::fromValue(y)}
        };
    }

    double x;
    double y;
};

class vm : public QObject
{
    Q_OBJECT
public:
    explicit vm(QObject *parent = nullptr);

    Q_INVOKABLE QList<double> dots() const;

public slots:
    void recalc();

private:
    QSharedPointer<Worker> m_workerA;
    QSharedPointer<Worker> m_workerB;
    QSharedPointer<Worker> m_workerC;

    QSharedPointer<QThread> m_threadA;
    QSharedPointer<QThread> m_threadB;
    QSharedPointer<QThread> m_threadC;

    double m_a;
    double m_b;
    double m_c;

    QList<double> m_dotsList;
};

#endif // VM_H
