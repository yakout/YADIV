#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QRect>
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QPixmap>
#include <QDebug>

class Image
{
public:
    Image(QString path);

    // getters
    QImage* getQImage();
    QImage* getOriginalQImage();
    QString getPath();
    QRect getCropArea();
    double getRotationAngle();
    int getScaleFactor();
    QPixmap* getPixMap();

    // setters
    void setCropArea(QRect);
    void setRotationAngle(double);
    void setScaleFactor(int);
    void setPixMap(QPixmap);
    void setQImage(QImage);
    void setOriginalQImage(QImage);

    // operation
    void saveImage(QString path);
    void reset();

private:
    Image();
    QPixmap pixmap;
    QString path;
    QImage image;
    QImage originalImage;
    double rotationAngle;
    QRect cropArea;
    int scaleFactor;
};

#endif // IMAGE_H
