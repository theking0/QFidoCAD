#include "graphicsview.h"
#include <QSettings>
#include <QColor>
#include "scene.h"
#include "math.h"


GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent)
{
    QSettings s;
    gridSize = s.value("grid_step").toInt();
    gridColor = s.value("grid_color").value<QColor>();

    enab=true;

    setViewportUpdateMode(ViewportUpdateMode::FullViewportUpdate);
}

void GraphicsView::setGrid(int size, QColor clr)
{
    gridSize = size;
    gridColor = clr;

    this->update();
}

void GraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
    if(enab)
    {
        painter->setRenderHint(QPainter::Antialiasing);
        QPen pen(gridColor);
        painter->setPen(pen);

        qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
        qreal top = int(rect.top()) - (int(rect.top()) % gridSize);
        QVector<QPointF> points;
        for (qreal x = left; x < rect.right(); x += gridSize){
            for (qreal y = top; y < rect.bottom(); y += gridSize){
                points.append(QPointF(x,y));
            }
        }
        painter->drawPoints(points.data(), points.size());
    }
/*
    qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
       qreal top = int(rect.top()) - (int(rect.top()) % gridSize);

       QVarLengthArray<QLineF, 100> lines;

       for (qreal x = left; x < rect.right(); x += gridSize)
           lines.append(QLineF(x, rect.top(), x, rect.bottom()));
       for (qreal y = top; y < rect.bottom(); y += gridSize)
           lines.append(QLineF(rect.left(), y, rect.right(), y));

       QVarLengthArray<QLineF, 100> thickLines;

       for (qreal x = left; x < rect.right(); x += gridSize * 5)
           thickLines.append(QLineF(x, rect.top(), x, rect.bottom()));
       for (qreal y = top; y < rect.bottom(); y += gridSize * 5)
           thickLines.append(QLineF(rect.left(), y, rect.right(), y));

       QPen myPen(Qt::NoPen);
       painter->setBrush(QBrush(QColor(55, 55, 55, 255)));
       painter->setPen(myPen);
       painter->drawRect(rect);

       QPen penHLines(QColor(75, 75, 75), 1, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin);
       painter->setPen(penHLines);
       painter->drawLines(lines.data(), lines.size());

       painter->setPen(QPen(QColor(100, 100, 100), 2, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
       painter->drawLines(thickLines.data(), thickLines.size());


       painter->setPen(Qt::blue);

       QVector<QPointF> points;
       for (qreal x = left; x < rect.right(); x += gridSize) {
           for (qreal y = top; y < rect.bottom(); y += gridSize) {
               points.append(QPointF(x, y));
           }
       }
       painter->drawPoints(points.data(), points.size());*/
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        // zoom
        const ViewportAnchor anchor = transformationAnchor();
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        int angle = event->angleDelta().y();
        qreal factor;
        if (angle > 0) {
            factor = 1.1;
        } else {
            factor = 0.9;
        }
        scale(factor, factor);
        setTransformationAnchor(anchor);

    } else {
        QGraphicsView::wheelEvent(event);
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    Scene* customScene = qobject_cast<Scene*> (scene());

    qreal xV = round(event->pos().x()/gridSize)*gridSize;
    qreal yV = round(event->pos().y()/gridSize)*gridSize;
    point = QPoint(xV,yV);
    customScene->update();

    emit mousePosChanged();

    QGraphicsView::mouseMoveEvent(event);
}
