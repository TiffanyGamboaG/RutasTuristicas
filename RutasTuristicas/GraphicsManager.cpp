#include "GraphicsManager.h"

GraphicsManager::GraphicsManager()
{
    menuImage =true;
    optionsImage = false;
    informationImage = false;
    enteringRouteName = false;
    enteringPointName = false;
    enteringPoints = false; 
    routeNameInput = " "; 
    pointNameInput = " ";
    touristRoute = new TouristRouteList();
    routePoints = new RouteList();
    menuButton = FloatRect(50, 626, 206, 84); 
    addRouteButton = FloatRect(50, 17, 206, 84);
    showRoutesButton = FloatRect(50, 111, 206, 84);
    editRouteButton = FloatRect(50, 212, 206, 84);
    changeColorButton = FloatRect(50, 305, 206, 84);
    deleteRouteButton = FloatRect(50, 401, 206, 84);
    exitButton = FloatRect(50, 498, 206, 84);
    backButton = FloatRect(65, 617, 206, 84);
    textLimitArea = FloatRect(12, 41, 300, 280);
    textLimitArea2 = FloatRect(12, 321, 300, 280);
}

void GraphicsManager::loadImageMenu()
{ 
    RenderWindow window(VideoMode(1280, 720), "Ventana");

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
        handleEvents(window);

        window.clear();
        if (menuImage) {
            drawMenu(window, menuSprite);
        }
        else if (optionsImage) {
            drawMenu(window, optionsMenuSprite);
        }
        else if (informationImage) {
            drawMenu(window, informationSprite);
            if (enteringRouteName) {
                drawTextInputRouteName(window);
                drawRouteName(window);
            }
            else if (enteringPoints) {
                drawPointInstruction(window);
                if (enteringPointName) {
                    drawTextInputPointName(window); 
                }
                drawCircule(window);
                drawlines(window); 
            }
        }
        
        window.display();
    }
}

void GraphicsManager::handleEvents(RenderWindow& window)
{
    Event event;
 
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            Vector2f mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));
            if (menuButton.contains(mousePosition)&&menuImage) {
                menuImage = false;
                optionsImage = true; 
            }
            else if (addRouteButton.contains(mousePosition)&&optionsImage) {
                optionsImage = false;
                informationImage = true;
                enteringRouteName = true;
                routeNameInput = "";
                
            }
            else if (exitButton.contains(mousePosition)&&optionsImage) {
            
                window.close();
            }
            else if (backButton.contains(mousePosition) && informationImage) { 
                informationImage = false;
                optionsImage = true; 

            }
            else if (enteringPoints&&!enteringPointName) { 
                enteringPointName = true; 
                pointNameInput = ""; 
                routePoints->addPoint(pointNameInput, mousePosition.x, mousePosition.y);
            }
        }
       
        if (enteringRouteName && event.type == Event::TextEntered) {
            if (event.text.unicode == '\b' && !routeNameInput.empty()) {
                routeNameInput.pop_back();
            }
            else if (event.text.unicode == 13) { 
                enteringRouteName = false;
                touristRoute->addRoute(routeNameInput);
                cout << "Ruta agregada: " << routeNameInput << endl;
                routeNameInput = "";
                enteringPoints = true; 
            }
            else if (event.text.unicode < 500) {
                routeNameInput += static_cast<char>(event.text.unicode);
            }
        }
        if (enteringPointName && event.type == Event::TextEntered) {
            if (event.text.unicode == '\b' && !pointNameInput.empty()) {
                pointNameInput.pop_back();
            }
            else if (event.text.unicode == 13) { 
                enteringPointName = false;
                cout << "Punto agregado: " << pointNameInput << endl;
                pointNameInput = ""; 
            }
            else if (event.text.unicode < 500) {
                pointNameInput += static_cast<char>(event.text.unicode);
            }
        }
      
    }
} 

void GraphicsManager::drawMenu(RenderWindow& window, Sprite& sprite)
{
    window.clear();
    window.draw(sprite); 
   
}

void GraphicsManager::drawTextInputRouteName(RenderWindow& window)
{
    Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/times.ttf")){
       
        return;
    }
    const int characterLimit = 28; 
    const int lineLimit = 10; 
    const int lineSpacing = 25; 

    char lines[lineLimit][30]= { {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'} };
    int lineCounter = 0; 

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

GraphicsManager::~GraphicsManager(){
 
    delete touristRoute; 
    delete routePoints; 
}

void GraphicsManager::drawTextInputPointName(RenderWindow& window)
{
    Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/times.ttf")) {

        return;
    }
    const int characterLimit = 28;
    const int lineLimit = 10;
    const int lineSpacing = 25;

    char lines[lineLimit][30]= { {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'} };
    int lineCounter = 1;

    string inputText = "Ingrese el nombre del punto: " + pointNameInput;
    char currentLine[30] = "\0";
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

void GraphicsManager::drawPointInstruction(RenderWindow& window)
{
    Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/times.ttf")) {
        return;
    }
    string inputText;
     if (enteringPoints) {
        inputText = "Realice un clic sobre el punto ";
     }

    Text text(inputText, font, 20);
    text.setPosition(textLimitArea.left + 5, textLimitArea.top + 5);
    text.setFillColor(Color::Black);
    window.draw(text);
}

void GraphicsManager::drawRouteName(RenderWindow& window)
{
    Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/times.ttf")) {
        return;
    }
    const int characterLimit = 28;
    const int lineLimit = 10;
    const int lineSpacing = 25;

    if (touristRoute->head == nullptr) {
        Text noRoutesText("No hay rutas disponibles.", font, 20);
        noRoutesText.setPosition(textLimitArea2.left + 5, textLimitArea2.top + 5);
        noRoutesText.setFillColor(Color::Black);
        window.draw(noRoutesText);
        return; 
    }

    Text headerText("Rutas Agregadas", font, 20);
    headerText.setPosition(textLimitArea2.left + 5, textLimitArea2.top + 5);
    headerText.setFillColor(Color::Black);
    window.draw(headerText);

    int lineCounter = 1; 
    TouristRouteNode* current = touristRoute->head;

    while (current!=nullptr&& lineCounter < lineLimit)
    {
        string routeName = current->routeName;
        if (routeName.length() > characterLimit) {
            routeName = routeName.substr(0, characterLimit) + "..."; 
        }

        Text text(routeName, font, 20);
        text.setPosition(textLimitArea2.left + 5, textLimitArea2.top + 5 + lineCounter * lineSpacing);
        text.setFillColor(Color::Black);

        
        window.draw(text);

        current = current->next; 
        lineCounter++;  
    }
}

void GraphicsManager::drawlines(RenderWindow& window)
{
    VertexArray lines(Lines);  

    RouteNode* current = routePoints->head; 

    while (current != nullptr) {
        
        lines.append(Vertex(Vector2f(current->positionX, current->positionY), Color::Red)); 

        if (current->next != nullptr) {
            lines.append(Vertex(Vector2f(current->next->positionX, current->next->positionY), Color::Red)); 
        }
        
        current = current->next;  
    }
    window.draw(lines); 
}

void GraphicsManager::drawCircule(RenderWindow& window)
{
    RouteNode* current = routePoints->head;
    while (current != nullptr) {
        CircleShape circle(5); 
        circle.setPosition(current->positionX - 5, current->positionY - 5); 
        circle.setFillColor(Color::Green);
        window.draw(circle);
        current = current->next;
    }
}
