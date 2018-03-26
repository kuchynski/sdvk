#ifndef CENABLEDDATCHIK_H
#define CENABLEDDATCHIK_H

#include <QWidget>
#include "cchecks.h"
#include "cparam.h"

class CEnabledDatchik : public QWidget
{
    Q_OBJECT
private:
    QImage image_back;
    CChecks *checks[2];
public:
    explicit CEnabledDatchik(QWidget *parent = 0);

    void paintEvent(QPaintEvent *p);
    void resizeEvent(QResizeEvent *r);
    void SetImageBack(const QImage &ib, const QRect &r);
    void SetData(const unsigned dat, const unsigned oborot, const unsigned state);
    unsigned GetData(const unsigned dat, const unsigned oborot) const;
signals:
    void IAmResize();

public slots:
};

#endif // CENABLEDDATCHIK_H
