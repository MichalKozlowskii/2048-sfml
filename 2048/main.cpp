#include  "SFML/Graphics.hpp" // replace quotes with less than and greater than symbols
#include "Board.h"

int main()
{
    srand(time(NULL));
    Board board;
    board.refresh();
    board.captureKeyboardInput();
    return 0;
}