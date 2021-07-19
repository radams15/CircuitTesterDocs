#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPixmapItem>
#include <vector>
#include <QIcon>

class Arrow;

class SceneItem : public QGraphicsPixmapItem {
public:

    SceneItem(std::string resourcePath, QGraphicsItem *parent = nullptr);

    void removeArrow(Arrow *arrow);
    void removeArrows();

    inline QPixmap getPixmap() { return pixmap; }

    void addArrow(Arrow *arrow);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

    QPixmap image(){ return pixmap; }

    QPointF centerpoint();

    std::vector<Arrow *> arrows;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    QPixmap pixmap;
    std::string resourcePath;

private:
    QPolygonF myPolygon;

    void loadPolygon(QString path);
};


#endif // DIAGRAMITEM_H
