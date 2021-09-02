# Stage 4 - Main Window (Merge Stages 2&3)


## Bugs

### Expandable settings menu double-click issue

The settings menu is activated by double-clicking on a component, which also needed to open the settings menu.

The problem was that if the menu was already open, the menu needed to be double clicked twice, first to select the item, then
to open the menu as the first double-click closed the menu.

The solution was simple - to check if the settings menu was open and only toggle the settings menu if the menu was not open.

Before:

```cpp
void MainWindow::itemRightClicked(UIComponent* item) {
    // Set the contents of the settingsmenu to the settingsbox of the item.
    settingsMenu->setInteriorLayout(item->settingsBox);

    // Open the menu
    settingsMenu->toggleButton->click();
}
```

After:

```cpp
void MainWindow::itemRightClicked(UIComponent* item) {
    // Set the contents of the settingsmenu to the settingsbox of the item.
    settingsMenu->setInteriorLayout(item->settingsBox);

    // Open the menu if the menu is not opened.
    if(not settingsMenu->toggleButton->isChecked()){
        settingsMenu->toggleButton->click();
    }
}
```

### Crash when double clicking an item

This occured when during the part where the settings window would change if a component was double clicked.

The issue was that if a line was double clicked, then the program would segfault.

The issue was that the QGraphicsSceneMouseEvent returned a QGraphicsItem\* which I always assumed was a UIComponent\*., but when a line
was clicked, the program blindyl casted the Line\* to a UIComponent\* and then attempted to call a UIComponent method, which doesn't
exist in Line, which crashed the program.

```bash
Process finished with exit code 139 (interrupted by signal 11: SIGSEGV)
```

I fixed this by using my already-existing IS_TYPE function to check if the UIreturned QGraphicsItem\* was a UIComponent\* or not.

Before:
```cpp
void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent) {

    // Is there anything selected?
    if(! selectedItems().empty()){
        // Get the first selected item, cast to a UIComponent.
        auto* item = ((UIComponent*) selectedItems().at(0));
        ((MainWindow*) parent())->itemRightClicked(item);
    }

    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}
```

After:
```cpp
void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent) {

    // Is there anything selected?
    if(! selectedItems().empty()){
        // Get the first selected item.
        auto* item = selectedItems().at(0);

        // Is the item a UIComponent (it could be a line as this causes a crash)
        if(IS_TYPE(UIComponent, item)) {
            ((MainWindow *) parent())->itemRightClicked((UIComponent*) item);
        }
    }

    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}
```
