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
	int positionX;
	int positionY;
	RouteNode* next;
	RouteNode* previuos;
    RouteNode(string&name,int coordinateX,int coordinateY):pointName(name),positionX(coordinateX),positionY(coordinateY), next(nullptr), previuos(nullptr) {}
};

class RouteList
{
public:
	RouteNode* head;
	RouteNode* tail;
	RouteList():head(nullptr),tail(nullptr){}
	void addPoint(string& pointName,int coordinateX,int coordinateY);
	void clearPoints();
	~RouteList();
};

