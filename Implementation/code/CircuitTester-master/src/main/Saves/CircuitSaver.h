//
// Created by rhys on 16/07/2021.
//

#ifndef CIRCUITTESTER_CIRCUITSAVER_H
#define CIRCUITTESTER_CIRCUITSAVER_H

#include <QList>
#include <QGraphicsItem>
#include "../UI/UIComponent.h"
#include "../UI/Arrow.h"

class CircuitSaver {
private:

public:
    void saveCircuit(std::vector<UIComponent*> components, std::vector<Arrow*> arrows);
};


#endif //CIRCUITTESTER_CIRCUITSAVER_H
