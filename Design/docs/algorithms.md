# Algorithms

The most complex part of my program is the circuit simulation code, which uses linear algebra
to find the currents and voltages at different parts of the circuit.

I will use modified nodal analysis (MNA) and Kirchhoff's laws to work out currents and
voltages at different nodes and vertices of the circuit.


## Convert circuits into matrices


`images/algorithms.png`{.include}


### Create matrix A and z


``` VB.NET

`pseudocode/make_matrices.txt`{.include}

```


### Solve the matrices


``` VB.NET

`pseudocode/solve_matrices.txt`{.include}

```
