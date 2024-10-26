#include "Route.h"

void Route::addPoint(const string& pointName, float xCoordinate, float yCoordinate)
{
	Point* newPoint = new Point(pointName, xCoordinate, yCoordinate);
	PointNode* newNode = new PointNode(newPoint);

    if (head==nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;  
        newNode->previuos = tail;
        tail = newNode;
    }
}

Route::~Route()
{
    PointNode* current = head; 
    PointNode* nextNode = nullptr; 

    while (current != nullptr) { 
        nextNode = current->next; 
        delete current; 
        current = nextNode; 
    }
}

