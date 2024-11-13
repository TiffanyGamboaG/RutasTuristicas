#include "RouteList.h"
#include "TouristRouteList.h"

void RouteList::addPoint(string& pointName, int coordinateX, int coordinateY)
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

void RouteList::clearPoints()
{
	RouteNode* current = head;
	RouteNode* nextNode = nullptr;

	while (current != nullptr) {
		nextNode = current->next;
		delete current;
		current = nextNode;
	}
	head = nullptr;
}

void RouteList::deletePoint(const string& pointName)
{
	RouteNode* current = head;
	while (current != nullptr) {
		if (current->pointName == pointName) {

			if (current->previuos != nullptr) {
				current->previuos->next = current->next;
			}
			else {
				head = current->next;
			}
			if (current->next != nullptr) {
				current->next->previuos = current->previuos;
			}
			else {
				tail = current->previuos;
			}

			delete current;
			return;
		}
		current = current->next;
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
