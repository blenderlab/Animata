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

#ifndef __JOINT_H__
#define __JOINT_H__

#include "Vector2D.h"

namespace Animata
{

/// Endpoints of Bone.
class Joint
{
public:
    Vector2D position;
    Vector2D viewPosition;

    bool fixed;     ///< fixed state
    bool selected;  ///< selection state
    bool dragged;   ///< set to true if the joint is dragged

    bool osc;       ///< joint parameters are transmitted via osc if true

    /** timestamp of last drag, needed when joints are moved as part of a
     * bone to move joints only once per frame
     */
    int dragTS;

    Joint(const Vector2D& v);

    const char *getName(void) const;
    void setName(const char *str);

    void simulate(void);
    void draw(int dragged = 0, int active = 1);
    void flipSelection(void);

    void drag(const Vector2D& d, int timeStamp = 0);

private:
    char name[16];
};

} /* namespace Animata */

#endif

