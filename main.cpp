#include "TheGame.h"

void init() {
    std::cout << "Initializing game..." << std::endl;
}

void cleanup() {
    std::cout << "Cleaning up game..." << std::endl;
}

int main() {
    Game game;

    DrawableGameComponent* dgc1 = new DrawableGameComponent();
    DrawableGameComponent* dgc2 = new DrawableGameComponent();

    game.Add(dgc1);
    game.Add(dgc2);

    game.SetInitialise(init);
    game.SetTerminate(cleanup);

    game.Run();

    return 0;
}
