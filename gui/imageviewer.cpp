#include "imageviewer.h"
#include <QTimeLine>
#include <QWheelEvent>


ImageViewer::ImageViewer(QWidget *parent) : QGraphicsView(parent)
{
    _scaling = 1.0;
    _numScheduledScalings = 0;
}



void ImageViewer::scalingTime(qreal x)
{
    qreal factor = 1.0+ qreal(_numScheduledScalings) / 500.0;
    if (_scaling*factor < 1.0)
       fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
    else {
       scale(factor, factor);
       _scaling *= factor;
    }
}

void ImageViewer::wheelEvent ( QWheelEvent * event )
{
    if (scene() == nullptr)
        return;
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15; // see QWheelEvent documentation
    _numScheduledScalings += numSteps;
    if (_numScheduledScalings * numSteps < 0) // if user moved the wheel in another direction, we reset previously scheduled scalings
    _numScheduledScalings = numSteps;

    QTimeLine *anim = new QTimeLine(100, this);
    anim->setUpdateInterval(1);

    connect(anim, SIGNAL (valueChanged(qreal)), SLOT (scalingTime(qreal)));
    connect(anim, SIGNAL (finished()), SLOT (animFinished()));
    anim->start();
}

void ImageViewer::animFinished()
{
    if (_numScheduledScalings > 0)
       _numScheduledScalings--;
    else
       _numScheduledScalings++;
    sender()->~QObject();
}
