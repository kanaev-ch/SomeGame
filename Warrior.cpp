#include "Warrior.h"



Warrior::Warrior(const char* vertexFile, const char* fragmentFile, const char* image, const char* image2, const char* image3, const char* image4, const char* image5, 
	const char* image6, const char* image7, float x_, float y_, float z_, float sprite_h_)
{
	//change global height of poligon
	vertices[10] = vertices[18] = sprite_h_;

	direction = true;

	speed_move = 0.003f;

	anime = stand;

	selected = false;

	//walk_range_x = 2;
	//walk_range_y = 2;
	walk_range = 2;

	step = new Step[walk_range];

	step[0].x = 4.0f; step[0].y = -9.0f; step[0].z = 0.0f;
	step[1].x = 3.0f; step[1].y = -8.0f; step[1].z = 0.0f;

	std::string vertexCode = get_file_contents(vertexFile);//func takes simbols from file to string
	std::string fragmentCode = get_file_contents(fragmentFile);//func takes simbols from file to string

	const char* vertexSource = vertexCode.c_str();//func takes simbols from string to array of chars
	const char* fragmentSource = fragmentCode.c_str();//func takes simbols from string to array of chars

	//create and compile vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");//check vertex compile errors

	//create and compile fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");//check fragment compile errors

	//create shader programm and link all shaders to it
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	compileErrors(shaderProgram, "PROGRAM");//check shader programm compile errors

	//delete shaders, they dont need anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//generate VAO objects in vector array
	generate_VAO_VBO(VAO_1, VBO_1, 1);
	generate_VAO_VBO(VAO_2, VBO_2, 2);
	generate_VAO_VBO(VAO_3, VBO_3, 3);
	generate_VAO_VBO(VAO_4, VBO_4, 4);
	generate_VAO_VBO(VAO_5, VBO_5, 5);
	generate_VAO_VBO(VAO_6, VBO_6, 6);
	generate_VAO_VBO(VAO_7, VBO_7, 7);
	generate_VAO_VBO(VAO_8, VBO_8, 8);
	generate_VAO_VBO(VAO_9, VBO_9, 9);
	generate_VAO_VBO(VAO_10, VBO_10, 10);

	//generate EBO obj
	glGenBuffers(1, &EBO);

	//block of creating VAO, VBO, EBO objects in vector arrays with parameters
	//reset texture coordinates for each EBO
	configure_VAO_VBO(vertices, sizeof(vertices), indices, sizeof(indices), VAO_1, VBO_1, 1, EBO, direction);
	configure_VAO_VBO(vertices, sizeof(vertices), indices, sizeof(indices), VAO_2, VBO_2, 2, EBO, direction);
	configure_VAO_VBO(vertices, sizeof(vertices), indices, sizeof(indices), VAO_3, VBO_3, 3, EBO, direction);
	configure_VAO_VBO(vertices, sizeof(vertices), indices, sizeof(indices), VAO_4, VBO_4, 4, EBO, direction);
	configure_VAO_VBO(vertices, sizeof(vertices), indices, sizeof(indices), VAO_5, VBO_5, 5, EBO, direction);
	configure_VAO_VBO(vertices, sizeof(vertices), indices, sizeof(indices), VAO_6, VBO_6, 6, EBO, direction);
	configure_VAO_VBO(vertices, sizeof(vertices), indices, sizeof(indices), VAO_7, VBO_7, 7, EBO, direction);
	configure_VAO_VBO(vertices, sizeof(vertices), indices, sizeof(indices), VAO_8, VBO_8, 8, EBO, direction);
	configure_VAO_VBO(vertices, sizeof(vertices), indices, sizeof(indices), VAO_9, VBO_9, 9, EBO, direction);
	configure_VAO_VBO(vertices, sizeof(vertices), indices, sizeof(indices), VAO_10, VBO_10, 10, EBO, direction);


	//matrix of position tile, and changing to needed position here
	view = glm::mat4(1.0f);
	//x = x_move = x_; y = y_move = -y_; z = z_;
	x = x_; y = -y_; z = z_;
	view = glm::translate(view, glm::vec3(x, y, z));

	//create texture object
	create_Texture(image, texture_stand);
	create_Texture(image2, texture_walk);
	create_Texture(image3, texture_strike_sword);
	create_Texture(image4, texture_injured);
	create_Texture(image5, texture_defends);
	create_Texture(image6, texture_fall);
	create_Texture(image7, texture_dead);

	//Load adresses of uniforms
	tex0Uni = glGetUniformLocation(shaderProgram, "tex0");//создаем перем в кот будем хранить указатель на переменную uniform
	uniSelected = glGetUniformLocation(shaderProgram, "selected_flag");
}


