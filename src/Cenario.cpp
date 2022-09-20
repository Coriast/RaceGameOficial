#include "Cenario.hpp"

// Parametros
float RoadStrip[q_Strips][2] = { {0.3, 0.0},
								 {0.3, 6.0}, 
								 {0.3, 12.0},
								 {0.3, 18.0} };

float StripVel = 32.5;

// Construtores
Cenario::Cenario(float xC, float yC, float zAxis) {
	this->xC = xC;
	this->yC = yC;
	this->zAxis = zAxis;
}

Cenario::Cenario(float xC, float yC) : Cenario(xC, yC, 0.0f) {}

// Metodos
void Cenario::DesenhaCena(){
	float RoadLine = xC * RoadRatio;

	glColor3f(0.0, 0.6, 0.0);
	glBegin(GL_QUADS);
		// Margem esquerda da estrada
		glVertex3f(-RoadLine, -yC, -zAxis);
		glVertex3f(-xC, -yC, -zAxis);
		glVertex3f(-xC, 0.0, -zAxis);
		glVertex3f(-RoadLine, 0.0, -zAxis);

		// Margem direita da estrada
		glVertex3f(RoadLine, -yC, -zAxis);
		glVertex3f(xC, -yC, -zAxis);
		glVertex3f(xC, 0.0, -zAxis);
		glVertex3f(RoadLine, 0.0, -zAxis);
	glEnd();
}

void Cenario::DesenhaEstrada() {

	
	// Desenha a Estrada
	float xE, yE;
	xE = RoadRatio * xC;
	yE = yC;
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_QUADS);
		glVertex3f(-xE, -yE, -zAxis);
		glVertex3f(xE, -yE, -zAxis);
		glVertex3f(xE, 0.0, -zAxis);
		glVertex3f(-xE, 0.0, -zAxis);
	glEnd();
	
	// Desenha Linhas da Estrada
	
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	for (int i = 0; i < q_Strips; i++)
	{
		float* xs = &RoadStrip[i][0];
		float* ys = &RoadStrip[i][1];

		// Coordenadas de Baixo 
		if ((*ys + StripSize) > yC) {
			glVertex3f(-*xs, -yC, -zAxis + 0.1);
			glVertex3f(*xs, -yC, -zAxis + 0.1);
		}
		else {
			glVertex3f(-*xs, -(*ys + StripSize), -zAxis + 0.1);
			glVertex3f(*xs, -(*ys + StripSize), -zAxis + 0.1);
		}

		// Coordenadas de Cima
		if (*ys < 0.0) {
			glVertex3f(*xs, 0.0, -zAxis + 0.1);
			glVertex3f(-*xs, 0.0, -zAxis + 0.1);
		}
		else {
			glVertex3f(*xs, -*ys, -zAxis + 0.1);
			glVertex3f(-*xs, -*ys, -zAxis + 0.1);
		}
		
		*ys += StripVel * (1.0 / 60.0);
		if (*ys > yC) {
			*ys = -StripSize;
		}
	}
	glEnd();
}
