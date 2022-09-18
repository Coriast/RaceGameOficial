#ifndef CENARIO_HPP
#define CENARIO_HPP

#include <iostream>
#include <GLFW/glfw3.h>

const int q_Strips = 1;

class Cenario {
public:
	// Parametros
	float RoadRatio = 0.8;
	float xC, yC;
	float zAxis = 0.0;

	float StripSize = 1.0;
	float RoadStrip[q_Strips][2] = { {0.1, 0.0}};

	// Construtores
	Cenario(float xC, float yC, float zAxis);
	Cenario(float xC, float yC);

	// Metodos
	void DesenhaCena();
	void DesenhaEstrada();
};


#endif
