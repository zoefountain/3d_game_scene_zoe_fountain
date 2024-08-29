#ifndef POINTCUBE_H
#define POINTCUBE_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/glut.h> // or <GL/freeglut.h> depending on your setup

class PointCube {
public:
    glm::vec3 position;
    float size;
    bool collected;

    PointCube(glm::vec3 pos, float s) : position(pos), size(s), collected(false) {}

    void render() {
        if (collected) return; // Don't render if collected

        // Render the cube
        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glScalef(size, size, size);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    bool checkCollision(const glm::vec3& playerPosition, float playerSize) {
        // Simple collision detection based on distance
        float distance = glm::length(playerPosition - position);
        if (distance < (playerSize + size) / 2.0f) {
            collected = true;
            return true;
        }
        return false;
    }
};

#endif