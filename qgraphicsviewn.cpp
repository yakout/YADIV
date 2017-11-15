#include "qgraphicsviewn.h"

using namespace std;

QGraphicsViewn::QGraphicsViewn(QWidget *parent) : QGraphicsView(parent)
{
    rubber_band = NULL;
}

void QGraphicsViewn::mousePressEvent(QMouseEvent * event)
{
    QGraphicsView::mousePressEvent(event);
    press = event->pos();

    press.setX(min(press.x(),this->size().width()));
    press.setY(min(press.y(),this->size().height()));
    press.setX(max(press.x(),0));
    press.setY(max(press.y(),0));
}

QRect* QGraphicsViewn::get_selected()
{
    QPoint start,end;
    start.setX(min(press.x(),release.x()));
    start.setY(min(press.y(),release.y()));
    end.setX(max(press.x(),release.x()));
    end.setY(max(press.y(),release.y()));

    QRect *ret= new QRect();
    ret->setX(start.x());
    ret->setY(start.y());
    ret->setWidth(end.x()-start.x());
    ret->setHeight(end.y()-start.y());

    return ret;
}

void QGraphicsViewn::mouseReleaseEvent(QMouseEvent * event)
{
    QGraphicsView::mouseReleaseEvent(event);
    release = event->pos();

    release.setX(min(release.x(),this->size().width()));
    release.setY(min(release.y(),this->size().height()));
    release.setX(max(release.x(),0));
    release.setY(max(release.y(),0));
    area_selected();
}


void QGraphicsViewn::mouseMoveEvent(QMouseEvent * event) {
    QGraphicsView::mouseMoveEvent(event);
    release = event->pos();

    release.setX(min(release.x(),this->size().width()));
    release.setY(min(release.y(),this->size().height()));
    release.setX(max(release.x(),0));
    release.setY(max(release.y(),0));
    area_selected();
}

void QGraphicsViewn::wheelEvent(QWheelEvent *e) {
    if (!zoomFlag) {
        QGraphicsView::wheelEvent(e);
        return;
    }

    if(e->delta() > 0){
        scale(1.05, 1.05);
    } else {
        scale(0.97, 0.97);
    }
}

void QGraphicsViewn::select() {
    if (!rubber_band)
           rubber_band = new QRubberBand(QRubberBand::Rectangle, this);
       rubber_band->setGeometry(*get_selected());
       rubber_band->show();
}
void QGraphicsViewn::unselect() {
    if(!rubber_band)
        return;
    rubber_band->hide();
          delete rubber_band;

    press.setX(0);
    press.setY(0);
    release.setX(0);
    release.setY(0);

    rubber_band = nullptr;
}

bool QGraphicsViewn::getZoomFlag()
{
    return zoomFlag;
}

void QGraphicsViewn::setZoomFlag(bool flag)
{
    this->zoomFlag = flag;
}
