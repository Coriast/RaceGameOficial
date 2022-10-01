#ifndef CENARIO_HPP
#define CENARIO_HPP

#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>

const int q_Strips = 8;

class Cenario {
public:
	// Parametros
	float RoadRatio = 0.2;
	float xC, yC;
	float zAxis = 0.0;

	float StripSize = 0.0;

	// Construtores
	Cenario(float xC, float yC, float zAxis);
	Cenario(float xC, float yC);

	// Metodos
	void DesenhaCena();
	void DesenhaEstrada(float JogadorVel);
	void DesenhaArvore(float zAxis, int lados, float raio, float yC);
};


#endif
