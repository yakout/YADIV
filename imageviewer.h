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
    void on_actioncrop_triggered();

private:
     Ui::ImageViewer *ui;
     QImage image;
     QImage default_image;
};

#endif // IMAGEVIEWER_H
