#include "imageviewer.h"
#include "ui_imageviewer.h"


QSize sizoo;
QAction *fitToWindowAct;
bool fittw;


// void ImageViewer::fitToWindow()
// {

// }

ImageViewer::ImageViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageViewer)
{
    ui->setupUi(this);
    //this->setStyleSheet("background-color: gray;");
   // ui->ImageLabel->addAction();
    ui->rotateSlider->setVisible(false);
    ui->angleSpinBox->setVisible(false);
    image.load(":/default.jpg");
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    QGraphicsScene *scene = new QGraphicsScene();
    item->scale();
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    ui->graphicsView->resize(100,100);

//    connect(ui->rotateSlider, SIGNAL(valueChanged(int)),
//                ui->angleSpinBox, SLOT(setValue(int)));

//    connect(ui->actionrotate, SIGNAL(toggled(bool)),
//                ui->rotateSlider, SLOT(setVisible(bool)));
    resize(QGuiApplication::primaryScreen()->availableSize() * 4 / 5);
}

ImageViewer::~ImageViewer()
{
    delete ui;
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
//        ui->ImageLabel->setPixmap(QPixmap::fromImage(image));
//        sizoo = image.size();

        // using graphics view
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        QGraphicsScene *scene = new QGraphicsScene();
        scene->addItem(item);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->show();
        //
    } else {
        QMessageBox::about(this, tr("Error Loading Image"),
                   tr("<p>Image corrupted or unsupported format</p>"));
    }
}

void ImageViewer::on_actionsave_triggered()
{

}

void ImageViewer::on_actionReset_triggered()
{

}

void ImageViewer::on_actionZoom_In_triggered()
{
    ui->graphicsView->scale(2,2);   //zoom in

//    image = image.scaled(image.size().width()*2,image.size().height()*2);
//    QSize sizoo = ui->ImageLabel->size()*2;
//    ui->ImageLabel->resize(sizoo);
//    ui->ImageLabel->setPixmap(QPixmap::fromImage(image));
}

void ImageViewer::on_actionZoom_Out_triggered()
{
    ui->graphicsView->scale(.5,.5); //zoom out
//    image = image.scaled(image.size().width()/2,image.size().height()/2);
//    sizoo = image.size();
//    if(ui->ImageLabel !=NULL){
//        ui->ImageLabel->resize(ui->ImageLabel->size()/2);
//    } //printf("%d %d\n",sizoo.height(),sizoo.width());
//    ui->ImageLabel->setPixmap(QPixmap::fromImage(image));
//    return;
}

void ImageViewer::on_actionabout_triggered()
{
    QMessageBox::about(this, tr("About Image Viewer"),
               tr("<p>The <b>Image Viewer</b> is an image editor written in Qt C++ that "
               "enables the user to view and modify images in different formats .</p>"));
}

void ImageViewer::on_actionrotate_triggered()
{
    ui->rotateSlider->setVisible(!ui->rotateSlider->isVisible());
    ui->angleSpinBox->setVisible(!ui->angleSpinBox->isVisible());
}

void ImageViewer::on_rotateSlider_valueChanged(int value)
{
//    qInfo() << value << "\n";
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


