#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Formulas.hpp"

class Camera
{
private:
	vec3 m_pos;
	vec3 m_dir;
	vec3 m_left;
	vec3 m_up;

public:
	Camera(vec3 pos);

	// Métodos
	void VisaoPadrao(vec3 pos);
	void VisaoJogador(vec3 pos);
};

#endif