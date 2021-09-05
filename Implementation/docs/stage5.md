# Stage 5 - Working Simulation (Merge Stages 1&4)

With stages 1 and 4 complete, I needed to merge them together to form a working simulation.

To do this I deciced to create a class that joins the two sections together called AnalysisMapper.
This class took in the UI components that had been created, turned them into MNA components, then returned a map of the
UI component to a struct of voltage and current of the component.

AnalysisMapper means that the UI never directly communicates to the MNA section, and uses only AnalysisMapper which communicates to both sides.

AnalysisMapper has only 3 public methods: the initialiser, makeGraph which returns an adjacency list of the circuit, and getSolution, which returns
a map of UIComponent:Resistance/Current for the components.

## Bugs

### Too Many Decimal Places

When putting the text on the scene, there were far too many decimal places:

Before:

![Too Many Decimals](images/decimals_before.png)

```cpp
for(auto it : sol){
        std::string textData = "Voltage: " + std::to_string(it.second.voltage) + "V";
        if (std::to_string(it.second.current) != "nan"){
            textData += "\nCurrent: " + std::to_string(it.second.current) + "A";
        }
}
```

After:

![Fixed Decimals](images/decimals_after.png)

```cpp
for(auto it : sol){
        std::stringstream ss;
        ss << std::setprecision(2);

        ss << "Voltage: ";
        ss << it.second.voltage;
        ss << "V";

        if (std::to_string(it.second.current) != "nan"){
            ss << "\nCurrent: ";
            if(it.second.current < 1000){
                ss << it.second.current;
            }else{
                ss << "∞";
            }
        }
}
```

### Initial Simulation Run

Running the simulation when there are no components on the QGraphicsScene would cause the program to segfault.

```cpp
void MainWindow::runSimulation() {
    AnalysisMapper mapper(scene->items().toStdList());
}
```

![Segfault](images/segfault_1.png)

The solution was to check if the scene was empty before running, then aborting if this is the case.

```cpp
void MainWindow::runSimulation() {
    if(scene->items().empty()){
        return;
    }

    AnalysisMapper mapper(scene->items().toStdList());
}
```
