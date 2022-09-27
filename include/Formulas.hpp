#ifndef FORMULAS_HPP
#define FORMULAS_HPP

struct vec3 {
    float x, y, z;
    vec3() :x(0.0), y(0.0), z(0.0) {}
    vec3(float x_, float y_, float z_) :x(x_), y(y_), z(z_) {}
    // Soma de vetores
    vec3 operator+(const vec3& v)const { return vec3(x + v.x, y + v.y, z + v.z); }
};


#endif 