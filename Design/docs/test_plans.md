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



- `get_current_source_total` negative:
	- Type: invalid
	- Data: -1
	- Expected: returns a total of 0 as the node does not exist

- `get_current_source_total` large number:
	- Type: invalid
	- Data: 100 (if there are less than 100 componenets)
	- Expected: returns a total of 0 as node does not exist



- `get_current_terms` invalid sign:
	- Type: invalid
	- Data: sign = -2
	- Expected: controlled error thrown

- `get_current_terms` invalid sign:
	- Type: invalid
	- Data: sign = `NULL`
	- Expected: controlled error thrown



- `get_connected_node_ids` invalid node:
	- Type: invalid
	- Data: 100 (if there are less than 100 componenets)
	- Expected: returns empty list

## [Element](#element)

- `contains_node` non-existant node:
	- Type: normal
	- Data: 100
	- Expected: returns `False`

- `get_opposite_node` non-existant node:
	- Type: invalid
	- Data: 100 (if there are less than 100 nodes
		attached to this node - which is unlikely)
	- Expected: controlled error thrown

## [Equation](#equation)

- `stamp` a or z are null:
	- Type: erroneous
	- Data: a = `NULL` or z = `NULL`
	- Expected: error thrown

- `stamp` get_index function is null:
	- Type: erroneous
	- Data: a = `NULL` or z = `NULL`
	- Expected: controlled error thrown

- `stamp` row non-existant node:
	- Type: invalid
	- Data: row = 100 (if there are less than 100 nodes
		attached to this node - which is unlikely)
	- Expected: controlled error thrown

## [Solution](#solution)

- `approx_equals` null solution:
	- Type: invalid
	- Data: `NULL`
	- Expected: returns `False`

- `approx_equals` non-equal solution:
	- Type: valid
	- Data: `NULL`
	- Expected: returns `False`

- `approx_equals` equal solution:
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



# Test Plans - Black Box

## Test 1 - Resistors in parallel:

![The circuit to be tested](images/blackbox_1.png)

This tests to see if current split between two parallel resistors
(20.0 $\ohm$ and 10.0 $\ohm$) occurs, and if the current split has
the correct values of 0.45A at the first resistor, and 1.35A when
they join back together. The battery has an arbitrary voltage of 9.0V.

## Test 2 - Batteries in series:

![The circuit to be tested](images/blackbox_2.png)

This tests to see if two 9.0V batteries have a total voltage of 18.0V
when placed in series.

## Test 2 - Batteries in parallel:

![The circuit to be tested](images/blackbox_3.png)

This tests to see is two 9.0V batteries have a total voltage of 9.0V,
and a resistor of resistance 10.0 $\ohm$ causes a current of 0.9A.

The two parallel batteries should have the same characteristics as just one
9.0V battery.
