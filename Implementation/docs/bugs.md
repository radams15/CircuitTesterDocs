# Bugs

## Save/Load system:

### Getting the username.

To save the circuits in a standard place, my program needed to find the home directory
of the user. This involved writing seperate code for the API of each targeted OS.

Luckily because Linux and MacOs are unix based, I could use `unistd.h`. For Windows I used
`windows.h`.

According to many websites (e.g. [Here](https://stackoverflow.com/questions/142508/how-do-i-check-os-with-a-preprocessor-directive)), this OS
could be determined using the preprocessor at compile time like this:

``` cpp
#if defined(__unix)
    #include <unistd.h>
    #include <pwd.h>
#elif defined(_WIN32)
    #include <windows.h>
    #include <Lmcons.h>
#endif
```

But this did not work for MacOS, leading to the project not compiling on MacOS, but working on Linux and Windows.

The solution was to add an extra check to make the new code as follows:

``` cpp
#if defined(__unix) || defined(__APPLE__)
    #include <unistd.h>
    #include <pwd.h>
#elif defined(_WIN32)
    #include <windows.h>
    #include <Lmcons.h>
#endif
```

This now works.

## Main Window

### Initial Simulation Run

Running the simulation when there are no components on the QGraphicsScene would cause the program to segfault.

```cpp
void MainWindow::runSimulation() {
    AnalysisMapper mapper(scene->items().toStdList());
}
```

![Segfault](images/segfault_1.png)

The solution was to check if the scene was empty before running, then aborting if this is the case.

```cpp
void MainWindow::runSimulation() {
    if(scene->items().empty()){
        return;
    }

    AnalysisMapper mapper(scene->items().toStdList());
}
```

## Settings Menu

### Changing Menu Contents

My settings window needed to be able to dynamically change content for each component, so I used a method to swap the contents of
a QVBoxLayout with many different other QVBoxLayouts. This did not work, as this resulted in a bug where the code could not delete existing menus
and eventually filled up with menus.

The problem was that the QVBoxLayout::children() function did not return layouts, only widgets, so my solution was to instead place
widgets in the QVBoxLayout. This worked well except for the below bug.

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

### Hiding Old Menus

With the above bug, after fixing, the old menus still showed, but did not work in any way, being the "ghost" of the widget.
I fixed this by setting the widget to hidden before removing it, which solved the issue.

New:

```cpp
void SettingsMenu::clear() {
    for(int i=0 ; i<innerLayout->count() ; i++){
        innerLayout->itemAt(i)->widget()->setHidden(true);
        innerLayout->removeItem(innerLayout->itemAt(i));
    }
}
```
