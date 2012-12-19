//
//  Matrix.hpp
//  RType
//
//  Created by Gael du Plessix on 18/12/12.
//
//

#ifndef RType_Matrix_hpp
# define RType_Matrix_hpp

# include <cmath>

namespace Graphic {
    
    //! Representation of a 4x4 Matrix
    template<class T>
    class Matrix4 {
    public:
        
        //! Contructs a 4x4 identity Matrix
        Matrix4() {
            identity();
        }
        
        //! Contructs a 4x4 Matrix
        Matrix4(T const& a, T const& b, T const& c, T const& d,
                T const& e, T const& f, T const& g, T const& h,
                T const& i, T const& j, T const& k, T const& l,
                T const& m, T const& n, T const& o, T const& p) {
            _matrix[0]  = a;
            _matrix[1]  = e;
            _matrix[2]  = i;
            _matrix[3]  = m;
            _matrix[4]  = b;
            _matrix[5]  = f;
            _matrix[6]  = j;
            _matrix[7]  = n;
            _matrix[8]  = c;
            _matrix[9]  = g;
            _matrix[10] = k;
            _matrix[11] = o;
            _matrix[12] = d;
            _matrix[13] = h;
            _matrix[14] = l;
            _matrix[15] = p;
        }
        
        //! Destruct the matrix
        ~Matrix4(void) {
        }
        
        //! Access to nth element of the matrix
        T const & operator[](int n) const {
            return (_matrix[n]);
        }
        
        //! Get a const pointer to matrix data.
        /*!
         Matrix values are stored as column-major.
         \return A const pointer to the matrix data(T*).
         */
        operator const T*() const {
            return (_matrix);
        }
        
        //! Return the value at position ij
        inline T const& get(uint32 i, uint32 j) const {
            return _matrix[i * 4 + j];
        }
        
        //! Set the value at position ij
        inline void set(uint32 i, uint32 j, T const& v) {
            _matrix[i * 4 + j] = v;
        }
        
        //! Set an identity 4x4 matrix
        Matrix4& identity(void) {
            _matrix[0] = _matrix[5] = _matrix[10] = _matrix[15] = 1;
            _matrix[4] = _matrix[8] = _matrix[12] = _matrix[1] =
            _matrix[9] = _matrix[13] = _matrix[2] = _matrix[6] =
            _matrix[14] = _matrix[3] = _matrix[7] = _matrix[11] = 0;
            return (*this);
        }
        
        //! Multiply the matrix with an other matrix
        Matrix4& operator*=(Matrix4 const& value) {
            Matrix4 tmp;
            for (uint32 i = 0; i < 4; ++i) {
                for (uint32 j = 0; j < 4; ++j) {
                    T sum = 0;
                    for (uint32 k = 0; k < 4; ++k)
                        sum += get(i, k) * value.get(k, j);
                    tmp.set(i, j, sum);
                }
            }
            *this = tmp;
            return (*this);
        }
        
        //! Apply a translation to the matrix
        /*!
         \param x Value of x translation
         \param y Value of y translation
         \param z Value of z translation
         */
        Matrix4& translate(T const & x, T const & y, T const & z=0) {
            Matrix4 tmp = translationMatrix(x, y, z);
            tmp *= *this;
            *this = tmp;
            return (*this);
        }
        
        //! Apply a scale transformation to the matrix
        Matrix4& scale(T const& x, T const& y, T const& z=1) {
            Matrix4 tmp = scaleMatrix(x, y, z);
            tmp *= *this;
            *this = tmp;
            return (*this);
        }
        
        //! Apply a z rotation transformation to the matrix
        Matrix4& rotate(float32 angle) {
            Matrix4 tmp = rotationMatrix(angle);
            tmp *= *this;
            *this = tmp;
            return (*this);
        }
        
        //! Get a translation matrix
        /*!
         \param x Value of x translation
         \param y Value of y translation
         \param z Value of z translation
         */
        static Matrix4 translationMatrix(T const& x, T const& y, T const& z) {
            return (Matrix4(1, 0, 0, x,
                            0, 1, 0, y,
                            0, 0, 1, z,
                            0, 0, 0, 1));
        }
        
        //! Get a scale matrix
        /*!
         \param x Scale coefficient on x axis
         \param y Scale coefficient on y axis
         \param z Scale coefficient on z axis
         */
        static Matrix4 scaleMatrix(T const& x, T const& y, T const& z) {
            return (Matrix4(x, 0, 0, 0,
                            0, y, 0, 0,
                            0, 0, z, 0,
                            0, 0, 0, 1));
        }
        
        //! Get a rotation matrix for z axis
        /*!
         \param angle Rotation angle
         */
        static Matrix4 rotationMatrix(float32 angle) {
            return (Matrix4(cos(angle), -sin(angle),    0, 0,
                            sin(angle), cos(angle),     0, 0,
                            0,          0,              1, 0,
                            0,          0,              0, 1));
        }

        
    private:
        T   _matrix[16];
    };
    
    //! Floating values matrix
    typedef Matrix4<float32> Matrix4f;
}

#endif
