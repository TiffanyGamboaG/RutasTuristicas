#include "TouristRouteList.h"

void TouristRouteList::addRoute(string& routeName)
{
	TouristRouteNode* newNode = new TouristRouteNode(routeName);
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

TouristRouteList::~TouristRouteList()
{
	TouristRouteNode* current = head;
	TouristRouteNode* nextNode = nullptr;

	while (current != nullptr) {
		nextNode = current->next;
		delete current;
		current = nextNode;
	}
}

