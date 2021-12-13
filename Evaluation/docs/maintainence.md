# Maintainence

My program is very portable, being able to run on the following systems:

- MacOS (>= 10.8)
- Linux (>= Ubuntu 14.04)
- Windows (>= XP)

When there is a new QT release the programs could be updated, although this is not required, only advised. Since my program does not access the internet, the vulnerabilities in the framework will not be exploited unless there is already malicious software on the host.

For example the Windows XP build runs on QT 5.6 which has not been supported since March 2019, but the builds for Windows 8+, MacOS 10.12+ and Ubuntu 16.04+ are still supported as the operating systems themselves are still supported by their creators.

If there is a breaking change with the QT framework, the program could need to be fixed or even re-written, but since this program even will build with the newest versions of QT 6, it seems unlikely this would need to be done for many years.

The program does not work very well on small screens (\<=10") or touchscreens because of the menubar that is hard to use without a mouse or keyboard.

The program does not need to backup or archive any data but the user can, if they want, open the save folder using the "Help->Open Save Folder" button in the menubar, which allows the user to backup or archive the data. In the future I may include a backup feature.

This program could be developed to use a more mobile-friendly UI using QtQuick2, but this would require a complete re-write of the GUI code, which is not feasable in the current time frame, and I am also unsure if I could fit full functionality into such a small size (≈6")

If needed, new features and components could be easily added because of the modular, object-oriented design of my program, the UIComponent is created with the correct image, then is added to the toolbar as a toolbutton. Once this is done the AnalysisMapper needs to be updated with the correct conversion between the UIComponent and the relevant MNAComponent, and the SaveLoad class needs to be updated with a way to serialise and deserialise the componet classes.

The UI is completely seperate to the backend analysis section, so the UI can be fairly easily changed without changing any part of the analysis code. This is useful if I were to re-write the UI in a different GUI framework like GTK or wxWidgets.

The code is very well commented, so with enough time to understand, others could contribute to the code to improve the program. This could theoretically port my program to new devices to assist others in learning.
