#ifndef POINT_CUBE_H
#define POINT_CUBE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class PointCube {
public:
    glm::vec3 position; // Position of the cube
    float size;         // Size of the cube
    bool collected;     // Whether the cube has been collected
    PointCube() : collected(false) {}

    PointCube(glm::vec3 pos, float s);
    void draw(GLuint shaderProgram, GLuint VAO);
    bool checkCollision(const glm::vec3& playerPos, float playerSize);
    void render() const;
};

#endif