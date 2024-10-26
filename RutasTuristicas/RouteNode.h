#pragma once
#include "Route.h"

class RouteNode
{
public:
    Route* route;
    RouteNode* next;
    RouteNode* previuos;

    RouteNode(Route* newRoute) : route(newRoute), next(nullptr), previuos(nullptr) {}
};

