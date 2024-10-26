#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<string>
#include "PointNode.h"
using namespace std;

class Route
{
private:
	PointNode* head;
	PointNode* tail;
public:
	string routeName;
	Route(const string& newRouteName) : routeName(newRouteName), head(nullptr), tail(nullptr) {}
	void addPoint(const string& newPointName, float xCoordinate, float yCoordinate);
	~Route();
};

