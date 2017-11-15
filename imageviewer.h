#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QWidget>
#include <QSlider>
#include <QSpinBox>
#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <QTransform>
#include <QImage>
#include <QScrollArea>

#include "image.h"

namespace Ui {
class ImageViewer;
}

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public slots:
    //void openFile();
    void select_area();

public:
    explicit ImageViewer(QWidget *parent = 0);
    ~ImageViewer();

    enum Mode {
        CROP,
        ROTATE,
        ZOOM_OUT,
        ZOOM_IN,
        NO_MODE
    };

private slots:

    void on_actionopen_triggered();
    void on_actionsave_triggered();
    void on_actionReset_triggered();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionabout_triggered();
    void on_actionrotate_triggered();
    void on_rotateSlider_valueChanged(int value);
    void load_image();
    void updatePixmap();
    void on_actioncrop_triggered();

    void on_actionselect_triggered();

private:
     Ui::ImageViewer *ui;
     Image* image;
     QPixmap pixmap;
     Mode mode;
};

#endif // IMAGEVIEWER_H
