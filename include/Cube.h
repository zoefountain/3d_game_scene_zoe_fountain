#ifndef CUBE_H // If the macro CUBE_H is not defined
#define CUBE_H // Define the macro CUBE_H to prevent multiple inclusions of this header file

#include <GL/glew.h>

/**
 * @file Cube.h
 * @brief Header file defining vertices, colors, UVs, and indices for a cube in OpenGL.
 */

//Cube Vertices
/*
		  (-1.0f, 1.0f, -1.0f)          (1.0f, 1.0f, -1.0f)
		          [7]                          [6]
		          #-----------------------------#
		         /|                            /|
		        / |                           / |
	  (-1.0f, 1.0f, 1.0f)           (1.0f, 1.0f, 1.0f)
		  [3] /                         [2] /
		     #-----------------------------#    |
		     |    |                        |    |
		     |    |                        |    |
		     |   [4]                       |   [5]
		  (-1.0f, -1.0f, -1.0f)         (1.0f, -1.0f, -1.0f)
		     |    #-----------------------------#
		     |   /                         |   /
		     |  /                          |  /
		     | /                           | /
		     |/                            |/
		     #-----------------------------#
		    [0]                           [1]
	(-1.0f, -1.0f, 1.0f)         (1.0f, -1.0f, 1.0f)
*/

// Constants for the cube geometry
// Each surface must have a defined specification to enable 
// the application of a texel onto it.
const int VERTICES	= 24;	// Total Number of Vertices
const int INDICES	= 12;	// Total Number of Indexes
const int UVS		= 48;	// Total Number of UVs
const int COLOURS	= 24;	// Total Number of Colours
const int NORMALS	= 12;	// Total Number of Normals

// Cube Vertices
/**
 * @defgroup Cube_Vertices Cube Vertices
 * @{
 */

/**
 * @brief Vertices of the cube.
 * 
 * Vertices are defined by their x, y, and z coordinates.
 * Each vertex is represented as a 3-element array.
 */

static const GLfloat vertices[] =
{
	// Front Face
	-1.00f, -1.00f,  1.00f,	// [0]	// ( 0)
	 1.00f, -1.00f,  1.00f,	// [1]	// ( 1)
	 1.00f,  1.00f,  1.00f,	// [2]	// ( 2)
	-1.00f,  1.00f,  1.00f,	// [3]	// ( 3)

	// Top Face
	-1.00f,  1.00f,  1.00f,	// [3]	// ( 4)
	 1.00f,  1.00f,  1.00f,	// [2]	// ( 5)
	 1.00f,  1.00f, -1.00f,	// [6]	// ( 6)
	-1.00f,  1.00f, -1.00f,	// [7]	// ( 7)

	// Back Face
	 1.00f, -1.00f, -1.00f,	// [5]	// ( 8)
	-1.00f, -1.00f, -1.00f, // [4]	// ( 9)
	-1.00f,  1.00f, -1.00f,	// [7]	// (10)
	 1.00f,  1.00f, -1.00f,	// [6]	// (11)

	// Bottom Face
	-1.00f, -1.00f, -1.00f, // [4]	// (12)
	 1.00f, -1.00f, -1.00f, // [5]	// (13)
	 1.00f, -1.00f,  1.00f, // [1]	// (14)
	-1.00f, -1.00f,  1.00f, // [0]	// (15)

	// Left Face
	-1.00f, -1.00f, -1.00f, // [4]	// (16)
	-1.00f, -1.00f,  1.00f, // [0]	// (17)
	-1.00f,  1.00f,  1.00f, // [3]	// (18)
	-1.00f,  1.00f, -1.00f, // [7]	// (19)

	// Right Face
	 1.00f, -1.00f,  1.00f, // [1]	// (20)
	 1.00f, -1.00f, -1.00f, // [5]	// (21)
	 1.00f,  1.00f, -1.00f, // [6]	// (22)
	 1.00f,  1.00f,  1.00f  // [2]	// (23)
};

/**
 * @}
 */

// Colours defined by Face
/**
 * @defgroup Cube_Colours Cube Colours
 * @{
 */

/**
 * @brief Colours of the cube faces.
 * 
 * Colours are represented as RGBA values.
 * Each colour is represented as a 4-element array.
 */