Warrior::~Warrior()
{
	//delete all elements
	for (int i = 0; i < sizeof(VAO_1); i++) glDeleteVertexArrays(1, &VAO_1[i]);
	for (int i = 0; i < sizeof(VBO_1); i++) glDeleteBuffers(1, &VBO_1[i]);
	for (int i = 0; i < sizeof(VAO_2); i++) glDeleteVertexArrays(1, &VAO_2[i]);
	for (int i = 0; i < sizeof(VBO_2); i++) glDeleteBuffers(1, &VBO_2[i]);
	for (int i = 0; i < sizeof(VAO_3); i++) glDeleteVertexArrays(1, &VAO_3[i]);
	for (int i = 0; i < sizeof(VBO_3); i++) glDeleteBuffers(1, &VBO_3[i]);
	for (int i = 0; i < sizeof(VAO_4); i++) glDeleteVertexArrays(1, &VAO_4[i]);
	for (int i = 0; i < sizeof(VBO_4); i++) glDeleteBuffers(1, &VBO_4[i]);
	for (int i = 0; i < sizeof(VAO_5); i++) glDeleteVertexArrays(1, &VAO_5[i]);
	for (int i = 0; i < sizeof(VBO_5); i++) glDeleteBuffers(1, &VBO_5[i]);
	for (int i = 0; i < sizeof(VAO_6); i++) glDeleteVertexArrays(1, &VAO_6[i]);
	for (int i = 0; i < sizeof(VBO_6); i++) glDeleteBuffers(1, &VBO_6[i]);
	for (int i = 0; i < sizeof(VAO_7); i++) glDeleteVertexArrays(1, &VAO_7[i]);
	for (int i = 0; i < sizeof(VBO_7); i++) glDeleteBuffers(1, &VBO_7[i]);
	for (int i = 0; i < sizeof(VAO_8); i++) glDeleteVertexArrays(1, &VAO_8[i]);
	for (int i = 0; i < sizeof(VBO_8); i++) glDeleteBuffers(1, &VBO_8[i]);
	for (int i = 0; i < sizeof(VAO_9); i++) glDeleteVertexArrays(1, &VAO_9[i]);
	for (int i = 0; i < sizeof(VBO_9); i++) glDeleteBuffers(1, &VBO_9[i]);
	for (int i = 0; i < sizeof(VAO_10); i++) glDeleteVertexArrays(1, &VAO_10[i]);
	for (int i = 0; i < sizeof(VBO_10); i++) glDeleteBuffers(1, &VBO_10[i]);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	glDeleteTextures(1, &texture_stand);
	glDeleteTextures(1, &texture_walk);
	glDeleteTextures(1, &texture_strike_sword);
	glDeleteTextures(1, &texture_defends);
	glDeleteTextures(1, &texture_fall);
	glDeleteTextures(1, &texture_dead);
	delete[]step;
}

//func anime bind by cycle
void Warrior::Anime_Cycle(int frames, GLuint* VAO, int size_VAO, GLuint& texture)
{
	bind_VAO(frames, float(global_time), VAO, size_VAO, texture);
}

//func anime bind one time NON cycle
void Warrior::Anime_NON_Cycle(int frames, GLuint* VAO, int size_VAO, GLuint& texture)
{
	//block to anime one time, NON cycle
	int time = int(global_time * 100) % (frames * size_VAO);

	//anime if not dead
	if (time >= frames * size_VAO - 1 && anime != fall)
		anime = stand;
	//anime if dead after fall
	else if (time >= frames * size_VAO - 1 && anime == fall)
		anime = dead;

	int count = bind_VAO(frames, float(global_time), VAO, size_VAO, texture);
}

void Warrior::Change_Enum_Anime(int anime_)
{
	anime = ANIMATION_ENUM(anime_);
}

