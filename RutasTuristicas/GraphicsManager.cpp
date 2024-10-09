#include "GraphicsManager.h"

void GraphicsManager::loadImageMenu()
{ 
    RenderWindow window(sf::VideoMode(1280, 720), "Ventana"); 

    Texture menu; 
    if (!menu.loadFromFile("mapaCR.png")) { 
        return; 
    }
    Sprite menuSprite(menu); 
    Texture optionsMenu; 
    optionsMenu.loadFromFile("mapaCR2.png");
    Sprite optionsMenuSprite(optionsMenu);
    bool imageLoaded = false;

    while (window.isOpen()) {
        handleEvents(window);
        if (imageLoaded) {
            drawMenu(window, optionsMenuSprite);
        }
        else {
            drawMenu(window, menuSprite);
        }
        checkClick(window, menuSprite, optionsMenuSprite, imageLoaded);
        window.display();

    }
}

void GraphicsManager::checkClick(RenderWindow& window, Sprite& menuSprite, Sprite& optionsMenuSprite, bool& imageLoaded)
{
    Vector2i mousePosittion = Mouse::getPosition(window); 

    int x1 = 49, y1 = 624, x2 = 209, y2 = 627, x3 = 38, y3 = 694, x4 = 229, y4 = 691;
    int width = x4 - x1;
    int height = y3 - y1;

    IntRect buttonRect(x1,y1,width,height); 
    if (Mouse::isButtonPressed(Mouse::Left)) { 
        if (buttonRect.contains(mousePosittion.x, mousePosittion.y)) { 
            imageLoaded = false;
            menuSprite = optionsMenuSprite; 
        }
    }
}

void GraphicsManager::handleEvents(RenderWindow& window)
{
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
    }
}

void GraphicsManager::drawMenu(RenderWindow& window, Sprite& sprite)
{
    window.clear();
    window.draw(sprite);
    drawButton(window);
}

void GraphicsManager::drawButton(RenderWindow& window)
{
    int x1 = 49, y1 = 624, x2 = 209, y2 = 627, x3 = 38, y3 = 694, x4 = 229, y4 = 691;

    IntRect buttonRect(x1,y1,x2-x1,y3-y1);

    RectangleShape buttonShape;

    buttonShape.setSize(Vector2f(buttonRect.width, buttonRect.height));
    buttonShape.setPosition(Vector2f(buttonRect.left, buttonRect.top));
    buttonShape.setFillColor(Color::Transparent);
    buttonShape.setOutlineColor(Color::Transparent);
    buttonShape.setOutlineThickness(2);
    window.draw(buttonShape);
}
