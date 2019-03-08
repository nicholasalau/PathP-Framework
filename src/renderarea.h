#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include "map.h"
#include "algorithms/astar/astar.h"

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);
    Path *path;
    Map *map;

protected:
    void paintEvent(QPaintEvent *event);
    void drawArea(QPainter &event);
    void drawInitPos(QPainter &event);
    void drawEndPos(QPainter &event);
    void drawMap(QPainter &event);
    void drawPaths(QPainter &event);

signals:
    void painting();

public slots:
};

#endif // RENDERAREA_H
