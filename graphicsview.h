#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
    int getGridSize() const {return this->gridSize;}
    void setGrid(int size, QColor clr);
    void enableGrid(bool enabled) {enab = enabled;}
    QPoint getMousePos() { return point;}

protected:
    void drawBackground (QPainter* painter, const QRectF &rect);
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    int gridSize;
    QColor gridColor;
    bool enab;
    QPoint point;

signals:
    void mousePosChanged();
};

#endif // GRAPHICSVIEW_H
