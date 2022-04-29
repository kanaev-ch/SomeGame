#include "Tile.h"

//func takes simbols from file to string
/*std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}*/

/*Tile::Tile()
{
}*/

Tile::Tile(const char* vertexFile, const char* fragmentFile, const char* image, float x_, float y_, float z_)
{
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

	//create VAO, VBO, EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind VAO
	glBindVertexArray(VAO);

	//bind VBO and link it to VAO activated before
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//bind EBO and link it to VAO activated before
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

	//matrix of position tile, and changing to needed position here
	view = glm::mat4(1.0f);
	x = x_; y = y_; z = z_;
	view = glm::translate(view, glm::vec3(x, y, z));

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


	//текстурная координата идет от 0,0 нижний левый угол, 1,1 верхний правый, если задать координаты больше 1, то изобр будет повторяться

	//Юниформа сообщает ogl какой модуль текстуры он должен использовать
	//загружаем из юниформы текстурные координаты, которые загружены из масссива в вертексный, потом в фрагментный, потом в юниформу tex0
	tex0Uni = glGetUniformLocation(shaderProgram, "tex0");//создаем перем в кот будем хранить указатель на переменную uniform
	glUseProgram(shaderProgram);
	glUniform1i(tex0Uni, 0);//загружаем в юниформу ID текстурного блока с картинкой (тот, что активировали ранее glActiveTexture(GL_TEXTURE0);)

	//End Texture
}

/*Tile::Tile(const Tile& tile)
{
	shaderProgram = tile.shaderProgram;
	VAO = tile.VAO;
	VBO = tile.VBO;
	EBO = tile.EBO;

	texture = tile.texture;
	tex0Uni = tile.tex0Uni;

	view = tile.view;

	x = tile.x; y = tile.y; z = tile.z;
}*/

Tile::~Tile()
{
	//delete all elements
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	glDeleteTextures(1, &texture);
}

void Tile::Draw(Camera & camera, CLR clr_)
{
	//activate shader programm and VAO
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	//load to vertex uniform current position of tile
	int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));	


	//Block for color tiles in different colors by load color in uniform
	//clr = red_green;
	//CLR clr = clr_;
	GLuint switch_clr = glGetUniformLocation(shaderProgram, "switch_clr");
	glUniform1i(switch_clr, clr_);



	//aplying camera uniform fo look at
	//camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
	camera.Matrix(shaderProgram, "camMatrix");

	//bind texture
	glBindTexture(GL_TEXTURE_2D, texture);

	//draw element
	glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
}

//if error in compile of shaders
void Tile::compileErrors(unsigned int shader, const char* type)
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