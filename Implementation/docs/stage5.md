# Stage 5 - Working Simulation (Merge Stages 1&4)

With stages 1 and 4 complete, I needed to merge them together to form a working simulation.

To do this I deciced to create a class that joins the two sections together called AnalysisMapper.
This class took in the UI components that had been created, turned them into MNA components, then returned a map of the
UI component to a struct of voltage and current of the component.

The AnalysisMapper class means that the UI never directly communicates to the MNA section, and uses only AnalysisMapper which communicates to both sides.

AnalysisMapper has only 3 public methods: the initialiser, makeGraph which returns an adjacency list of the circuit, and getSolution, which returns
a map of UIComponent:Resistance/Current for the components.

This section required me to create a bridge between the UI and the MNA code, I called this AnalysisMapper.

This class wouldm be able to convert the UIComponents into UIComponents, run the calculations, and then return
the outputs of the calculations to the UI without showing any MNA code to the UI or any UI code to the MNA.

The general solution is first to convert each UIComponent into an MNAComponent through a switch either
converting to a battery (Battery) or a resistor (Resistor, Wire, Switch).

Next, my program assigns nodes to each component by selecting a start component and running
through each other on the circuit. I found this a challenge and I struggled with it.

Eventually I solved the problem by turning the circuit into a graph and then using a breadth first search, with the difference from the start component node converted into the node number.

E.g. this:

![Original Circuit](image/demonstration_circuit.png)

Becomes this:

![Circuit Graph](images/circuit_graph.png)

I used a findShortestPath method, which I adapted from the Python examples at [https://pythoninwonderland.wordpress.com/2017/03/18/how-to-implement-breadth-first-search-in-python/](https://pythoninwonderland.wordpress.com/2017/03/18/how-to-implement-breadth-first-search-in-python/).

The original worked perfectly for my needs, but I changed it to fit my needs in my test programs by returning values instead of printing a string:

Original:

```python
def bfs_shortest_path(graph, start, goal):
    # keep track of explored nodes
    explored = []
    # keep track of all the paths to be checked
    queue = [[start]]
 
    # return path if start is goal
    if start == goal:
        return "That was easy! Start = goal"
 
    # keeps looping until all possible paths have been checked
    while queue:
        # pop the first path from the queue
        path = queue.pop(0)
        # get the last node from the path
        node = path[-1]
        if node not in explored:
            neighbours = graph[node]
            # go through all neighbour nodes, construct a new path and
            # push it into the queue
            for neighbour in neighbours:
                new_path = list(path)
                new_path.append(neighbour)
                queue.append(new_path)
                # return path if neighbour is goal
                if neighbour == goal:
                    return new_path
 
            # mark node as explored
            explored.append(node)
 
    # in case there's no path between the 2 nodes
    return "So sorry, but a connecting path doesn't exist :("
```


Adapted:

```python
def find_shortest_path(graph, start, goal):
    explored = []

    # Queue for traversing the
    # graph in the BFS
    queue = [[start]]

    # If the desired node is
    # reached
    if start == goal:
        print("Same Node")
        return [end]

    # Loop to traverse the graph
    # with the help of the queue
    while queue:
        path = queue.pop(0)
        node = path[-1]

        # Condition to check if the
        # current node is not visited
        if node not in explored:
            neighbours = graph[node]

            # Loop to iterate over the
            # neighbours of the node
            for neighbour in neighbours:
                new_path = list(path)
                new_path.append(neighbour)
                queue.append(new_path)

                # Condition to check if the
                # neighbour node is the goal
                if neighbour == goal:
                    return new_path
            explored.append(node)

    return []
```

I then translated this to C++:

```cpp
Path* AnalysisMapper::findShortestPath(Graph *graph, UIComponent *start, UIComponent *end) {
    std::vector<UIComponent*> explored;

    std::queue<std::vector<UIComponent*>*> q;

    auto v = new std::vector<UIComponent*>;
    v->push_back(start);
    q.emplace(v);

    // Is the path to the same node?
    // If so just return the end node.
    if(start == end){
        auto out = new Path;
        out->push_back(end);
        return out;
    }

    while(! q.empty()){
        Path* path = q.front();
        q.pop();

        // Get end node from the path.
        UIComponent* node = path->at(path->size()-1);

        // If node has not already been explored
        if(std::find(explored.begin(), explored.end(), node) == explored.end()){
            auto neighbors = graph->at(node);

            for(auto neighbor : neighbors){
                Path* new_path = new Path;
                std::copy(path->begin(), path->end(), back_inserter(*new_path));
                new_path->push_back(neighbor);
                q.emplace(new_path);

                // Have we reached the end node?
                // If so return the path.
                if(neighbor == end){
                    return new_path;
                }
            }

            explored.push_back(node);
        }
    }

    // If no path was found return an empty path.
    return new Path;
}

```

## Validation

There was a little validation that needed to take place, especially in the main breadth-first search algorithm.

Here I needed to check that the start node was not equal to the end node to save time iterating when there
is only one possible path.

```cpp
if(start == end){
    auto out = new Path;
    out->push_back(end);
    return out;
}
```

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

### Initial Simulation Run Segfault.

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

## Review

The program is starting to work very well, and this simple stage helped to make the program work almost completely.

The hardest part of this was figuring out how to convert the canvas into node numbers, as I created a number of failed
python prototypes that never worked properly.

Finally I had the idea to use the shortest path algorithm to do this, and that worked perfectly for my simple
needs.

The easiest part was probably the idea for the AnalysisMapper as this was perfect for seperating my different
stages from each other with one interface class.
