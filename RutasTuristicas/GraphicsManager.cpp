#include "GraphicsManager.h"

GraphicsManager::GraphicsManager()
{
    menuImage =true;
    optionsImage = false;
    informationImage = false;
    enteringRouteName = false;
    routeNameInput = " "; 
    touristRoutes = nullptr;
    textLimitArea = FloatRect(12, 41, 300, 567);
}

void GraphicsManager::setTouristRoutes(TouristRoute* routes)
{
    touristRoutes = routes;
}

void GraphicsManager::loadImageMenu(const FloatRect& menuButton, const FloatRect& addRouteButton, const FloatRect& backButton, const FloatRect& exitButton)
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

    Texture information;
    if (!information.loadFromFile("mapaCR3.png")) {
        return;
    }
    Sprite informationSprite(information);

    while (window.isOpen()) {
        handleEvents(window, menuButton,addRouteButton,backButton, exitButton);

        window.clear();
        if (menuImage) {
            drawMenu(window, menuSprite);
        }
        else if (optionsImage) {
            drawMenu(window, optionsMenuSprite);
        }
        else if (informationImage) {
            drawMenu(window, informationSprite);
            drawTextInput(window);
        }

        window.display();
    }
}

void GraphicsManager::handleEvents(RenderWindow& window, const FloatRect& menuButton, const FloatRect& addRouteButton, const FloatRect& backButton, const FloatRect& exitButton)
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
                optionsImage = true; 
            }
            else if (addRouteButton.contains(mousePosittion)&&optionsImage) {
                optionsImage = false;
                informationImage = true;
                enteringRouteName = true;
                routeNameInput = "";
            }
            else if (exitButton.contains(mousePosittion)&&optionsImage) {
            
                window.close();
            }
            else if (backButton.contains(mousePosittion) && informationImage) { // Manejo del botón de regreso
                informationImage = false;
                optionsImage = true; // Volver a mostrar el menú de opciones
            }
        }
        if (enteringRouteName && event.type == Event::TextEntered) {
            if (event.text.unicode == '\b' && !routeNameInput.empty()) { 
                routeNameInput.pop_back();
            }
            else if (event.text.unicode == '\n') { 
                enteringRouteName = false;
                informationImage = false;

                if (touristRoutes) {
                    touristRoutes->addRoute(routeNameInput);
                }
            }
            else if (event.text.unicode < 500) {
                routeNameInput += static_cast<char>(event.text.unicode);
            }
        }
        
    }
}

void GraphicsManager::drawMenu(RenderWindow& window, Sprite& sprite)
{
    window.clear();
    window.draw(sprite);
}

void GraphicsManager::drawTextInput(RenderWindow& window)
{
    Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
       
        return;
    }
 
    const int characterLimit = 28; 
    const int lineLimit = 20; 
    const int lineSpacing = 25; 

    char lines[lineLimit][30];
    int lineCounter = 0; 

    for (int i = 0; i < lineLimit; ++i) {
        for (int j = 0; j < 30; ++j) {
            lines[i][j] = '\0';
        }
    }
    string inputText = "Ingrese el nombre de la ruta: " + routeNameInput;
    char currentLine[30]="\0";
    int currentLineLength = 0;

    for (int i = 0; i < inputText.length(); ++i) {
        char currentCharacter = inputText[i];
        if (currentLineLength < characterLimit) {
            currentLine[currentLineLength] = currentCharacter;
            currentLineLength++;
        }
        else {
            if (lineCounter < lineLimit) {
                for (int j = 0; j < currentLineLength; ++j) {
                    lines[lineCounter][j] = currentLine[j];
                }

                lineCounter++;
                currentLineLength = 0; 
                currentLine[currentLineLength] = currentCharacter;
                currentLineLength++;
            }
        }
    }

    
    if (lineCounter < lineLimit && currentLineLength > 0) {
        for (int j = 0; j < currentLineLength; ++j) {
            lines[lineCounter][j] = currentLine[j]; 
        }
        lineCounter++;
    }

    for (int i = 0; i < lineCounter; ++i) {
        Text text(lines[i], font, 20);
        text.setPosition(textLimitArea.left + 5, textLimitArea.top + 5 + i * lineSpacing);
        text.setFillColor(Color::Black);
        window.draw(text);
    }
}


