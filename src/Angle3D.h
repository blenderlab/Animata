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

#ifndef __ANGLE3D_H__
#define __ANGLE3D_H__

namespace Animata
{

class Matrix;

class Angle3D
{
public:
    float x, y, z;

    Angle3D();
    Angle3D(float x, float y, float z);
    Angle3D(const Angle3D *p);

    Angle3D& set(float _x, float _y, float _z);
    Angle3D& setElement(float f, int index);

    bool operator == (const Angle3D &p) const;
    bool operator != (const Angle3D &p) const;

    Angle3D& operator += (const Angle3D&);
    Angle3D& operator -= (const Angle3D&);

    Angle3D& operator += (float f);
    Angle3D& operator -= (float f);
    Angle3D& operator *= (float f);
    Angle3D& operator /= (float f);

    Angle3D operator = (const Angle3D&);

    Angle3D operator + (const Angle3D& p) const;
    Angle3D operator - (const Angle3D& p) const;

    Angle3D operator + (float f) const;
    Angle3D operator - (float f) const;
    Angle3D operator * (float f) const;
    Angle3D operator / (float f) const;

    inline bool isNaN() const
        { return (x!=x) || (y!=y) || (z!=z); }
};

} /* namespace Animata */

#endif

