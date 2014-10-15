#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <memory>

namespace gssmraytracer {
  namespace math {
    class Vector {
    public:
      //! Creates a Vector set to (0,0,0)
      Vector();
      //! Initializes a Vector with an x, y and z value
      Vector(const float x, const float y, const float z);

      //! Copy constructor
      Vector(const Vector &vector);

      //! Assignment operator
      Vector& operator=(const Vector &other);

      //! Add two Vectors together and return a new Vector
      Vector operator+(const Vector &v) const;

      //! Add a Vector to this Vector
      Vector& operator+=(const Vector &v);

      //! Returns a new Vector which is the difference between this Vector and v.
      Vector operator-(const Vector &v) const;

      //! Subtract a Vector from this Vector.
      Vector& operator-=(const Vector &v);

      //! Returns a new Vector which is the product of this Vector and a scalar.
      Vector operator*(const float s) const;

      //! Scales this Vector by a scalar
      Vector& operator*=(const float s);

      //! Cross product.  Returns a new Vector
      Vector cross(const Vector &other) const;

      //! Dot product.  Returns a float
      const float dot(const Vector &other) const;

      //! Returns the length of the Vector
      const float length() const;

      //! Returns the direction of the Vector
      const Vector direction() const;

      //! Normalizes this Vector
      void normalize();

      //! Returns a new Normalized Vector based on this
      const Vector normalized() const;

      //! Allows printing of the vector to std::cout
      friend std::ostream& operator<<(std::ostream &os, const Vector &vec);

      //! returns the x value
      const float x() const;

      //! returns the y value
      const float y() const;

      //! returns the z value
      const float z() const;
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
    //! Allows multiplying of a scalar by a Vector (left multiply).
    Vector operator*(const float s, const Vector &vec);
  }
}
#endif // __VECTOR_H__
