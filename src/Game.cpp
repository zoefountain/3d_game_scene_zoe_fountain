/**
 * @file Game.cpp
 * @brief This file contains the implementation of the Game class.
 */

#include <./include/Debug.h>	 // Include Debug header file
#include <./include/Cube.h>		 // Include Cube header file
#include <./include/Game.h>		 // Include Game header file
#include <./include/stb_image.h> // Include single file header for loading images
#include <./include/Maze.h>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

/* STB_IMAGE_IMPLEMENTATION should be defined only once */
#define STB_IMAGE_IMPLEMENTATION // Define STB_IMAGE_IMPLEMENTATION only once
#include <./include/stb_image.h> // Include single file header for loading images

/**
 * @brief Converts a given number to its string representation.
 *
 * This function takes a numeric value of type T and converts it into its string representation.
 * Helper Template function to convert Number to String for HUD
 *
 * @tparam T The type of the input number. It can be any numeric type supported by the stringstream.
 * @param number The numeric value to be converted to a string.
 * @return A string representation of the input number.
 *
 * @note This function utilizes a stringstream to perform the conversion, ensuring compatibility with various numeric types.
 * @warning Beware of potential precision loss or formatting issues when converting floating-point numbers.
 *
 * Example usage:
 * @code
 * int num = 123;
 * string numString = toString(num); // numString will be "123"
 * @endcode
 */
template <typename T>
string toString(T number)
{
	ostringstream oss;
	oss << number;
	return oss.str();
}

GLuint vsid, // Vertex Shader ID
	fsid,	 // Fragment Shader ID
	progID,	 // Program ID
	vbo,	 // Vertex Buffer ID
	vib,	 // Vertex Index Buffer
	to[1];	 // Texture ID

GLint positionID, // Position ID
	colorID,	  // Color ID
	textureID,	  // Texture ID
	uvID,		  // UV ID
	mvpID;		  // Model View Projection ID

GLenum error; // OpenGL Error Code

// Filename for texture
const string filename = "./assets/textures/grid.tga";
// Please see ../assets/textures/ for more textures
// const string filename = "./assets/textures/coordinates.tga";
// const string filename = "./assets/textures/cube.tga";
// const string filename = "./assets/textures/grid_wip.tga";
// const string filename = "./assets/textures/minecraft.tga";
// const string filename = "./assets/textures/texture.tga";
// const string filename = "./assets/textures/texture_2.tga";
// const string filename = "../assets/textures/uvtemplate.tga";

int width;						 // width of texture
int height;						 // height of texture
int comp_count;					 // Component of texture
const int colour_components = 4; // 4 = RGBA

// Texture image data
unsigned char *img_data;

// View Projection Matrices
mat4 projection, view;

Font font; // Game font

float x_offset, y_offset, z_offset; // offset on screen (Vertex Shader)

/**
 * @brief Constructs a new Game object with the specified context settings.
 *
 * @param settings Context settings for the window.
 */
Game::Game(int mazeWidth, int mazeHeight, const sf::ContextSettings& settings)
	: maze(mazeWidth, mazeHeight), playerPosition(1.0f, 0.0f, 1.0f), playerSpeed(2.0f) // Initialize the maze and player
{
	// Create the SFML window with OpenGL context
	window.create(sf::VideoMode(800, 600), "3D Maze Game", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Set up OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Set up the perspective projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);

	game_objects.push_back(new GameObject(gpp::TYPE::PLAYER)); // Correctly add the player object to the vector
}

static void drawCube(float size) {
	float halfSize = size / 2.0f;

	glBegin(GL_QUADS);

	// Front face
	glVertex3f(-halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, halfSize);

	// Back face
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);

	// Left face
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(-halfSize, -halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);

	// Right face
	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);

	// Top face
	glVertex3f(-halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, halfSize, halfSize);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);

	// Bottom face
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(-halfSize, -halfSize, halfSize);

	glEnd();
}

