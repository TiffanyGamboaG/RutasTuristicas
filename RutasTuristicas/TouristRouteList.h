#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<string>
#include "RouteList.h"
#include "fstream"
using namespace std;
using namespace sf;

class TouristRouteNode
{
public:
	string routeName;
	TouristRouteNode* next;
	TouristRouteNode* previuos;
	RouteList routePointsTourist;
	TouristRouteNode(string name):routeName(name),next(nullptr),previuos(nullptr){}

	void addPoint(string& pointName, int positionX, int positionY) {
		routePointsTourist.addPoint(pointName,positionX,positionY);
	}
};
class TouristRouteList
{
public:
	TouristRouteNode* head;
	TouristRouteNode* tail;
	TouristRouteList():head(nullptr),tail(nullptr){}
	void addRoute(string& routeName);
	void deleteRoute(const string& routeName);
	void saveRoutesToFiles(const string& directory);
	void loadRoutesFromFiles(const string& directory);
	~TouristRouteList();
};

