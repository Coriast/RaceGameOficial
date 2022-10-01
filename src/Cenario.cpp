#include <glm/glm.hpp>
#include <glm/ext.hpp>
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

float yArvore = 45.0;

void DesenhaFace(float yC, int lados, GLfloat PI) {

	std::vector<glm::vec3> pontos;

	glm::vec3 center = glm::vec3(0, 0, 0);
	GLfloat theta = 2.0 * PI / lados;

	glBegin(GL_TRIANGLE_FAN);
	center = glm::vec3(0, 0, 1.0);
	glVertex3fv(glm::value_ptr(center));
	for (int i = 0; i <= lados; i++) {
		GLfloat x = cos(i * theta);
		GLfloat y = sin(i * theta);
		glm::vec3 ponto = glm::vec3( x, y, 1.0 );
		pontos.push_back(ponto);
		glVertex3fv(glm::value_ptr(ponto));
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	center = glm::vec3(0, 0, -1.0);
	glVertex3fv(glm::value_ptr(center));
	for (int i = 0; i <= lados; i++) {
		GLfloat x = cos(i * theta);
		GLfloat y = sin(i * theta);
		glm::vec3 ponto = glm::vec3(x, y, -1.0);
		pontos.push_back(ponto);
		glVertex3fv(glm::value_ptr(ponto));
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < lados; i++) {
		glVertex3fv(glm::value_ptr(pontos[i]));
		glVertex3f(pontos[i].x, pontos[i].y, pontos[i].z * -1);
		if (i == lados - 1) {
			glVertex3fv(glm::value_ptr(pontos[0]));
			glVertex3f(pontos[0].x, pontos[0].y, pontos[0].z * -1);
		}
	}
	glEnd();
}

void Cenario::DesenhaArvore(float zAxis, int lados, float raio, float yC) {
	const GLfloat PI = 3.14159265359;
	float alt = (raio * 10)/2;
	// Transformações
	glm::vec3 pos = glm::vec3(8, -yArvore, -(zAxis-alt));
	glm::mat4 M = glm::mat4(1);

	// Estas são as transformações gerais do Objeto de forma complexa
	glm::mat4 T = glm::translate(M, pos);
	glm::mat4 R = glm::rotate(M, (float)glm::radians(0.0), glm::vec3(1, 0, 0));
	glm::mat4 S = glm::scale(M, glm::vec3(raio, raio, raio));
	glm::mat4 F = glm::mat4(1);
	F = T * R * S;

	// Estas são as transformações que vão ser aplicadas apenas para partes específicas
	glm::mat4 Td = glm::translate(M, glm::vec3(0, 0, 0));
	glm::mat4 Rd = glm::rotate(M, (float)glm::radians(0.0), glm::vec3(0, 1, 0));
	glm::mat4 Sd = glm::scale(M, glm::vec3(2, 2, 6));
	glm::mat4 Fd = glm::mat4(1);
	Fd = (T * Td) * (R * Rd) * (S * Sd); // uma multiplicação entre as matrizes padrões com a matriz própria de uma parte
	
	glm::mat4 Te = glm::translate(M, glm::vec3(0, 0, 5*raio));
	glm::mat4 Re = glm::rotate(M, (float)glm::radians(90.0), glm::vec3(1, 0, 0));
	glm::mat4 Se = glm::scale(M, glm::vec3(4, 4, 4));
	glm::mat4 Fe = glm::mat4(1);
	Fe = (T * Te) * (R * Re) * (S * Se); // uma multiplicação entre as matrizes padrões com a matriz própria de uma parte

	glColor3ub(36, 26, 24);
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(Fd));
	DesenhaFace(yC, lados, PI);
	glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3ub(86, 125, 67);
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(Fe));
	DesenhaFace(yC, lados, PI);
	glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3ub(66, 105, 47);
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(Fe));
	DesenhaFace(yC, lados, PI);
	glPopMatrix();

	yArvore = yArvore + StripVel * (1.0 / 60.0);
	if (yArvore > yC * 2)
		yArvore = -15.0;
}

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
	DesenhaArvore(zAxis, 6, 0.8, yC);
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