/**
 * @brief Destroys the Game object.
 */
Game::~Game()
{
	DEBUG_MSG("\nGame::~Game() Destructor\n");
}

void Game::updateMVPMatrix()
{
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)window.getSize().x / (float)window.getSize().y, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(
		glm::vec3(playerPosition.x, playerPosition.y + 2.0f, playerPosition.z + 5.0f), // Camera position
		glm::vec3(playerPosition.x, playerPosition.y, playerPosition.z),               // Look at player
		glm::vec3(0.0f, 1.0f, 0.0f)                                                    // Up vector
	);

	for (auto& gameObject : game_objects) {
		if (gameObject != nullptr) {
			gameObject->setMVPMatrix(projection * view * gameObject->getModelMatrix());
		}
	}
}

void Game::handleInput(float deltaTime) {
	glm::vec3 previousPosition = playerPosition; // Save previous position for collision detection

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		playerPosition.z -= playerSpeed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		playerPosition.z += playerSpeed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		playerPosition.x -= playerSpeed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerPosition.x += playerSpeed * deltaTime;
	}

	// Collision detection with maze walls
	int gridX = static_cast<int>(playerPosition.x);
	int gridZ = static_cast<int>(playerPosition.z);
	if (maze.getMaze()[gridX][gridZ] == 1) {
		// Collision occurred, revert position
		playerPosition = previousPosition;
	}
}

void Game::update(float deltaTime)
{
	handleInput(deltaTime);
	updateMVPMatrix(); // Update the MVP matrix for all game objects
}

void Game::renderMaze() {
	const auto& grid = maze.getMaze();
	float size = 1.0f;  // Size of each cell

	glColor3f(1.0f, 1.0f, 1.0f);  // Set color to white for the walls

	for (std::size_t x = 0; x < grid.size(); ++x) {
		for (std::size_t y = 0; y < grid[x].size(); ++y) {
			if (grid[x][y] == 1) {
				glPushMatrix();
				glTranslatef(x * size, 0.0f, y * size);
				glBegin(GL_QUADS);
				// Draw the walls of the maze cell
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(size, 0.0f, 0.0f);
				glVertex3f(size, size, 0.0f);
				glVertex3f(0.0f, size, 0.0f);
				glEnd();
				glPopMatrix();
			}
		}
	}
}

void Game::renderPlayer() {
	glPushMatrix();
	glTranslatef(playerPosition.x, playerPosition.y, playerPosition.z);
	glColor3f(0.0f, 1.0f, 0.0f); // Set player color to green
	drawCube(0.5f); // Render player as a cube
	glPopMatrix();
}

/**
 * @brief Initializes the game.
 *
 * This method initializes various resources and sets up OpenGL for rendering. Method is responsible for setting up various OpenGL
 * resources, including shaders, buffers, textures, and matrices. It initializes GLEW, sets up shaders (vertex and fragment), loads
 * texture data, and sets up projection and camera matrices.
 */
