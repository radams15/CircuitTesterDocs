# Stage 1 - Modified Nodal Analysis
 
I will build up my program in 3 separate prototype projects, the first is my circuit analysis program.

First, I made a prototype in Python in order to more easily test the algorithms, as starting with C++ would be slower because
of the lack of functions such as `map` and list comprehensions.

At all times I attempted to use python 3.6 type hints in order to ease the transition from Python to C++.

The two main sections are shown below.

### MNACircuit.py

%include_py(spice3/MNACircuit.py)

### MNASolution.py

%include_py(spice3/MNASolution.py)

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

## Validation

### MNAComponent

No component can have a zero value as this breaks the analysis. The program therefore must do a
range check when an MNAComponent is created to make sure that the value is not 0.

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
