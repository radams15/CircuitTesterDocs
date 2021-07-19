//
// Created by rhys on 18/04/2021.
//

#include <iostream>
#include "MNAComponent.h"

MNAComponent::MNAComponent(int n0, int n1, ElementType type, double value, double currentSolution) {
    // Sets the class attributes from the passed initialiser values.
    this->n0 = n0;
    this->n1 = n1;

    this->type = type;

    this->value = value;
    this->currentSolution = currentSolution;
}

MNAComponent* MNAComponent::withCurrentSolution(double newCurrentSolution) {
    return new MNAComponent(n0, n1, type, value, newCurrentSolution);
}

bool MNAComponent::contains(int n) {
    // n is contained if n0 or n1 are equal to n.
    return n == n0 || n == n1;
}

int MNAComponent::opposite(int n) {
    // The opposite of n1 is n0, and vice-versa.
    return n == n0? n1 : n0;
}

bool MNAComponent::equals(MNAComponent other) {
    // If n0, n1 and type from other are the same as this, they are equal.
    return other.n0 == n0 && other.n1 == n1 && other.type == type;
}
