# Algorithms

The most complex part of my program is the circuit simulation code, which uses linear algebra
to find the currents and voltages at different parts of the circuit.

I will use modified nodal analysis (MNA) and Kirchhoff's laws to work out currents and
voltages at different nodes and vertices of the circuit.


## Convert circuits into matrices

![Algorithm Decomposition](images/algorithms.png)


\newpage

## Main_Window


![Main Window Class](images/Class_MainWindow.png)

This is the class that acts as the main GUI for my program.

It holds references to a [Scene](#scene) object that has been initialised to hold
the components for the current circuit.

The functions `create_toolbox`, `create_menus`, and `create_toolbar` are simply functions that
create their respective classes and add them to the main window, without any complex algorithms.


### Find Shortest Path

This function finds the shortest path between two components by interpreting the
circuit as a mathematical graph.

This means that the paths can be used to set the node numbers of the components.

%include_pc(pseudocode/find_shortest_path.txt)

### Run Simulation

This function will set the n0 and n1 value for each component, allowing the program to
then work out the voltages and currents at each point of the circuit.

%include_pc(pseudocode/run_simulation.txt)

\newpage

## Circuit

![Circuit Class](images/Class_Circuit.png)

This class is used to hold a circuit as an object. It is designed
so that it takes in a list of [Element](#element) classes, and splits
them up into the class attributes batteries, resistors and current_sources, which
are then used throughout the program.

This class has only 2 public methods including the initialiser,
and the other majority are private attributes and methods.


### Initialiser

%include_pc(pseudocode/circuit_init.txt)


### Solver

%include_pc(pseudocode/circuit_solve.txt)


### Miscellaneous functions

%include_pc(pseudocode/circuit_misc.txt)


\newpage


## Element

![Element Class](images/Class_Element.png)

This is the parent class for all elements.

This has values for the nodes, the value (which is a resistance, a current,
a voltage, etc depending on the child class), and a type which is set
by any child class. It is essentially an interface class.

The children are a resistor, a battery and a current source, of which each acts
differently inside the [Circuit](#circuit) class.

A switch is the child of resistor, as I can say that when the switch is open,
the resistance is infinitely large, and when the switch is closed, the resistance is
almost zero.

### Pseudocode for class

%include_pc(pseudocode/element.txt)

\newpage

## Equation

![Equation Class](images/Class_Equation.png)

This stores an equation of x = y + z.

Value is the known x value, and terms is a list of [Terms](#term),
that equal value.

### Pseudocode for class methods

%include_pc(pseudocode/equation.txt)

\newpage

## Solution

![Solution Class](images/Class_Solution.png)

### Pseudocode for class methods

%include_pc(pseudocode/solution.txt)

\newpage

## Term

![Term Class](images/Class_Term.png)

This stores a term with a sign, and a variable of type [Unknown](#unknown)

This has no pseudocode as it it purely a structure.

In programming languages with a `struct` type, this is a `struct`.
Otherwise it is a `class` with no methods.

\newpage

## Unknown

![Element Class](images/Class_Unknown.png)

These are simply elements for which the voltage or current has not yet been calculated.

Both UnknownVoltage and UnknownCurrent are under the Unknown class, so that they can both be
stored in the same arrays as pointers.

The Type attribute allows functions to know if they are an UnknownVoltage or an UnknownCurrent.

### Unknown Voltage

%include_pc(pseudocode/unknown_voltage.txt)

### Unknown Current

%include_pc(pseudocode/unknown_current.txt)

\newpage
