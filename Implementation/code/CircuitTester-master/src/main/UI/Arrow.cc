#include "Arrow.h"
#include "SceneItem.h"

#include <QPainter>
#include <QPen>
#include <QtMath>


Arrow::Arrow(SceneItem *startItem, SceneItem *endItem, QGraphicsItem *parent)
    : QGraphicsLineItem(parent), myStartItem(startItem), myEndItem(endItem){
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}



QRectF Arrow::boundingRect() const{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}



QPainterPath Arrow::shape() const{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}



void Arrow::updatePosition(){
    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);
}



void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    if (myStartItem->collidesWithItem(myEndItem)) {
        return;
    }

    QPen myPen = pen();
    myPen.setColor(myColor);
    painter->setPen(myPen);
    painter->setBrush(myColor);

    setLine(QLineF(myEndItem->centerpoint(), myStartItem->centerpoint()));
 
    painter->drawLine(line());

    if (isSelected()) {
        painter->setPen(QPen(myColor, 1, Qt::DashLine));
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(myLine);
    }
}

