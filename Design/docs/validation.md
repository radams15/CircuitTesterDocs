# Validation

My program will have only a few inputs in a few places so will need minimal validation.

## Component settings dialogue

The configuration inside of a component will have only a few types of settings:

- On/Off button - no validation needed as the user will only be able to select the on/off position.
- Resistance/voltage spinbox - needs to not be 0, which can be built into the range of the slider. Resistors and batteries must not have a 0 value as this would not work with the algorithm. Batteries can have a negative voltage (i.e. if they are reversed), but resistors always have a positive resistance as they cannot generate a current, only decrease it.
- Wire length and area - needs to not be 0, which can be built into the range of the slider, explanation as above.
- Wire material - no validation needed as it is a combobox so the user can only select predefined values.

## Saving & loading of circuits

This will need to be validated to make sure that the the file has not been edited by the user
and/or corrupted by errors.

This will mean:

- Coordinates are within the boundaries of the canvas.
- Components do not have values less than or equal to 0.
