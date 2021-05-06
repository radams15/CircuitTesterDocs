# UI Design

## Main Window (Settings Open)

![Main Window Wireframe](images/main_window_wireframe.png)


- A:
	The toolbox. Contains the components that can be
	dragged onto the canvas.

- B:
	Components. These represent the QSceneItems that can be placed onto
	the canvas. These are buttons that use a smaller version of the image
	of the component.

- C:
	Expandable settings menu. This is expanded when the user double clicks
	on a component that is placed on the canvas. It will contain the different
	settings that each component will have.

- D:
	The canvas. This is the main QGraphicsScene that will allow the components to
	be dragged onto and moved about. It also handles the signals when a line is
	drawn between two components.

- E:
	Drag tool. This button is pressed when the user wishes to drag components around
	the canvas. This is the default action.

- F:
	Wire tool. This button is pressed when the user wishes to connect components together
	with a wire.

## Main Window (Settings Open)

![Main Window Wireframe With Settings Open](images/main_window_settings_wireframe.png)

- G:
	Settings menu. This is the expanded version of C (which is now facing the opposite
	direction). This contains the settings that vary for each component.

- H:
	Title. The name of the currently selected component.

- I:
	Setting slider. An example of the type of setting that can be set in the menu.
	A slider could be for battery voltage, or for resistivity of wires.

- J:
	Settings checkbox. An example of the type of setting that can be set in the menu.
	A checkbox could be to enable or disable a switch or battery.

\newpage

# Mockups

## Main Window

![Main Window Mockup](images/mockup_main.png)

This is what the user will see as they open up the program.

There is a simple yet fully featured scrollable bar at the side,
which is designed to hold the components.

The buttons at the top are to toggle the mouse action, with the
cursor for letting the user drag the components, and the line to
allow the user to connect components together.


## Main Window In Use

![Main Window Mockup With Diagram](images/mockup_diagram.png)

This is the same as above but with a circuit diagram layed out.

The images on the canvas are just larger versions of the images on the buttons,
so are easily recognisable.

\newpage

# Usability Features

My program is designed to be very easy to understand.

The toolbox is designed to show the components as large, colourful
pictures, which means that they are very easy to see. The toolbox buttons also
will generate a tooltip whenever they are hovered over with a mouse, which will
help users to make sure that the component they are clicking on is the correct one
for their usage.

The toolbox buttons are left-clicked once, then the user moves the cursor to the place they wish
to put the component. This is where the component is placed. This is a very simple
way to build up circuits, and to show the user exactly what they have created.

The canvas will be able to be zoomed in and out, allowing circuits to be examined
more closely, and to help those who have poor eyesight. This also means that the
circuits will be easier to view for everybody.

The layout is very simple, which links to the ease of usability section on the requirements.
