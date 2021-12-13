//
// Created by rhys on 18/04/2021.
//

#include "Circuit.h"

#include <Eigen/Dense>
#include <iostream>

#define CUR_IN 1
#define CUR_OUT 0

template<typename T>
T Circuit::vecPopFront(std::vector<T>& vec){
    std::reverse(vec.begin(),vec.end()); // first becomes last, reverses the vector
    T out = vec.back(); // get last component
    vec.pop_back(); // pop last component off the vector
    std::reverse(vec.begin(),vec.end()); // reverses it again, so the components are in the same order as before

    return out;
}

Circuit::Circuit(std::vector<Component *> components) {
    // Clear the batteries, resistors and currentSources lists just in case they
    // contain some components for any reason.
    batteries.clear();
    resistors.clear();

    // Instead of adding the 3 lists, just copy the passed list into the
    // class attribute.
    this->components = components;

    // Split the components into the 3 types: battery, resistor and current source.
    for(auto e : components){
        // Each component object is checked for its type attribute to sort it.
        // This component was set by the Resistor, Battery, CurrentSource or derivative classes.
        switch(e->type){
            case MNA_BATTERY:
                batteries.push_back(e);
                break;
            case MNA_RESISTOR:
                resistors.push_back(e);
                break;
        }
    }

    // Populates the node list.
    for(auto e : components){
        nodes.push_back(e->n0);
        nodes.push_back(e->n1);
    }

    // Sort then remove duplicate values from nodes.
    std::sort(nodes.begin(), nodes.end());
    nodes.erase(std::unique(nodes.begin(), nodes.end()), nodes.end());

    // Counts the number of nodes.
    nodeCount = nodes.size();
}

int Circuit::getNumUnknownCurrents() {
    // Batteries are the only component with an unknown resistance and therefore an unknown current.
    return batteries.size();
}

int Circuit::getNumVars() {
    // The node count is the number of voltage nodes, and each node
    // has an unknown voltage.
    return nodeCount + getNumUnknownCurrents();
}

std::vector<Term *>* Circuit::getCurrents(int node, int side) {
    /*Convert the side to the current direction - if side is 0, current direction
     * is 1, otherwise the current direction is -1*/
    int currentDirection = side == 0 ? 1 : -1;

    // Check that the side is valid - either 0 or 1.
    if(side != 0 and side != 1) throw std::invalid_argument("Invalid Side!");

    // The current terms to return.
    auto* out = new std::vector<Term*>;

    for(auto b : batteries){
        // Convert node index into node value.
        int n = side == 0? b->n0 : b->n1;

        // If this is the node that was specified in the parameter.
        if(n == node) {
            // Batteries have an unknown current.
            out->push_back(new Term(currentDirection, new UnknownCurrent(b)));
        }
    }

    for(auto r : resistors) {
        // Convert node index into node value.
        int n = side == 0 ? r->n0 : r->n1;

        // If correct node
        if(n == node){
            // The voltage enters and leaves the component, so there are 2 terms. This uses V=IR to find current, e.g. (1/R)*V =  V/R = I
            out->push_back(new Term(-currentDirection / r->value, new UnknownVoltage(r->n1 )));
            out->push_back(new Term(currentDirection / r->value, new UnknownVoltage(r->n0 )));
        }
    }

    return out;
}

std::vector<int>* Circuit::getRefNodes() {
    auto* out = new std::vector<int>;

    std::vector<int> toVisit = nodes;

    while(! toVisit.empty()){
        // Get the component to visit next from toVisit.
        int refNodeId = toVisit.at(0);

        // Add the reference node to the output list
        out->push_back(refNodeId);

        std::vector<int>* connectedNodes = getConnectedNodes(refNodeId);

        // Remove every node that is directly connected to this reference node,
        // as there cannot be 2 nodes that are connected but are both reference nodes.
        for(auto c : *connectedNodes){
            // Remove c from toVisit by iterating over every item and removing
            // the matching one.
            toVisit.erase(std::remove_if(toVisit.begin(), toVisit.end(), [c](int i){
                return i == c;
            }), toVisit.end());
        }
    }

    return out;
}

std::vector<int>* Circuit::getConnectedNodes(int node) {
    // A queue of visited nodes from this node.
    auto* visited = new std::vector<int>;

    // A list of nodes that we want to visit in the future.
    std::vector<int> toVisit = {node};

    // This is basically a breadth first iteration of every component connected to this node.
    while(not toVisit.empty()){
        // Get the top vector item.
        int nodeToVisit = vecPopFront<int>(toVisit);

        visited->push_back(nodeToVisit);

        for(auto e : components){
            if(e->contains(nodeToVisit)){
                // Get the node leaving the component.
                int oppositeNode = e->opposite(nodeToVisit);

                // Visit the opposite node in the future if we have not already visited it.
                if(! std::count(visited->begin(), visited->end(), oppositeNode)){
                    toVisit.push_back(oppositeNode);
                }
            }
        }
    }

    // Remove duplicate values, just in case there was an error.
    visited->erase(unique( visited->begin(), visited->end() ), visited->end());
    return visited;
}

