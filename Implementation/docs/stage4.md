# Stage 4 - Main Window (Merge Stages 2&3)

This was my first merge, adding the settings window and the graphics scene together, and so is still part of the
main window from the design phase.

I added the ability to draw lines between components, the ability to add components, and the ability
to alter the settings of components.

Also in this stage I improved the toolbar by adding an about button, added the toolbox of
items onto the left of the screen, and adding a menubar that has a toggle for the movement and line-drawing modes.

### Drawing lines

I created a class Line that was initialised with the start item and the end item.

Luckily, QT has a QGraphicsLineItem that does this exact purpose, so I only needed to expand that
class to draw a line between two SceneItems.

The first thing I did was set the start and end items as class attributes, and setup the pen to be solid, black, round ended and 2 pixels wide.

I also allowed the line to be selectable to allow deletion, but not to be able to be moved by the user.

```cpp
Line::Line(SceneItem *startItem, SceneItem *endItem)
    : QGraphicsLineItem(nullptr) {

    this->start = startItem;
    this->end = endItem;

    // Create a solid black pen with a width of 2px.
    setPen(QPen(penColour, penSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    // Can select the item to delete it.
    setFlag(QGraphicsItem::ItemIsSelectable, true);

    // Set the z coordinate to -1000 so it is always behind any other components.
    setZValue(-1000);
}
```

I created a method that was run when any component was moved to update the position of the line:

```cpp
void Line::update(){
    // Set the start and end coords of the line.
    setLine(QLineF(start->startPoint(), end->endPoint()));
}
```

The last part was simply drawing the line, which I overrided QGraphicsLineItem's paint method:

```cpp
void Line::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    // Make a pen, set the colour
    QPen myPen = pen();
    myPen.setColor(penColour);

    // Set the pen to the painter object.
    painter->setPen(myPen);
    painter->setBrush(penColour);

    update();

    // Draw the line.
    painter->drawLine(line());
}
```

I added a feature to the Scene to have different modes:

```cpp
enum Mode {
    /** Item being placed down.
    *
    */
    INSERT_ITEM,
    /** Line being placed down.
    *
    */
    INSERT_LINE,

    /** Item being moved.
    *
    */
    MOVE
};
```

Along with a method called setMode which sets the current mode of the scene.

When the scene detects a mouse press, it checks the current mode to either insert an item or a line.

```cpp
void Scene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
    // Only do anything if there was a left click.
    if (mouseEvent->button() == Qt::LeftButton){
        switch (currentMode) {
            case INSERT_ITEM:
                // Add the item to the scene.
                addItem(component);

                // Set the position of the component to where the mouse click occurred.
                component->setPos(mouseEvent->scenePos());

                // Notify others that an item was inserted.
                itemInserted(component);
                break;

            case INSERT_LINE:
                // Create the line
                line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));

                // Set the pen to be 2px wide and black
                line->setPen(QPen(Qt::black, 2));

                // Add the line.
                addItem(line);
                break;

            default: // Any other mode does nothing.
                break;
        }

        // QGraphicsScene then completes what it normally completes by default.
        QGraphicsScene::mousePressEvent(mouseEvent);
    }
}
```

### Adding Components

To add components I just needed to add the toolbar of components. I created a utility method that would
create QWidget buttons for each component.

There was a button group that would call one function each time any of the tool buttons were pressed, and each
button had a specific ID which was the ComponentType enum.

This generates the QWidget button:

```cpp
template<class T>
QWidget *MainWindow::createCellWidget(const QString &text) {
    // Initialise the widget to get the pixmap.
    T item;
    QIcon icon(item.getPixmap());

    // Make a 50*50 icon button for to select the item.
    auto* button = new QToolButton;
    button->setIcon(icon);
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    // Add the button to the buttongroup.
    buttonGroup->addButton(button, item.getId());

    // Create a grid with the icon and a label of the icon name.
    auto *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    // Create a widget for the layout.
    auto* widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}
```

This creates the grid of buttons and calls the method when a button is pressed.

```cpp
void MainWindow::createToolBox() {
    // Create the button group.
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);

    // When the button group is clicked, call buttonGroupClicked.
    connect(buttonGroup, static_cast<void(QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),
            this, &MainWindow::buttonGroupClicked); // https://doc.qt.io/archives/qt-5.6/qbuttongroup.html#buttonClicked

    // Create new grid layout, add the widgets for each component type to a 2*n grid.
    auto* layout = new QGridLayout;
    layout->addWidget(createCellWidget<Resistor>(tr("Resistor")), 0, 0);
    layout->addWidget(createCellWidget<Battery>(tr("Battery")), 0, 1);
    layout->addWidget(createCellWidget<Wire>(tr("Wire")), 1, 0);
    layout->addWidget(createCellWidget<Switch>(tr("Switch")), 1, 1);

    /* More Code */
```


The buttonGroupClicked method below simply unchecks all the other buttons, and then creates the correct
component depending on the ID of the button clicked, passing the new component to the scene in order to
place the item down. It then sets the scene to insert mode.

```cpp
void MainWindow::buttonGroupClicked(QAbstractButton *button) {
    const QList<QAbstractButton *> buttons = buttonGroup->buttons();

    for (QAbstractButton* myButton : buttons) {
        // Uncheck all the buttons that are not the clicked one.
        if (myButton != button){
            button->setChecked(false);
        }
    }
    const int id = buttonGroup->id(button);

    // Set the scene item to a new instance of the selected button.
    switch(id){
        case UI_RESISTOR:
            scene->setItem(new Resistor);
            break;
        case UI_BATTERY:
            scene->setItem(new Battery);
            break;
        case UI_WIRE:
            scene->setItem(new Wire);
            break;
        case UI_SWITCH:
            scene->setItem(new Switch);
            break;
        default:
            return;
    }

    scene->setMode(Scene::INSERT_ITEM);
}

```

