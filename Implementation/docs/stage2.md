# Stage 2 - Graphics Scene

This is the scene where all the components are placed.

I first made a prototype where there was a single QGraphicsScene derivitive
(Scene), and a QGraphicsView which is the GUI representation of the QGraphicsScene.

I also created a class called SceneItem which derived from QGraphicsPixmapItem. This
simply takes in the path of the image to be used, scales the image to 200x200 px, 
then sets the item to be able to be moved and seleted, using the code below:

```cpp
SceneItem::SceneItem(std::string resourcePath, QGraphicsItem* parent) : QGraphicsPixmapItem (parent){
    this->resourcePath = resourcePath;
    this->pixmap = QPixmap(QString::fromStdString(resourcePath));
    pixmap = pixmap.scaled(200, 200);
    setPixmap(this->pixmap);

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}
```


Then I made the program automatically add a SceneItem of a battery to the Scene.


My MainWindow was simply:

```cpp
MainWindow::MainWindow() {
    createActions();

    // Create the scene, set it to the specified size.
    scene = new Scene(this);
    scene->setSceneRect(QRectF(0, 0, CANVAS_SIZE));

    // Resize the window
    resize(WINDOW_SIZE);

	// Create layout
    auto* layout = new QHBoxLayout;

	// Create graphicsView and view scene in the view.
    view = new QGraphicsView(scene);
    layout->addWidget(view);

    // Create a widget to hold the layout.
    auto *widget = new QWidget;
    widget->setLayout(layout);

    // Set the widget to the centre of the window.
    setCentralWidget(widget);
    setWindowTitle(tr("Circuit Simulator Stage 2"));

	// Makes the toolbar on mac look the same colour as the titlebar - just aesthetic.
    setUnifiedTitleAndToolBarOnMac(true);

	// Add a new battery to the scene
    scene->addItem(new Battery);
}

void MainWindow::createActions() {
    deleteAction = new QAction(QIcon(":/images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteItem);
}
```

This resulted in the following:

![Stage 2](images/stage2.png)