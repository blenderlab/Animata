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

#include <math.h>
#include <float.h>
#include "Vector3D.h"
#include "Matrix.h"

using namespace Animata;

Vector3D::Vector3D()
{
    x = y = z = 0.f;
}

Vector3D::Vector3D(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D::Vector3D(const Vector2D& p)
{
    this->x = p.x;
    this->y = p.y;
    this->z = 0.0f;
}

Vector3D& Vector3D::set(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    x = _z;
    return *this;
}

Vector3D& Vector3D::setElement(float f, int index)
{
    switch (index) {
        case 0:
            x = f;
            break;
        case 1:
            y = f;
            break;
        case 2:
            z = f;
            break;
        default:
            break;
    }
    return *this;
}

bool Vector3D::operator == (const Vector3D &v) const
{
    return (  ((x - v.x) * (x - v.x)
             + (y - v.y) * (y - v.y)
             + (z - v.z) * (z - v.z)) < FLT_EPSILON);
}

bool Vector3D::operator != (const Vector3D &v) const
{
    return (  ((x - v.x) * (x - v.x)
             + (y - v.y) * (y - v.y)
             + (z - v.z) * (z - v.z)) >= FLT_EPSILON);
}

Vector3D& Vector3D::operator += (const Vector3D& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3D& Vector3D::operator -= (const Vector3D& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector3D& Vector3D::operator *= (const Vector3D& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

Vector3D& Vector3D::operator /= (const Vector3D& v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

Vector3D& Vector3D::operator += (float f)
{
    x += f;
    y += f;
    z += f;
    return *this;
}

Vector3D& Vector3D::operator -= (float f)
{
    x -= f;
    y -= f;
    z -= f;
    return *this;
}

Vector3D& Vector3D::operator *= (float f)
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

Vector3D& Vector3D::operator /= (float f)
{
    x /= f;
    y /= f;
    z /= f;
    return *this;
}

Vector3D& Vector3D::operator = (const Vector3D& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

Vector3D Vector3D::operator + (const Vector3D& v) const
{
    return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D Vector3D::operator - (const Vector3D& v) const
{
    return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D Vector3D::operator * (const Vector3D& v) const
{
    return Vector3D(x * v.x, y * v.y, z * v.z);
}

Vector3D Vector3D::operator / (const Vector3D& v) const
{
    return Vector3D(x / v.x, y / v.y, z / v.z);
}

Vector3D Vector3D::operator + (float f) const
{
    return Vector3D(x + f, y + f, z + f);
}

Vector3D Vector3D::operator - (float f) const
{
    return Vector3D(x - f, y - f, z - f);
}

Vector3D Vector3D::operator * (float f) const
{
    return Vector3D(x * f, y * f, z * f);
}

Vector3D Vector3D::operator / (float f) const
{
    f = 1.0f / f;
    return Vector3D(x * f, y * f, z * f);
}

Vector3D& Vector3D::rotate(const Matrix& m)
{
    Vector3D *r = new Vector3D();

    r->x = x * m[0] + y * m[4] + z * m[8];
    r->y = x * m[1] + y * m[5] + z * m[9];
    r->z = x * m[2] + y * m[6] + z * m[10];

    return *r;
}

Vector3D& Vector3D::transform(const Matrix& m)
{
    Vector3D *t = new Vector3D();

    t->x = x * m[0] + y * m[4] + z * m[8] + m[12];
    t->y = x * m[1] + y * m[5] + z * m[9] + m[13];
    t->z = x * m[2] + y * m[6] + z * m[10] + m[14];

    return *t;
}

void Vector3D::normalize(void)
{
    float len = sqrt(x * x + y * y + z * z);
    if(len > FLT_EPSILON) {
        x /= len;
        y /= len;
        z /= len;
    }
}

float Vector3D::size(void) const
{
    return sqrt(x*x + y*y + z*z);
}

