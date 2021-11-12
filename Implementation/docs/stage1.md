# Stage 1 - Modified Nodal Analysis

I will build up my program in many separate prototype projects, the first is my circuit analysis program.

The justification for this prototype is that this is the core of my project, without this my project is just a drag-and-drop
circuit designer.

This section encompasses the Circuit, Element, Equation, Solution and Term elements of my algorithm design, and they have been grouped this way
as they all rely on each other and cannot be run without the other sections.

My goal is to be able to have this section be relatively independent of the main window section, and have neither of them communicate directly, effectively
making this stage a library.

First, I made a prototype in Python in order to more easily test the algorithms, as starting with C++ would be slower because of the lack of functions such as `map` and list comprehensions. Overall though, C++ will result in a faster program than the equivalent Python because C++ is compiled whereas Python is not.

I subsequently translated these two into equivalent C++ classes:

### MNACircuit.h

%include_cpp(spice2/MNACircuit.h)

### MNACircuit.cc

%include_cpp(spice2/MNACircuit.cc)

### MNASolution.h

%include_cpp(spice2/MNASolution.h)

### MNASolution.cc

%include_cpp(spice2/MNASolution.cc)


## Testing

First, I created targeted white-box tests to test each individual class.

Next, I created a test file to test the functions ofthe stage as a whole, called Test_MNA which had tests for each of the
white-box tests on the design document.

The Test_MNACircuit contains the tests for each of the tests in the black-box section of the design document.

Eventually I succeeded in passing all the tests:

![Tests Passing](images/mna_test_success.png)

The bugs below were all located by unit tests failing.
 
## Bugs

### Matrix undefined behaviour:

Eigen matrix A in the MNACircuit::solve method normally created
a matrix of zeroes, but when doing a test, the values of the solve function
were completely wrong, often returning just zeroes.

I managed to find out that the following code was initialising the matrices
with random data:

``` cpp
auto A = Eigen::MatrixXd(equations->size(), getNumVars());
auto z = Eigen::MatrixXd(equations->size(), 1);
```

I found a way to zero the matrix - the MatrixXd::setZero function - and the problem was solved.
The fixed code is shown here:

``` cpp
auto A = Eigen::MatrixXd(equations->size(), getNumVars()).setZero();
auto z = Eigen::MatrixXd(equations->size(), 1).setZero();
```

### Matrix solution completely wrong

One major problem I encountered was that the matrix seemed to be geenrated correctly according to the examples from the QUCS page,but when the matrix
was solved, the output was completely wrong.

After running the debugger through the solution I found that the Eigen library has many methods to solve matrices, and the one I had selected
was not good solving matrices with many decimal places.

This was the table of options:

![Eigen Decomposition Algorithms](images/eigen_decomps.png)

Previously I had selected LDLT because of the speed, but this was returning low accuracy numbers as indicated above.

The solution was to switch to a more accurate method on the table.

Before:

```cpp
Eigen::MatrixXd x = A.ldlt().solve(z);
```

After

```cpp
Eigen::MatrixXd x = A.fullPivLu().solve(z);
```

### Returning negative voltages.

Whilst this is technically correct, it is not helpful for students when it comes to learning, so I needed
to remove the negative if the value was less than 1.

I fixed this by simply using std::abs on the getVoltage function, but this then broke the getCurrent function, as previously I was doing -getVoltage to remove the negative number.

Before:

```cpp
double MNASolution::getCurrent(MNAComponent resistor) {
    // Returns the current by doing V=IR, which is equal to I=V/R.
    double v = -getVoltage(resistor);
    double r = resistor.value;
    double i = v / r;

    return  i;
}

double MNASolution::getVoltage(MNAComponent element) {
    // Gets the difference between the voltages the start and end nodes
    // as voltage is the potential difference between two components.
    return voltageMap.at(element.n1) - voltageMap.at(element.n0);
}
```

After:

```cpp
double MNASolution::getCurrent(MNAComponent resistor) {
    // Returns the current by doing V=IR, which is equal to I=V/R.
    double v = getVoltage(resistor);
    double r = resistor.value;
    double i = v / r;

    return  i;
}

double MNASolution::getVoltage(MNAComponent element) {
    // Gets the difference between the voltages the start and end nodes
    // as voltage is the potential difference between two components.
    return std::abs(voltageMap.at(element.n1) - voltageMap.at(element.n0));
}
```

## Validation

There is little validation that needs to be done in this stage as any data that will be fed into it will be validated already by the GUI, but this section will happily throw exceptions that can be caught by the main program to react to errors.

### MNAComponent

No component can have a zero value as this breaks the analysis. The program therefore must do a range check when an MNAComponent is created to make sure that the value is not 0.

This is solved in the initialiser function:

```cpp
MNAComponent::MNAComponent(int n0, int n1, ElementType type, double value, double currentSolution) {
    // Sets the class attributes from the passed initialiser values.
    this->n0 = n0;
    this->n1 = n1;

    this->type = type;

    if(this->value <= 0.01){ // Set an arbitrary value of 0.01, where anything below this raises an exception.
        throw std::string("Cannot have a zero-valued component!\n");
    }

    this->value = value;
    this->currentSolution = currentSolution;
}
```


## Review

Overall, this stage fits in well with my ideas for the backend, as it provides fairly easy access for the program to call the circuit solver, and receive the solutions back out.

Obviously, the hardest part of this was comprehending how the mathematical algorithms worked and how to extract the desired
information from them afterwards. The actual programming related sections such as class, enum and data structure designs were a lot
easier to plan and write.

It is difficult to ask the stakeholder input on this as it is purely a library implementation rather than a program that
can be tested and run, but since the tests were successful, I would say that this was a success.
