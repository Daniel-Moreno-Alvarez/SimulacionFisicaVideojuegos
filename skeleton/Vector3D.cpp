#include "Vector3D.h"
#include <cmath>

using namespace std;

Vector3D::Vector3D() : x(0), y(0), z(0) {}

Vector3D::Vector3D(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

float Vector3D::modulo() const {
    return sqrt(x * x + y * y + z * z);
}

Vector3D Vector3D::normalizar() const {
    float mod = modulo();
    if (mod == 0) {
        return Vector3D(0, 0, 0);
    }
    else return Vector3D(x / mod, y / mod, z / mod);
}

// Iguala
void Vector3D::operator=(const Vector3D& otro) {
    x = otro.x;
    y = otro.y;
    z = otro.z;
}

// suma
Vector3D Vector3D::operator+(const Vector3D& otro) const {
    return Vector3D(x + otro.x, y + otro.y, z + otro.z);
}

// Resta
Vector3D Vector3D::operator-(const Vector3D& otro) const {
    return Vector3D(x - otro.x, y - otro.y, z - otro.z);
}

// Multiplicacion por un escalar
Vector3D Vector3D::operator*(float escalar) const {
    return Vector3D(x * escalar, y * escalar, z * escalar);
}

// Producto escalar
float Vector3D::operator*(const Vector3D& otro) const {
    return x * otro.x + y * otro.y + z * otro.z;
}


