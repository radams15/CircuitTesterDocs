# Stage 6 - Save/Load System

This is where the contents of the circuit are saved in a file on the harddisk.

I achieved this by turning each circuit component into JSON data and saving this to a file.

E.g. this:

![Save/Load Example](images/saveload1.png)

Becomes this:

```json
{
    "name": "test2",
    "parts": [
        {
            "component": {
                "pos": [
                    280.0,
                    220.0
                ],
                "state": false,
                "type": 2,
                "voltage": 3.0
            },
            "connections": [
                6
            ],
            "id": 4
        },
        {
            "component": {
                "area": 1.0,
                "length": 3.0,
                "material": "Iron",
                "pos": [
                    260.0,
                    500.0
                ],
                "type": 3
            },
            "connections": [
                4
            ],
            "id": 6
        }
    ]
}
```


The only issue I faced with the design was that there was no way to save the connections between the components.

The solution I made was that the UIComponent class would have a static counter which incremented whenever a new component was created, so each
component had a unique ID.

```cpp
static int currentId;
```

```cpp
UIComponent::UIComponent(int id, std::string resourcePath): ID(id), SceneItem(std::move(resourcePath)){
    componentId = currentId;
    currentId++;

    settingsBox = new QVBoxLayout();
}
```

As seen in the example save data above, each component has the field "id", and a list of ids it is connected to in the list "connections".

## Validation

I changed each Component derivative class to have a constructor with optional parameters for
the component values as seen below.

```cpp
Battery(double voltage=1.0f, bool on=true);
```

```cpp
Resistor(double resistance=1.0f);
```

```cpp
Switch(bool on=true);
```

```cpp
Wire(double length=1.0f, double area=1.0f, std::string material="Copper");
```

Each method independently validates the inputs, e.g. for Wire which is the most complex validation:

```cpp
lengthSpinner->setValue(length < 0.1? 0.1 : length);
areaSpinner->setValue(area < 0.1? 0.1 : area);

if(resistivities.find(material) != resistivities.end()) {
    // If the material is a valid one (in the resistivities map).
    wireCombo->setCurrentText(QString::fromStdString(material));
}else {
    // The material is invalid, set material to the first one in the combobox.
    wireCombo->setCurrentIndex(0);
}
```

## Bugs

### Getting the username.

To save the circuits in a standard place, my program needed to find the home directory
of the user. This involved writing seperate code for the API of each targeted OS.

Luckily because Linux and MacOs are unix based, I could use `unistd.h`. For Windows I used
`windows.h`.

According to many websites (e.g. [Here](https://stackoverflow.com/questions/142508/how-do-i-check-os-with-a-preprocessor-directive)), this OS
could be determined using the preprocessor at compile time like this:

``` cpp
#if defined(__unix)
    #include <unistd.h>
    #include <pwd.h>
#elif defined(_WIN32)
    #include <windows.h>
    #include <Lmcons.h>
#endif
```

But this did not work for MacOS, leading to the project not compiling on MacOS, but working on Linux and Windows.

The solution was to add an extra check to make the new code as follows:

``` cpp
#if defined(__unix) || defined(__APPLE__)
    #include <unistd.h>
    #include <pwd.h>
#elif defined(_WIN32)
    #include <windows.h>
    #include <Lmcons.h>
#endif
```

This now works.

### "Directory does not exist"

This is an error I found when I was trying to load a circuit, trying to validate whether or not the circuit file existed.

The problem was that I was trying to use the dirExists method I had created to see if a file exists, which always returned false since
the file is not a directory.

The solution was found after changing the pieces of code that check if the path is a file, which I removed to just check if a path
exists rather than a directory.

Before:

```cpp
bool UserUtils::dirExists(std::string dir){
#if UNIX
    struct stat sb; // https://stackoverflow.com/questions/3828192/checking-if-a-directory-exists-in-unix-system-call
    if (stat(dir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)){
        return true;
    }
    return false;
#elif WINDOWS
    DWORD ftyp = GetFileAttributesA(dir.c_str()); // https://stackoverflow.com/questions/8233842/how-to-check-if-directory-exist-using-c-and-winapi
    if (ftyp == INVALID_FILE_ATTRIBUTES){
        return false;
    }

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY){
        return true;
    }

    return false;
#else
#error Cannot determine OS (dirExists)!
#endif
}
```

After:

```cpp
bool UserUtils::pathExists(std::string dir){
#if UNIX
    struct stat sb; // https://stackoverflow.com/questions/3828192/checking-if-a-directory-exists-in-unix-system-call
    if (stat(dir.c_str(), &sb) == 0){
        return true;
    }
    return false;
#elif WINDOWS
    DWORD ftyp = GetFileAttributesA(dir.c_str()); // https://stackoverflow.com/questions/8233842/how-to-check-if-directory-exist-using-c-and-winapi
    if (ftyp == INVALID_FILE_ATTRIBUTES){
        return false;
    }

    if (ftyp){
        return true;
    }

    return false;
#else
#error Cannot determine OS (dirExists)!
#endif
}
```


### Loaded values are wrong

When I saved a wire then opened it again, the values were all in the wrong place.

The problem was that I had misplaced the method arguments in Wire:

```cpp

```

Before:

```cpp
comp = new Wire(part["component"]["area"].get<double>(), part["component"]["length"].get<double>(), part["component"]["material"].get<std::string>());
```

After:

```cpp
comp = new Wire(part["component"]["length"].get<double>(), part["component"]["area"].get<double>(), part["component"]["material"].get<std::string>());
```
