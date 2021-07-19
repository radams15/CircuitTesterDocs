//
// Created by rhys on 21/04/2021.
//

#ifndef LAYOUTTEST1_BATTERY_H
#define LAYOUTTEST1_BATTERY_H


#include "../UIComponent.h"

class Battery : public UIComponent {
private:

public:
    enum{
        ID = 2
    };

    Battery() : UIComponent(ID, ":/images/battery.png") {};
};


#endif //LAYOUTTEST1_BATTERY_H
