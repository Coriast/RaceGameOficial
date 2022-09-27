#include <iostream>
#include <random>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <gl/GLU.h>
#include "Cenario.hpp"
#include "Carro.hpp"
#include "Camera.hpp"

// Tamanho da Estrada
float roadSize = 30.0;

// jogador
float JogadorPos[3] = { 2.0, -roadSize + 2.0, 0.0 };
float JogadorVel = 0.0;
float JogadorMaxVel = 50.0;

// Inimigos
bool desenhaEn[4] = {false, false, false, false};
float En_Pos[4][3] = {	{-2.0, 1.0, 0.0 },
						{3.0, 1.0, 0.0 },
						{-1.5, 1.0, 0.0 },
						{1.0, 1.0, 0.0 } };
float En_Vel[4] = { 22.0, 30.0, 17.5, 45.0 };

// Variáveis para FPS
float FPS = 60.0f, now = 0.0f, dt = 0.0f, lastTime = 0.0f;

// Inicializar Câmera
bool VisaoJogador = true;
Camera camera(vec3(0, 0, 0));

void iniciar() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST); // Habilita a profundidade
}

int randomNumber() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(-3, 3);
	return distr(gen);
}

void configuraVisao(int w, int h) {
	glViewport(0, 0, w, h);
	float aspect = (float)w / (float)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.1, 500.0);

	glMatrixMode(GL_MODELVIEW);
}

void EventosInimigo() {
	for (int i = 0; i < 4; i++) {
		if (En_Pos[i][1] < 1.0)
			En_Pos[i][1] = En_Pos[i][1] + ((En_Vel[i] - JogadorVel) * (1.0 / FPS));
		else
			En_Pos[i][1] = 0.9;

		if (En_Pos[i][1] > 0.0)
			desenhaEn[i] = false;
		if (En_Pos[i][1] < 0.0)
			desenhaEn[i] = true;

		// Quando o cara sumir da visão ele percorre ainda um espaço antes de ser gerado de novo
		if (En_Pos[i][1] < -(2 * roadSize)) {
			En_Pos[i][0] = (float)randomNumber();
			En_Pos[i][1] = 0.0;
		}
	}
	
}

void checaEventos(GLFWwindow* window) {
	// Velocidade do Jogador
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		if (JogadorVel < JogadorMaxVel)
			JogadorVel = JogadorVel + (5.0 * (1.0 / FPS));
	} else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		if (JogadorVel > 0.0)
			JogadorVel = JogadorVel - (5.0 * (1.0 / FPS));
		if (JogadorVel < 0.0)
			JogadorVel = 0.0;
	}
	else {
		JogadorVel = JogadorVel - (2.0 * (1.0 / FPS));
		if (JogadorVel < 0.0)
			JogadorVel = 0.0;
	}
	std::cout << JogadorVel << std::endl;

	// Checagens do Inimigo
	EventosInimigo();

	// Mover Esquerda Direita
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		if (JogadorPos[0] > -3.0)
			JogadorPos[0] = JogadorPos[0] - (4.0 * (1.0 / FPS) * (JogadorVel/20));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		if (JogadorPos[0] < 3.0)
			JogadorPos[0] = JogadorPos[0] + (4.0 * (1.0 / FPS) * (JogadorVel/20));
	}

	// Mudar Câmera
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		VisaoJogador = true;
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		VisaoJogador = false;
	}
}

void desenhaCoordenadas() {
	glPushMatrix();
	// Preciso mandar minha rota de Coordenadas para o -55 do meu Z se não fica fora da visão
	glTranslatef(0.0, 0.0, -55.0);

	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(-500.0, 0.0, 0.0);
	glVertex3f(500.0, 0.0, 0.0);

	glColor3f(0, 1, 0);
	glVertex3f(0.0, -500.0, 0.0);
	glVertex3f(0.0, 500.0, 0.0);

	glColor3f(0, 0, 1);
	glVertex3f(0.0, 0.0, -500.0);
	glVertex3f(0.0, 0.0, 500.0);
	glEnd();
	glPopMatrix();
}

void desenha(Cenario cena, Carro jogador, Carro inimigo) {
	glLoadIdentity();

	if (VisaoJogador) {
		camera.VisaoJogador(vec3(JogadorPos[0], JogadorPos[1], -52.0));
	}	
	else {
		camera.VisaoPadrao(vec3(JogadorPos[0], JogadorPos[1]/2, 0.0));
	}

	desenhaCoordenadas();

	cena.DesenhaCena();
	cena.DesenhaEstrada(JogadorVel);

	jogador.DesenhaCarro(JogadorPos, 0, JogadorVel);

	for (int i = 0; i < 4; i++) {
		if (desenhaEn[i])
			inimigo.DesenhaCarro(En_Pos[i], i+1, En_Vel[i]);
	}
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

	Cenario cena(20.0, roadSize, 55.0);
	Carro jogador(2.0, 55.0);
	Carro inimigo(2.0, 55.0);

	while (!glfwWindowShouldClose(window)) {
		// Processamento de Eventos
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		checaEventos(window);

		// Renderizar
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpeza dos buffers do loop passado

		int w, h;
		glfwGetFramebufferSize(window, &w, &h);
		configuraVisao(w, h);

		desenha(cena, jogador, inimigo);

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
