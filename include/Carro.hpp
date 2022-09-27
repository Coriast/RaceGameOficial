#ifndef CARRO_HPP
#define CARRO_HPP

#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

class Carro {
public:

	// Parametros
	float CarSize = 0.0;
	float zAxis = 0.0;

	// Construtores
	Carro(float CarSize, float zAxis);

	// Métodos
	void DesenhaRodas(GLfloat rodaPos[3]);
	void DesenhaCarro(float pos_[3], int id, float Vel);

};

#endif 
