namespace gssmraytracer {
  namespace math {
    struct Vector {
      Vector() : vec() {}
      Vector(float x, float y, float z) : vec(x,y,z) {}
      Vector operator+(const Vector &v) const {
        return Vector(x + v.x, y + v.y, z + v.z);
      }
      Vector& operator+=(const Vector &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
      }
      Vector operator-(const Vector &v) const {
        return Vector(x - v.x, y - v.y, z - v.z);
      }
      Vector& operator-=(const Vector &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
      }

      float x,y,z;
    };
  }
}
