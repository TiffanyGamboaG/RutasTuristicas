#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<string>
using namespace std;

class Point
{
public:
	string name;
	float xCoordinate;
	float yCoordinate;
	Point(const string&newName,float newXCoordinate,float newYCoordinate):name(newName),xCoordinate(newXCoordinate),yCoordinate(newYCoordinate){}
};

