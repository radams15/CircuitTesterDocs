#include "SceneItem.h"
#include "Arrow.h"

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>
#include <QResource>
#include <QFile>
#include <QMessageBox>
#include <iostream>
#include <cmath>

#define GRID_SNAP_STEP 20


SceneItem::SceneItem(std::string resourcePath, QGraphicsItem *parent) : QGraphicsPixmapItem(parent){
    this->resourcePath = resourcePath;
    this->pixmap = QPixmap(QString::fromStdString(resourcePath));
    pixmap = pixmap.scaled(200, 200);
    setPixmap(this->pixmap);

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}


void SceneItem::removeArrow(Arrow *arrow){
    arrows.erase(std::remove(arrows.begin(), arrows.end(), arrow), arrows.end());
}


void SceneItem::removeArrows(){
    // need a copy here since removeArrow() will
    // modify the arrows container
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}


void SceneItem::addArrow(Arrow *arrow){
    arrows.push_back(arrow);
}

QVariant SceneItem::itemChange(GraphicsItemChange change, const QVariant &value){
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow : qAsConst(arrows))
            arrow->updatePosition();
    }

    return value;
}

QPointF SceneItem::centerpoint() {
    double w = pixmap.width();
    double h = pixmap.height();

    QPointF p = pos();

    double x = p.x();
    double y = p.y();

    double xc = x + (w/2);
    double yc = y + (h/2);

    return {xc, yc};
}

void SceneItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    double xx=x();
    double yy=y();

    if((int)xx / GRID_SNAP_STEP != xx/(float)GRID_SNAP_STEP){
        xx=5.0*round(xx/5.);
    }

    if((int)yy / GRID_SNAP_STEP != yy/(float)GRID_SNAP_STEP){
        yy=(float)GRID_SNAP_STEP*round(yy/(float)GRID_SNAP_STEP);
    }

    setPos(xx,yy);
    QGraphicsItem::mouseReleaseEvent(event);
}
