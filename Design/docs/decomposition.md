# Decomposition

![Decomposition](images/decomposition.png)


## Justifications


### Circuit runner
because the back end logic is totally separate to the front end display, so
these need to be separated into seperate sections of the program.

This is also where the linear algebra is done, so I would like to keep the library
imports in one class only.


### User interface

This will be purely for logic related to the GUI. This will be the only area where I
will be importing the QT libraries, as again I wish to keep libraries separate.


### Menubar

This will be the part that deals with the bar at the top of the window.
The appearance is slightly different depending on the operating system used,
as Windows has the menubar in the window, with a file and a item menu, whereas
MacOS has the menubar in the top bar of the desktop, and replaces the file and
help menus with a general menu for the application, as seen below:

![MacOS Menubar](images/titlebar_mac.png)

![Windows Menubar](images/titlebar_win.png)

![Linux Menubar](images/titlebar_lin.png)

<br><br>

### Drag and drop canvas

This is the main canvas, so all aspects of the actual circuit go here such as placing
down components, connecting them and removing them. Each component is a component class
that can draw itself and can also conduct some mathematics.

### Components toolbox

This is the scrollable toolbox that contains the components that can be dragged onto the
canvas. This is separate to the canvas because this contains only buttons that create the
components, whereas the canvas contains the actual component classes.
