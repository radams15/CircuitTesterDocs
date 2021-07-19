//
// Created by rhys on 08/04/2021.
//

#ifndef LAYOUTTEST1_RESISTOR_H
#define LAYOUTTEST1_RESISTOR_H

#include "../UIComponent.h"

class Resistor : public UIComponent {
private:

public:
    enum{
        ID = 1
    };


    Resistor() : UIComponent(ID, ":/images/resistor.png") {};
};


#endif //LAYOUTTEST1_RESISTOR_H
