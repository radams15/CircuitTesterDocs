# Test Plans - White Box


## [Circuit](#circuit)

- `init` empty list:
	- Type: boundary
	- Data: [ ]
	- Expected: no error, as this is just no circuit

- `init` null:
	- Type: erroneous
	- Data: `NULL`
	- Expected: should return the function before any actual
		data is used



- `get_current_total` negative:
	- Type: invalid
	- Data: -1
	- Expected: returns a total of 0 as the node does not exist

- `get_current_total` large number:
	- Type: invalid
	- Data: 100 (if there are less than 100 componenets)
	- Expected: returns a total of 0 as node does not exist



- `get_currents` invalid sign:
	- Type: invalid
	- Data: sign = -2
	- Expected: controlled error thrown

- `get_currents` invalid sign:
	- Type: invalid
	- Data: sign = `NULL`
	- Expected: controlled error thrown



- `get_connected_nodes` invalid node:
	- Type: invalid
	- Data: 100 (if there are less than 100 componenets)
	- Expected: returns empty list

## [Element](#element)

- `contains`:
	- Type: normal
	- Data: Element(Resistor, 2, 3, 5).contains(2)
	- Expected: returns `True`

- `contains` non-existant node:
	- Type: normal
	- Data: 100 (where there is no node 100)
	- Expected: returns `False`

- `opposite` non-existant node:
	- Type: invalid
	- Data: 100 (if there are less than 100 nodes
		attached to this node - which is unlikely)
	- Expected: controlled error thrown

## [Equation](#equation)

- `apply` a or z are null:
	- Type: erroneous
	- Data: a = `NULL` or z = `NULL`
	- Expected: error thrown

- `apply` get_index function is null:
	- Type: erroneous
	- Data: a = `NULL` or z = `NULL`
	- Expected: controlled error thrown

- `apply` row non-existant node:
	- Type: invalid
	- Data: row = 100 (if there are less than 100 nodes
		attached to this node - which is unlikely)
	- Expected: controlled error thrown

## [Solution](#solution)

- `equals` null solution:
	- Type: invalid
	- Data: `NULL`
	- Expected: returns `False`

- `equals` non-equal solution:
	- Type: valid
	- Data: `NULL`
	- Expected: returns `False`

- `equals` equal solution:
	- Type: valid
	- Data: `NULL`
	- Expected: returns `True`


- `get_voltage` unknown variable:
	- Type: invalid
	- Data: New element that is not in any solution list
	- Expected: controlled error thrown


## [Unknown](#unknown)

- `equals` other is null:
	- Type: erroneous
	- Data: other = `NULL`
	- Expected: return `false`

- `equals` other is of other type:
	- Type: boundary
	- Data: this = `UnknownCurrent` other = `UnknownVoltage`
	- Expected: returns `False`


\newpage


# Test Plans - Black Box

## Test 1 - Resistors in parallel

![The circuit to be tested](images/blackbox_1.png)

This tests to see if current split between two parallel resistors
(20.0 $\Omega$ and 10.0 $\Omega$) occurs, and if the current split has
the correct values of 0.45A at the first resistor, and 1.35A when
they join back together. The battery has an arbitrary voltage of 9.0V.

\newpage

## Test 2 - Batteries in series

![The circuit to be tested](images/blackbox_2.png)

This tests to see if two 9.0V batteries have a total voltage of 18.0V
when placed in series.

\newpage

## Test 2 - Batteries in parallel

![The circuit to be tested](images/blackbox_3.png)

This tests to see is two 9.0V batteries have a total voltage of 9.0V,
and a resistor of resistance 10.0 $\Omega$ causes a current of 0.9A.

The two parallel batteries should have the same characteristics as just one
9.0V battery.

\newpage

## Test 3 - Place down an item

This simply tests if a component can be placed onto the canvas.

## Test 4 - Move an item

Can an item be moved around the canvas.

## Test 5 - Delete an item

Can an item be deleted from the canvas.

## Test 6 - Save/load

Save a circuit to a file, close the program, then load the file again and check they
are the same.

## Test 7 - Export/Import

Save a circuit, export it to the desktop, then try to import the circuit on a different
device by emailing the file, importing it, then loading the file.

## Test 8 - Editing a save file

Save a circuit with a wire component, change the component material to a random string,
change the coordinates to both be -1. Load the circuit and see whether or not the program
corrects the problems.
