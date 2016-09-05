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
#include "Vector2D.h"

using namespace Animata;

Vector2D::Vector2D()
{
    x = y = 0.f;
}

Vector2D::Vector2D(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2D& Vector2D::set(float _x, float _y)
{
    x = _x;
    y = _y;
    return *this;
}

Vector2D& Vector2D::setElement(float f, int index)
{
    switch (index) {
        case 0:
            x = f;
            break;
        case 1:
            y = f;
            break;
        default:
            break;
    }
    return *this;
}


bool Vector2D::operator == (const Vector2D &v) const
{
    return (((x - v.x)*(x - v.x) + (y - v.y)*(y - v.y)) < FLT_EPSILON);
}

bool Vector2D::operator != (const Vector2D &v) const
{
    return (((x - v.x)*(x - v.x) + (y - v.y)*(y - v.y)) >= FLT_EPSILON);
}

bool Vector2D::operator > (const Vector2D &v) const
{
    return (x > v.x) || (y > v.y);
}

bool Vector2D::operator >= (const Vector2D &v) const
{
    return (x >= v.x) || (y >= v.y);
}

bool Vector2D::operator < (const Vector2D &v) const
{
    return (x < v.x) || (y < v.y);
}

bool Vector2D::operator <= (const Vector2D &v) const
{
    return (x <= v.x) || (y <= v.y);
}

Vector2D& Vector2D::operator += (const Vector2D& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

Vector2D& Vector2D::operator -= (const Vector2D& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector2D& Vector2D::operator *= (const Vector2D& v)
{
    x *= v.x;
    y *= v.y;
    return *this;
}

Vector2D& Vector2D::operator /= (const Vector2D& v)
{
    x /= v.x;
    y /= v.y;
    return *this;
}

Vector2D& Vector2D::operator += (float f)
{
    x += f;
    y += f;
    return *this;
}

Vector2D& Vector2D::operator -= (float f)
{
    x -= f;
    y -= f;
    return *this;
}

Vector2D& Vector2D::operator *= (float f)
{
    x *= f;
    y *= f;
    return *this;
}

Vector2D& Vector2D::operator /= (float f)
{
    x /= f;
    y /= f;
    return *this;
}

Vector2D& Vector2D::operator = (const Vector2D& v)
{
    x = v.x;
    y = v.y;
    return *this;
}

Vector2D Vector2D::operator + (float f) const
{
    return Vector2D(x + f, y + f);
}

Vector2D Vector2D::operator - (float f) const
{
    return Vector2D(x - f, y - f);
}

Vector2D Vector2D::operator * (float f) const
{
    return Vector2D(x * f, y * f);
}

Vector2D Vector2D::operator / (float f) const
{
    f = 1.0f / f;
    return Vector2D(x * f, y * f);
}

Vector2D Vector2D::operator + (const Vector2D& v) const
{
    return Vector2D(x + v.x, y + v.y);
}

Vector2D Vector2D::operator - (const Vector2D& v) const
{
    return Vector2D(x - v.x, y - v.y);
}

Vector2D Vector2D::operator * (const Vector2D& v) const
{
    return Vector2D(x * v.x, y * v.y);
}

Vector2D Vector2D::operator / (const Vector2D& v) const
{
    return Vector2D(x / v.x, y / v.y);
}

float Vector2D::cross(const Vector2D& v1, const Vector2D& v2) const
{
    return v1.x * v2.x + v1.y * v2.y;
}

float Vector2D::dot(const Vector2D& v1, const Vector2D& v2) const
{
    return v1.x * v2.y - v1.y * v2.x;
}

void Vector2D::normalize(void)
{
    float len = sqrt(x * x + y * y);

    if(len > FLT_EPSILON) {
        x /= len;
        y /= len;
    }
}

float Vector2D::size(void) const
{
    return sqrt(x*x + y*y);
}

float Vector2D::atan2(void) const
{
    return ::atan2(y, x);
}

