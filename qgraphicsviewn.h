#ifndef QGRAPHICSVIEWN_H
#define QGRAPHICSVIEWN_H

#include <QWidget>
#include <QGraphicsView>
#include <QPoint>
#include <QMouseEvent>
#include <QRect>
#include <QRubberBand>
class QGraphicsViewn : public QGraphicsView
{
    Q_OBJECT
private:
    QPoint press,release;
     QRubberBand *rubber_band;
public:
    explicit QGraphicsViewn(QWidget *parent = nullptr);
    QRect get_selected();

signals:
    void area_selected();

public slots:
    void select();
    void unselect();

protected slots:
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
};

#endif // QGRAPHICSVIEWN_H
