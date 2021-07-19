//
// Created by rhys on 15/05/2021.
//

#ifndef CIRCUITTESTER_UICOMPONENT_H
#define CIRCUITTESTER_UICOMPONENT_H

#include <string>

#include <utility>

#include "SceneItem.h"

class UIComponent : public SceneItem{
protected:
    int ID;

    explicit UIComponent(int id, std::string resourcePath): ID(id), SceneItem(std::move(resourcePath)){};

private:

public:
    inline int getId() { return ID; }

    int n0 = -1;
    int n1 = -1;

    std::vector<Arrow*> connections;

    std::string str();
    bool equals(UIComponent* c);
};


#endif //CIRCUITTESTER_UICOMPONENT_H
