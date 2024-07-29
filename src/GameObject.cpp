/**
 * @file GameObject.h
 * @brief Contains the implementation of the GameObject class, representing a game object with vertex, color, and UV data.
 */

#include <./include/GameObject.h>

using namespace gpp; // GPP namespace

/**
 * @brief Default constructor for the GameObject class.
 *
 * Initializes a GameObject by copying vertex, color, and UV data from the Cube class.
 * UV data is copied to all faces of the GameObject.
 * The position of the GameObject is set to the origin (0, 0, 0).
 */
GameObject::GameObject(TYPE type)
{
    // Copy the Cube contents into GameObject
    memcpy(this->vertex, vertices, sizeof(this->vertex));
    memcpy(this->colour, colours, sizeof(this->colour));
    memcpy(this->uv, uvs, sizeof(this->uv));

    // Copy UV's to all faces
    for (int i = 1; i < 6; i++)
        memcpy(&uv[i * 4 * 2], &uv[0], 2 * 4 * sizeof(GLfloat));

    memcpy(this->index, indices, sizeof(this->index));

    this->position = vec3(0.0f); // Init Position at 0.0f
    this->type = type;

    // Initialize MVP matrix as Identity Matrix
	this->mvp = mat4(
		1.0f // Identity Matrix
	);

    // Initialize Model matrix as Identity Matrix
	this->model = mat4(
		1.0f // Identity Matrix
	);
}

/**
 * @brief Destructor for the GameObject class.
 *
 * This is a default destructor and does not currently perform any specific cleanup tasks.
 */
GameObject::~GameObject()
{
}

/**
 * @brief Getter method for retrieving the position of the GameObject.
 *
 * @return The position of the GameObject as a vec3 vector.
 */
vec3 GameObject::getPosition() { return this->position; }

/**
 * @brief Setter method for setting the position of the GameObject.
 *
 * @param position The new position of the GameObject as a vec3 vector.
 */
void GameObject::setPosition(vec3 position) { this->position = position; }

/**
 * @brief Getter method for retrieving the model of the GameObject.
 *
 * @return The model of the GameObject as a mat4 matrix.
 */
mat4 GameObject::getModelMatrix() { return this->model; }

/**
 * @brief Setter method for setting the model of the GameObject.
 *
 * @param model The new model of the GameObject as a mat4 matrix.
 */
void GameObject::setModelMatrix(mat4 model) { this->model = model; }

/**
 * @brief Getter method for retrieving the model view projection of the GameObject.
 *
 * @return The model view projection of the GameObject as a mat4 matrix.
 */
mat4 GameObject::getMVPMatrix() { return this->mvp; }

/**
 * @brief Setter method for setting the model view projection of the GameObject.
 *
 * @param model The new model view projection of the GameObject as a mat4 matrix.
 */
void GameObject::setMVPMatrix(mat4 mvp) { this->mvp = mvp; }

/**
 * @brief Getter method for retrieving the first element of the vertex array.
 *
 * @return A pointer to the first element of the vertex array.
 */
GLfloat *GameObject::getVertex() { return this->vertex; }

/**
 * @brief Getter method for retrieving the count of vertices.
 *
 * @return The count of vertices in the vertex array.
 */
int GameObject::getVertexCount() { return ARRAY_SIZE(vertex) / 3; }

/**
 * @brief Getter method for retrieving the first element of the color array.
 *
 * @return A pointer to the first element of the color array.
 */
GLfloat *GameObject::getColor() { return this->colour; }

/**
 * @brief Getter method for retrieving the count of colours.
 *
 * @return The count of colours in the color array.
 */
int GameObject::getColorCount() { return ARRAY_SIZE(colours) / 4; }

/**
 * @brief Getter method for retrieving the first element of the UV array.
 *
 * @return A pointer to the first element of the UV array.
 */
GLfloat *GameObject::getUV() { return this->uv; }

/**
 * @brief Getter method for retrieving the count of UVs.
 *
 * @return The count of UVs in the UV array.
 */
int GameObject::getUVCount() { return ARRAY_SIZE(uv); }

/**
 * @brief Getter method for retrieving the first element of the index array.
 *
 * @return A pointer to the first element of the index array.
 */
GLfloat *GameObject::getIndex() { return this->index; }

/**
 * @brief Getter method for retrieving the count of indices.
 *
 * @return The count of indices in the index array.
 */
int GameObject::getIndexCount() { return ARRAY_SIZE(index) / 3; }

/**
 * @brief method for retrieving enum type as a string. 
 * Function to converts GameObject Type value to a string
 *
 * @return enum type as a string.
 */
string GameObject::enumToString()
{
    switch (this->type)
    {
    case TYPE::PLAYER:
        return "Player GameObject";
    case TYPE::NPC:
        return "NPC GameObject";
    case TYPE::BOSS:
        return "BOSS GameObject";
    default:
        return "Unknown GameObject";
    }
}
