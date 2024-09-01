#include <include/pointCube.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <ostream>

PointCube::PointCube(glm::vec3 pos, float s)
    : position(pos), size(s), collected(false) {}

void PointCube::draw(GLuint shaderProgram, GLuint VAO)
{
}


bool PointCube::checkCollision(const glm::vec3& playerPos, float playerSize)
{
    if (!collected &&
        fabs(playerPos.x - position.x) < (playerSize + size) &&
        fabs(playerPos.y - position.y) < (playerSize + size) &&
        fabs(playerPos.z - position.z) < (playerSize + size)) {
        collected = true; // Mark as collected
        return true;
    }
    return false;
}

void PointCube::render() const 
{
    if (!collected) {
        glPushMatrix();

        std::cout << "Rendering PointCube at position: ("
            << position.x << ", "
            << position.y << ", "
            << position.z << ")" << std::endl;

        glTranslatef(position.x, position.y, position.z);
        glScalef(size, size, size);

        glBegin(GL_QUADS);

        // Front Face
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);

        // Back Face
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);

        // Top Face
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);

        // Bottom Face
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);

        // Right Face
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);

        // Left Face
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);

        glEnd();

        glPopMatrix();
    }
}