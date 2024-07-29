/**
 * @file Easing.h
 * @brief Contains the implementation of the Easing class for performing easing functions.
 */

#include <./include/Easing.h>

using namespace gpp;

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
 * 
 * @note This method provides a linear interpolation by default. Experiment with the parameters for different easing effects.
 */
float Easing::easeIn(float t, float b, float c, float d)
{
    // Experiment with t, b, c, and d
    // Linear interpolation
    return c * (t / d) + b;
}

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
 * 
 * @note This method provides a linear interpolation by default. Experiment with the parameters for different easing effects.
 */
float Easing::easeOut(float t, float b, float c, float d)
{
    // Experiment with t, b, c, and d
    // Linear interpolation
    t /= d;
    return -c * t * (t - 2) + b;
}
