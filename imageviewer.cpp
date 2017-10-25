#include "imageviewer.h"
#include "ui_imageviewer.h"

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
