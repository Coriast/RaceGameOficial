#include "Cenario.hpp"

// Parametros
float RoadStrip[q_Strips][2] = {};
float space = 0.0;
float StripVel = 0.0;
float BufferStrip[2] = { 0.3, 0.0 }; bool useBuffer = false;
float RoadLine = 0.0;

float placaPos[3] = { RoadLine + 0.5, 0.0, 2.5 }; bool invert = false;
float pL = 0.2;

float xCloud = 0.0, cloudH = 15.0;

void DesenhaPlaca(float zAxis, float yC) {
	if (invert) 
		placaPos[0] = placaPos[0] * -1;

	// desenha Suporte 
	glColor3ub(105, 105, 105);
	glBegin(GL_QUADS);
	glVertex3f(placaPos[0], -placaPos[1], -zAxis);
	glVertex3f(placaPos[0] + pL, -placaPos[1], -zAxis);
	glVertex3f(placaPos[0] + pL, -placaPos[1], -(zAxis - placaPos[2]));
	glVertex3f(placaPos[0], -placaPos[1], -(zAxis - placaPos[2]));
	glEnd();

	float pA = (zAxis - (placaPos[2] + (pL*5)));
	// Desenha Placa
	glColor3ub(255, 32, 21);
	glBegin(GL_QUADS);	
	glVertex3f(placaPos[0] - (pL*2), -placaPos[1], -(zAxis - placaPos[2]));
	glVertex3f(placaPos[0] + pL*3, -placaPos[1], -(zAxis - placaPos[2]));
	glVertex3f(placaPos[0] + pL*3, -placaPos[1], -pA);
	glVertex3f(placaPos[0] - (pL*2), -placaPos[1], -pA);
	glEnd();



	placaPos[1] = placaPos[1] + StripVel * (1.0 / 60.0);
	if (placaPos[1] > yC * 2) {
		placaPos[1] = 0.0;
		if (invert)
			invert = false;
		else
			invert = true;
	}
}

void DesenhaCeu(float zAxis) {
	glColor3ub(35, 16, 121);
	glBegin(GL_QUADS);
	glVertex3f(-500.0, 0.0, -zAxis);
	glVertex3f(500.0, 0.0, -zAxis);
	glVertex3f(500.0, 0.0, 0.0);
	glVertex3f(-500.0, 0.0, 0.0);
	glEnd();

	float zC = (zAxis - cloudH);
	glColor3ub(240, 234, 214);
	glBegin(GL_QUADS);
	glVertex3f(-xCloud, -10.0, -zC);
	glVertex3f(-(xCloud - 5.0), -10.0, -zC);
	glVertex3f(-(xCloud - 5.0), -10.0, -(zC - 3.0));
	glVertex3f(-xCloud, -10.0, -(zC - 3.0));

	glVertex3f(-(xCloud - 5.0), -10.0, -zC);
	glVertex3f(-(xCloud - 15.0), -10.0, -zC);
	glVertex3f(-(xCloud - 15.0), -10.0, -(zC - 7.0));
	glVertex3f(-(xCloud - 5.0), -10.0, -(zC - 7.0));
	glEnd();

	xCloud = xCloud + 14.0 * (1.0 / 60.0);
	if (xCloud > 100.0)
		xCloud = -100.0;
}

// Construtores
Cenario::Cenario(float xC, float yC, float zAxis) {
	this->xC = xC;
	this->yC = yC;
	this->zAxis = zAxis;
	StripSize = (0.5 * yC)/q_Strips;
	space = (0.5 * yC) / q_Strips;

	for (int i = 0; i < q_Strips; i++) {
		RoadStrip[i][0] = 0.3;
		if (i == 0)
			RoadStrip[i][1] = 0.0;
		else
			RoadStrip[i][1] = RoadStrip[i - 1][1] + StripSize+ space;
	}
}

Cenario::Cenario(float xC, float yC) : Cenario(xC, yC, 0.0f) {}

// Metodos
void Cenario::DesenhaCena(){
	float RoadLine = xC * RoadRatio;

	glColor3f(0.0, 0.6, 0.0);
	glBegin(GL_QUADS);
		// Margem esquerda da estrada
		glVertex3f(-RoadLine, -yC, -zAxis);
		glVertex3f(-100, -yC, -zAxis);
		glVertex3f(-100, 0.0, -zAxis);
		glVertex3f(-RoadLine, 0.0, -zAxis);

		// Margem direita da estrada
		glVertex3f(RoadLine, -yC, -zAxis);
		glVertex3f(100, -yC, -zAxis);
		glVertex3f(100, 0.0, -zAxis);
		glVertex3f(RoadLine, 0.0, -zAxis);
	glEnd();

	placaPos[0] = RoadLine + 0.5;
	DesenhaPlaca(zAxis, yC);
	DesenhaCeu(zAxis);
}

void Cenario::DesenhaEstrada(float JogadorVel) {
	StripVel = JogadorVel;
	
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
		// Problema que tive ao implementar o Buffer foi não notar que ele executava 4 vezes por causa do For 
		if (useBuffer && i == 0) {
			// Coords de Baixo
			glVertex3f(-BufferStrip[0], -yC, -zAxis + 0.01);
			glVertex3f(BufferStrip[0], -yC, -zAxis + 0.01);

			// Coords de Cima
			glVertex3f(BufferStrip[0], -BufferStrip[1], -zAxis + 0.01);
			glVertex3f(-BufferStrip[0], -BufferStrip[1], -zAxis + 0.01);

			BufferStrip[1] += StripVel * (1.0 / 60.0);
			if (BufferStrip[1] > yC) {
				useBuffer = false;
				BufferStrip[1] = 0.0;
			}
		}

		float* xs = &RoadStrip[i][0];
		float* ys = &RoadStrip[i][1];

		// Coordenadas de Baixo 
		if ((*ys + StripSize) > yC) {
			glVertex3f(-*xs, -yC, -zAxis + 0.01);
			glVertex3f(*xs, -yC, -zAxis + 0.01);
		}
		else {
			glVertex3f(-*xs, -(*ys + StripSize), -zAxis + 0.01);
			glVertex3f(*xs, -(*ys + StripSize), -zAxis + 0.01);
		}

		// Coordenadas de Cima
		if (*ys < 0.0) {
			glVertex3f(*xs, 0.0, -zAxis + 0.01);
			glVertex3f(-*xs, 0.0, -zAxis + 0.01);
		}
		else {
			glVertex3f(*xs, -*ys, -zAxis + 0.01);
			glVertex3f(-*xs, -*ys, -zAxis + 0.01);
		}

		*ys += StripVel * (1.0 / 60.0);
		if (*ys > (yC - StripSize)) {
			useBuffer = true;
			BufferStrip[1] = *ys;
			*ys = -StripSize;
		}
	}
	glEnd();
}
