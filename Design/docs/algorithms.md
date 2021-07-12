# Algorithms

The most complex part of my program is the circuit simulation section, which uses linear algebra and matrices
to find the currents and voltages at different parts of the circuit.

I will use modified nodal analysis (MNA) and Kirchhoff's current and voltage laws to work out currents and
voltages at different nodes and vertices of the circuit.

Throughout the explanation this circuit will be used as an example.

![Example Circuit](images/example_circuit.png)


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

### Finding terms

This algorithm is used to find the terms entering or leaving a node.

This simply follows the following rules:

##### For each battery with a node on the requested side:

- Return a term where the coefficient is the sign (-1 for input, +1 for output because of conventional current) and the variable is the unknown current of the battery, e.g. for a battery exiting node 2 the term would be $+1x$ where $x$ is the battery current.

##### For each resistor with a node on the requested side:

- Return 2 terms.

- The first is a term of ${{S}\over{R}} V$ where $S$ is the sign, $R$ is the resistance of the resistor, and $V$ is the unknown voltage.

- The second is a term of ${-{{S}\over{R}}} V$ where $S$ is the sign, $R$ is the resistance of the resistor, and $V$ is the unknown voltage.

This results in the following terns:

- Node 1 => $-I_{0\rightarrow1}, -{{V_1}\over{4}}, {{V_2}\over{4}}$
- Node 2 => ${{V_2}\over{4}}, -{{V_1}\over{4}}, -{{V_3}\over{3}}, {{V_2}\over{3}}, -{{V_3}\over{6}},{{V_2}\over{6}}$
- Node 3 => ${{V_3}\over{3}}, -{{V_2}\over{3}}, {{V_3}\over{6}}, -{{V_2}\over{6}}, -{{V_0}\over{10}}, {{V_3}\over{10}}$

%include_pc(pseudocode/find_terms.txt)

### Making equations

This is where the algebraic equations that will be placed into the matrices are created.

First, each reference node is assigned a voltage of $0V$, as they are what all
the other nodes in the circuit are compared to.

