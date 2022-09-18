#ifndef CENARIO_HPP
#define CENARIO_HPP

#include <iostream>
#include <GLFW/glfw3.h>


class Cenario {
public:
	// Parametros
	float RoadRatio = 0.8;
	float xC, yC;
	float zAxis = 0.0;

	// Construtores
	Cenario(float xC, float yC, float zAxis);
	Cenario(float xC, float yC);

	// Metodos
	void DesenhaCena();
	void DesenhaEstrada();
};


#endif
