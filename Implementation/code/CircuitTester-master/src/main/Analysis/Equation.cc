//
// Created by rhys on 18/04/2021.
//

#include <iostream>
#include "Equation.h"

Equation::Equation(double value, std::vector<Term*> terms) {
    this->value = value;
    this->terms = terms;
}

void Equation::apply(int row, Eigen::MatrixXd* A, Eigen::MatrixXd* z, std::function<int(Unknown*)> getIndexFunc) {
    // Sets the value of the equation to the correct section on the z matrix.
    (*z)(row, 0) = value;

    for(auto t : terms){
        // Find the index of the unknown variable of this term.
        int index = getIndexFunc(t->variable);

        // Add the known coefficient of this term into the matrix A,
        // adding onto the existing value there.
        (*A)(row, index) += t->coefficient;
    }
}

std::string Equation::str() {
    std::stringstream termList;

    for (auto t : terms) {
        termList << t->str() << " + ";
    }

    return termList.str() + " = " + std::to_string(value);
}