Next, the program iterates over all non-reference nodes, for each [finding the terms](#finding-terms) that
enter and leave the nodes, creating an equation where
all the nodes entering and leaving the equation sum to 0.

Each battery also has an equation where the voltage of the node before the battery is
the negative of the battery voltage, and the node after the battery has a voltage of the
battery voltage, e.g. for a $9V$ battery, the node before has a voltage of $-9V$, and
the node after has a voltage of $+9V$.

This results in the following equations for our example:

- Node 0 => Reference node - no equations.
- Node 1 => $-I_{0\rightarrow1} + -{{V_1}\over{4}} + {{V_2}\over{4}} = 0$
- Node 2 => ${{V_2}\over{4}} + -{{V_1}\over{4}} + -{{V_3}\over{3}} + {{V_2}\over{3}} + -{{V_3}\over{6}} + {{V_2}\over{6}} = 0$
- Node 3 => ${{V_3}\over{3}} + -{{V_2}\over{3}} + {{V_3}\over{6}} + -{{V_2}\over{6}} + -{{V_0}\over{10}} + {{V_3}\over{10}} 0 0$
- Battery 1 => $-V_0 + V_1 = 6$

%include_pc(pseudocode/make_equations.txt)

### Miscellaneous functions

%include_pc(pseudocode/circuit_misc.txt)


### Solver

This is where the equations are placed into matrices.

First, the [equations are created](#making-equations), then a list of unknowns is created
by forming a list of unknown currents, and the list of unknown voltages at each node of the circuit.

The list of unknowns for our example is: $[I_{0\rightarrow1}, V_0, V_1, V_2, V_3]$.

Next, the empty matrices $A$ and $z$ are created. $A$ is the number of equations by (the number of nodes + the number of batteries), and $z$ is the number of equations by 1.

For our example this is what is created:

A: $$ \begin{bmatrix}
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 
\end{bmatrix}  $$

Z: $$ \begin{bmatrix}
0 \\
0 \\
0 \\
0 \\
0 
\end{bmatrix}  $$

Next, each equation is individually added to the matrix, starting with the equation for node 0, adding the equation
for each node until all the equations are added, and since the equations were made in order of nodes, the equation list
is iterated over to add to the matrices.

For every row of the matrix, the equation at that row is added. The numerical value of the equation is added to the correct
column on matrix $z$ (the column is the node number).
For each term in the equation, the coefficient of the term is placed on the matrix $A$
on the current row at the column of the index of the term unknown in the unknowns array.
The value is added to any existing data.

For our example:

Row 0 has only our reference nodes, with an equation of $V_0 = 0$:

- $0$ is placed at $z[0, 0]$
- $1$ is placed at $A[1, 0]$
- A: $$ \begin{bmatrix}
0 & \color{red}1 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 
\end{bmatrix}  $$
- Z: $$ \begin{bmatrix}
0 \\
0 \\
0 \\
0 \\
0 
\end{bmatrix}  $$

Row 1 has the equation ${{V_2}\over{4}} + -{{V_1}\over{4}} + -{{V_3}\over{3}} + {{V_2}\over{3}} + -{{V_3}\over{6}} + {{V_2}\over{6}} = 0$:

- $0$ is placed at $z[0, 1]$
- $-1$ is added to $A[0, 1]$
- ${-{1}\over{4}}$ is added to $A[3, 1]$
- ${{1}\over{4}}$ is added to $A[2, 1]$
- A: $$ \begin{bmatrix}
0 & 1 & 0 & 0 & 0 \\
\color{red}-1 & 0 & \color{red}{{1}\over{4}} & \color{red}{-{{1}\over{4}}} & 0 \\
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 
\end{bmatrix}  $$
- Z: $$ \begin{bmatrix}
0 \\
0 \\
0 \\
0 \\
0 
\end{bmatrix}  $$

Row 2 has the equation ${{V_2}\over{4}} + -{{V_1}\over{4}} + -{{V_3}\over{3}} + {{V_2}\over{3}} + -{{V_3}\over{6}} + {{V_2}\over{6}} = 0$:

- $0$ is placed at $z[0, 2]$
- ${{1}\over{4}}$ is added to $A[3, 2]$
- $-{{1}\over{4}}$ is added to $A[2, 2]$
- $-{{1}\over{3}}$ is added to $A[4, 2]$
- ${{1}\over{3}}$ is added to $A[3, 2]$
- $-{{1}\over{6}}$ is added to $A[4, 2]$
- ${{1}\over{6}}$ is added to $A[3, 2]$
- A: $$ \begin{bmatrix}
0 & 1 & 0 & 0 & 0 \\
-1 & 0 & {{1}\over{4}} & -{{1}\over{4}} & 0 \\
0 & 0 & \color{red}{-{{1}\over{4}}} & \color{red}{{{1}\over{4}} + {{1}\over{3}} + {{1}\over{6}}} & \color{red}{-{{1}\over{3}} -{{1}\over{6}}} \\
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 
\end{bmatrix}  $$
- Z: $$ \begin{bmatrix}
0 \\
0 \\
0 \\
0 \\
0 
\end{bmatrix}  $$

Row 3 has the equation ${{V_3}\over{3}} + -{{V_2}\over{3}} + {{V_3}\over{6}} + -{{V_2}\over{6}} + -{{V_0}\over{10}} + {{V_3}\over{10}} 0 0$:

- $0$ is placed at $z[0, 3]$
- ${{1}\over{3}}$ is added to $A[4, 3]$
- $-{{1}\over{3}}$ is added to $A[3, 3]$
- ${{1}\over{6}}$ is added to $A[4, 3]$
- $-{{1}\over{6}}$ is added to $A[3, 3]$
- $-{{1}\over{10}}$ is added to $A[1, 3]$
- ${{1}\over{10}}$ is added to $A[4, 3]$
- A: $$ \begin{bmatrix}
0 & 1 & 0 & 0 & 0 \\
-1 & 0 & {{1}\over{4}} & -{{1}\over{4}} & 0 \\
0 & 0 & -{{1}\over{4}} & {{1}\over{4}} + {{1}\over{3}} + {{1}\over{6}} & -{{1}\over{3}} -{{1}\over{6}} \\
0 & \color{red}{-{{1}\over{10}}} & 0 & \color{red}{-{{1}\over{3}} -{{1}\over{6}}} & \color{red}{{{1}\over{3}} + {{1}\over{6}} + {{1}\over{10}}} \\
0 & 0 & 0 & 0 & 0 
\end{bmatrix}  $$
- Z: $$ \begin{bmatrix}
0 \\
0 \\
0 \\
0 \\
0 
\end{bmatrix}  $$

Row 4 has only the battery equation of $-V_0 + V_1 = 6$:

- $6$ is placed at $z[0, 4]$
- $-1$ is added to $A[1, 4]$
- $1$ is added to $A[2, 4]$
- A: $$ \begin{bmatrix}
0 & 1 & 0 & 0 & 0 \\
-1 & 0 & {{1}\over{4}} & -{{1}\over{4}} & 0 \\
0 & 0 & -{{1}\over{4}} & {{1}\over{4}} + {{1}\over{3}} + {{1}\over{6}} & -{{1}\over{3}} -{{1}\over{6}} \\
0 & -{{1}\over{10}} & 0 & -{{1}\over{3}} -{{1}\over{6}} & {{1}\over{3}} + {{1}\over{6}} + {{1}\over{10}} \\
0 & \color{red}{-1} & \color{red}{1} & 0 & 0 
\end{bmatrix}  $$
- Z: $$ \begin{bmatrix}
0 \\
0 \\
0 \\
0 \\
\color{red}{6} 
\end{bmatrix}  $$


When we solve $Ax = z$, the matrix $x$ is returned: $$ \begin{bmatrix}
0.375 \\
0 \\
6 \\
4.5 \\
3.75 
\end{bmatrix}  $$

Next, we must extract the results from our matrix. We create a dictionary of node:voltage for
our circuit by reading the index of each unknown voltage from the unknowns list from $x$.
E.g. the index in the unknowns list of node 3 ($V_3$) is 4, and $x[0, 4] = 3.75V$, so node 3 has a voltage of $3.75V$
This results in the following voltage map: $[0:0, 1:6, 2:4.5, 3:3.75]$

We also extract currents from the matrix by finding the index of the unknown current as above with the unknown voltage.
E.g. the index in the unknowns list of the battery ($I_{0\rightarrow1}$) is 0, and $x[0, 0] = 0.375A$, so the battery has
a current of $0.375A$.


%include_pc(pseudocode/circuit_solve.txt)


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
