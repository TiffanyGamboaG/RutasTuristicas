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

void TouristRouteList::deleteRoute(const string& routeName)
{
	TouristRouteNode* current = head;
	while (current != nullptr) {
		if (current->routeName == routeName) {
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
			current->routePointsTourist.clearPoints();

			delete current;
			return;
		}
		current = current->next;
	}
}

void TouristRouteList::saveRoutesToFiles(const string& directory)
{
	TouristRouteNode* currentRoute = head;
	int routeCount = 1;

	while (currentRoute != nullptr) {
		string filename = directory + "/Route" + to_string(routeCount) + ".txt";
		ofstream outFile(filename);

		if (outFile.is_open()) {
			outFile << currentRoute->routeName << endl;
			RouteNode* currentPoint = currentRoute->routePointsTourist.head;
			while (currentPoint != nullptr) {
				outFile << currentPoint->pointName << " "
					<< currentPoint->positionX << " "
					<< currentPoint->positionY << "\n";
				currentPoint = currentPoint->next;
			}
			outFile.close(); 
			routeCount++;
		}
		else {
			
			cerr << "Error al abrir el archivo: " << filename << endl;
		}
		currentRoute = currentRoute->next;
	}
}

void TouristRouteList::loadRoutesFromFiles(const string& directory)
{
	int routeCount = 1;
	while (true) {
		string fileName = directory + "/Route" + to_string(routeCount) + ".txt";
		ifstream inFile(fileName);
		if (!inFile.is_open()) {
			break; 
		}
		string routeName;
		getline(inFile, routeName);

		addRoute(routeName);
		TouristRouteNode* currentRoute = head;
		while (currentRoute != nullptr) {
			if (currentRoute->routeName == routeName) {
				break; 
			}
			currentRoute = currentRoute->next;
		}

		if (currentRoute != nullptr) { 
			string pointName;
			int x, y;
			while (inFile >> pointName >> x >> y) {
				currentRoute->addPoint(pointName, x, y);
			}
		}
		inFile.close(); 
		routeCount++; 
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

