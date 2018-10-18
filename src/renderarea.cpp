#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{

}

void RenderArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawArea(painter);
    drawInitPos(painter);
    drawEndPos(painter);
    drawMap(painter);
    emit painting();
}

void RenderArea::drawArea(QPainter &painter)
{
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    QRect area;
    area.setTopLeft(QPoint(this->x(), this->y()));
    area.setBottomRight(QPoint(this->width()-1, this->height()-1));
    painter.setPen(Qt::black);
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(area);
    painter.restore();
}

void RenderArea::drawInitPos(QPainter &painter)
{
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.setBrush(QBrush(Qt::blue));
    painter.drawEllipse(START_POS_X, START_POS_Y, 8.0, 8.0);
    painter.restore();

}

void RenderArea::drawEndPos(QPainter &painter)
{
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.setBrush(QBrush(Qt::red));
    painter.drawEllipse(END_POS_X, END_POS_Y, 8.0, 8.0);
    painter.restore();

}

void RenderArea::drawMap(QPainter &painter)
{
    int rows = WORLD_HEIGHT;
    int columns = WORLD_WIDTH;
    int pixelScale = map->pixelRepresentation;
    int displacement = pixelScale - 1;
    int flagFirst = 1;
    int x = 0, y = 0;
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.setBrush(QBrush(Qt::black));

    for (int i = 0; i <= rows; i++)
    {
        for(int j = 0; j <= columns; j++)
        {
            if(flagFirst == 0)
            {
                if(map->mapMatrix[j][i].isOccupied == 1.00)
                {
                    x = j + displacement;
                    painter.drawRect(x, y, pixelScale, pixelScale);
                }
            }
            else
            {
                if(map->mapMatrix[j][i].isOccupied == 1.00)
                {
                    painter.drawRect(j, y, pixelScale, pixelScale);
                    flagFirst = 0;
                }
            }
        }
        flagFirst = 1;
        y = i + displacement;
    }
    painter.restore();
}
