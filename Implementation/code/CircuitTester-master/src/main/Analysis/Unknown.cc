//
// Created by rhys on 09/05/2021.
//

#include "Unknown.h"

UnknownCurrent::UnknownCurrent(MNAComponent *element) : Unknown(CURRENT) {
    this->element = element;
}

std::string UnknownCurrent::str() {
    return "I"+std::to_string(element->n0)+"_"+std::to_string(element->n1);
}

bool UnknownCurrent::equals(Unknown* other) {
    // If they are not the same type they are obviously not equal.
    if(other->type != Unknown::CURRENT){
        return false;
    }

    // Cast into an UnknownCurrent to get proper class attributes.
    auto* c = (UnknownCurrent*) other;
    return c->element == element;
}

UnknownVoltage::UnknownVoltage(int node)  : Unknown(VOLTAGE) {
    this->node = node;
}

std::string UnknownVoltage::str() {
    return "V"+std::to_string(node);
}

bool UnknownVoltage::equals(Unknown *other) {
    // If they are not the same type they are obviously not equal.
    if(other->type != Unknown::VOLTAGE){
        return false;
    }

    // Cast into an UnknownVoltage to get proper class attributes.
    auto* c = (UnknownVoltage*) other;
    return c->node == node;
}

Unknown::Unknown(Type t) {
    this->type = t;
}