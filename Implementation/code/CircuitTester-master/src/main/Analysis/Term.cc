//
// Created by rhys on 13/05/2021.
//

#include "Term.h"

Term::Term(double coefficient, Unknown *variable) {
    this->coefficient = coefficient;
    this->variable = variable;
}

std::string Term::str() {
    std::string prefix = coefficient == 1? "" : coefficient == -1? "-" : std::to_string(coefficient);

    return prefix + variable->str();
}