### Incorporating the settings window

For this part, I first needed to simply add a small line of code to the main window to add the settings window:

```cpp
// Create and add the settings menu.
settingsMenu = new SettingsMenu();
layout->addWidget(settingsMenu);
```

I then made the scene call the MainWindow if a component was double clicked by creating this method which is automatically called by
QGraphicsScene:

```cpp
void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    // Is there anything selected?
    if(! selectedItems().empty()){
        // Get the first selected item.
        auto* item = selectedItems().at(0);

        // Is the item a UIComponent (it could be a line as this causes a crash)
        if(IS_TYPE(UIComponent, item)) {
            ((MainWindow *) parent())->itemDoubleClicked((UIComponent *) item);
        }
    }

    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}
```

This then calls the MainWindow itemDoubleClicked method which sets the interior of the settings window then clicks the
toggle button if the settings menu is not open yet:

```cpp
void MainWindow::itemDoubleClicked(UIComponent* item) {
    // Set the contents of the settingsmenu to the settingsbox of the item.
    settingsMenu->setInteriorLayout(item->settingsBox);

    // Open the menu if the menu is not opened.
    if(not settingsMenu->toggleButton->isChecked()){
        settingsMenu->toggleButton->click();
    }
}
```

Each component has a different set of methods to get the properties back out, e.g. the Wire, Resistor and Switch
are all children of the ResistiveElement class which has a method `double getResistance()`, which returns the
resistance of the component, and the Battery has a `double getVoltage()` method which returns the voltage.

Both methods use the child class to extract data from the settings menus, possibly run calculations, then return the result.

E.g. Wire has the following in the `getResistance()` method:

```cpp
double Wire::getResistance() {
    // Get the length, convert cm to m by dividing by 100.
    long double length = lengthSpinner->value()/100L;

    // Get the area, convert mm^2 to m^2 by dividing by 1000^2
    long double area = areaSpinner->value()/1e6L;

    // Get the material by converting the wire combobox to text and then indexing the resistivities map.
    std::string material = wireCombo->currentText().toStdString();
    long double resistivity = resistivities.at(material);

    // Use the resistivity formula p=(RA/l), rearranged to R=(pl)/A
    long double resistance = (resistivity*length)/area;

    return (double) resistance;
}
```

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

### Line drawing crash

When drawing a line at mouseReleaseEvent, the program would crash every time.

I realised this is because the items() function returns items at the point of the line start, but this includes the line, so I needed
to remove the line from the list of start items that were at the position.

Before:

```cpp
// Get all the items at the position of the start of the line.
QList<QGraphicsItem *> startItems = items(line->line().p1());

// Same as above but with the end point.
QList<QGraphicsItem *> endItems = items(line->line().p2());
```


After:

```cpp
// Get all the items at the position of the start of the line.
QList<QGraphicsItem *> startItems = items(line->line().p1());
if (startItems.count() != 0 && startItems.first() == line) {
    // Remove the line as the line starts at the start point of the line obviously.
    startItems.removeFirst();
}

// Same as above but with the end point.
QList<QGraphicsItem *> endItems = items(line->line().p2());
if (endItems.count() != 0 && endItems.first() == line) {
    endItems.removeFirst();
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

## Review

This turned out to be the largest prototype of my whole project due to the large amount of inseperable components.

It was fairly difficult, and there were many bugs that needed lots of time to diagnose, but eventually I solved almost all of them.


### Stakeholder Feedback

This was the first prototype that I thought was of enough completion to show my
stakeholder, and so I decided it was the correct time to have their feedback on the
project so far.

I asked the following questions to my physics teacher:

1. **On opening the program, did you understand what every section did?**
    Not really, but I am sure if it was explained to me it would be easier.
2. **Were you aware of how to place components onto the canvas?**
    No.
3. **Did you find the program ran quickly or slowly on your computer?**
    It started very quickly and seemed fast.
4. **Is there anything you found especially difficult or unusual?**
    Again, the app was hard to understand without guidance.
5. **Is there anything that you found missing?**
    There is nothing that I missed except more A-Level components.
6. **Do you see yourself using this to help teach your students?**
    Maybe when I understand how to use it I can teach my students how to learn with it.

Similar questions I asked my peers in A-Level physics:

1. **On opening the program, did you understand what every section did?**
    When I opened the app first everything looked OK, but when I tried to do anything
    it was complicated to understand.
2. **Were you aware of how to place components onto the canvas?**
    Eventually I did but it was not clear.
3. **Did you find the program ran quickly or slowly on your computer?**
    The program was very fast.
4. **Is there anything you found especially difficult or unusual?**
    Placing down circuits was hard, and drawing lines was strange because the
    lines did not connect to the right ends of the components.
    Another unusual thing was that I couldn't connect the components with the wire component
    by placing them together.
5. **Is there anything that you found missing?**
    No.
6. **Do you see this program aiding your learning in the future?**
    Possibly, if the problems are fixed.


From these responses, I deduced that the program was too hard to understand, so
I decided to include an instructions page in the program under the help menu with the following:

Menu:

![Tutorial Menu](images/tutorial_menu.png)

Popup:

![Tutorial Popup](images/tutorial.png)

I then asked the following question after sending off the improved prototype with guidance on
where the tutorial menu is.

To my physics teacher:

**After reading the tutorial menu, did you more easily understand how the program works?**

I now understand what to do to place down the circuits, there is no longer any part of the program that
I do not understand.

To my peers:

**After reading the tutorial menu, did you more easily understand how the program works?**

Yes. It is easier now.
