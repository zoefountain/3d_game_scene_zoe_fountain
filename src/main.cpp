/**
 * @file Game.h
 * @brief Contains the main entry point for the game application.
 */
#include <SFML/Window.hpp>
#include <./include/Game.h>
#define GLM_ENABLE_EXPERIMENTAL

/**
 * @brief The main entry point for the game application.
 * 
 * This function initializes the game by setting up SFML context settings, creates an instance of the Game class,
 * and runs the game loop. If an exception occurs during the execution of the game, it is caught and handled,
 * printing an error message to the standard error stream.
 * 
 * @return 0 if the program exits successfully, -1 if an exception occurs.
 */
int main() {
    sf::ContextSettings settings;
    settings.depthBits = 24; // Request a 24-bit depth buffer

    Game game(10, 10, settings); // Initialize game with a 10x10 maze
    game.run();

    return 0;
}
