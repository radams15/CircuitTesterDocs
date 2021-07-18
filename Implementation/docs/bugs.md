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

## Save/Load system:

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
