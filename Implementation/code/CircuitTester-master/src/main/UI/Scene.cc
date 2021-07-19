#include "Scene.h"
#include "Arrow.h"

#include <QGraphicsSceneMouseEvent>
#include <QTextCursor>
#include <iostream>

#include "Components/Resistor.h"


Scene::Scene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent){

    myItemMenu = itemMenu;
    myMode = MoveItem;
    component = nullptr;
    line = nullptr;
    textItem = nullptr;
    myItemColor = Qt::white;
    myTextColor = Qt::black;
    myLineColor = Qt::black;

}


void Scene::setMode(Mode mode){
    myMode = mode;
}

void Scene::setItemType(UIComponent* c){
    this->component = c;
}


void Scene::editorLostFocus(SceneText *item){
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);

    if (item->toPlainText().isEmpty()) {
        removeItem(item);
        item->deleteLater();
    }
}



void Scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    switch (myMode) {
        case InsertItem:
            addItem(component);
            component->setPos(mouseEvent->scenePos());
            emit itemInserted(component);
            break;

        case InsertLine:
            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));

            line->setPen(QPen(myLineColor, 2));

            addItem(line);
            break;
 
    default:
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}



void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if (myMode == InsertLine && line != nullptr) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    } else if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}



void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if (line != nullptr && myMode == InsertLine) {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;
 

        if (startItems.count() > 0 && endItems.count() > 0 && startItems.first()->type() == SceneItem::Type && endItems.first()->type() == SceneItem::Type &&  startItems.first() != endItems.first()) {
            SceneItem *startItem = qgraphicsitem_cast<SceneItem *>(startItems.first());
            SceneItem *endItem = qgraphicsitem_cast<SceneItem *>(endItems.first());
            Arrow *arrow = new Arrow(startItem, endItem);
            arrow->setColor(myLineColor);
            startItem->addArrow(arrow);
            endItem->addArrow(arrow);
            arrow->setZValue(-1000.0);
            addItem(arrow);
            arrow->updatePosition();
        }
    }
 
    line = nullptr;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}



bool Scene::isItemChange(int type) const{
    const QList<QGraphicsItem *> items = selectedItems();

    return std::find_if(items.begin(), items.end(), [type](const QGraphicsItem *item) {
        return item->type() == type;
    }) != items.end();
}

