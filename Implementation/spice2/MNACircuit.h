#ifndef CircuitTester_MNACIRCUIT_H
#define CircuitTester_MNACIRCUIT_H

#include <vector>
#include <map>
#include <string>

#include "Component.h"
#include "Equation.h"
#include "Solution.h"

class Circuit {
private:
    std::vector<Component*> batteries;

    std::vector<Component*> resistors;

    std::vector<Component*> components;

    int nodeCount;

    std::vector<int> nodes;

    template<typename T>
    T vecPopFront(std::vector<T>& vec);

    int getNumUnknownCurrents();

    int getNumVars();

    std::vector<int>* getRefNodes();

    std::vector<Equation*>* getEquations();

    std::vector<UnknownCurrent*>* getUnknownCurrents();

    template <typename T>
    int getElementIndex(std::vector<T*>* array, T* component);

public:
    explicit Circuit(std::vector<Component *> components);

    Solution* solve();

    std::vector<int>* getConnectedNodes(int node);

    std::vector<Term*>* getCurrents(int node, int side);
};

#endif //CircuitTester_MNACIRCUIT_H

