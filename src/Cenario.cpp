#include "Cenario.hpp"

// Parametros

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
		glVertex3f(-xC, -yC, -0.1);
		glVertex3f(-RoadLine, -yC, -0.1);
		glVertex3f(-RoadLine, 0.0, -zAxis);
		glVertex3f(-xC * zAxis, 0.0, -zAxis);

		// Margem direita da estrada
		glVertex3f(RoadLine, -yC, -0.1);
		glVertex3f(xC, -yC, -0.1);
		glVertex3f(xC * zAxis, 0.0, -zAxis);
		glVertex3f(RoadLine, 0.0, -zAxis);
	glEnd();
}

void Cenario::DesenhaEstrada() {

	float xE, yE;
	xE = RoadRatio * xC;
	yE = yC;
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		glVertex3f(-xE, -yE, -0.1);
		glVertex3f(xE, -yE, -0.1);
		glVertex3f(xE, 0.0, -zAxis);
		glVertex3f(-xE, 0.0, -zAxis);
	glEnd();
}
