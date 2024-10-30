#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<string>
using namespace std;
using namespace sf;

class RouteNode
{
public:
	string pointName;
	float positionX;
	float positionY;
	RouteNode* next;
	RouteNode* previuos;
    RouteNode(string&name,float coordinateX,float coordinateY):pointName(name),positionX(coordinateX),positionY(coordinateY), next(nullptr), previuos(nullptr) {}
};

class RouteList
{
public:
	RouteNode* head;
	RouteNode* tail;
	RouteList():head(nullptr),tail(nullptr){}
	void addPoint(string& pointName,float coordinateX,float coordinateY);
	~RouteList();
};

