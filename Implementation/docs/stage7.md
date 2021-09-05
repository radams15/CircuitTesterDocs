# Stage 7 - Final Merge (Merge 5&6)

## Bugs

### Save/load crash on empty/invalid file name

When the input box for saving/loading was submitted empty, the program would crash as it attempted to load
an empty file.

This was simply fixed by using the UserUtils::pathExists method to validate the directory.

Before:

```cpp
void CircuitSaver::loadCircuit(std::string name, Scene* s) {
    std::string path = getPath(name);

    std::cout << "Load: '" << path << "'" << std::endl;

    /** more code **/
```

After:

```cpp
void CircuitSaver::loadCircuit(std::string name, Scene* s) {
    std::string path = getPath(name);

    if(not UserUtils::pathExists(path)){
        std::cerr << "Directory: '" << path << "' does not exist!" << std::endl;
        return;
    }

    std::cout << "Load: '" << path << "'" << std::endl;

    /** more code **/
```

### Invalid load circuits are created.

When the user tried to open a non-existant circuit, the program would then create the file the next time the user saved.

The problem was that currentOpenedCircuit was set before validating if the circuit even existed, so the next time the user
saved, currentOpenedCircuit would be equal to the name of the invalid circuit.

This was trivial to fix.

Before:

```cpp
void MainWindow::openScene() {
    // Prompt the user for the name of the circuit to open.
    std::string name = QInputDialog::getText(this, tr("Circuit Name"), tr("Name")).toStdString();
    CircuitSaver::loadCircuit(name, scene);
    currentOpenedCircuit = name;
}
```

After:

```cpp
void MainWindow::openScene() {
    // Prompt the user for the name of the circuit to open.
    std::string name = QInputDialog::getText(this, tr("Circuit Name"), tr("Name")).toStdString();
    currentOpenedCircuit = name;
    CircuitSaver::loadCircuit(name, scene);
}
```
