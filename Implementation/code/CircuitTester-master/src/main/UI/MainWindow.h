#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <map>
#include <vector>

#include <QMainWindow>
#include <QAbstractButton>
#include <QComboBox>
#include <QFontComboBox>
#include <QToolBox>
#include <QToolButton>
#include <QGraphicsView>

#include "UIComponent.h"
#include "SceneItem.h"
#include "Scene.h"

typedef std::map<UIComponent*, std::vector<UIComponent*>> Graph;
typedef std::vector<UIComponent*> Path;

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
   MainWindow();

private slots:
    void buttonGroupClicked(QAbstractButton *button);
    void deleteItem();
    void pointerGroupClicked();
    void itemInserted(UIComponent *item);
    void sceneScaleChanged(const QString &scale);
    void about();
    void runSimulation();

private:
    void createToolBox();
    void createActions();
    void createMenus();
    void createToolbars();

    template<class T> QWidget *createCellWidget(const QString &text);

    static Path* find_shortest_path(Graph* graph, UIComponent* start, UIComponent* end);

    Scene *scene;
    QGraphicsView *view;

    QAction *exitAction;
    QAction *deleteAction;
    QAction *runAction;
    QAction *aboutAction;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *aboutMenu;
    QMenu *simMenu;

    QToolBar *pointerToolbar;

    QComboBox *sceneScaleCombo;

    QToolBox *toolBox;
    QButtonGroup *buttonGroup;
    QButtonGroup *pointerTypeGroup;
    QAction *lineAction;
};


#endif // MAINWINDOW_H
