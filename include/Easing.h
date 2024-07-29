#ifndef EASING_H // If the macro EASING_H is not defined
#define EASING_H // Define the macro EASING_H to prevent multiple inclusions of this header file

// Include GLM headers for mathematics library
#include <glm/glm.hpp>                  // OpenGL Mathematics

namespace gpp
{
    /**
     * @file Easing.h
     * @class Easing
     * @brief Provides static methods for performing easing animations.
     */
    class Easing
    {
    public:
        /**
         * @brief Performs easing in animation.
         *
         * This method calculates the eased value of a property at the current time using an easing-in function.
         *
         * @param t Current time (independent variable).
         * @param b Start value of the property being eased.
         * @param c Change in value of the property being eased (target value - start value).
         * @param d Total duration of the easing animation.
         * @return The eased value of the property at the current time.
         */
        static float easeIn(float t, float b, float c, float d);

        /**
         * @brief Performs easing out animation.
         *
         * This method calculates the eased value of a property at the current time using an easing-out function.
         *
         * @param t Current time (independent variable).
         * @param b Start value of the property being eased.
         * @param c Change in value of the property being eased (target value - start value).
         * @param d Total duration of the easing animation.
         * @return The eased value of the property at the current time.
         */
        static float easeOut(float t, float b, float c, float d);

    private:
        // No private members for now
    };
}

#endif // EASING_H
