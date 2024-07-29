#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

// Define a macro for calculating the size of an array
#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

// Include necessary headers
#include <stdio.h>	// For standard input and output operations
#include <string.h> // For string manipulation (memcpy)
#include <string> 	// For string manipulation

// Include GLM headers for mathematics library
#include <glm/glm.hpp>					// OpenGL Mathematics
#include <glm/gtc/matrix_transform.hpp> // Matrix transformations

// Include custom header
#include <./include/Cube.h> // Header for Cube class

// Using directives to avoid typing glm:: prefix
using namespace glm;
using namespace std;

namespace gpp
{
	// GameObject Type
	enum class TYPE
	{
		PLAYER,
		NPC,
		BOSS
	};

	/**
	 * @class GameObject
	 * @brief Represents a game object with vertex, color, and UV data.
	 */
	class GameObject
	{
	private:
		// Cube Elements
		GLfloat vertex[ARRAY_SIZE(vertices)]; // Array of vertex positions
		GLfloat colour[ARRAY_SIZE(colours)];  // Array of vertex colours
		GLfloat uv[ARRAY_SIZE(uvs)];		  // Array of texture coordinates
		GLfloat index[ARRAY_SIZE(indices)];	  // Array of vertex indices

		// GameObject Attributes
		vec3 position; // Position of the game object in 3D space
		mat4 model;	   // Model Matrix for GameObject
		mat4 mvp;	   // Model View Project Matrix
		TYPE type;	   // GameOject Type

	public:
		/**
		 * @brief Default constructor for the GameObject class.
		 *
		 * Initializes a GameObject by copying vertex, color, and UV data from the Cube class.
		 * UV data is copied to all faces of the GameObject.
		 * The position of the GameObject is set to the origin (0, 0, 0).
		 */
		GameObject(TYPE type);

		/**
		 * @brief Destructor for the GameObject class.
		 *
		 * This is a default destructor and does not perform any specific cleanup tasks.
		 */
		~GameObject();

		/**
		 * @brief Getter method for retrieving the position of the game object.
		 *
		 * @return The position of the game object as a vec3 vector.
		 */
		vec3 getPosition();

		/**
		 * @brief Setter method for setting the position of the game object.
		 *
		 * @param position The new position of the game object as a vec3 vector.
		 */
		void setPosition(vec3 position);

		/**
		 * @brief Getter method for retrieving the model of the game object.
		 *
		 * @return The model matrix of the game object as a mat4 matrix.
		 */
		mat4 getModelMatrix();

		/**
		 * @brief Setter method for setting the model of the game object.
		 *
		 * @param model The new model of the game object as a mat4 matrix.
		 */
		void setModelMatrix(mat4 model);

		/**
		 * @brief Getter method for retrieving the model view projection of the game object.
		 *
		 * @return The model view projection matrix of the game object as a mat4 matrix.
		 */
		mat4 getMVPMatrix();

		/**
		 * @brief Setter method for setting the model view projection of the game object.
		 *
		 * @param model The new model view projection of the game object as a mat4 matrix.
		 */
		void setMVPMatrix(mat4 model);

		/**
		 * @brief Getter method for retrieving the first element of the vertex array.
		 *
		 * @return A pointer to the first element of the vertex array.
		 */
		GLfloat *getVertex();

		/**
		 * @brief Getter method for retrieving the count of vertices.
		 *
		 * @return The count of vertices in the vertex array.
		 */
		int getVertexCount();

		/**
		 * @brief Getter method for retrieving the first element of the color array.
		 *
		 * @return A pointer to the first element of the color array.
		 */
		GLfloat *getColor();

		/**
		 * @brief Getter method for retrieving the count of colours.
		 *
		 * @return The count of colours in the color array.
		 */
		int getColorCount();

		/**
		 * @brief Getter method for retrieving the first element of the UV array.
		 *
		 * @return A pointer to the first element of the UV array.
		 */
		GLfloat *getUV();

		/**
		 * @brief Getter method for retrieving the count of UVs.
		 *
		 * @return The count of UVs in the UV array.
		 */
		int getUVCount();

		/**
		 * @brief Getter method for retrieving the first element of the index array.
		 *
		 * @return A pointer to the first element of the index array.
		 */
		GLfloat *getIndex();

		/**
		 * @brief Getter method for retrieving the count of indices.
		 *
		 * @return The count of indices in the index array.
		 */
		int getIndexCount();

		/**
		 * @brief method for retrieving enum type as a string.
		 * 
		 * @return enum type as a string.
		 */
		string enumToString();
	};
}

#endif // GAME_OBJECT_H
