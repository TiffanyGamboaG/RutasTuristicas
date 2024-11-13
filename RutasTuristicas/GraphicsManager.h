#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TouristRouteList.h"
using namespace std;
using namespace sf;

class GraphicsManager
{
private:
    bool menuImage;
    bool optionsImage;
    bool informationImage;
    bool enteringRouteName;  
    bool enteringPointName;
    bool enteringPoints; 
    string routeNameInput;
    string pointNameInput;
    TouristRouteList* touristRoute;
    RouteList* routePoints;
    FloatRect menuButton;
    FloatRect addRouteButton;
    FloatRect loadRouteButton; 
    FloatRect editRouteButton;
    FloatRect exitButton;
    FloatRect backButton;
    FloatRect textLimitArea;
    FloatRect textLimitAreaRouteName;
    FloatRect mapLimitArea;
    FloatRect colorAreas[8];
    Color selectedColor; 
    Color colors[7];
    int pointPositionX;
    int pointPositionY;
    void handleEvents(RenderWindow& window);
    void drawMenu(RenderWindow& window, Sprite& sprite);
    void drawTextInputRouteName(RenderWindow& window);
    void drawTextInputPointName(RenderWindow& window);
    void drawPointInstruction(RenderWindow& window); 
    void drawRouteName(RenderWindow& window); 
    void drawCircule(RenderWindow& window);
    void drawColorPalette(RenderWindow& window); 
    void saveRoutes();
    void loadRoutes();
    void drawCurved(RenderWindow& window);
    void drawCurvedLines(RenderWindow& window, RouteNode* routeNode);
    
public:
    GraphicsManager();
    void loadImageMenu();
    ~GraphicsManager();
};

