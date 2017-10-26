#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QWidget>
#include <QMap>

class QPushButton;
class QLabel;
class QLineEdit;
class QTextEdit;
class QScrollArea;
class QScrollBar;


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
    void on_actionrotate_triggered();


private:
     Ui::ImageViewer *ui;

     double scaleFactor;
     QImage image;
     QScrollArea *scrollArea;
     QLabel *imageLabel;
};

#endif // IMAGEVIEWER_H
