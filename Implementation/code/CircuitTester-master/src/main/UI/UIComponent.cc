//
// Created by rhys on 15/05/2021.
//

#include "UIComponent.h"

std::string UIComponent::str() {
    return resourcePath + "(n" + std::to_string(n0) + ")";
}

bool UIComponent::equals(UIComponent* c) {
    return this == c;
}