static const GLfloat colours[] = {
	
	// Front Face
	1.0f, 0.0f, 0.0f, 1.0f, // [0]	// ( 0)
	1.0f, 0.0f, 0.0f, 1.0f, // [1]	// ( 1)
	1.0f, 0.0f, 0.0f, 1.0f, // [2]	// ( 2)
	1.0f, 0.0f, 0.0f, 1.0f, // [3]	// ( 3)

	// Top Face
	0.0f, 1.0f, 0.0f, 1.0f, // [3]	// ( 4)
	0.0f, 1.0f, 0.0f, 1.0f, // [2]	// ( 5)
	0.0f, 1.0f, 0.0f, 1.0f, // [6]	// ( 6)
	0.0f, 1.0f, 0.0f, 1.0f, // [7]	// ( 7)

	// Back Face
	0.0f, 0.0f, 1.0f, 1.0f, // [5]	// ( 8)
	0.0f, 0.0f, 1.0f, 1.0f, // [4]	// ( 9)
	0.0f, 0.0f, 1.0f, 1.0f, // [7]	// (10)
	0.0f, 0.0f, 1.0f, 1.0f, // [6]	// (11)

	// Bottom Face
	0.0f, 1.0f, 1.0f, 1.0f, // [4]	// (12)
	0.0f, 1.0f, 1.0f, 1.0f, // [5]	// (13)
	0.0f, 1.0f, 1.0f, 1.0f, // [1]	// (14)
	0.0f, 1.0f, 1.0f, 1.0f, // [0]	// (15)

	// Left Face
	1.0f, 1.0f, 0.0f, 1.0f, // [4]	// (16)
	1.0f, 1.0f, 0.0f, 1.0f, // [0]	// (17)
	1.0f, 1.0f, 0.0f, 1.0f, // [3]	// (18)
	1.0f, 1.0f, 0.0f, 1.0f, // [7]	// (19)

	// Right Face
	1.0f, 0.0f, 1.0f, 1.0f, // [1]	// (20)
	1.0f, 0.0f, 1.0f, 1.0f, // [5]	// (21)
	1.0f, 0.0f, 1.0f, 1.0f, // [6]	// (22)
	1.0f, 0.0f, 1.0f, 1.0f // [2]	// (23)
};

/**
 * @}
 */

// Normals defined by Face
/**
 * @defgroup Cube_Normals Cube Normals
 * @{
 */

/**
 * @brief Normals of the cube faces.
 * 
 * Normals are represented as XYZ values.
 * Each Normals is represented as a 3-element array.
 */

static const GLfloat normals[] = {
	
	// Front Face
	0.0f, 0.0f, 1.0f, // [0]
	0.0f, 0.0f, 1.0f,

	// Top Face
	0.0f, 1.0f, 0.0f, // [1]
	0.0f, 1.0f, 0.0f,

	// Back Face
	0.0f, 0.0f, -1.0f,// [2]
	0.0f, 0.0f, -1.0f,

	// Bottom Face
	0.0f, -1.0f, 0.0f,// [3]
	0.0f, -1.0f, 0.0f,

	// Left Face
	-1.0f, 0.0f, 0.0f,// [4]
	-1.0f, 0.0f, 0.0f,

	// Right Face
	1.0f, 0.0f, 0.0f, // [5]
	1.0f, 0.0f, 0.0f
};

/**
 * @}
 */

// UVs defined by Face (applies texture to face geometry)
// customised to apply specific texels
/**
 * @brief UVs (texture coordinates) for the cube faces.
 * 
 * UVs are defined to map textures onto the cube faces.
 * Each UV coordinate is represented as a 2-element array.
 */

static GLfloat uvs[2 * 4 * 6] = {
	// Front Face (other faces populated in initialisation)
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0
};

// Vertex indexes defined by Face
/**
 * @brief Vertex indices defining the faces of the cube.
 * 
 * Vertex indices are used to construct triangles from the cube vertices.
 * Each set of three indices represents a triangle.
 */
static const GLuint indices[] =
{
	// Front Face
	0, 1, 2,
	2, 3, 0,

	// Top Face
	4, 5, 6,
	6, 7, 4,

	// Back Face
	8, 9, 10,
	10, 11, 8,

	// Bottom Face
	12, 13, 14,
	14, 15, 12,

	// Left Face
	16, 17, 18,
	18, 19, 16,

	// Right Face
	20, 21, 22,
	22, 23, 20
};

#endif // CUBE_H
