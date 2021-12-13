# Test Plans - White Box


## [Circuit](#circuit)

+---------------------+--------------+-----------+-------------------------------+-----------------------------------------------+
| Method              | Name         | Type      | Data                          | Expected                                      |
+---------------------+--------------+-----------+-------------------------------+-----------------------------------------------+
| init                | empty list   | boundary  | [ ]                           | no error, just no circuit.                    |
+---------------------+--------------+-----------+-------------------------------+-----------------------------------------------+
| init                | null         | erroneous | NULL                          | should return before any actual data is used. |
+---------------------+--------------+-----------+-------------------------------+-----------------------------------------------+
| get_current_total   | negative     | invalid   | -1                            | returns a total of 0 as node does not exist.  |
+---------------------+--------------+-----------+-------------------------------+-----------------------------------------------+
| get_current_total   | large number | invalid   | 100                           | returns total of 0 as node does not exist.    |
|                     |              |           | (if less than 100 components) |                                               |
+---------------------+--------------+-----------+-------------------------------+-----------------------------------------------+
| get_currents        | invalid sign | invalid   | sign = -2                     | controlled error thrown.                      |
+---------------------+--------------+-----------+-------------------------------+-----------------------------------------------+
| get_currents        | invalid sign | invalid   | sign = NULL                   | controlled error thrown.                      |
+---------------------+--------------+-----------+-------------------------------+-----------------------------------------------+
| get_connected_nodes | invalid node | invalid   | 100                           | returns empty list.                           |
|                     |              |           | (if less than 100 components) |                                               |
+---------------------+--------------+-----------+-------------------------------+-----------------------------------------------+

## [Component](#component)

+----------+-------------------+----------+----------------------------------------+--------------------------+
| Method   | Name              | Type     | Data                                   | Expected                 |
+----------+-------------------+----------+----------------------------------------+--------------------------+
| contains | normal            | expected | Component(Resistor, 2, 3, 5).contains(2) | returns `true`.          |
+----------+-------------------+----------+----------------------------------------+--------------------------+
| contains | non-existent node | normal   | 100 (when no node 100)                 | returns `false`.         |
+----------+-------------------+----------+----------------------------------------+--------------------------+
| opposite | non-existent node | invalid  | 100 (when less than 100 nodes)         | controlled error thrown. |
+----------+-------------------+----------+----------------------------------------+--------------------------+

## [Equation](#equation)

+--------+-----------------------+-----------+----------------------------+--------------------------+
| Method | Name                  | Type      | Data                       | Expected                 |
+--------+-----------------------+-----------+----------------------------+--------------------------+
| apply  | a or z are NULL       | erroneous | a = NULL or z = NULL       | controlled error thrown. |
+--------+-----------------------+-----------+----------------------------+--------------------------+
| apply  | get_index method NULL | erroneous | get_index = NULL           | controlled error thrown. |
+--------+-----------------------+-----------+----------------------------+--------------------------+
| apply  | non-existent node     | invalid   | row = 100                  | controlled error thrown. |
|        |                       |           | (when less than 100 nodes) |                          |
+--------+-----------------------+-----------+----------------------------+--------------------------+

## [Solution](#solution)

+-------------+--------------------+---------+-----------------------------------+--------------------------+
| Method      | Name               | Type    | Data                              | Expected                 |
+-------------+--------------------+---------+-----------------------------------+--------------------------+
| equals      | null solution      | invalid | NULL                              | returns `false`.         |
+-------------+--------------------+---------+-----------------------------------+--------------------------+
| equals      | non-equal solution | valid   | NULL                              | returns `false`.         |
+-------------+--------------------+---------+-----------------------------------+--------------------------+
| equals      | equal solution     | valid   | different pointer to same object. | returns `true`.          |
+-------------+--------------------+---------+-----------------------------------+--------------------------+
| get_voltage | unknown variable   | invalid | new component not in solution list. | controlled error thrown. |
+-------------+--------------------+---------+-----------------------------------+--------------------------+

## [Unknown](#unknown)

+--------+------------------------+-----------+------------------------------------------------------+------------------+
| Method | Name                   | Type      | Data                                                 | Expected         |
+--------+------------------------+-----------+------------------------------------------------------+------------------+
| equals | other is null          | erroneous | NULL                                                 | returns `false`. |
+--------+------------------------+-----------+------------------------------------------------------+------------------+
| equals | other is of other type | boundary  | this = `UnknownCurrent` and other = `UnknownVoltage` | returns `false`. |
+--------+------------------------+-----------+------------------------------------------------------+------------------+


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

## Test 3 - Batteries in parallel

![The circuit to be tested](images/blackbox_3.png)

This tests to see is two 9.0V batteries have a total voltage of 9.0V,
and a resistor of resistance 10.0 $\Omega$ causes a current of 45A.

The two parallel batteries should have the same characteristics as just one
9.0V battery.

\newpage

## Test 4 - Place down an item

This simply tests if a component can be placed onto the canvas.

## Test 5 - Move an item

Can an item be moved around the canvas.

## Test 6 - Delete an item

Can an item be deleted from the canvas.

## Test 7 - Save/load

Save a circuit to a file, close the program, then load the file again and check they
are the same.

## Test 8 - Export/Import

Save a circuit, export it to the desktop, then try to import the circuit on a different
device by emailing the file, importing it, then loading the file.

## Test 9 - Editing a save file

Save a circuit with a wire component, change the component material to a random string,
change the coordinates to both be -1. Load the circuit and see whether or not the program
corrects the problems.
