#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class GraphicsManager
{
public:
    void loadImageMenu();  
    void checkClick(RenderWindow& window, Sprite& menuSprite, Sprite& optionsMenuSprite, bool& imageLoaded);
    void handleEvents(RenderWindow& window);  
    void drawMenu(RenderWindow& window,Sprite& sprite);
    void drawButton(RenderWindow& window);
};