void Game::initialise()
{
	DEBUG_MSG("\n******** Initialisation Procedure STARTS ********\n");

	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	if (!(!glewInit()))
	{
		DEBUG_MSG("ERROR: GLEW INIT");
		DEBUG_MSG(glewGetErrorString(glewInit()));
		throw runtime_error("\nGLEW Init Failed\n");
	}

	DEBUG_MSG("\n******** Init GameObjects STARTS ********\n");

	game_objects.push_back(new GameObject(gpp::TYPE::PLAYER));
	game_objects[0]->setPosition(glm::vec3(0.0001f, 0.0f, 0.0f));

	DEBUG_MSG("\n******** Init GameObjects ENDS ********\n");

	// Copy UV coordinates to all faces (initially only one face is defined in Cube.h)
	// This loop iterates over each face (except the first one) and copies the UV coordinates
	// from the first face to the UV array for that face.
	for (int i = 1; i < 6; i++)
	{
		// Calculate the starting position of UV coordinates for the current face in the UV array
		int uv_start_position = i * 4 * 2; // Each face has 4 vertices, each vertex has 2 UV coordinates

		// Copy UV coordinates from the first face to the current face
		memcpy(&uvs[uv_start_position], &uvs[0], 2 * 4 * sizeof(GLfloat)); // Each vertex has 2 UV coordinates,
		// and there are 4 vertices per face
	}

	// 	for (int i = 1; i < 6; i++) {
	//		memcpy(&uvs[i * 4 * 2], &uvs[0], 2 * 4 * sizeof(GLfloat));
	//	}

	// Output GPU information to the debug console
	DEBUG_MSG("\n******** GPU information STARTS ********\n");
	// Retrieve and output GPU vendor information
	DEBUG_MSG(glGetString(GL_VENDOR));
	// Retrieve and output GPU renderer information
	DEBUG_MSG(glGetString(GL_RENDERER));
	// Retrieve and output GPU version information
	DEBUG_MSG(glGetString(GL_VERSION));
	// Retrieve and output GPU shading language version information
	DEBUG_MSG(glGetString(GL_SHADING_LANGUAGE_VERSION));
	DEBUG_MSG("\n******** GPU information ENDS ********\n");

	// Vertex Buffer Object
	glGenBuffers(1, &vbo); // Generate Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	DEBUG_MSG("\n******** Model information STARTS ********\n");
	// Vertices (3) x,y,z , Colors (4) RGBA, UV/ST (2)
	for (auto& gameObject : game_objects) {
		if (gameObject != nullptr) {
			int countVERTICES = gameObject->getVertexCount();
			int countCOLORS = gameObject->getColorCount();
			int countUVS = gameObject->getUVCount();
			DEBUG_MSG("\n******** Model information ENDS ********\n");

			// Vertices (3) x,y,z , Colours (4) RGBA, UV/ST (2)
			glBufferData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLOURS) + (2 * UVS)) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

			glGenBuffers(1, &vib); // Generate Vertex Index Buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);

			// Count of Indices
			for (auto& gameObject : game_objects) {
				if (gameObject != nullptr) {
					int countINDICES = gameObject->getIndexCount();

					DEBUG_MSG("\nVertices : " + to_string(countVERTICES));
					DEBUG_MSG("Colors : " + to_string(countCOLORS));
					DEBUG_MSG("UVs : " + to_string(countUVS));
					DEBUG_MSG("Indexes : " + to_string(countINDICES));

					// Indices to be drawn
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * INDICES * sizeof(GLuint), indices, GL_STATIC_DRAW);

					// NOTE: uniforms values must be used within Shader so that they
					// can be retreived
					// Define and compile Vertex Shader
					const char* vs_src =
						"#version 130\n\n"
						"\n"
						"in vec3 sv_position;\n"
						"in vec4 sv_colour;\n"
						"in vec2 sv_uv;\n\n"
						"\n"
						"out vec4 colour;\n"
						"out vec2 uv;\n\n"
						"\n"
						"uniform mat4 sv_mvp;\n"
						"\n"
						"void main() {\n"
						"	colour = sv_colour;\n"
						"	uv = sv_uv;\n"
						//"	gl_Position = vec4(sv_position, 1);\n"
						"	gl_Position = sv_mvp * vec4(sv_position, 1 );\n"
						"}\n"; // Vertex Shader Src

					DEBUG_MSG("\n******** Vertex Shader src STARTS ********\n");
					DEBUG_MSG(string(vs_src));
					DEBUG_MSG("\n******** Vertex Shader src ENDS ********\n");

					DEBUG_MSG("Setting Up Vertex Shader");

					// Compile Vertex Shader
					vsid = glCreateShader(GL_VERTEX_SHADER);
					glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL);
					glCompileShader(vsid);

					// Check if Vertex Shader is Compiled
					glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

					if (isCompiled == GL_TRUE)
					{
						DEBUG_MSG("Vertex Shader Compiled");
						isCompiled = GL_FALSE;
					}
					else
					{
						GLint logLength = 0;
						glGetShaderiv(vsid, GL_INFO_LOG_LENGTH, &logLength);
						char* errorLog = new char[logLength];
						glGetShaderInfoLog(vsid, logLength, &logLength, &errorLog[0]);
						DEBUG_MSG("\n******** Vertex Shader ErrorLog STARTS ********\n");
						DEBUG_MSG(string(errorLog));
						DEBUG_MSG("\n******** Vertex Shader ErrorLog ENDS ********\n");
						throw runtime_error("\nERROR: Vertex Shader Compilation Error\n");
					}
				}
			}

			// Define and compile Fragment Shader
			const char* fs_src =
				"#version 130\n\n"
				"\n"
				"uniform sampler2D f_texture;\n"
				"\n"
				"in vec4 colour;\n"
				"in vec2 uv;\n"
				"\n"
				"out vec4 fColor;\n"
				"\n"
				"void main() {\n"
				"	vec4 lightColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);\n"
				"	fColor = lightColor * (colour + texture2D(f_texture, uv));\n"
				"\n"
				"}\n"; // Fragment Shader Src

			DEBUG_MSG("\n******** Fragment Shader src STARTS ********\n");
			DEBUG_MSG(string(fs_src));
			DEBUG_MSG("\n******** Fragment Shader src ENDS ********\n");

			DEBUG_MSG("Setting Up Fragment Shader");

			// Compile Fragment Shader
			fsid = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
			glCompileShader(fsid);

			// Check is Shader Compiled
			glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

			if (isCompiled == GL_TRUE)
			{
				DEBUG_MSG("Fragment Shader Compiled");
				isCompiled = GL_FALSE;
			}
			else
			{
				GLint logLength = 0;
				glGetShaderiv(fsid, GL_INFO_LOG_LENGTH, &logLength);
				char* errorLog = new char[logLength];
				glGetShaderInfoLog(fsid, logLength, &logLength, &errorLog[0]);
				DEBUG_MSG("\n******** Vertex Shader ErrorLog STARTS ********\n");
				DEBUG_MSG(string(errorLog));
				DEBUG_MSG("\n******** Vertex Shader ErrorLog ENDS ********\n");
				throw runtime_error("\nERROR: Fragment Shader Compilation Error\n");
			}

			// Create and link shader program
			DEBUG_MSG("\n******** Shader Linking STARTS ********\n");
			DEBUG_MSG("Setting Up and Linking Shader");
			progID = glCreateProgram();
			glAttachShader(progID, vsid);
			glAttachShader(progID, fsid);
			glLinkProgram(progID);

			// Check if Shader Program is linked
			glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

			if (isLinked == 1)
			{
				DEBUG_MSG("Vertex and Fragment Shader Linked");
			}
			else
			{
				throw runtime_error("\nERROR: Vertex and Fragment Shader Link Error\n");
			}
			DEBUG_MSG("\n******** Shader Linking ENDS ********\n");
			// Use Shader Program on GPU
			glUseProgram(progID);

			// Set image data
			// https://github.com/nothings/stb/blob/master/stb_image.h
			// Load texture image data
			img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, colour_components);

			if (img_data == NULL)
			{
				throw runtime_error("\nERROR: Texture not loaded " + filename + "\n");
			}

			// Enable 2D texturing
			DEBUG_MSG("\n******** Enabling Textures STARTS ********\n");
			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &to[0]);
			glBindTexture(GL_TEXTURE_2D, to[0]);

			// Texture wrapping
			// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

			// Texture filtering
			// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Transfer texture image data to GPU
			// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
			glTexImage2D(
				GL_TEXTURE_2D,	  // 2D Texture Image
				0,				  // Mipmapping Level
				GL_RGBA,		  // GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA
				width,			  // Width
				height,			  // Height
				0,				  // Border
				GL_RGBA,		  // Bitmap
				GL_UNSIGNED_BYTE, // Specifies Data type of image data
				img_data		  // Image Data
			);

			DEBUG_MSG("\n******** Enabling Textures ENDS ********\n");

			// Set up Projection Matrix
			DEBUG_MSG("\n******** MVP STARTS ********\n");
			projection = perspective(
				45.0f,		 // Field of View 45 degrees
				4.0f / 3.0f, // Aspect ratio: 4:3
				5.0f,		 // Display Range Min : 0.1f unit
				100.0f		 // Display Range Max : 100.0f unit
			);

			// Set up Camera Matrix
			view = lookAt(
				vec3(0.0f, 4.0f, 10.0f), // Camera (x,y,z), in World Space
				vec3(0.0f, 0.0f, 0.0f),	 // Camera looking at origin
				vec3(0.0f, 1.0f, 0.0f)	 // 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
			);

			DEBUG_MSG("\n******** MVP ENDS ********\n");

			// Enable Depth Test for accurate rendering
			DEBUG_MSG("\n******** CULLING ENABLE STARTS ********\n");
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			glEnable(GL_CULL_FACE);
			DEBUG_MSG("\n******** CULLING ENABLE ENDS ********\n");

			DEBUG_MSG("\n******** OpenGL Error Check STARTS ********\n");
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
			{
				throw runtime_error("ERROR: OpenGL Error : " + to_string(error));
			}
			DEBUG_MSG("\n******** OpenGL Error Check ENDS ********\n");

			// Load Font
			font.loadFromFile("./assets/fonts/BBrick.ttf");

			DEBUG_MSG("\n******** Initialisation Procedure ENDS ********\n");
		}
	}
}
/**
 * @brief Updates the game state.
 */
