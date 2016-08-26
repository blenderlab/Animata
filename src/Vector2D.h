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

#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__

#include "math.h"

namespace Animata
{

class Vector2D
{
public:
    float x, y;

    Vector2D();
    Vector2D(float x, float y);

    Vector2D& set(float _x, float _y);
    Vector2D& setElement(float f, int index);

    bool operator == (const Vector2D &p) const;
    bool operator != (const Vector2D &p) const;
    bool operator < (const Vector2D &p) const;
    bool operator <= (const Vector2D &p) const;
    bool operator > (const Vector2D &p) const;
    bool operator >= (const Vector2D &p) const;

    Vector2D& operator += (const Vector2D& v);
    Vector2D& operator -= (const Vector2D& v);
    Vector2D& operator *= (const Vector2D& v);
    Vector2D& operator /= (const Vector2D& v);

    Vector2D& operator += (float f);
    Vector2D& operator -= (float f);
    Vector2D& operator *= (float f);
    Vector2D& operator /= (float f);

    Vector2D& operator = (const Vector2D& v);

    Vector2D operator + (const Vector2D& v) const;
    Vector2D operator - (const Vector2D& v) const;
    Vector2D operator * (const Vector2D& v) const;
    Vector2D operator / (const Vector2D& v) const;

    Vector2D operator + (float f) const;
    Vector2D operator - (float f) const;
    Vector2D operator * (float f) const;
    Vector2D operator / (float f) const;

    float dot(const Vector2D& v1, const Vector2D& v2) const;
    float cross(const Vector2D& v1, const Vector2D& v2) const;

    void normalize(void);
    float size(void) const;
    float atan2(void) const;

    inline bool isNaN() const
        { return (x!=x) || (y!=y); }
};

} /* namespace Animata */

#endif

