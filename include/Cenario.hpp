#ifndef CENARIO_HPP
#define CENARIO_HPP

#include <iostream>
#include <GLFW/glfw3.h>

const int q_Strips = 4;

class Cenario {
public:
	// Parametros
	float RoadRatio = 0.2;
	float xC, yC;
	float zAxis = 0.0;

	float StripSize = 3.5;

	// Construtores
	Cenario(float xC, float yC, float zAxis);
	Cenario(float xC, float yC);

	// Metodos
	void DesenhaCena();
	void DesenhaEstrada();
};


#endif
