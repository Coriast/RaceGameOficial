#include "Cores.hpp"
#include "Formulas.hpp"
#include "Carro.hpp"

const GLfloat PI = 3.14159265359;
float rodaTam = 0.4;
float CarroVel = 0.0;
float rotacionaRoda = 0.0;

void rect(vec3 p1, vec3 p2, vec3 p3, vec3 p4, float cor[3]) {
	glColor3f(cor[0], cor[1], cor[2]);
	glBegin(GL_QUADS);
	glVertex3fv(&p1.x);
	glVertex3fv(&p2.x);
	glVertex3fv(&p3.x);
	glVertex3fv(&p4.x);
	glEnd();
}

void DesenhaCubo(float CarSize, float zAxis, float pos_[3], int id) {
	float corFrentePadrao[3] = { corFrente[0], corFrente[1], corFrente[2] };
	float corCostasPadrao[3] = { corCostas[0], corCostas[1], corCostas[2] };

	if (id != 0) {
		corFrentePadrao[0] = corFrenteEn[id-1][0];
		corFrentePadrao[1] = corFrenteEn[id-1][1];
		corFrentePadrao[2] = corFrenteEn[id-1][2];

		corCostasPadrao[0] = corCostasEn[id-1][0];
		corCostasPadrao[1] = corCostasEn[id-1][1];
		corCostasPadrao[2] = corCostasEn[id-1][2];
	}

	float xS = CarSize / 3.0;
	float yS = CarSize / 2.0;
	float zFrente = zAxis - xS;

	vec3 v1 = { -xS, yS, -zFrente };
	vec3 v2 = { -xS, -yS, -zFrente };
	vec3 v3 = { xS, -yS, -zFrente };
	vec3 v4 = { xS, yS, -zFrente };

	vec3 v5 = { xS, yS, -zAxis };
	vec3 v6 = { xS, -yS, -zAxis };
	vec3 v7 = { -xS, -yS, -zAxis };
	vec3 v8 = { -xS, yS, -zAxis };

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();

	glTranslatef(pos_[0], pos_[1], pos_[2]);

	// frente 
	rect(v1, v2, v3, v4, corFrentePadrao);
	// direita
	rect(v4, v3, v6, v5, corFrentePadrao);
	// Costas
	rect(v5, v8, v7, v6, corCostasPadrao);
	// esquerda
	rect(v1, v8, v7, v2, corFrentePadrao);
	// Em Cima
	rect(v1, v4, v5, v8, corFrentePadrao);
	// Em Baixo
	rect(v2, v7, v6, v3, corCostasPadrao);
	glPopMatrix();
}