void Game::update() {
#if (DEBUG >= 2)
	DEBUG_MSG("Updating... MVP");
#endif
	// Update the Model View Projection matrix by combining the projection, view, and model matrices

	for (auto& gameObject : game_objects) 
	{
		if (gameObject != nullptr) 
		{  // Check if the pointer is valid
		    // Set the MVP matrix for the current GameObject
			gameObject->setMVPMatrix(projection * view * gameObject->getModelMatrix());
		}
	}

#if (DEBUG >= 2)
	DEBUG_MSG("MVP : " + game_objects->enumToString());
	DEBUG_MSG(glm::to_string(game_objects->getModelMatrix()));
#endif


#if (DEBUG >= 2)
	DEBUG_MSG("MVP : " + glm::to_string(mvp));
#endif

#if (DEBUG >= 2)
	DEBUG_MSG("Finished Updating... MVP");
#endif
}

/**
 * @brief Runs the game loop.
 *
 * Method contains the main game loop where events are handled, the game state is updated (Game::update()), and
 * the scene is rendered (Game::render()). The loop runs until the isRunning flag is false.
 */
void Game::run() {
	sf::Clock clock;

	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();

		// Handle events
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		update(deltaTime);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		gluLookAt(
			playerPosition.x, playerPosition.y + 2.0f, playerPosition.z + 5.0f, // Camera position
			playerPosition.x, playerPosition.y, playerPosition.z, // Look at player
			0.0f, 1.0f, 0.0f  // Up vector
		);

		renderMaze();
		renderPlayer();

		window.display();
	}
}

