#ifndef QGRAPHICSVIEWN_H
#define QGRAPHICSVIEWN_H

#include <QWidget>
#include <QGraphicsView>
#include <QPoint>
#include <QMouseEvent>
#include <QRect>
#include <QRubberBand>
#include <QDebug>
#include <cstdlib>

class QGraphicsViewn : public QGraphicsView
{
    Q_OBJECT
private:
    QPoint press,release;
    QRubberBand *rubber_band;
    bool zoomFlag = false;

public:
    explicit QGraphicsViewn(QWidget *parent = nullptr);
    QRect* get_selected();
    void setZoomFlag(bool);
    bool getZoomFlag();

signals:
    void area_selected();

public slots:
    void select();
    void unselect();

protected slots:
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent *e);
};

#endif // QGRAPHICSVIEWN_H
