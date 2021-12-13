#include <iostream>
#include <algorithm>
#include "Solution.h"

#define APPROX_EPSILON 1e-6

Solution::Solution(std::map<int, double> voltageMap, std::vector<Component *> components) {
    // Setup class variables.
    this->voltageMap = voltageMap;
    this->components = components;
}

bool Solution::equals(Solution mnaSolution) {
    std::vector<int> nodes; // The nodes of this circuit.
    std::vector<int> otherNodes; // The nodes of the circuit to compare to.

    for(auto n : voltageMap){
        nodes.push_back(n.first);
    }

    for(auto n : mnaSolution.voltageMap){
        otherNodes.push_back(n.first);
    }

    for(auto key : nodes){
        // Check if every key in this equals the same key in the solution.
        if(!numApproxEquals(getNodeVoltage(key), mnaSolution.getNodeVoltage(key))){
            return false;
        }
    }

    // Check if all the currents in this are in solution.
    if((!hasAllComponents(mnaSolution))){
        return false;
    }

    // Check if all the currents in solution are in this.
    if(!mnaSolution.hasAllComponents(*this)) {
        return false;
    }

    // All checks passed, must be equal.
    return true;
}

double Solution::getNodeVoltage(int nodeIndex) {
    // Gets the voltage from the voltageMap.
    return voltageMap[nodeIndex];
}

double Solution::getCurrent(Component resistor) {
    // Returns the current by doing V=IR, which is equal to I=V/R.
    double v = getVoltage(resistor);
    double r = resistor.value;
    double i = v / r;

    return  i;
}

double Solution::getVoltage(Component component) {
    // Gets the difference between the voltages the start and end nodes
    // as voltage is the potential difference between two components.
    return std::abs(voltageMap.at(component.n1) - voltageMap.at(component.n0));
}

bool Solution::hasAllComponents(Solution mnaSolution) {
    // Return whether containsComponent returns true for every
    // component in mnaSolution.
    return std::all_of(mnaSolution.components.begin(),
                       mnaSolution.components.end(),
                       [this](Component* e){
        return containsComponent(e);
    });
}

bool Solution::containsComponent(Component* component) {
    // Returns whether any of the components in this are equal
    // to the passed component.
    return std::any_of(components.begin(),
                       components.end(),
                       [this, component](Component* e){
        return e->n0 == component->n0 && e->n1 == component->n1 && numApproxEquals(e->currentSolution, component->currentSolution);
    });
}

bool Solution::numApproxEquals(double a, double b) {
    // Finds the difference between a and b then compares the difference
    // to an epsilon.
    return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * APPROX_EPSILON);
}
