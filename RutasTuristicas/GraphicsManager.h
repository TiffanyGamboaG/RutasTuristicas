#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class GraphicsManager
{private:
    bool menuImage;

public:
    GraphicsManager();
    void loadImageMenu(const FloatRect& menuButton, const FloatRect& exitButton);
    void handleEvents(RenderWindow& window,const FloatRect& menuButton,const FloatRect& exitButton);
    void drawMenu(RenderWindow& window,Sprite& sprite);
};

