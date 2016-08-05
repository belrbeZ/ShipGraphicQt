#include "randomvaluegenerator.h"

qint32 random(qint32 lb, qint32 rb){
    if (rb < lb) { qDebug() << "Left boundary bigger than right!"; exit(1); }
    qint32 t;
    qsrand(QTime::currentTime().secsTo(QTime(0,0,0)) + qrand());
    t = qrand();
    t = t % (rb - lb + 1);
    t += lb;
    return t;
}

