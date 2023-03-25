#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ctime>

class GameComponent {
public:
    GameComponent() {
        id = ++instances;
    }

    virtual ~GameComponent() {}

    int GetId() {
        return id;
    }

    virtual void Update(time_t currentTime) {
        std::cout << "GameComponent id " << id << " updated at " << ctime(&currentTime);
    }

private:
    int id;
    static int instances;
};

int GameComponent::instances = 0;

class DrawableGameComponent : public GameComponent {
public:
    enum Direction {
        Up,
        Down,
        Left,
        Right
    };

    DrawableGameComponent() {
        x = 0;
        y = 0;
        direction = Right;
    }

    virtual ~DrawableGameComponent() {}

    virtual void Update(time_t currentTime) {
        std::cout << "DrawableGameComponent id " << GetId() << " updated at " << ctime(&currentTime);
        IncrementPosition();
        Draw();
        ChangeDirection();
    }

    void printDirection(Direction direction) {
        switch (direction) {
            case Up:
                std::cout << "Up" << std::endl;
                break;
            case Down:
                std::cout << "Down" << std::endl;
                break;
            case Left:
                std::cout << "Left" << std::endl;
                break;
            case Right:
                std::cout << "Right" << std::endl;
                break;
            default:
                std::cout << "Error" << std::endl;
                break;
        }
    }

    virtual void Draw() {
        std::string directionString;
        switch (direction) {
            case Up:
                directionString = "Up";
                break;
            case Down:
                directionString = "Down";
                break;
            case Left:
                directionString = "Left";
                break;
            case Right:
                directionString = "Right";
                break;
            default:
                directionString = "Unknown";
                break;
        }

        std::cout << "Direction: " << directionString << ", x: " << x << ", y: " << y << std::endl;
    }

    void IncrementPosition() {
        switch (direction) {
            case Up:
                y--;
                break;
            case Down:
                y++;
                break;
            case Left:
                x--;
                break;
            case Right:
                x++;
                break;
        }
        x = std::max(0, std::min(80, x));
        y = std::max(0, std::min(20, y));
    }

    void ChangeDirection() {
        Direction newDirection;
        do {
            newDirection = static_cast<Direction>(rand() % 4);
        } while (newDirection == direction);
        direction = newDirection;
    }

private:
    int x;
    int y;
    Direction direction;
};

class Game {
public:
    typedef void (*FP)();

    Game() {
        componentCount = 0;
        Initialise = nullptr;
        Terminate = nullptr;
    }

    virtual ~Game() {}

    void Add(GameComponent* component) {
        components[componentCount] = component;
        componentCount++;
    }

    void SetInitialise(FP func) {
        Initialise = func;
    }

    void SetTerminate(FP func) {
        Terminate = func;
    }

    void Run() {
        if (Initialise) {
            std::cout << "Initialising game" << std::endl;
            (*Initialise)();
        }

        // Game loop
        time_t startTime = time(nullptr);
        int numUpdates = 0;
        while (numUpdates < 5) {
            time_t currentTime = time(nullptr);
            if (currentTime - startTime >= 1) {
                for (int i = 0; i < componentCount; i++) {
                    components[i]->Update(currentTime);
                }
                startTime = currentTime;
                numUpdates++;
            }
        }

        if (Terminate) {
            std::cout << "Terminating game" << std::endl;
            (*Terminate)();
        }
    }

private:
    GameComponent* components[100];
    int componentCount;
    FP Initialise;
    FP Terminate;
};

#endif // GAME_H
