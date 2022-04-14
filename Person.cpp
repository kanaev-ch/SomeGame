#include "Person.h"

void create_VAO(GLfloat* vertices, int sizeof_vertices, GLuint* indices, int sizeof_indices, float count_of_frames, float current_frame, GLuint& VAO, GLuint& VBO, GLuint& EBO)
{
	//change texture coordinates for different frames
	float frame = 1 / count_of_frames;
	if (current_frame != 0)
	{
		vertices[6] += frame;
		vertices[14] += frame;
		vertices[22] += frame;
		vertices[30] += frame;
	}

	//bind VAO
	glBindVertexArray(VAO);

	//bind VBO and link it to VAO activated before
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof_vertices, vertices, GL_STATIC_DRAW);

	//bind EBO and link it to VAO activated before
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof_indices, indices, GL_STATIC_DRAW);

	//insert in vertex shader layouts of coordinates and colors from array vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	//activate layouts
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//unbind all elements
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void create_Texture(const char* image, GLuint& texture)
{
	//Texture
	int widthImg, heightImg, numColCh;//ширина, высота в пикселах, кол-во цвет каналов картинки
	stbi_set_flip_vertically_on_load(true);//т.к. ogl считае изобр из левого нижнего угла в правый верхний, а stb из левого верхнего в правый нижний картинка получается перевенутой, эта ф-я как бы переворачивает восприятие stb
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &texture);//генерируем, создаем объект текстуры, 1 - кол-во текстур, 2 - ссылочная переменная

	//Назначаем текстуру текстурному блоку - это слоты для текстур, кот объединяются в связку, обычно они содержат около 16 текстур и фрагментный шейдер работает с ними одновременно
	glActiveTexture(GL_TEXTURE0);//активируем текстурный блок, это его айди, как я понимаю в нем хранится до 16 текстур?
	glBindTexture(GL_TEXTURE_2D, texture);//связываем (bind), делаем активной, 1 - тип, 2 - ссылка на текстуру

	//Настраиваем параметры исп-я текстуры
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//Как картинка будет обрабатываться при увеличении или уменьшении, GL_NEAREST - сохраняет все пиксели как есть это предпочтительнее с пиксельной графикой,
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//GL_LINEAR - создает новые пиксели  в соответствии с соседними, картинка более размытая, GL_TEXTURE_MIN_FILTER - при уменьшении, GL_TEXTURE_MAG_FILTER - пр увеличении

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//как текстура будет повторяться по осям, GL_TEXTURE_WRAP_: S - ось X, Т - ось Y, R - ось Z
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//GL_REPEAT - просто повторяет, GL_MIRRORED_REPEAT - повторяет но каждый раз отражает-переворачивает его

	//Генерируем текстуру
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);//1 - тип, 3 - тип цветных каналов кот мы хотим увидеть
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);//1 - тип, 3 - тип цветных каналов кот мы хотим увидеть

	glGenerateMipmap(GL_TEXTURE_2D);//генерация mit-карты, это версии той же текстуры с меньшим разрешением, кот исп например если текстура далеко

	stbi_image_free(bytes);//удаляем ненужный массив
	glBindTexture(GL_TEXTURE_2D, 0);//отвязываем текстуру чтобы случайно не повредить
}

void generate_VAO_VBO(GLuint * VAO, GLuint * VBO, int size)
{
	for (int i = 0; i < size; i++) glGenVertexArrays(1, &VAO[i]);
	for (int i = 0; i < size; i++) glGenBuffers(1, &VBO[i]);
}

void configure_VAO_VBO(GLfloat * vertices, int sizeof_vertices, GLuint * indices, int sizeof_indices, GLuint* VAO, GLuint* VBO, float count_frames, GLuint& EBO, bool direction)
{
	float frame = 1.0f / count_frames;

	if (direction)
	{
		vertices[6] = 0.0f;
		vertices[14] = 0.0f;
		vertices[22] = frame;
		vertices[30] = frame;
	}
	else {
		vertices[6] = frame;
		vertices[14] = frame;
		vertices[22] = 0.0f;
		vertices[30] = 0.0f;
	}
	//create VAO, VBO, EBO objects in vector arrays with parameters
	for (int i = 0; i < count_frames; i++)
		create_VAO(vertices, sizeof_vertices, indices, sizeof_indices, count_frames, float(i), VAO[i], VBO[i], EBO);
}

/*Person::Person(const char* vertexFile, const char* fragmentFile, const char* image, float x_, float y_, float z_, float sprite_h_)
{
	//change global height of poligon
	vertices[10] = vertices[18] = sprite_h_;

	direction = true;

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
	x = x_; y = y_ * -1; z = z_;
	view = glm::translate(view, glm::vec3(x, y, z));

	//create texture object
	create_Texture(image, texture);

}*/

void Person::change_Height_Sprite(float sprite_h_)
{
	//change global height of poligon
	sprite_h = sprite_h_;

	//change global height of poligon
	vertices[10] = vertices[18] = sprite_h;

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
}

void Person::change_Direction(bool direction_)
{
	direction = direction_;

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
}

void Person::Move(float x_, float y_, float z_)
{
	view = glm::mat4(1.0f);
	if (x != x_)
	{
		walk = true;
		if (x < x_)
		{
			x += speed_move;
			change_Direction(false);
			if (x > x_)
			{
				x = x_;
				walk = false;
				change_Direction(true);
			}
		}
		else {
			x -= speed_move;
			if (x < x_)
			{
				x = x_;
				walk = false;
			}
		}
	}

	float y__ = y_ * -1;
	view = glm::mat4(1.0f);
	if (y != y__)
	{
		walk = true;
		if (y < y__)
		{
			y += speed_move;
			if (y > y__)
			{
				y = y__;
				walk = false;
			}
		}
		else {
			y -= speed_move;
			if (y < y__)
			{
				y = y__;
				walk = false;
			}
		}
	}

	view = glm::translate(view, glm::vec3(x, y, z));
}
void Person::bind_Texture(GLuint& texture_)
{
	//bind texture
	glBindTexture(GL_TEXTURE_2D, texture_);
}


int Person::bind_VAO(int frame_milliseconds_, float time_, GLuint * VAO, int size_VAO, GLuint& texture_)
{
	int i = 0;
	int frame_milliseconds = frame_milliseconds_;
	int frame_time_counter = 0;
	int time = int(time_ * 100) % (frame_milliseconds * size_VAO);

	//bind VAO
	for (i = 0; i < size_VAO; i++)
	{
		if (time >= frame_time_counter && time <= frame_time_counter + frame_milliseconds)
		{
			glBindVertexArray(VAO[i]);
			break;
		}
		frame_time_counter += frame_milliseconds;
	}

	//bind texture
	bind_Texture(texture_);
	return i;
}

void Person::Selected_Uniform_Load(bool flag)
{
	glUseProgram(shaderProgram);
	glUniform1i(uniSelected, flag);//загружаем в юниформу флаг подсветки текстуры
}



Person::~Person()
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
	glDeleteTextures(1, &texture);
}

//if error in compile of shaders
void Person::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infolog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infolog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infolog << std::endl;
		}
	}
	else
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infolog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infolog << std::endl;
		}
	}
}
