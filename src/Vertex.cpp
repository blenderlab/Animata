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

#include "Vertex.h"
#include "Primitives.h"

void Vertex::draw(int mouseOver, int active)
{
	drawVertex(this, mouseOver, active);
	/*
	if (mouseOver)
		drawVertexMouseOver(this);
	else
	if (selected)
		drawVertexSelected(this);
	else
		drawVertex(this); */
}

void Vertex::flipSelection(void)
{
	selected = !selected;
}