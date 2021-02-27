#ifndef CUSTOMRECTITEM_H
#define CUSTOMRECTITEM_H

#include <QGraphicsRectItem>
#include "scene.h"
#include "math.h"

class CustomRectItem : public QGraphicsRectItem
{
public:
    CustomRectItem(const QRect& rect, QGraphicsItem* parent = 0);
protected:
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    qreal x,y;
};

#endif // CUSTOMRECTITEM_H
