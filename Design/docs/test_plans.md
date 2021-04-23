# Test Plans

## [Circuit](#circuit)

- `init` empty list:
	- Type: boundary.
	- Data: [].
	- Expected: no error, as this is just no circuit.

- `init` null:
	- Type: erroneous.
	- Data: NULL.
	- Expected: should return the function before any actual
		data is used.

- `get_current_source_total` negative:
	- Type: invalid
	- Data: -1
	- Expected: returns a total of 0 as the node does not exist.

- `get_current_source_total` large number:
	- Type: invalid
	- Data: 100 (if there are less than 100 componenets)
	- Expected: returns a total of 0 as node does not exist

- `get_current_terms` invalid sign:
	- Type: invalid
	- Data: sign=-2
	- Expected: error thrown

- `get_current_terms` invalid sign:
	- Type: invalid
	- Data: sign=NULL
	- Expected: error thrown

- `get_connected_node_ids` invalid node:
	- Type: invalid
	- Data: 100 (if there are less than 100 componenets)
	- Expected: returns empty list

## [Element](#element)

## [Equation](#equation)

## [Solution](#solution)

## [Unknown](#unknown)
