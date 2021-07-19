//
// Created by rhys on 16/07/2021.
//

#include "CircuitSaver.h"

#include <iostream>

void CircuitSaver::saveCircuit(std::vector<UIComponent *> components, std::vector<Arrow *> arrows) {
    for(auto c : components){
        std::cout << c->getId() << ": " << c->centerpoint().x() << ", " << c->centerpoint().y() << std::endl;
    }
}
