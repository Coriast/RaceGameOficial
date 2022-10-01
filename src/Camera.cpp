#include "Camera.hpp"
#include <Windows.h>
#include <gl/GLU.h>

Camera::Camera(vec3 pos) {
	m_pos = vec3(pos); // Posição da Câmera
	m_dir = vec3(0, 0, -1); // Direção para onde quero olhar
	m_left = vec3(-1, 0, 0); 
	m_up = vec3(0, 1, 0); // Topo da Câmera
}


void Camera::VisaoPadrao(vec3 pos) {
	m_pos = pos;
	m_dir = vec3(0, 0, -1); // Direção para onde quero olhar
	m_left = vec3(-1, 0, 0);
	m_up = vec3(0, 1, 0); // Topo da Câmera
	vec3 look = m_pos + m_dir;

	gluLookAt(m_pos.x, m_pos.y, m_pos.z, look.x, look.y, look.z, m_up.x, m_up.y, m_up.z);
}

void Camera::VisaoJogador(vec3 pos) {
	m_pos = pos;
	m_dir = vec3(0, 10, -1); // Direção para onde quero olhar
	m_left = vec3(-1, 0, 0);
	m_up = vec3(0, 1, 0); // Topo da Câmera
	vec3 look = m_pos + m_dir;

	gluLookAt(m_pos.x, m_pos.y - 7.3, m_pos.z, look.x, look.y, look.z, m_up.x, m_up.y, m_up.z);
}