#include "GraphicsManager.h"

GraphicsManager::GraphicsManager()
{
    menuImage =true;
}

void GraphicsManager::loadImageMenu(const FloatRect& menuButton, const FloatRect& exitButton)
{ 
    RenderWindow window(sf::VideoMode(1280, 720), "Ventana");

    Texture menu;
    if (!menu.loadFromFile("mapaCR.png")) {
        return;
    }
    Sprite menuSprite(menu);
    Texture optionsMenu;
    if (!optionsMenu.loadFromFile("mapaCR2.png")) {
        return;
    }
    Sprite optionsMenuSprite(optionsMenu);

    while (window.isOpen()) {
        handleEvents(window, menuButton, exitButton);

        window.clear();
        if (menuImage) {
            drawMenu(window, menuSprite);
        }
        else {
            drawMenu(window, optionsMenuSprite);
        }
        window.display();
    }
}

void GraphicsManager::handleEvents(RenderWindow& window, const FloatRect& menuButton, const FloatRect& exitButton)
{
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            Vector2f mousePosittion = window.mapPixelToCoords(Mouse::getPosition(window));
            if (menuButton.contains(mousePosittion)&&menuImage) {
                menuImage = false;
            }
           
            else if (!menuImage && exitButton.contains(mousePosittion)) {
            
                window.close();
            }
        }
    }
}

void GraphicsManager::drawMenu(RenderWindow& window, Sprite& sprite)
{
    window.clear();
    window.draw(sprite);
}


