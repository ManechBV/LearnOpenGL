#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <math.h>

void	ft_framebuffer_size_callback(GLFWwindow *window, int width, int height);
void	ft_process_input(GLFWwindow *window);

const char	*vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;"
"layout (location = 1) in vec3 aColor;"
"out vec3 ourColor;"
"void main()"
"{"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
"	ourColor = aColor;"
"}\0";

const char	*fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;"
"in vec3 ourColor;"
"void main()"
"{"
"	FragColor = vec4(ourColor, 1.0);"
"}\0";

int	main()
{
	// Flags pour mettre bien glfw et dire on est en version 3.3 avec le profil core
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creer une fenetre
	GLFWwindow	*window = glfwCreateWindow(800, 600, "my game", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window");
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(window);

	// initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD");
		return (-1);
	}

	// tell opengl our window size
	glViewport(0, 0, 800, 600);
	// tell glfw to use our callback function
	glfwSetFramebufferSizeCallback(window, ft_framebuffer_size_callback);

	unsigned int	vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int		success;
	char	infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
	}

	unsigned int	fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s", infoLog);
	}

	unsigned int	shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("ERROR::SHADER_PROGRAM::LINKING_FAILED\n%s", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
		// positions		// colors
		 0.5f,  -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,// top right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// bottom right
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f// bottom left
	};

	unsigned int	indices[] = {
		0, 1, 2 
	};

	unsigned int	VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	unsigned int	VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int	EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // activate wireframe mode (stylax)

	// main loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		ft_process_input(window);

		// rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// TRIIIIIIIIIIIIIAAAAAAAAAAAAAAAAAAAANNNNNNNNNNNNNGLE
		glUseProgram(shaderProgram);

		/*
		float	time_value = glfwGetTime();
		float	green_value = (sin(time_value) / 2.0f) + 0.5f;
		int		vertex_color_location = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertex_color_location, 0.0f, green_value, 0.0f, 1.0f);
		*/

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// check and call events and swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return (0);
}

void	ft_framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void	ft_process_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
