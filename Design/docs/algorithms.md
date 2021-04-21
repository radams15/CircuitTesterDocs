# Algorithms

The most complex part of my program is the circuit simulation code, which uses linear algebra
to find the currents and voltages at different parts of the circuit.

I will use modified nodal analysis (MNA) and Kirchhoff's laws to work out currents and
voltages at different nodes and vertices of the circuit.


## Convert circuits into matrices

![Algorithm Decomposition](images/algorithms.png)


\newpage


## Circuit

![Circuit Class](images/Class_Circuit.png)


### Initialiser

%include_pc(pseudocode/circuit_init.txt)


### Solver

%include_pc(pseudocode/circuit_solve.txt)


### Miscellaneous functions

%include_pc(pseudocode/circuit_misc.txt)


\newpage


## Element

![Element Class](images/Class_Element.png)


\newpage

## Equation

![Equation Class](images/Class_Equation.png)

\newpage

## Solution

![Solution Class](images/Class_Solution.png)

\newpage

## Term

![Term Class](images/Class_Term.png)

\newpage

## Unknown

![Element Class](images/Class_Unknown.png)

These are simply elements for which the voltage or current has not yet been calculated.

Both UnknownVoltage and UnknownCurrent are under the Unknown class, so that they can both be
stored in the same arrays as pointers.

The Type attribute allows functions to know if they are an UnknownVoltage or an UnknownCurrent.

\newpage
