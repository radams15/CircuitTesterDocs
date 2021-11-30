# Stage 3 - Expanding Settings Window

The expanding settings window was a design decision I made as it is helpful in saving
space on the window.

This was a seperate stage as it was a distinct part of the main window design, and the animation section
looked to be fairly difficult to code, so I made a seperate part to write and test.

I had previously used an idea like this in a previous personal project, so I already had a somewhat working prototype
of a window that expanded and contracted with a button.

![Existing Project (Closed)](images/settings_existing_closed.png)

![Existing Project (Open)](images/settings_existing_open.png)

I had based this prototype off of a StackOverflow post [https://stackoverflow.com/questions/32476006/how-to-make-an-expandable-collapsable-section-widget-in-qt](https://stackoverflow.com/questions/32476006/how-to-make-an-expandable-collapsable-section-widget-in-qt), but had changed many things
about it such as:

### Changing the orientation:

In the original, the help box extended downwards, so I had to change this. First I placed the button to the left of the
content area by changing the grid packing:

Before:

```cpp
mainLayout.addWidget(&toggleButton, row, 0, 1, 1, Qt::AlignLeft);
mainLayout.addWidget(&headerLine, row++, 2, 1, 1);
mainLayout.addWidget(&contentArea, row, 0, 1, 3);
```

After:

```cpp
// Add the button at coordinates 0, 0.
mainLayout->addWidget(toggleButton, 0, 0, 1, 1, Qt::AlignTop);
// Add the changeable widget at coordinates 0, 1, i.e. to the right of the button.
mainLayout->addWidget(contentArea, 0, 1, 1, 1);
```

I then changed the arrows from down/up to left/right:

Before:

```cpp
toggleButton.setArrowType(checked ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
toggleAnimation.setDirection(checked ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
toggleAnimation.start();
```

After:

```cpp
// Change arrow depending on direction. E.g. right arrow to close if open, left arrow to open if closed.
toggleButton->setArrowType(checked? Qt::RightArrow : Qt::LeftArrow);

// Set the animation to move forward or backward, e.g. to open move the animation forward,
// to close move the animation backward.
toggleAnimation->setDirection(checked? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
// Begin the animation.
toggleAnimation->start();
```

I then made the animation move from minimum to maximum width instead of height:

Before:

```cpp
toggleAnimation.addAnimation(new QPropertyAnimation(this, "minimumHeight"));
toggleAnimation.addAnimation(new QPropertyAnimation(this, "maximumHeight"));
toggleAnimation.addAnimation(new QPropertyAnimation(&contentArea, "maximumHeight"));
```

After:

```cpp
toggleAnimation->addAnimation(new QPropertyAnimation(this, "minimumWidth"));
toggleAnimation->addAnimation(new QPropertyAnimation(this, "maximumWidth"));
toggleAnimation->addAnimation(new QPropertyAnimation(contentArea, "maximumWidth"));
```

### Improving the code

Being a small example, the original code was not especially good, so I improved upon it in a number of ways.

First, I replaced a lambda expression with a proper function, but also compromised by making toggleButton and toggleAnimation class
variables instead of a local ones.

Before:

```cpp
QObject::connect(&toggleButton, &QToolButton::clicked, [this](const bool checked) {
    toggleButton.setArrowType(checked ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
    toggleAnimation.setDirection(checked ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
    toggleAnimation.start();
});
```

After:

```cpp
SettingsMenu::SettingsMenu() : QWidget(nullptr){
    /** Other Code **/
    connect(toggleButton, &QToolButton::clicked, this, &SettingsMenu::startAnimation);
   /** Other Code **/
}

void SettingsMenu::startAnimation(bool checked) {
    // Change arrow depending on direction. E.g. right arrow to close if open, left arrow to open if closed.
    toggleButton->setArrowType(checked? Qt::RightArrow : Qt::LeftArrow);

    // Set the animation to move forward or backward, e.g. to open move the animation forward,
    // to close move the animation backward.
    toggleAnimation->setDirection(checked? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
    // Begin the animation.
    toggleAnimation->start();
}
```

Next, I changed the constructor to be less generic, as I needed my settings window to do one job only and not be used again.

Before:

```cpp
explicit Spoiler(const QString & title = "", const int animationDuration = 300, QWidget *parent = 0);
```

After:

```cpp
const int animationDuration = 300;

SettingsMenu();
```

## Bugs

### Changing Menu Contents

My settings window needed to be able to dynamically change content for each component, so I used a method to swap the contents of a QVBoxLayout with many different other QVBoxLayouts. This did not work, as this resulted in a bug where the code could not delete existing menus and eventually filled up with menus.

The problem was that the QVBoxLayout::children() function did not return layouts, only widgets, so my solution was to instead place widgets in the QVBoxLayout.

Old:

```cpp
void SettingsMenu::clear() {
    for(int i=0 ; i<innerLayout->children.length() ; i++){
        innerLayout->removeItem(innerLayout->children().at(i));
    }
}

void SettingsMenu::setInteriorLayout(QLayout* layout) {
    innerLayout->addLayout(layout);
}
```

New:

```cpp
void SettingsMenu::clear() {
    for(int i=0 ; i<innerLayout->count() ; i++){
        innerLayout->removeItem(innerLayout->itemAt(i));
    }
}

void SettingsMenu::setInteriorLayout(QLayout* layout) {
    clear();

    auto* newWidget = new QWidget;
    newWidget->setLayout(layout);

    innerLayout->addWidget(newWidget);
}
```

This worked well except for the next bug.

### Hiding Old Menus

With the above bug, after fixing, the old menus still showed, but did not work in any way, being the "ghost" of the widget.
This is because removing the item did not redraw the widget, so the widget was never hidden after deletion.

I fixed this by setting the widget to hidden before removing it, which corrected the issue.

New:

```cpp
void SettingsMenu::clear() {
    for(int i=0 ; i<innerLayout->count() ; i++){
        innerLayout->itemAt(i)->widget()->setHidden(true);
        innerLayout->removeItem(innerLayout->itemAt(i));
    }
}
```

## Validation

Effectively, since the settings window has only one public method with any parameters, setInteriorLayout, there was very little Validation to do.

The only validation needed was to ensure that the pointer passed in was not a null pointer, as the static code analysis of the IDE and compiler warnings would make sure that everything else was valid.

```cpp
void SettingsMenu::setInteriorLayout(QLayout* layout) {
    if(layout == nullptr){
        return;
    }

    clear();

    auto* newWidget = new QWidget;
    newWidget->setLayout(layout);

    innerLayout->addWidget(newWidget);
}
```

## Review

Overall, this section was more difficult than stage 2, but easier than stage 1. This part had a few methods so was modular,
but was only 1 class, as this stage did one job that I did not think would benefit from being split up into many classes.

Once again, this was part of the main window element of the design, and I believe that this section went very well.

At the end of the stage, the prototype looked like this:

![Stage 3 Closed](images/stage3_closed.png)

![Stage 3 Open](images/stage3_open.png)
