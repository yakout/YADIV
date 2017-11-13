#include "imageviewer.h"
#include "ui_imageviewer.h"
#include <QDebug>
#include <QGraphicsView>
#include <QRect>

ImageViewer::ImageViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageViewer)
{
    ui->setupUi(this);
    ui->rotateSlider->setVisible(false);
    ui->angleSpinBox->setVisible(false);
    image.load(":/default.jpg");
    default_image = image.copy(0,0,image.size().width(),image.size().height());
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    QGraphicsScene *scene = new QGraphicsScene();
    item->scale();
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    ui->graphicsView->resize(100,100);
   QWidget::connect (ui->graphicsView, SIGNAL(area_selected()),
                      this, SLOT(select_area()));
    resize(QGuiApplication::primaryScreen()->availableSize() * 4 / 5);
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

void ImageViewer::load_image() {
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    QGraphicsScene *scene = new QGraphicsScene();
    item->scale();
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}
void ImageViewer::on_actionopen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
           tr("Choose image to view"),"",tr("Images (*.png *.jpg *.jpeg *.bmp"));
    bool canLoad;
    if (QString ::compare(fileName,QString()) !=0) {
        canLoad = image.load(fileName);

    }
    if (canLoad) {
        default_image = image.copy(0,0,image.size().width(),image.size().height());
        this->load_image();

    } else {
        QMessageBox::about(this, tr("Error Loading Image"),
                   tr("<p>Image corrupted or unsupported format</p>"));
    }
}

void ImageViewer::on_actionsave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
           tr("Choose image to view"),"",tr("Images (*.png *.jpg *.jpeg *.bmp"));
    image.save(fileName);

}

void ImageViewer::select_area(){
    ui->graphicsView->select();


}
void ImageViewer::on_actionReset_triggered()
{
    ui->graphicsView->unselect();
    image = default_image.copy(0,0,default_image.size().width(),default_image.size().height());
    this->load_image();

    ui->rotateSlider->setVisible(false);
    ui->rotateSlider->setValue(0);
    ui->angleSpinBox->setVisible(false);
}

void ImageViewer::on_actionZoom_In_triggered()
{

    ui->graphicsView->unselect();
    ui->graphicsView->scale(2,2);   //zoom in

}

void ImageViewer::on_actionZoom_Out_triggered()
{

    ui->graphicsView->unselect();
    ui->graphicsView->scale(.5,.5); //zoom out
}

void ImageViewer::on_actionabout_triggered()
{
    QMessageBox::about(this, tr("About Image Viewer"),
               tr("<p>The <b>Image Viewer</b> is an image editor written in Qt C++ that "
               "enables the user to view and modify images in different formats .</p>"));
}

void ImageViewer::on_actionrotate_triggered()
{

    ui->graphicsView->unselect();
    ui->rotateSlider->setVisible(!ui->rotateSlider->isVisible());
    ui->angleSpinBox->setVisible(!ui->angleSpinBox->isVisible());
}

void ImageViewer::on_rotateSlider_valueChanged(int value)
{
//    qInfo() << value << "\n";

    ui->graphicsView->unselect();
    ui->angleSpinBox->setValue(value);
    QMatrix rm;
    rm.rotate(value);
    QPixmap pixmap = QPixmap::fromImage(image);
    pixmap = pixmap.transformed(rm, Qt::SmoothTransformation).copy();
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
}



void ImageViewer::on_actioncrop_triggered()
{
    QRect *area = ui->graphicsView->get_selected();
    qDebug() << area->x() << " "<<area->y();

    QPointF temp =  ui->graphicsView->mapToScene( *(new QPoint(area->x(),area->y())) );
    QPointF temp2 =  ui->graphicsView->mapToScene( *(new QPoint(area->x()+area->width()
                                                               ,area->y()+area->height())) );
    qDebug() << temp << " "<<temp2;
    area->setX( temp.x());
    area->setY( temp.y());
    area->setWidth(temp2.x()-temp.x());

    area->setHeight(temp2.y()-temp.y());

    if(!area)
        return;
    image = image.copy(*area);
    this->load_image();

    ui->rotateSlider->setVisible(false);
    ui->rotateSlider->setValue(0);
    ui->angleSpinBox->setVisible(false);
    ui->graphicsView->unselect();
}
