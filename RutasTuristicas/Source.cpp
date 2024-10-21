#include <SFML/Graphics.hpp>
#include "GraphicsManager.h"
#include <iostream>
int main()
{
    FloatRect menuButton(50, 626, 206, 84);
    FloatRect addRouteButton(50, 17, 206,84);
    FloatRect showRoutesButton(50, 111, 206, 84);
    FloatRect editRouteButton(50, 212, 206, 84);
    FloatRect changeColorButton(50, 305, 206, 84);
    FloatRect deleteRouteButton(50, 401, 206, 84);
    FloatRect exitButton(50, 498, 206, 84);
  

    GraphicsManager prueba;
    prueba.loadImageMenu(menuButton,exitButton);

  
    return 0;
}