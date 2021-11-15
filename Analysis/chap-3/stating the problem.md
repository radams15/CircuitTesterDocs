# Stating the problem


## The problem

GCSE physics students in DGSB require knowledge of circuits as part of their
course, but unfortunately the physical equipment to teach many of these circuits
is expensive, limited in the school, is easily broken, and home learning
is not possible as equipment cannot be taken outside of school. Most students
simply learn about these circuits from an image in a textbook.


## The solution

A circuit simulator program that demonstrates
simple electrical circuits to determine if they will work, and allows students
to check if they function correctly would be an ideal solution.

The program would show current split, resistance
over distance, voltages, etc, as this is not possible inside school with
their present equipment.

The program is perfect for this problem as it is:

 - Cheaper to make than to purchase new circuit equipment
 - There are no user limits, so can be freely distributed to as many students as
	possible (even on devices at home), 
 - It is difficult to break as bugs can be easily fixed if identified.

This program would allow students to experiment with circuits at home as well,
as usually students cannot take equipment home because there is a limited amount,
and they are also quite delicate.


## Justification for computational solution

The physics calculations are an ideal fit for a computational solution.
This is because the amount of maths required is significant, so would be time-consuming for
anybody to do to just demonstrate the physics.

These calculations are not required by GCSE
level physics, so would be difficult to be shown manually by a teacher who does not need to
know or explain the equations. Showing the values of current and voltage at any point is
sufficient at GCSE level.

I will use the following computational methods:

### Abstraction

The user will not be aware of any of the processes happening behind the scenes,
as the calculations are beyond the needs of the stakeholders. The user will simply
be able to view and place components on the canvas, and a button will be able to be pressed
to run the circuit.


### Polymorphism

The main element of polymorphism is the component class. This will branch off
into various other components, with each having different calculations they need
to perform. Components will be able to all be stored in lists of components,
but when individually used they will be instances of individual components with
the same public methods.

### Decomposition / Divide and Conquer

I will decompose the project into much smaller sections, making them easier
to program individually. I will write several small programs to solve the
decomposed sub-programs, and then will be able to use this existing code in
my main project.

### Concurrence

My project will need to run the GUI and the simulation aspects at the same time,
so that the user interface does not freeze when the circuit is computed.

### Iteration

My software needs to follow the circuit, using many algorithms, which require loops
and complex calculations.

### Modelling

My program will model the real-life functions of various circuits, with the goal of
helping students to learn their physics lessons with ease. This will make the difficult
job of manually computing and explaining circuits far easier, for the teacher and
the students.
