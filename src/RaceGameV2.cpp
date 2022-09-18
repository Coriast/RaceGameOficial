#include <iostream>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <gl/GLU.h>
#include "Cenario.hpp"

// Variáveis para FPS
float FPS = 60.0f, now = 0.0f, dt = 0.0f, lastTime = 0.0f;

void iniciar() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST); // Habilita a profundidade
}

void configuraCamera(int w, int h) {
	glViewport(0, 0, w, h);
	float aspect = (float)w / (float)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.1, 500.0);

	glMatrixMode(GL_MODELVIEW);
}

void desenha(Cenario cena) {
	glLoadIdentity();

	cena.DesenhaCena();
	cena.DesenhaEstrada();
}

int main()
{
	const int LARGURA = 800, ALTURA = 600;

	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// Criar Tela
	GLFWwindow* window = glfwCreateWindow(LARGURA, ALTURA, "Race Game", NULL, NULL);
	glfwSetWindowPos(window, 300, 100);

	glfwMakeContextCurrent(window);

	iniciar();

	Cenario cena(1.0, 1.0);

	while (!glfwWindowShouldClose(window)) {
		// Processamento de Eventos
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		// Renderizar
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpeza dos buffers do loop passado

		int w, h;
		glfwGetFramebufferSize(window, &w, &h);
		configuraCamera(w, h);

		desenha(cena);

		glfwSwapBuffers(window);
		// Prende em 60 FPS, tenho quase certeza de que é a forma errada de fazer :3
		do {
			now = (float)glfwGetTime();
			dt = now - lastTime;

		} while (dt < (1.0f / FPS));
		lastTime = now;
	}

	glfwTerminate();
	return 0;
}
