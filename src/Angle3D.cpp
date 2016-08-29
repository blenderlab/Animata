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
#include "Angle3D.h"
#include "Matrix.h"

using namespace Animata;

Angle3D::Angle3D()
{
    x = y = z = 0.f;
}

Angle3D::Angle3D(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Angle3D::Angle3D(const Angle3D *p)
{
    this->x = p->x;
    this->y = p->y;
    this->z = p->z;
}

Angle3D& Angle3D::set(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    x = _z;
    return *this;
}

Angle3D& Angle3D::setElement(float f, int index)
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

bool Angle3D::operator == (const Angle3D &v) const
{
    return (  ((x - v.x) * (x - v.x)
             + (y - v.y) * (y - v.y)
             + (z - v.z) * (z - v.z)) < FLT_EPSILON);
}

bool Angle3D::operator != (const Angle3D &v) const
{
    return (  ((x - v.x) * (x - v.x)
             + (y - v.y) * (y - v.y)
             + (z - v.z) * (z - v.z)) >= FLT_EPSILON);
}

Angle3D& Angle3D::operator += (const Angle3D& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Angle3D& Angle3D::operator -= (const Angle3D& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Angle3D& Angle3D::operator += (float f)
{
    x += f;
    y += f;
    z += f;
    return *this;
}

Angle3D& Angle3D::operator -= (float f)
{
    x -= f;
    y -= f;
    z -= f;
    return *this;
}

Angle3D& Angle3D::operator *= (float f)
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

Angle3D& Angle3D::operator /= (float f)
{
    x /= f;
    y /= f;
    z /= f;
    return *this;
}

Angle3D Angle3D::operator = (const Angle3D& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    return Angle3D(x, y, z);
}

Angle3D Angle3D::operator + (const Angle3D& v) const
{
    return Angle3D(x + v.x, y + v.y, z + v.z);
}

Angle3D Angle3D::operator - (const Angle3D& v) const
{
    return Angle3D(x - v.x, y - v.y, z - v.z);
}

Angle3D Angle3D::operator + (float f) const
{
    return Angle3D(x + f, y + f, z + f);
}

Angle3D Angle3D::operator - (float f) const
{
    return Angle3D(x - f, y - f, z - f);
}

Angle3D Angle3D::operator * (float f) const
{
    return Angle3D(x * f, y * f, z * f);
}

Angle3D Angle3D::operator / (float f) const
{
    f = 1.0f / f;
    return Angle3D(x * f, y * f, z * f);
}
