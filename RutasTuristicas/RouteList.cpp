#include "RouteList.h"

void RouteList::addPoint(string& pointName, float coordinateX, float coordinateY)
{
	RouteNode* newNode = new RouteNode(pointName, coordinateX, coordinateY);
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

RouteList::~RouteList()
{
	RouteNode* current = head;
	RouteNode* nextNode = nullptr;

	while (current != nullptr) {
		nextNode = current->next;
		delete current;
		current = nextNode;
	}
}
