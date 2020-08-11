#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QPainter>
#include <QApplication>
#include <QSettings>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = 0);
    int getGridSize() const {return this->gridSize;}
    void setGrid(int size, QColor clr);
    void enableGrid(bool enabled) {enab = enabled;};
protected:
    void drawBackground (QPainter* painter, const QRectF &rect);
private:
    int gridSize;
    QColor gridColor;
    bool enab;
};

#endif // SCENE_H
