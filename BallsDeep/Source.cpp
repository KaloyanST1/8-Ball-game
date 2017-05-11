#include <iostream>
#include <cmath>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SOIL/SOIL.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shaders.h"
#include "ball.h"
using namespace std;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
const GLuint WIDTH = 800, HEIGHT = 600;
GLfloat Xball_speed = 0.005f;
GLfloat Zball_speed = 0.003f;
GLfloat Xball_speed2 = 0.005f;
GLfloat Zball_speed2 = 0.003f;
GLuint VBO, VAO, EBO, VBO2;
GLuint texture1;
GLuint texture2;
GLuint texture3;
GLfloat Xball = 0.0;
GLfloat Zball = 0.0;
GLfloat Xball2 = 0.0;
GLfloat Zball2 = 0.0;
GLfloat camA = 1.0f;
GLfloat camB = 3.0f;
GLfloat camC = 0.0f;
bool* keyStates = new bool[256];
int main()
{
    makeBall();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Balls Deep", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glewExperimental = GL_TRUE;
    glewInit();
    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_DEPTH_TEST);
    Shader ourShader("vertexshader.glsl", "fragmentshader.glsl");

	GLfloat vertices_table[] = {

		-2.0f, -0.25f, -1.0f,  0.0f, 0.0f,
		2.0f, -0.25f, -1.0f,  1.0f, 0.0f,
		2.0f,  0.25f, -1.0f,  1.0f, 1.0f,
		2.0f,  0.25f, -1.0f,  1.0f, 1.0f,
		-2.0f,  0.25f, -1.0f,  0.0f, 1.0f,
		-2.0f, -0.25f, -1.0f,  0.0f, 0.0f,
		-2.0f, -0.25f,  1.0f,  0.0f, 0.0f,
		2.0f, -0.25f,  1.0f,  1.0f, 0.0f,
		2.0f,  0.25f,  1.0f,  1.0f, 1.0f,
		2.0f,  0.25f,  1.0f,  1.0f, 1.0f,
		-2.0f,  0.25f,  1.0f,  0.0f, 1.0f,
		-2.0f, -0.25f,  1.0f,  0.0f, 0.0f,
		-2.0f,  0.25f,  1.0f,  1.0f, 0.0f,
		-2.0f,  0.25f, -1.0f,  1.0f, 1.0f,
		-2.0f, -0.25f, -1.0f,  0.0f, 1.0f,
		-2.0f, -0.25f, -1.0f,  0.0f, 1.0f,
		-2.0f, -0.25f,  1.0f,  0.0f, 0.0f,
		-2.0f,  0.25f,  1.0f,  1.0f, 0.0f,
		2.0f,  0.25f,  1.0f,  1.0f, 0.0f,
		2.0f,  0.25f, -1.0f,  1.0f, 1.0f,
		2.0f, -0.25f, -1.0f,  0.0f, 1.0f,
		2.0f, -0.25f, -1.0f,  0.0f, 1.0f,
		2.0f, -0.25f,  1.0f,  0.0f, 0.0f,
		2.0f,  0.25f,  1.0f,  1.0f, 0.0f,
		-2.0f, -0.25f, -1.0f,  0.0f, 1.0f,
		2.0f, -0.25f, -1.0f,  1.0f, 1.0f,
		2.0f, -0.25f,  1.0f,  1.0f, 0.0f,
		2.0f, -0.25f,  1.0f,  1.0f, 0.0f,
		-2.0f, -0.25f,  1.0f,  0.0f, 0.0f,
		-2.0f, -0.25f, -1.0f,  0.0f, 1.0f
	};


	
	

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height;
    unsigned char* image = SOIL_load_image("table.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); 

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    unsigned char* image2 = SOIL_load_image("ball.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image2);
    glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	unsigned char* image3 = SOIL_load_image("ball2.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image3);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image3);
	glBindTexture(GL_TEXTURE_2D, 0);

    while (!glfwWindowShouldClose(window))
    {

        Xball = (Xball + Xball_speed);
        Zball = (Zball + Zball_speed);

        if (Xball >= 18 || Xball <= -18){
            Xball_speed = -Xball_speed;   
        }
        if (Zball >= 8 || Zball <= -8){
            Zball_speed = -Zball_speed;
        }
		cout << Xball << endl;
		cout << Zball << endl;
		Xball2 = (Xball2 + Xball_speed2);
		Zball2 = (Zball2 + Zball_speed2);

		if (Xball2 >= 18 || Xball2 <= -18) {
			Xball_speed2 = -Xball_speed2;
		}
		if (Zball2 >= 8 || Zball2 <= -8) {
			Zball_speed2 = -Zball_speed2;
		}
		cout << Xball2 << endl;
		cout << Zball2 << endl;
        glfwPollEvents();


        glClearColor(0.4f, 1.0f, 1.0f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);


        glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);

        ourShader.Use();

        glm::mat4 view;
        glm::mat4 projection;
        view = glm::lookAt(glm::vec3(camA, camB, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);


        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint modelLoc2 = glGetUniformLocation(ourShader.Program, "model2");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_table), vertices_table, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0); 
        glBindVertexArray(VAO);
        glm::mat4 model;
		glm::mat4 model2;
        model = glm::translate(model, glm::vec3( 0.0f,  0.0f,  0.0f));
		model2 = glm::translate(model2, glm::vec3(0.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers( 1, &EBO );
        glDeleteBuffers( 1, &VBO2 );
        

        glBindTexture(GL_TEXTURE_2D, texture2);
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenBuffers(1, &VBO2);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLint), &indices[0], GL_STATIC_DRAW);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO2);
        glBufferData(GL_ARRAY_BUFFER, UV.size() * sizeof(GLfloat), &UV[0], GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);
        glBindVertexArray(VAO);
        model = glm::scale(model,glm::vec3(0.1f)) * glm::translate(model, glm::vec3(Xball, -0.5f, Zball));
		model2= glm::scale(model2, glm::vec3(0.1f)) * glm::translate(model2, glm::vec3(Xball2, -0.5f, Zball2));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers( 1, &EBO );
        glDeleteBuffers( 1, &VBO2 );
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO2);
    glfwTerminate();
    return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		Xball_speed *= 2;
		Zball_speed *= 2;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		Xball_speed /= 2;
		Zball_speed /= 2;
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		camB = camB + 0.5f;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		camA = camA - 0.5f;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		camA = camA + 1.0f;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		camB = camB - 0.5f;
	}
}

