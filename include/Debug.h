// Undefine DEBUG if it is already defined to avoid redefinition
#ifdef DEBUG
#undef DEBUG
#endif

// Define DEBUG to 1 or 2 for a greater level of debug messages
#define DEBUG 1

// MACRO for streaming debug messages
#if defined DEBUG // Check if DEBUG is defined
    // Check the DEBUG level to determine whether to print debug messages
    #if (DEBUG >= 1) // DEBUG level 1 or higher
        #define DEBUG_MSG(x) (std::cout << (x) << std::endl) // Print the debug message using std::cout
    #else // DEBUG level is 0
        #define DEBUG_MSG(x) // No action for debug messages
    #endif
#else // DEBUG is not defined
    #define DEBUG_MSG(x) // No action for debug messages
#endif