std::vector<Equation *>* Circuit::getEquations() {
    auto* equations = new std::vector<Equation *>;

    std::vector<int>* refNodeIds = getRefNodes();

    for(auto r : *refNodeIds){
        // Reference nodes have a voltage of zero as the voltage is relative to this node.
        equations->push_back(new Equation(0, {
                new Term(1, new UnknownVoltage(r))
        }));
    }

    for(auto n : nodes){
        //Create an equation containing the total current
        // source multiplied by each of the outgoing and incoming
        // current nodes from the node.

        // If n not in refNodeIds.
        if(not std::count(refNodeIds->begin(), refNodeIds->end(), n)){
            // All current nodes entering node n at n1.
            std::vector<Term *>* incoming = getCurrents(n, CUR_IN);
            // All current nodes leaving node n at n0.
            std::vector<Term *>* outgoing = getCurrents(n, CUR_OUT);

            //Currents leave at n0 and enter at n1 because conventional
            // currents are opposite to actual charge flow.

            // Add together the two lists of terms.
            auto* conserved = new std::vector<Term *>;
            conserved->insert(conserved->end(), incoming->begin(), incoming->end());
            conserved->insert(conserved->end(), outgoing->begin(), outgoing->end());

            // Create an equation of total current equals the sum of all the terms.
            equations->push_back(new Equation(0, *conserved));
        }
    }

    for(auto b : batteries){
        // Make an equation for every battery.
        equations->push_back(new Equation(b->value, {
                // N0 is negative as voltage is lost.
                // N1 is the positive as voltage is gained.
                new Term(-1, new UnknownVoltage(b->n0)),
                new Term(1, new UnknownVoltage(b->n1))
        }));
    }

    return equations;
}

std::vector<UnknownCurrent *> *Circuit::getUnknownCurrents() {
    auto* out = new std::vector<UnknownCurrent*>;

    for(auto b : batteries){
        //Batteries have an unknown current before they are placed into a circuit.
        out->push_back(new UnknownCurrent(b));
    }

    return out;
}

Solution *Circuit::solve() {
    std::vector<Equation *>* equations = getEquations();
    std::vector<UnknownCurrent*>* unknownCurrents = getUnknownCurrents();
    auto* unknownVoltages = new std::vector<UnknownVoltage*>;

    // Create an UnknownVoltage for each node as we don't know any voltage for any node.
    for(auto v : nodes){
        unknownVoltages->push_back(new UnknownVoltage(v));
    }

    auto* unknowns = new std::vector<Unknown*>(unknownCurrents->begin(), unknownCurrents->end());

    unknowns->insert(unknowns->end(), unknownVoltages->begin(), unknownVoltages->end());

    //Make two matrices, one which is the width of the number of equations by the number
    // of variables, and the other has a width of the number of equations but is only 1 wide
    auto A = Eigen::MatrixXd(equations->size(), getNumVars()).setZero();
    auto z = Eigen::MatrixXd(equations->size(), 1).setZero();

    for(int i=0 ; i<equations->size() ; i++){
        // Apply the correct numbers of every equation onto the matrices,
        //  passing in a lambda to find the index of each
        //  term of the equation in class attribute unknowns.
        equations->at(i)->apply(i, &A, &z, [this, unknowns](Unknown *u) {
            return getComponentIndex<Unknown>(unknowns, u);
        });
    }

    // Solve the matrix equation a = z
    Eigen::MatrixXd x = A.fullPivLu().solve(z); // https://eigen.tuxfamily.org/dox/group__TutorialLinearAlgebra.html

    // A map of which nodes have which voltages on the circuit.
    auto* voltageMap = new std::map<int, double>;

    for(auto v : *unknownVoltages){
        // Get the voltage out from the solved matrix at the index of the component
        // in the vector of unknowns. As the index is the node, and the node has the voltage.
        auto voltage = x(getComponentIndex<Unknown>(unknowns, v));

        // Add to the voltage map
        voltageMap->insert(std::pair<int, double>(v->node, voltage));
    }

    //
    std::vector<Component*> elems;

    for(auto c : *unknownCurrents){
        // Set the new current for each component, as the matrix column 0 has the solved currents.
        c->component->currentSolution = x(getComponentIndex<Unknown>(unknowns, c), 0);
        elems.push_back(c->component);

    }

    return new Solution(*voltageMap, elems);
}

template <typename T>
int Circuit::getComponentIndex(std::vector<T*>* array, T* component) {
    // Iterate over every index in the array.
    for(int i=0 ; i<array->size() ; i++){
        if(array->at(i)->equals(component)){
            //If the array component equals the passed component, return the index.
            return i;
        }
    }

    // Not found, return -1.
    return -1;
}

