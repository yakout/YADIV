#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QWidget>
#include <QMap>

class QPushButton;
class QLabel;
class QLineEdit;
class QTextEdit;

namespace Ui {
class ImageViewer;
}

class ImageViewer : public QMainWindow
{
    Q_OBJECT


public slots:

    //void openFile();



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

private:
    Ui::ImageViewer *ui;
     QPushButton *addButton;
};

#endif // IMAGEVIEWER_H
