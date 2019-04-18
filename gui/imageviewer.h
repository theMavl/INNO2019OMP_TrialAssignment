#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QGraphicsView>

class ImageViewer : public QGraphicsView
{
    Q_OBJECT

public:
     explicit ImageViewer(QWidget *parent = nullptr);
      //~ImageViewer();

private:
    double _scaling;
    int _numScheduledScalings;

private slots:
    void wheelEvent(QWheelEvent* event);

    void scalingTime(qreal x);

    void animFinished();

};

#endif // IMAGEVIEWER_H