void DesenhaPoligono(float cor[3], GLfloat raio, GLuint nLados) {
	std::vector< std::vector<GLuint>> indices;
	std::vector<vec3> pontos;
	GLfloat x = 0.0;
	GLfloat larg = raio / 2;

	GLfloat theta = PI * 2 / nLados;
	GLfloat tangent = tanf(theta);

	GLfloat rad = cosf(theta);

	GLfloat z = raio;
	GLfloat y = 0;

	for (GLuint i = 0; i < nLados; i++)
	{
		GLfloat tz = -y;
		GLfloat ty = z;

		z += tz * tangent;
		y += ty * tangent;

		z *= rad;
		y *= rad;

		std::vector<GLuint> pt;
		pontos.push_back(vec3(x, y, z));
		GLuint index = pontos.size() - 1;
		pt.push_back(index);
		indices.push_back(pt);
	}

	// Ponto do Centro para Fazer o GL_Polygon
	std::vector<GLuint> pt;
	pontos.push_back(vec3(x, 0.0, 0.0));
	GLuint index = pontos.size() - 1;
	pt.push_back(index);
	indices.push_back(pt);

	// Inicia Desenho
	glColor3f(corCostas[0], corCostas[1], corCostas[2]);
	glBegin(GL_POLYGON);
	for (GLuint i = 0; i < pontos.size(); i++)
	{
		glVertex3fv(&pontos[i].x);
	}
	glEnd();
	   
	glColor3f(cor[0], cor[1], cor[2]);
	glBegin(GL_POLYGON);
	for (GLuint i = 0; i < pontos.size(); i++)
	{
		pontos[i].x = pontos[i].x + larg;
		glVertex3fv(&pontos[i].x);
	}
	glEnd();
	   
	glColor3f(cor[0], cor[1], cor[2]);
	glBegin(GL_QUAD_STRIP);
	for (GLuint i = 0; i < pontos.size() - 1; i++)
	{
		pontos[i].x = pontos[i].x - larg;
		glVertex3fv(&pontos[i].x);
		pontos[i].x = pontos[i].x + larg;
		glVertex3fv(&pontos[i].x);

		if (i == pontos.size() - 2) {
			pontos[0].x = pontos[0].x - larg;
			glVertex3fv(&pontos[0].x);
			pontos[0].x = pontos[0].x + larg;
			glVertex3fv(&pontos[0].x);
		}
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	for (GLuint i = 0; i < pontos.size() - 1; i++)
	{
		pontos[i].x = pontos[i].x - larg;
		glVertex3fv(&pontos[i].x);
		pontos[i].x = pontos[i].x + larg;
		glVertex3fv(&pontos[i].x);

		if (i == pontos.size() - 2) {
			pontos[0].x = pontos[0].x - larg;
			glVertex3fv(&pontos[0].x);
			pontos[0].x = pontos[0].x + larg;
			glVertex3fv(&pontos[0].x);
		}
	}
	glEnd();
}

void Carro::DesenhaRodas(GLfloat rodaPos[3], int id) {
	float corFrentePadrao[3] = { corFrente[0], corFrente[1], corFrente[2] };
	float corCostasPadrao[3] = { corCostas[0], corCostas[1], corCostas[2] };

	if (id != 0) {
		corFrentePadrao[0] = corFrenteEn[id - 1][0];
		corFrentePadrao[1] = corFrenteEn[id - 1][1];
		corFrentePadrao[2] = corFrenteEn[id - 1][2];

		corCostasPadrao[0] = corCostasEn[id - 1][0];
		corCostasPadrao[1] = corCostasEn[id - 1][1];
		corCostasPadrao[2] = corCostasEn[id - 1][2];
	}
	
	int lados = 6;

	rotacionaRoda = rotacionaRoda - (5.0 * CarroVel) * (1.0/60.0);

	glPushMatrix();
	glTranslatef(rodaPos[0] - (CarSize/3), rodaPos[1] - (CarSize / 2), rodaPos[2]);
	glRotatef(rotacionaRoda, 1.0, 0.0, 0.0);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	DesenhaPoligono(corFrentePadrao, rodaTam, lados);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(rodaPos[0] + (CarSize / 3), rodaPos[1] - (CarSize / 2), rodaPos[2]);
	glRotatef(rotacionaRoda, 1.0, 0.0, 0.0);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	DesenhaPoligono(corFrentePadrao, rodaTam, lados);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(rodaPos[0] - (CarSize / 3), rodaPos[1] + (CarSize / 2), rodaPos[2]);
	glRotatef(rotacionaRoda, 1.0, 0.0, 0.0);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	DesenhaPoligono(corFrentePadrao, rodaTam, lados);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(rodaPos[0] + (CarSize / 3), rodaPos[1] + (CarSize / 2), rodaPos[2]);
	glRotatef(rotacionaRoda, 1.0, 0.0, 0.0);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	DesenhaPoligono(corFrentePadrao, rodaTam, lados);
	glPopMatrix();
	if (rotacionaRoda > 360.0)
		rotacionaRoda = 0.0;
}

// Construtor
Carro::Carro(float CarSize, float zAxis) {
	this->CarSize = CarSize;
	this->zAxis = zAxis;
}

// Métodos
void Carro::DesenhaCarro(float pos_[3], int id, float Vel) {
	DesenhaCubo(CarSize, zAxis-rodaTam, pos_, id);
	
	CarroVel = Vel;

	GLfloat rodaPos[3] = { pos_[0], pos_[1], -(zAxis-rodaTam)};
	DesenhaRodas(rodaPos, id);
}