#include "GraphicsManager.h"

void GraphicsManager::handleEvents(RenderWindow& window)
{
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
		}
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
			Vector2f mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));
			if (menuButton.contains(mousePosition) && menuImage) {
				menuImage = false;
				optionsImage = true;
			}
			else if (addRouteButton.contains(mousePosition) && optionsImage) {
				optionsImage = false;
				informationImage = true;
				enteringRouteName = true;
				routeNameInput = "";
				routePoints->clearPoints();
			}
			else if (exitButton.contains(mousePosition) && optionsImage) {
				saveRoutes(); 
				window.close();
			}
			else if (backButton.contains(mousePosition) && informationImage) {
				informationImage = false;
				optionsImage = true;
				enteringPointName = false;
				enteringPoints = false;
				enteringRouteName = false;
			}
			else if (editRouteButton.contains(mousePosition) && optionsImage) {
				optionsImage = false;
				informationImage = true;
				editingRouteName = true;  
				editingRouteNameInput = ""; 
			} 
			else if (loadRouteButton.contains(mousePosition) && optionsImage) {
				loadRoutes(); 
			}
			if (mapLimitArea.contains(mousePosition) && !enteringPointName) {
				positionX = mousePosition.x;
				positionY = mousePosition.y;
				enteringPointName = true;
			}

			for (int i = 0; i < 7; ++i) {
				if (colorAreas[i].contains(mousePosition)) {
					selectedColor = colors[i];
					break;
				}
			}
		}
		
		if (enteringRouteName && event.type == Event::TextEntered) {
			if (event.text.unicode == '\b' && !routeNameInput.empty()) {
				routeNameInput.pop_back();
			}
			else if (event.text.unicode == 13) {
				enteringRouteName = false;
				touristRoute->addRoute(routeNameInput);
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
				routePoints->addPoint(pointNameInput, positionX, positionY);
				positionX = 0;
				positionY = 0;
				pointNameInput = "";
			}
			else if (event.text.unicode < 500) {
				pointNameInput += static_cast<char>(event.text.unicode);
			}
		}
		if (editingRouteName && event.type == Event::TextEntered) {
			if (event.text.unicode == '\b' && !editingRouteNameInput.empty()) {
				editingRouteNameInput.pop_back();
			}
			else if (event.text.unicode == 13) {
				editingRouteName = false;
				
				TouristRouteNode* current = touristRoute->head;
				bool routeFound = false;
				while (current != nullptr) {
					if (current->routeName == editingRouteNameInput) {
						routeFound = true;
						break;
					}
					current = current->next;
				}
				if (routeFound) {
					routeFoundOptions = true; 
				}  
			}
			else if (event.text.unicode < 500) {
				editingRouteNameInput += static_cast<char>(event.text.unicode);
			}
		}
		if (event.type == Event::TextEntered) {
			if (event.text.unicode == '\b') {

				if (!optionInput.empty()) {
					optionInput.pop_back();
				}
			}
			else if (event.text.unicode == 13) {
				if (optionInput == "1") {
					cout << "hello";
				}
				else if (optionInput == "2") {
					deleteRouteFromList(editingRouteNameInput);
					cout << editingRouteNameInput;
				}
				optionInput = "";
				editingRouteNameInput = ""; 
			}
			else if (event.text.unicode < 500) {
				optionInput += static_cast<char>(event.text.unicode);
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
	if (!font.loadFromFile("C:/Windows/Fonts/times.ttf")) {

		return;
	}
	const int characterLimit = 28;
	const int lineLimit = 10;
	const int lineSpacing = 25;

	char lines[lineLimit][30] = { {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'} };
	int lineCounter = 0;

	string inputText = "Ingrese el nombre de la ruta: " + routeNameInput;
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

void GraphicsManager::drawTextInputPointName(RenderWindow& window)
{
	Font font;
	if (!font.loadFromFile("C:/Windows/Fonts/times.ttf")) {

		return;
	}
	const int characterLimit = 28;
	const int lineLimit = 10;
	const int lineSpacing = 25;

	char lines[lineLimit][30] = { {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'} };
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
	while (current != nullptr && lineCounter < lineLimit)
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

		lines.append(Vertex(Vector2f(current->positionX, current->positionY), selectedColor));

		if (current->next != nullptr) {
			lines.append(Vertex(Vector2f(current->next->positionX, current->next->positionY), selectedColor));
		}
		current = current->next;
	}
	window.draw(lines);
}

void GraphicsManager::drawCircule(RenderWindow& window)
{
	Font font;
	RouteNode* current = routePoints->head;
	if (!font.loadFromFile("C:/Windows/Fonts/times.ttf")) {
		return;
	}

	while (current != nullptr) {
		CircleShape circle(5);
		circle.setPosition(current->positionX - 5, current->positionY - 5);
		circle.setFillColor(selectedColor);
		circle.setOutlineColor(selectedColor);

		Text pointNameText;
		pointNameText.setFont(font);
		pointNameText.setString(current->pointName);
		pointNameText.setCharacterSize(18);
		pointNameText.setFillColor(selectedColor);
		pointNameText.setPosition(current->positionX + 10, current->positionY - 5);

		if (mapLimitArea.contains(circle.getPosition())) {
			window.draw(pointNameText);
			window.draw(circle);
		}
		current = current->next;
	}
}

void GraphicsManager::drawColorPalette(RenderWindow& window)
{
	int startX = 461;
	int startY = 641;
	int sizeRectangle = 50;

	for (size_t i = 0; i < 7; ++i) {
		RectangleShape colorBox(Vector2f(sizeRectangle, sizeRectangle));
		colorBox.setFillColor(colors[i]);
		colorBox.setPosition(startX + i * (static_cast<unsigned long long>(sizeRectangle) + 10), startY);
		window.draw(colorBox);
	}
}

void GraphicsManager::drawTextInputRouteToEdit(RenderWindow& window)
{
	Font font;
	if (!font.loadFromFile("C:/Windows/Fonts/times.ttf")) {
		return;
	}
	if (touristRoute->head == nullptr) {
		return;
	}
	const int characterLimit = 28;
	const int lineLimit = 10;
	const int lineSpacing = 25;

	char lines[lineLimit][30] = { {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'} };
	int lineCounter = 0;

	string inputText = "Ingrese el nombre de la ruta a editar: " + editingRouteNameInput;
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

void GraphicsManager::drawRouteToEdit(RenderWindow& window)
{
	Font font;
	if (!font.loadFromFile("C:/Windows/Fonts/times.ttf")) {
		return;
	}
	if (touristRoute->head == nullptr) {
		return;
	}

	string message;
	bool routeFound = false;

	TouristRouteNode* currentRoute = touristRoute->head;
	if (!editingRouteNameInput.empty()) {
		
		while (currentRoute != nullptr) {
			if (currentRoute->routeName == editingRouteNameInput) {
				routeFound = true;
				RouteList& routePoints = currentRoute->routePointsTourist;
				drawlines(window);
				drawCircule(window);
				break;
			}
			currentRoute = currentRoute->next;
		}
	}

	 if (!routeFound&&currentRoute==nullptr) {
		message = "La ruta '" + editingRouteNameInput + "' no existe.";
	 }
	 if (!message.empty()) {
		 Text displayMessage(message, font, 20);
		 displayMessage.setPosition(10, 10);
		 displayMessage.setFillColor(Color::Black);
		 window.draw(displayMessage);
	 }
}

void GraphicsManager::editoptions(RenderWindow& window)
{
	Font font;
	if (!font.loadFromFile("C:/Windows/Fonts/times.ttf")) {
		return;
	}
	Text message("Digite una opcion:", font, 20);
	message.setPosition(textLimitArea.left + 5, textLimitArea.top + 5);
	message.setFillColor(Color::Black);
	window.draw(message);

	Text option1("1. Eliminar un punto", font, 18);
	option1.setPosition(textLimitArea.left + 5, textLimitArea.top + 35);
	option1.setFillColor(Color::Black);
	window.draw(option1);

	Text option2("2. Eliminar la ruta completa", font, 18);
	option2.setPosition(textLimitArea.left + 5, textLimitArea.top + 60);
	option2.setFillColor(Color::Black);
	window.draw(option2);

	Text userInputText("Opción seleccionada: " + optionInput, font, 18);
	userInputText.setPosition(textLimitArea.left + 5, textLimitArea.top + 95);
	userInputText.setFillColor(Color::Black);
	window.draw(userInputText);
}

void GraphicsManager::deletePointFromRoute(const string& pointName)
{
	TouristRouteNode* currentRoute = touristRoute->head;
	while (currentRoute != nullptr) {
		if (currentRoute->routeName == editingRouteNameInput) {
			currentRoute->routePointsTourist.deletePoint(pointName);
			break;
		}
		currentRoute = currentRoute->next;
	}
}

void GraphicsManager::deleteRouteFromList(const string& routeName)
{
	touristRoute->deleteRoute(routeName);  
}

void GraphicsManager::saveRoutes()
{
	touristRoute->saveRoutesToFiles("C:/Proyecto/RutasTuristicas/RutasTuristicas/assets/Route");
}

void GraphicsManager::loadRoutes()
{
	touristRoute->loadRoutesFromFiles("C:/Proyecto/RutasTuristicas/RutasTuristicas/assets/Route");
}

GraphicsManager::GraphicsManager()
{
	menuImage = true;
	optionsImage = false;
	informationImage = false;
	enteringRouteName = false;
	enteringPointName = false;
	enteringPoints = false;
	editingRouteName = false;
	routeFoundOptions = false;
	deletePoint = false;
	deleteRoute = false;
	routeNameInput = " ";
	pointNameInput = " ";
	editingRouteNameInput = " ";
	optionInput = " ";
	touristRoute = new TouristRouteList();
	routePoints = new RouteList();
	menuButton = FloatRect(50, 626, 206, 84);
	addRouteButton = FloatRect(50, 17, 206, 84);
	loadRouteButton = FloatRect(50, 111, 206, 84);
	editRouteButton = FloatRect(50, 212, 206, 84);
	exitButton = FloatRect(50, 305, 206, 84);
	backButton = FloatRect(65, 617, 206, 84);
	textLimitArea = FloatRect(12, 41, 300, 280);
	textLimitArea2 = FloatRect(12, 321, 300, 280);
	mapLimitArea = FloatRect(350, 2, 931, 642);
	for (int i = 0; i < 7; ++i) {
		colorAreas[i] = FloatRect(461 + i * 60, 641, 50, 50);
	}
	colors[0] = Color::Black;
	colors[1] = Color::Red;
	colors[2] = Color::Green;
	colors[3] = Color::Blue;
	colors[4] = Color::Yellow;
	colors[5] = Color::Magenta;
	colors[6] = Color::Cyan;
	selectedColor = colors[3];
	positionX = 0;
	positionY = 0;
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
			drawRouteName(window);
			if (enteringRouteName) {
				drawTextInputRouteName(window);
			}
			else if (enteringPoints) {
				drawPointInstruction(window);
				if (enteringPointName) {
					drawTextInputPointName(window);
				}
				drawCircule(window);
				drawlines(window);
				drawColorPalette(window);
			}
			if (editingRouteName) {
				drawTextInputRouteToEdit(window);
				drawRouteToEdit(window);
			}
			if (routeFoundOptions) {
				
				editoptions(window);
				drawColorPalette(window);
			}
			
		}
		window.display();
	}
}

GraphicsManager::~GraphicsManager()
{
	delete touristRoute;
	delete routePoints;
}