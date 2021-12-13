#ifndef CircuitTester_MNASOLUTION_H
#define CircuitTester_MNASOLUTION_H

#include <map>
#include <vector>
#include <string>

#include "Component.h"

class Solution {
private:
    static bool numApproxEquals(double a, double b);

    bool hasAllComponents(Solution mnaSolution);

    bool containsComponent(Component* component);

public:
    std::map<int, double> voltageMap;

    std::vector<Component*> components;

    Solution(std::map<int, double> voltageMap, std::vector<Component*> components);

    bool equals(Solution mnaSolution);

    double getNodeVoltage(int nodeIndex);

    double getVoltage(Component component);

    double getCurrent(Component resistor);
};


#endif //CircuitTester_MNASOLUTION_H

