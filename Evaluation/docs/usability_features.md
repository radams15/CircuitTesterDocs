# Usability Features

I would say that my program has all the features required by the specification.

### Changing Component Settings

The first is that I can change any component settings during the program operation:

![Changing Component Settings](images/attributes.png)


### Viewing Circuit Information

The next is the ability to view circuit information at any point on the circuit, e.g. here is a circuit where we can see the current split over 2 resistors of different resistance.

This does not use an ammeter or a voltmeter as the analysis stated, but this works fairly well and is functional for the stakeholders.

![View Circuit Information](images/show_currents.png)


### Saving and Loading Circuits

The program can save and load circuits. This could be simpler or more clear, but this would be a future development and would take too long to complete.

Save:

![Save and Load Circuits](images/save.png)

Load:

![Save and Load Circuits](images/open.png)

### Importing and Exporting Circuits

The program can also import and export circuits to any folder on the computer using my .cir file - which is JSON. The .cir extension is automatically added if the user does not specify it.

![Import and Export Circuits](images/export.png)

And here the circuit is saved in the folder, showing the export functionality.

![The Exported .cir File](images/export2.png)

### Accessibility

The program is accessible, as the underlying QT framework is compatable with general OS narration and magnifier programs, meaning that the OS handles text-to-speech functionality for any visually-impaired users.

There is however no way for these users to be able to see what component is what without being able to see the image, which may limit the usage of the program for these users. There are ways to interface with the text-to-speech engines but this would take a long time and would cause very little benefit so I will not do this.
