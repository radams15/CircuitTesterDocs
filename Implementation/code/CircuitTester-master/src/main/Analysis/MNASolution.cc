//
// Created by rhys on 18/04/2021.
//

#include <iostream>
#include <algorithm>
#include "MNASolution.h"

#define APPROX_EPSILON 1e-6

MNASolution::MNASolution(std::map<int, double> voltageMap, std::vector<MNAComponent *> elements) {
    // Setup class variables.
    this->voltageMap = voltageMap;
    this->elements = elements;
}

bool MNASolution::equals(MNASolution mnaSolution) {
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
    if((!hasAllElements(mnaSolution))){
        return false;
    }

    // Check if all the currents in solution are in this.
    if(!mnaSolution.hasAllElements(*this)) {
        return false;
    }

    // All checks passed, must be equal.
    return true;
}

double MNASolution::getNodeVoltage(int nodeIndex) {
    // Gets the voltage from the voltageMap.
    return voltageMap[nodeIndex];
}

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

bool MNASolution::hasAllElements(MNASolution mnaSolution) {
    // Return whether containsElement returns true for every
    // element in mnaSolution.
    return std::all_of(mnaSolution.elements.begin(),
                       mnaSolution.elements.end(),
                       [this](MNAComponent* e){
        return containsElement(e);
    });
}

bool MNASolution::containsElement(MNAComponent* element) {
    // Returns whether any of the elements in this are equal
    // to the passed element.
    return std::any_of(elements.begin(),
                       elements.end(),
                       [this, element](MNAComponent* e){
        return e->n0 == element->n0 && e->n1 == element->n1 && numApproxEquals(e->currentSolution, element->currentSolution);
    });
}

bool MNASolution::numApproxEquals(double a, double b) {
    // Finds the difference between a and b then compares the difference
    // to an epsilon.
    return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * APPROX_EPSILON);
}