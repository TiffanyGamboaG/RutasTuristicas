#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<string>

#include "Route.h"
#include "RouteNode.h"
using namespace std;

class TouristRoute
{
private:
	RouteNode* head;
	RouteNode* tail;
public:
	TouristRoute() : head(nullptr), tail(nullptr) {}
	void addRoute(const string& routeName);
	~TouristRoute();
};

