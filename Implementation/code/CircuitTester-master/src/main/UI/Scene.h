#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include "SceneItem.h"
#include "SceneText.h"

#include <QGraphicsScene>
#include "UIComponent.h"


class Scene : public QGraphicsScene{
    Q_OBJECT

public:
    enum Mode { InsertItem, InsertLine, InsertText, MoveItem };

    explicit Scene(QMenu *itemMenu, QObject *parent = nullptr);
    QFont font() const { return myFont; }
    QColor textColor() const { return myTextColor; }
    QColor itemColor() const { return myItemColor; }
    QColor lineColor() const { return myLineColor; }

public slots:
    void setMode(Mode mode);
    void setItemType(UIComponent* c);
    void editorLostFocus(SceneText *item);

signals:
    void itemInserted(UIComponent *c);
    void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    bool isItemChange(int type) const;

    UIComponent* component;
    QMenu *myItemMenu;
    Mode myMode;
    bool leftButtonDown;
    QPointF startPoint;
    QGraphicsLineItem *line;
    QFont myFont;
    SceneText *textItem;
    QColor myTextColor;
    QColor myItemColor;
    QColor myLineColor;
};


#endif // DIAGRAMSCENE_H
