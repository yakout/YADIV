#include "imageviewer.h"
#include "ui_imageviewer.h"
#include "QMessageBox"
#include "QFileDialog"
ImageViewer::ImageViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewer)
{
    ui->setupUi(this);
    //this->setStyleSheet("background-color: gray;");

}

ImageViewer::~ImageViewer()
{
    delete ui;
}


void ImageViewer::on_actionopen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
           tr("Choose image to view"),"",tr("Images (*.png *.jpg *.jpeg"));
    bool canLoad;
    if (QString ::compare(fileName,QString()) !=0){
         canLoad = image.load(fileName);

    }
    if (canLoad){
        ui->ImageLabel->setPixmap(QPixmap::fromImage(image));

    }
    else {
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

}

void ImageViewer::on_actionZoom_Out_triggered()
{

}

void ImageViewer::on_actionabout_triggered()
{
    QMessageBox::about(this, tr("About Image Viewer"),
               tr("<p>The <b>Image Viewer</b> is an image editor written in Qt C++ that "
               "enables the user to view and modify images in different formats .</p>"));
}
