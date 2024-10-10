
class Vector3D {
public:
    float x, y, z;
    Vector3D();
    Vector3D(float x_, float y_, float z_);

    float modulo() const;
    Vector3D normalizar() const;

    void operator=(const Vector3D& otro);
    Vector3D operator+(const Vector3D& otro) const;
    Vector3D operator-(const Vector3D& otro) const;
    Vector3D operator*(float escalar) const;
    float operator*(const Vector3D& otro) const;
};