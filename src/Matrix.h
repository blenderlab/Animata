/*
 Animata

 Copyright (C) 2007 Peter Nemeth, Gabor Papp, Bence Samu
 Kitchen Budapest, <http://animata.kibu.hu/>

 This file is part of Animata.

 Animata is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Animata is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Animata. If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "Vector3D.h"
#include "Angle3D.h"

namespace Animata
{

// class storing 4x4 float matrix
class Matrix
{
public:

    ///< items of the matrix in one dimension to adapt to the openGL convention
    float f[16];

    Matrix();
    Matrix(double e[16]);

    void clear();           ///< zero matrix
    void loadIdentity();    ///< indentity matrix

    inline float& operator [] (int i) { return f[i]; }
    inline float operator [] (int i) const { return f[i]; }

    Matrix& operator = (const Matrix& m);     ///< assignment operator
    Matrix& operator = (float e[16]);   ///< float assignment operator
    Matrix& operator *= (const Matrix& m);    ///< right multiply operator

    ///< computes the inverse rotation from the 3x3 rotation portion of this matrix
    Matrix& inverseRotation();

    ///< computes and returns the inverse of this matrix
    Matrix& inverse();

    ///< mutiplies the current matrix with the given translate matrix
    Matrix& translate(const Vector3D& v);

    ///< mutiplies the current matrix with the given scale matrix
    Matrix& scale(const Vector3D& v);

    ///< multiplies the current matrix with the given rotation
    Matrix& rotate(const Angle3D& a);
    Matrix& rotateZ(float theta);

    void print();
};

} /* namespace Animata */

#endif

