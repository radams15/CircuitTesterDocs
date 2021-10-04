# Post-Developmental Testing

## Test 1 - Resistors in parallel

![Resistors in parallel](images/wb1.png)

This shows the current is split unevenly between the two resistors because of different resistances, with half as much current going to the left resistor than the middle resistor, and the right-most resistor that acts as a ammeter shows the total current of the 2 other resistors combines to get a total current of 1.3A.

## Test 2 - Batteries in series

![Batteries in series](images/wb2.png)

This shows that 2 9V batteries have a total voltage of 18V when in series.

## Test 3 - Batteries in parallel

![Batteries in series](images/wb3a.png)

![Batteries in series](images/wb3b.png)

This shows that the result of test 3 is correct and matches the required values of 45A in both the first and second circuits.

## Tests 4-8

- [x] Can place down an item.
- [x] Can move an item.
- [x] Can delete an item.
- [x] Can save and load circuits.
- [x] Can import/export a circuit.

## Test 9 - Editing a save file.

This test is to make sure that any corrupted files are fixed by the program without any crashes that could render save files unuseable.

I created this circuit, and saved it as test9:

![Test file](images/wb9a.png)

This resulted in the following save file content:

```javascript
{
    "name": "test9",
    "parts": [
        {
            "component": {
                "pos": [
                    320.0,
                    240.0
                ],
                "state": true,
                "type": 2,
                "voltage": 3.0
            },
            "connections": [
                5
            ],
            "id": 4
        },
        {
            "component": {
                "area": 0.5,
                "length": 2.0,
                "material": "Carbon",
                "pos": [
                    340.0,
                    520.0
                ],
                "type": 3
            },
            "connections": [
                4
            ],
            "id": 5
        }
    ]
}
```

I edited the file to the following content:

```javascript
{
    "name": "test9",
    "parts": [
        {
            "component": {
                "pos": [
                    320.0,
                    240.0
                ],
                "state": true,
                "type": 2,
                "voltage": 3.0
            },
            "connections": [
                5
            ],
            "id": 4
        },
        {
            "component": {
                "area": 0.5,
                "length": 2.0,
                "material": "gdgssjdgsnjgsd",
                "pos": [
                    -1,
                    -1
                ],
                "type": 3
            },
            "connections": [
                4
            ],
            "id": 5
        }
    ]
}
```

I then loaded the file:

![Changed test file](images/wb9b.png)

This resulted in the \[-1, -1\] coordinates changing into \[0, 0\], and the material changing from "gdgssjdgsnjgsd" to Carbon. This causes the program to load the wire to the top left of the screen as this is where the origin of the canvas is.


The corrupted values were reset to their default values by the program because the validation section in the UIComponent classes worked as expected.

This means the test has passed as there were no crashes, only a silent correction of the corrupted data.
