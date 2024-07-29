/**
 * @file Game.h
 * @brief Contains the main entry point for the game application.
 */

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
int main(void)
{
    // Setup SFML Context Settings
    // For more information, refer to:
    // - https://www.sfml-dev.org/documentation/2.6.1/structsf_1_1ContextSettings.php
    // - https://www.sfml-dev.org/documentation/2.6.1/ContextSettings_8hpp_source.php
    ContextSettings settings;
    settings.depthBits = 24u; // for depth buffer Z-Buffer
    settings.antialiasingLevel = 4u;

    try
    {
        // Create a reference to the game and run
        Game game(settings);
        game.run();
    }
    catch (const exception &e)
    {
        // Exception occurred, print error message
        cerr << "Exception: " << e.what() << endl;
        // Return -1 indicating program exited with errors
        return -1;
    }

    // Return 0 indicating program exited successfully
    return 0;
}
