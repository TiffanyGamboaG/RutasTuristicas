#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include"TouristRoute.h"
using namespace std;
using namespace sf;

class GraphicsManager
{private:
    bool menuImage;
    bool optionsImage;
    bool informationImage;
    bool enteringRouteName;      
    string routeNameInput;    
    TouristRoute* touristRoutes;
    FloatRect textLimitArea;

public:
    GraphicsManager();
    void setTouristRoutes(TouristRoute* routes);
    void loadImageMenu(const FloatRect& menuButton, const FloatRect& addRouteButton, const FloatRect& backButton,
        const FloatRect& exitButton);
    void handleEvents(RenderWindow& window,const FloatRect& menuButton, const FloatRect& addRouteButton,
        const FloatRect& backButton,const FloatRect& exitButton);
    void drawMenu(RenderWindow& window,Sprite& sprite);
    void drawTextInput(RenderWindow& window);
};

