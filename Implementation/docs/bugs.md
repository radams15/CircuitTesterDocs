# Bugs

## Circuit Analysis

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

So I found a way to zero the matrix and the problem was solved.
The fixed code is shown here:

``` cpp
    auto A = Eigen::MatrixXd(equations->size(), getNumVars()).setZero();
    auto z = Eigen::MatrixXd(equations->size(), 1).setZero();
```