bool Warrior::Move(float x_, float y_, float z_)
{
	view = glm::mat4(1.0f);
	if (x < x_)
	{
		//x += speed_move;
		x += speed_move * past_time;
		change_Direction(false);
		if (x > x_)
		{
			x = x_;
			//x = x_move = x_;
		}
	}
	else {
		//x -= speed_move;
		x -= speed_move * past_time;
		change_Direction(true);
		if (x < x_)
		{
			x = x_;
			//x = x_move = x_;
		}
	}

	//view = glm::mat4(1.0f);

	if (y < -y_)
	{
		//std::cout << "UP" << std::endl;
		//y += speed_move;
		y += speed_move * past_time;
		if (y > -y_)
		{
			y = -y_;
			//y = y_move = -y_;
		}
	}
	else {
		//std::cout << "DOWN" << std::endl;
		//y -= speed_move;
		y -= speed_move * past_time;
		if (y < -y_)
		{
			y = -y_;
			//y = y_move = -y_;
		}
	}


	//block of calculate move by X with range
	/*if (x_ - x_move <= walk_range_x && x_ - x_move > 0)
	{
		//std::cout << "right x" << x << std::endl;
		//x += speed_move;
		x += speed_move * past_time;
		change_Direction(false);
		if (x > x_)
		{
			x = x_move = x_;
		}
	}
	else if (x_ - x_move >= -walk_range_x && x_ - x_move < 0)
	{
		//std::cout << "left x" << x << std::endl;
		//x -= speed_move;
		x -= speed_move * past_time;
		change_Direction(true);
		if (x < x_)
		{
			x = x_move = x_;
		}
	}

	//view = glm::mat4(1.0f);
	//block of calculate move by Y with range
	if (-y_ - y_move <= walk_range_y && -y_ - y_move > 0)
	{
		//std::cout << "UP" << -y_ - y_move << std::endl;
		//y += speed_move;
		y += speed_move * past_time;
		if (y > -y_)
		{
			y = y_move = -y_;
		}
	}
	else if (-y_ - y_move >= -walk_range_y && -y_ - y_move < 0)
	{
		//std::cout << "DOWN" << -y_ - y_move << std::endl;
		//y -= speed_move;
		y -= speed_move * past_time;
		if (y < -y_)
		{
			y = y_move = -y_;
		}
	}*/

	//std::cout << -y_ - y_move << std::endl;

	//view = glm::mat4(1.0f);
	if (z < z_)
	{
		//z += speed_move;
		z += speed_move * past_time;
		if (z > z_)
		{
			z = z_;
		}
	}
	else {
		//z -= speed_move;
		z -= speed_move * past_time;
		if (z < z_)
		{
			z = z_;
		}
	}

	view = glm::translate(view, glm::vec3(x, y, z));

	if (x == x_ && y == -y_ && z == z_) return true;
	else return false;
}



void Warrior::Draw(GLFWwindow* window, Camera& camera)
{
	//std::cout << x << " " << y << " " << z << std::endl;
	//activate shader programm
	glUseProgram(shaderProgram);

	//load to vertex uniform current position of tile
	int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	//aplying camera uniform fo look at
	//camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
	camera.Matrix(shaderProgram, "camMatrix");


	//simple control
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && anime != strike_sword)
	{
		anime = strike_sword;
		global_time = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
	{
		anime = walk;
		global_time = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && anime != injured)
	{
		anime = injured;
		global_time = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && anime != defends)
	{
		anime = defends;
		global_time = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && anime != fall)
	{
		anime = fall;
		global_time = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		anime = dead;
		global_time = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		selected = true;
	}

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		selected = false;
	}

	//Load select or not flag in uniform for background light
	Selected_Uniform_Load(selected);

	//choose what anime play
	switch (anime)
	{
	case stand:			Anime_Cycle(50, VAO_1, sizeof(VAO_1) / sizeof(int), texture_stand); break;
	case walk:			Anime_Cycle(25, VAO_3, sizeof(VAO_3) / sizeof(int), texture_walk); break;
	case strike_sword:	Anime_NON_Cycle(25, VAO_4, sizeof(VAO_4) / sizeof(int), texture_strike_sword); break;
	case injured:		Anime_NON_Cycle(50, VAO_2, sizeof(VAO_2) / sizeof(int), texture_injured); break;
	case defends:		Anime_NON_Cycle(50, VAO_2, sizeof(VAO_2) / sizeof(int), texture_defends); break;
	case fall:			Anime_NON_Cycle(50, VAO_3, sizeof(VAO_3) / sizeof(int), texture_fall); break;
	case dead:			Anime_Cycle(50, VAO_1, sizeof(VAO_1) / sizeof(int), texture_dead); break;
/*	case stand: Stand(50, VAO_2, sizeof(VAO_2) / sizeof(int), texture_stand); break;
	case walk: Walk(50, VAO_6, sizeof(VAO_6) / sizeof(int), texture_walk); break;
	case strike_sword: Strike_Sword(50, VAO_5, sizeof(VAO_5) / sizeof(int), texture_strike_sword); break;
	case injured: Injured(50, VAO_2, sizeof(VAO_2) / sizeof(int), texture_injured); break;*/
	}

	//bind_VAO(25, time_, VAO_5, sizeof(VAO_5) / sizeof(int), texture_strike_sword);
	//bind_VAO(50, time_, VAO_2, sizeof(VAO_2) / sizeof(int), texture_stand);

	//загружаем из юниформы текстурные координаты, которые загружены из масссива в вертексный, потом в фрагментный, потом в юниформу tex0
	//tex0Uni = glGetUniformLocation(shaderProgram, "tex0");//создаем перем в кот будем хранить указатель на переменную uniform
	glUseProgram(shaderProgram);
	glUniform1i(tex0Uni, 0);//загружаем в юниформу ID текстурного блока с картинкой (тот, что активировали ранее glActiveTexture(GL_TEXTURE0);)

	//draw element
	glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
}