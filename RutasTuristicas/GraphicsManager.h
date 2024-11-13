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
    bool editingRouteName;
    bool routeFoundOptions;
    bool deletePoint;
    bool deleteRoute;
    string routeNameInput;
    string pointNameInput;
    string editingRouteNameInput;
    string optionInput;
    TouristRouteList* touristRoute;
    RouteList* routePoints;
    FloatRect menuButton;
    FloatRect addRouteButton;
    FloatRect loadRouteButton; 
    FloatRect editRouteButton;
    FloatRect changeColorButton;
    FloatRect deleteRouteButton;
    FloatRect exitButton;
    FloatRect backButton;
    FloatRect textLimitArea;
    FloatRect textLimitArea2;
    FloatRect mapLimitArea;
    FloatRect colorAreas[8];
    Color selectedColor; 
    Color colors[7];
    int positionX;
    int positionY;
    void handleEvents(RenderWindow& window);
    void drawMenu(RenderWindow& window, Sprite& sprite);
    void drawTextInputRouteName(RenderWindow& window);
    void drawTextInputPointName(RenderWindow& window);
    void drawPointInstruction(RenderWindow& window); 
    void drawRouteName(RenderWindow& window); 
    void drawlines(RenderWindow& window);
    void drawCircule(RenderWindow& window);
    void drawColorPalette(RenderWindow& window); 
    void drawTextInputRouteToEdit(RenderWindow& window);
    void drawRouteToEdit(RenderWindow& window);
    void editoptions(RenderWindow& window);
    void deletePointFromRoute(const string& pointName);
    void deleteRouteFromList(const string& routeName);
    void saveRoutes();
    void loadRoutes();
public:
    GraphicsManager();
    void loadImageMenu();
    ~GraphicsManager();
};

