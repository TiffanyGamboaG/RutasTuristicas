#include "TouristRoute.h"


void TouristRoute::addRoute(const string& routeName)
{
    Route* newRoute = new Route(routeName); 
    RouteNode* newNode = new RouteNode(newRoute); 

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->previuos = tail;
        tail = newNode;
    }
}

TouristRoute::~TouristRoute() 
{
    RouteNode* current = head;
    RouteNode* nextNode = nullptr;

    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
}
