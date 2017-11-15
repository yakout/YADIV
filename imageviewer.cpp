#include <QDebug>
#include <QGraphicsView>
#include <QRect>
#include <QFile>
#include <QIODevice>

#include "imageviewer.h"
#include "ui_imageviewer.h"

ImageViewer::ImageViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageViewer)
{
    mode = NO_MODE;
    ui->setupUi(this);
    ui->rotateSlider->setVisible(false);
    ui->angleSpinBox->setVisible(false);

#ifdef QT_DEBUG
    // only in development mode
    image = new Image(":/default.jpg");
    load_image();
#endif

//    pixmap = QPixmap::fromImage(*image->getQImage());
//    updatePixmap();

    ui->graphicsView->resize(100, 100);
    QWidget::connect (ui->graphicsView, SIGNAL(area_selected()),
                      this, SLOT(select_area()));
    resize(QGuiApplication::primaryScreen()->availableSize() * 4 / 5);
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

void ImageViewer::load_image() {
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(*image->getQImage()));
    QGraphicsScene *scene = new QGraphicsScene();
    item->scale();
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void ImageViewer::updatePixmap() {
    QMatrix rm;
    rm.rotate(image->getRotationAngle());

    pixmap = QPixmap::fromImage(*image->getQImage());

    pixmap = pixmap.transformed(rm, Qt::SmoothTransformation);
    if (image->getCropArea().width() != 0 && mode == CROP) {
        pixmap = pixmap.copy(image->getCropArea().x(),
                             image->getCropArea().y(),
                             image->getCropArea().width(),
                             image->getCropArea().height());
    }

    image->setPixMap(pixmap);

    qDebug() << mode << "\n";
    if (mode == CROP) {
        image->setQImage(pixmap.toImage().copy());
    }

    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
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
    bool canLoad = false;
    if (QString ::compare(fileName, QString()) !=0) {
        canLoad = image->getQImage()->load(fileName);
    }
    if (canLoad) {
        image->reset();
        image->setOriginalQImage(image->getQImage()->copy());
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
    qDebug() << fileName << "\n";
//    image->getQImage()->save(fileName);
    image->saveImage(fileName);

}

void ImageViewer::select_area()
{
    ui->graphicsView->select();
}

void ImageViewer::on_actionReset_triggered()
{
    ui->graphicsView->unselect();
    image->reset();
    image->setQImage(image->getOriginalQImage()->copy());

    this->load_image();

    ui->rotateSlider->setVisible(false);
    ui->rotateSlider->setValue(0);
    ui->angleSpinBox->setVisible(false);
}

void ImageViewer::on_actionZoom_In_triggered()
{
    mode = ZOOM_IN;
    double scale_ = 2;
    if (ui->graphicsView->get_selected()->width() != 0) {
        QPointF tempP = ui->graphicsView->mapToScene(ui->graphicsView->get_selected()->x(),
                                               ui->graphicsView->get_selected()->y());
        ui->graphicsView->fitInView(tempP.x(),
                                    tempP.y(),
                                    ui->graphicsView->get_selected()->width(),
                                    ui->graphicsView->get_selected()->height(),
                                    Qt::KeepAspectRatio);

//        ui->graphicsView->setSceneRect(tempP.x(),
//                                       tempP.y(),
//                                       ui->graphicsView->get_selected()->width(),
//                                       ui->graphicsView->get_selected()->height());

        ui->graphicsView->centerOn(ui->graphicsView->mapToScene(ui->graphicsView->get_selected()->center()));

        ui->graphicsView->unselect();
    } else {
        ui->graphicsView->scale(scale_ , scale_);
    }
}

void ImageViewer::on_actionZoom_Out_triggered()
{
    mode = ZOOM_OUT;
    double scale_  = 0.5;
    if (ui->graphicsView->get_selected()->width() != 0) {
        ui->graphicsView->centerOn(ui->graphicsView->get_selected()->center());
        ui->graphicsView->unselect();
        scale_ = 0.7;
    }
    ui->graphicsView->scale(scale_, scale_);
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
    mode = ROTATE;
    ui->graphicsView->unselect();
    ui->angleSpinBox->setValue(value);
    image->setRotationAngle(value);
    updatePixmap();
}


void ImageViewer::on_actioncrop_triggered()
{
    mode = CROP;
    QRect *area = ui->graphicsView->get_selected();
    if(area->width() == 0)
        return;

    QPointF temp = ui->graphicsView->mapToScene( *(new QPoint(area->x(),area->y())) );
    QPointF temp2 = ui->graphicsView->mapToScene( *(new QPoint(area->x()+area->width()
                                                               ,area->y()+area->height())));

    area->setX(temp.x());
    area->setY(temp.y());
    area->setWidth(temp2.x()-temp.x());
    area->setHeight(temp2.y()-temp.y());

    image->setCropArea(*area);
    updatePixmap();

    ui->rotateSlider->setVisible(false);
    ui->angleSpinBox->setVisible(false);
    ui->graphicsView->unselect();
}
