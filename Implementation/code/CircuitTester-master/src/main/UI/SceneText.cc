#include "SceneText.h"
#include "Scene.h"


SceneText::SceneText(QGraphicsItem *parent)
    : QGraphicsTextItem(parent){
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}



QVariant SceneText::itemChange(GraphicsItemChange change,
                               const QVariant &value){
    if (change == QGraphicsItem::ItemSelectedHasChanged)
        emit selectedChange(this);
    return value;
}



void SceneText::focusOutEvent(QFocusEvent *event){
    setTextInteractionFlags(Qt::NoTextInteraction);
    emit lostFocus(this);
    QGraphicsTextItem::focusOutEvent(event);
}



void SceneText::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    if (textInteractionFlags() == Qt::NoTextInteraction)
        setTextInteractionFlags(Qt::TextEditorInteraction);
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}

