#include "Board.h"
#include <iostream>

Board::Board() {
    this->setup();
}

void Board::spawnTile() {
    int randomX, randomY, state;
    bool bSpawned = false;

    if ((1 + (rand() % 10)) == 1) {
        state = 4;
    }
    else {
        state = 2;
    }

    while (!bSpawned) {
        randomX = 1 + (rand() % 4);
        randomY = 1 + (rand() % 4);
        for (std::list<Node>::iterator it = this->grid.begin(); it != this->grid.end(); it++) {
            if (randomX == it->getX() && randomY == it->getY()) {
                if (it->getState() == 0) {
                    it->setState(state);
                    it->setSpawnStatus(true);
                    bSpawned = true;
                }
            }
        }
    }
}

void Board::fillGrid() {
    for (int y = 1; y <= 4; y++) {
        for (int x = 1; x <= 4; x++) {
            Node tile(x, y, 0);
            this->grid.push_back(tile);
        }
    }
}

int Board::getScore() {
    int pointsSum = 0;
    for (std::list<Node>::iterator it = this->grid.begin(); it != this->grid.end(); it++) {
        pointsSum += it->getState();
    }
    return pointsSum;
}

void Board::drawUI() {
    window.clear(sf::Color(250, 248, 239));

    sf::Texture boardTxt;
    boardTxt.loadFromFile("board.png");

    sf::Sprite boardImg;
    boardImg.setTexture(boardTxt);
    boardImg.setPosition(0, 102);
    window.draw(boardImg);

    sf::RectangleShape scoreBox(sf::Vector2f(150, 80));
    scoreBox.setPosition(10, 10);
    scoreBox.setFillColor(sf::Color(187, 173, 160, 100));
    window.draw(scoreBox);

    sf::Font font;
    if (!font.loadFromFile("digital-7.ttf")) {
        cout << "nie uda�o si� za�adowa� czcionki";
    }

    sf::Text scoreText;
    scoreText.setString("Wynik");
    scoreText.setPosition(51, 5);
    scoreText.setCharacterSize(32);
    scoreText.setFont(font);
    window.draw(scoreText);

    sf::Text score;
    score.setString(std::to_string(getScore()));
    score.setCharacterSize(38);
    score.setPosition(48, 41);
    score.setFont(font);
    window.draw(score);

    sf::Text instruction;
    instruction.setString("Stworz plytke o wartosci 2048, aby wygrac. \n\nPoruszaj plytkami przy pomocy WSAD lub strzalek. \n\nZ kazdym ruchem pojawia sie nowa plytka (2 lub 4). \n\nKazda nowa plytka ma zolta obwodke.");
    instruction.setCharacterSize(20);
    instruction.setPosition(175, 10);
    instruction.setFont(font);
    instruction.setFillColor(sf::Color::Black);
    window.draw(instruction);
}

void Board::drawWinScreen() {
    sf::RectangleShape winFrame(sf::Vector2f(580, 580));
    winFrame.setPosition(10, 115);
    winFrame.setFillColor(sf::Color(187, 173, 160, 215));
    window.draw(winFrame);

    sf::Font font;
    if (!font.loadFromFile("digital-7.ttf")) {
        cout << "nie uda�o si� za�adowa� czcionki";
    }

    sf::Text winText;
    winText.setString("GRATULACJE, WYGRALES!");
    winText.setPosition(10, 300);
    winText.setCharacterSize(64);
    winText.setFont(font);
    window.draw(winText);

    sf::Text instruction;
    instruction.setString("(kliknij esc, aby wyjsc)");
    instruction.setPosition(150, 380);
    instruction.setCharacterSize(32);
    instruction.setFont(font);
    window.draw(instruction);
}

void Board::drawLooseScreen() {
    sf::RectangleShape lFrame(sf::Vector2f(580, 580));
    lFrame.setPosition(10, 115);
    lFrame.setFillColor(sf::Color(187, 173, 160, 215));
    window.draw(lFrame);

    sf::Font font;
    if (!font.loadFromFile("digital-7.ttf")) {
        cout << "nie uda�o si� za�adowa� czcionki";
    }

    sf::Text lText;
    lText.setString("Przegrales!");
    lText.setPosition(150, 300);
    lText.setCharacterSize(64);
    lText.setFont(font);
    window.draw(lText);

    sf::Text instruction;
    instruction.setString("(kliknij esc, aby wyjsc)");
    instruction.setPosition(150, 380);
    instruction.setCharacterSize(32);
    instruction.setFont(font);
    window.draw(instruction);
}

