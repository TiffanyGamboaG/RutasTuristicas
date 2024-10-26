#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<string>
#include "Point.h"
using namespace std;

class PointNode
{
public:
	Point* point;
	PointNode* next;
	PointNode* previuos;
	PointNode(Point* newPoint) : point(newPoint), next(nullptr), previuos(nullptr) {}
};