/**
 * @brief Renders the game scene.
 * method clears the color and depth buffers, draws the HUD (heads-up display), binds buffers, sets shader uniforms,
 * enables vertex arrays, and draws the cube using indexed drawing.
 */
void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Render Loop...");
#endif

	// Clear the color buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save current OpenGL render states
	// https://www.sfml-dev.org/documentation/2.0/classsf_1_1RenderTarget.php#a8d1998464ccc54e789aaf990242b47f7
	window.pushGLStates();

	// Find mouse position using sf::Mouse
	int x = Mouse::getPosition(window).x;
	int y = Mouse::getPosition(window).y;

	string hud = "Heads Up Display [" + string(toString(x)) + "][" + string(toString(y)) + "]";

	Text text(hud, font);

	text.setFillColor(sf::Color(255, 255, 255, 170));
	text.setPosition(50.f, 20.f);

	window.draw(text);

	// Restore OpenGL render states
	// https://www.sfml-dev.org/documentation/2.0/classsf_1_1RenderTarget.php#a8d1998464ccc54e789aaf990242b47f7

	window.popGLStates();

	// Rebind Buffers and then set SubData
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);

	// Use Progam on GPU
	glUseProgram(progID);

	// Find variables within the shader
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	if (positionID == -1)
	{
		throw runtime_error("\nERROR: positionID not found\n");
	}

	colorID = glGetAttribLocation(progID, "sv_colour");
	if (colorID == -1)
	{
		throw runtime_error("\nERROR: colorID not found\n");
	}

	uvID = glGetAttribLocation(progID, "sv_uv");
	if (uvID == -1)
	{
		throw runtime_error("\nERROR: uvID not found\n");
	}

	textureID = glGetUniformLocation(progID, "f_texture");
	if (textureID == -1)
	{
		throw runtime_error("\nERROR: textureID not found\n");
	}

	mvpID = glGetUniformLocation(progID, "sv_mvp");
	if (mvpID < 0)
	{
		throw runtime_error("\nERROR: mvpID not found\n");
	}


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Camera setup
	gluLookAt(
		playerPosition.x, playerPosition.y + 2.0f, playerPosition.z + 5.0f, // Camera position
		playerPosition.x, playerPosition.y, playerPosition.z,               // Look at player
		0.0f, 1.0f, 0.0f                                                   // Up vector
	);

	renderMaze();
	renderPlayer();

	// Render each game object
	for (auto& gameObject : game_objects) {
		if (gameObject != nullptr) {
			glBufferSubData(GL_ARRAY_BUFFER, 0 * VERTICES * sizeof(GLfloat), 3 * VERTICES * sizeof(GLfloat), gameObject->getVertex());
			glUniformMatrix4fv(mvpID, 1, GL_FALSE, &(gameObject->getMVPMatrix())[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, VERTICES);
		}
	}

	window.display();

	// Disable Arrays
	glDisableVertexAttribArray(positionID);
	glDisableVertexAttribArray(colorID);
	glDisableVertexAttribArray(uvID);

	// Unbind Buffers with 0 (Resets OpenGL States...important step)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Reset the Shader Program to Use
	glUseProgram(0);

	// Check for OpenGL Error code
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		DEBUG_MSG(error);
	}
}

/**
 * @brief Performs cleanup by releasing resources allocated during the initialization or execution of the game.
 *
 * The unload method is responsible for releasing various resources used by the game,
 * including shaders, shader programs, buffers, and image data. Releasing resources that are no longer needed to
 * free up memory and prevent resource leaks
 *
 * @note This method should be called when the game is shutting down or when resources are no longer needed.
 */

void Game::unload()
{
#if (DEBUG >= 2)
	// Output a debug message indicating that cleanup process has started
	DEBUG_MSG("Cleaning up...STARTS");
#endif

	// Detach the vertex shader from the shader program
	// Shader could be used with more than one progID
	glDetachShader(progID, vsid);

	// Detach the fragment shader from the shader program
	glDetachShader(progID, fsid);

	// Delete the vertex shader
	glDeleteShader(vsid);

	// Delete the fragment shader
	glDeleteShader(fsid);

	// Delete the shader program
	glDeleteProgram(progID);

	// Delete the vertex buffer object
	glDeleteBuffers(1, &vbo);

	// Delete the vertex index buffer object
	glDeleteBuffers(1, &vib);

	// Free the image data
	stbi_image_free(img_data);

#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...ENDS");
#endif
}

