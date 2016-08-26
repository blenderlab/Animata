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

#include "Face.h"

using namespace Animata;

void Face::move(const Vector2D& d)
{
    v[0]->coord += d;
    v[1]->coord += d;
    v[2]->coord += d;
}

Vector2D Face::center(void)
{
    Vector2D c(v[0]->coord + v[1]->coord + v[2]->coord);
    return c / 3.0;
}

void Face::attachTexture(Texture *t)
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    float scale = t->getScale();

    Vector2D s = t->dimensions * scale;

    for (unsigned int i = 0; i < 3; i++) {
        v[i]->texCoord = (v[i]->coord - t->position) / s;
    }
}

