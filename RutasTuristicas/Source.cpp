#include <SFML/Graphics.hpp>
#include "GraphicsManager.h"
#include <iostream>
#include<string>
using namespace std;
int main()
{
    FloatRect menuButton(50, 626, 206, 84);
    FloatRect addRouteButton(50, 17, 206,84);
    FloatRect showRoutesButton(50, 111, 206, 84);
    FloatRect editRouteButton(50, 212, 206, 84);
    FloatRect changeColorButton(50, 305, 206, 84);
    FloatRect deleteRouteButton(50, 401, 206, 84);
    FloatRect exitButton(50, 498, 206, 84);
    FloatRect backButton(65, 617, 206, 84);

    TouristRoute touristRoutes;
    GraphicsManager graphicsManager;
    graphicsManager.setTouristRoutes(&touristRoutes);

    GraphicsManager prueba;
    prueba.loadImageMenu(menuButton,addRouteButton,backButton,exitButton);

  
    return 0;
}