void Board::setup() {
    this->fillGrid();
    window.create(sf::VideoMode(600, 700), "2048");

    this->spawnTile();
    this->spawnTile();

    this->drawUI();
}

bool Board::hasWon() {
    for (std::list<Node>::iterator it = this->grid.begin(); it != this->grid.end(); it++) {
        if (it->getState() == 2048) {
            return true;
        }
    }
    return false;
}

bool Board::isAbleToMove() {
    for (int iteration = 0; iteration < 2; iteration++) { // w pierwszej iteracji sprawdzamy czy można się ruszyć poziomo, w drugiej czy można pionowo
        for (int counter = 3; counter >= 0; counter--) { // iteracja 4 razy, ponieważ plansza jest 4x4
            std::vector<Node> currRow; // tworzymy vector, w którym będą wszystkie komórki danego rzędu/kolumny
            for (std::list<Node>::iterator it = this->grid.begin(); it != this->grid.end(); it++) {
                if (iteration == 0) {
                    if (it->getY() == counter + 1) {
                        Node currNode(it->getX(), it->getY(), it->getState());
                        currRow.push_back(currNode); // wpisujemy do vectora wszystkie komórki z danego rzędu
                    }
                }
                else if (iteration == 1) {
                    if (it->getX() == counter + 1) {
                        Node currNode(it->getX(), it->getY(), it->getState());
                        currRow.push_back(currNode); // wpisujemy do vectora wszystkie komórki z danej kolumny
                    }
                }
            }
            for (int i = 2; i >= 0; i--) { // iteracja od 3. pola dla ruchu w prawo/dol
                for (int j = i; j < 3; j++) { // iteracja od numeru aktualnego pola do pola numer 3
                    if (currRow[j].getState() != 0) { // jesli komórka ma wartość
                        if (currRow[j].getState() == currRow[j + 1].getState() || currRow[j + 1].getState() == 0) {
                            // jeśli aktualna komórka ma wartość taką samą jak następna, lub następna komórka nie ma wartości (jest pusta)
                            return true; // to można wykonać ruch
                        }
                    }
                }
            }
            for (int i = 1; i < 4; i++) { // iteracja od 2. pola dla ruchu w lewo/gora
                for (int j = i; j > 0; j--) { // iteracja od numeru aktualnego pola do pola numer 1
                    if (currRow[j].getState() != 0) { // jesli komórka ma wartość
                        if (currRow[j].getState() == currRow[j - 1].getState() || currRow[j - 1].getState() == 0) {
                            // jeśli aktualna komórka ma wartość taką samą jak następna, lub następna komórka nie ma wartości (jest pusta)
                            return true; // to można wykonać ruch
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool Board::hasLost() {
    for (std::list<Node>::iterator it = this->grid.begin(); it != this->grid.end(); it++) {
        if (it->getState() == 0) {
            return false;
        }
    }

    if (this->isAbleToMove()) {
        return false;
    }

    return true;
}

void Board::captureKeyboardInput() {
    sf::Event event;
    sf::Keyboard keyboard;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            if (this->canMove && !this->hasWon() && !this->hasLost()) {
                if (keyboard.isKeyPressed(keyboard.W) || keyboard.isKeyPressed(keyboard.Up)) {
                    this->move(UP);
                }
                else if (keyboard.isKeyPressed(keyboard.S) || keyboard.isKeyPressed(keyboard.Down)) {
                    this->move(DOWN);
                }
                else if (keyboard.isKeyPressed(keyboard.A) || keyboard.isKeyPressed(keyboard.Left)) {
                    this->move(LEFT);
                }
                else if (keyboard.isKeyPressed(keyboard.D) || keyboard.isKeyPressed(keyboard.Right)) {
                    this->move(RIGHT);
                }
            }
        }
    }
}

void Board::move(Direction dir) {
    this->canMove = false;
    bool wasMoveMade = false;

    for (int counter = 3; counter >= 0; counter--) { // iteracja 4 razy, ponieważ plansza jest 4x4
        std::vector<Node> currRow; // tworzymy vector, w którym będą wszystkie komórki danego rzędu/kolumny
        for (std::list<Node>::iterator it = this->grid.begin(); it != this->grid.end(); it++) { 
            if (dir == RIGHT || dir == LEFT) {
                if (it->getY() == counter + 1) {
                    Node currNode(it->getX(), it->getY(), it->getState());
                    currRow.push_back(currNode); // wpisujemy do vectora wszystkie komórki z danego rzędu
                }
            }
            else if (dir == UP || dir == DOWN) {
                if (it->getX() == counter + 1) {
                    Node currNode(it->getX(), it->getY(), it->getState());
                    currRow.push_back(currNode); // wpisujemy do vectora wszystkie komórki z danej kolumny
                }
            }
        }
        bool wasMerged = false; // w jednym ruchu możemy połączyć dwie płytki ze sobą tylko raz, więc deklarujemy zmienną bool
        if (dir == RIGHT || dir == DOWN) {
            for (int i = 2; i >= 0; i--) { // iteracja od 3. pola do 1. pola
                for (int j = i; j < 3; j++) { // iteracja od numeru aktualnego pola do pola numer 3
                    if (currRow[j].getState() != 0) { // jeśli aktualnie rozpatrywana komórka ma wartość
                        if (currRow[j].getState() == currRow[j + 1].getState() && !wasMerged) {
                            // jeśli następna komórka ma wartość taką jak aktualna i żadne połączenie nie zostało jeszcze wykonane w tym rzędzie
                            currRow[j + 1].setState(currRow[j].getState() * 2); // podwajamy wartość następnej komórki
                            currRow[j].setState(0); // ustawiamy wartość aktualnej na 0
                            // w ten sposób "łączymy płytki"
                            wasMerged = true;
                            wasMoveMade = true;
                        }
                        if (currRow[j + 1].getState() == 0) { // jeśli następna komórka nie ma wartości to
                            currRow[j + 1].setState(currRow[j].getState()); // ustawiamy wartość następnej komórki na wartość aktualnej komórki
                            currRow[j].setState(0); // ustawiamy wartość aktualnej komórki na 0
                            // w ten sposób płytka się "przesuwa"
                            wasMoveMade = true;
                        }
                    }
                }
            }
        }
        else if (dir == LEFT || dir == UP) {
            for (int i = 1; i < 4; i++) { // iteracja od 2. pola
                for (int j = i; j > 0; j--) { // iteracja od numeru aktualnego pola do pola numer 1
                    if (currRow[j].getState() != 0) { 
                        if (currRow[j].getState() == currRow[j - 1].getState() && !wasMerged) {
                            currRow[j - 1].setState(currRow[j].getState() * 2);
                            currRow[j].setState(0);
                            wasMerged = true;
                            wasMoveMade = true;
                        }
                        if (currRow[j - 1].getState() == 0) {
                            currRow[j - 1].setState(currRow[j].getState());
                            currRow[j].setState(0);
                            wasMoveMade = true;
                        }
                    }
                }
            }
        }
        for (std::vector<Node>::iterator it = currRow.begin(); it != currRow.end(); it++) {
            it->insert(this->grid, it->getX(), it->getY(), it->getState()); // komórki z wektora aktualnego rzędu/kolumny wpisujemy do listy grid
            // "wrzucamy" je na plansze
        }
    }

    sf::Clock clock;
    while (!this->canMove) {
        sf::Time elapsed = clock.getElapsedTime();

        if (elapsed.asMilliseconds() >= 200) {
            this->canMove = true; // cooldown przed następnym ruchem
        }
    }

    if (wasMoveMade && !this->hasWon() && !this->hasLost()) {
        this->spawnTile(); // jeśli udało nam się wykonać ruch to spawnujemy nową płytkę
    }
    this->refresh(); // update planszy
}

void Board::refresh() {

    this->drawUI();

    for (std::list<Node>::iterator it = this->grid.begin(); it != this->grid.end(); it++) {
        if (it->getState() != 0) {
            sf::Texture tileTxt;
            tileTxt.loadFromFile("tile" + std::to_string(it->getState()) + ".png");
            sf::Sprite tile;
            tile.setTexture(tileTxt);
            tile.setPosition(it->getPosX(), it->getPosY());

            // zolta obwodka na zespawnowanym kafelku
            if (it->getSpawnedStatus() == true) {
                it->setSpawnStatus(false);
                sf::RectangleShape rect(sf::Vector2f(130, 130));
                rect.setPosition(it->getPosX(), it->getPosY());
                rect.setFillColor(sf::Color::Transparent);
                rect.setOutlineThickness(2);
                rect.setOutlineColor(sf::Color::Yellow);
                window.draw(rect);
            }
            window.draw(tile);
        }
    }

    if (this->hasWon()) {
        this->drawWinScreen();
    }
    if (this->hasLost()) {
        this->drawLooseScreen();
    }

    window.display();
}
