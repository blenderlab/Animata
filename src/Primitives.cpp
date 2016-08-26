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
#include "animata.h"
#include "Primitives.h"
#include "Bone.h"
#include "Joint.h"
#include "Layer.h"

using namespace Animata;

float Primitives::fillColorR = 0.5f;
float Primitives::fillColorG = 0.5f;
float Primitives::fillColorB = 0.5f;
float Primitives::fillColorA = 0.7f;

float Primitives::strokeColorR = 1.0f;
float Primitives::strokeColorG = 1.0f;
float Primitives::strokeColorB = 1.0f;
float Primitives::strokeColorA = 1.0F;

bool Primitives::doStroke = true;
bool Primitives::doFill = false;
float Primitives::strokeW = 1;

float Primitives::boneSize = 5;
float Primitives::jointSize = 5;
float Primitives::vertexSize = 5;
float Primitives::border = 4;
int Primitives::dAlpha = 100;


///////////////////////////////    LAYER     //////////////////////////////////

void Primitives::drawCrossHairs(Layer *l)
{
    strokeColor(255, 255, 0, 128);
    Vector3D offset = l->getOffset();
    drawLine(Vector2D(offset.x, -1000000),
             Vector2D(offset.x, 1000000));
    drawLine(Vector2D(-1000000, offset.y),
             Vector2D(1000000, offset.y));
}

///////////////////////////////    BONE     //////////////////////////////////

void Primitives::drawBone(Bone *b, int mouseOver, int active)
{
    Vector2D d(b->j1->viewPosition - b->j0->viewPosition);
    d.normalize();
    d *= boneSize;

    Vector2D v1(b->j0->viewPosition + d);
    Vector2D v2(b->j1->viewPosition - d);

    float size = b->damp*3;

    int alpha = active ? 0 : dAlpha;

    stroke(true);
    strokeWeight(boneSize + border);
    if (mouseOver) {
        strokeColor(0, 255, 0, 128 - alpha);
    }
    else {
        strokeColor(0, 0, 0, 128 - alpha);
    }
    drawLine(v1, v2);
    strokeWeight(boneSize * size);
    if (mouseOver) {
        strokeColor(255, 255, 0, 128 - alpha);
    }
    else if (b->selected) {
        strokeColor(255, 255, 0, 200 - alpha);
    }
    else if (b->getTempo() > 0) {
        strokeColor(176, 0, 0, 200 - alpha);
    }
    else {
        strokeColor(255, 255, 255, 128 - alpha);
    }
    drawLine(v1, v2);
    if (!(b->selected)) {
        strokeWeight(boneSize / 3 * size);
        strokeColor(255, 255, 255, 128 - alpha);
        drawLine(v1, v2);
    }
}

void Primitives::drawBoneWhileConnecting(const Vector2D& p1, const Vector2D& p2)
{
    stroke(true);
    strokeWeight((boneSize + border) );
    strokeColor(0, 0, 0, 128);
    drawLine(p1, p2);
    strokeWeight(boneSize);
    strokeColor(0, 255, 0, 128);
    drawLine(p1, p2);
}

///////////////////////////////    JOINT    //////////////////////////////////

void Primitives::drawJoint(Joint *j, int mouseOver, int active)
{
//    float x = j->vx;
//    float y = j->vy;

    int alpha = active ? 0 : dAlpha;

    stroke(false);
    fill(true);
    fillColor(0, 0, 0, 128 - alpha);
    drawCircle(j->viewPosition, jointSize + border);

    if (mouseOver) {
        stroke(true);
        fill(true);
        strokeColor(0, 255, 0, 200 - alpha);
        fillColor(0, 255, 0, 200 - alpha);
    }
    else if (j->selected) {
        stroke(true);
        fill(true);
        strokeColor(255, 255, 255, 200 - alpha);
        fillColor(255, 255, 0, 200 - alpha);
    }
    else if (j->fixed) {
        stroke(true);
        fill(true);
        strokeColor(255, 255, 255, 200 - alpha);
        fillColor(255, 0, 255, 200 - alpha);
    }
    else {
        stroke(true);
        fill(false);
        strokeColor(255, 255, 255, 200 - alpha);
    }
    strokeWeight(2);
    drawCircle(j->viewPosition, jointSize);
}

///////////////////////////////    VERTEX   //////////////////////////////////

void Primitives::drawVertex(Vertex *v, int mouseOver, int active)
{
    int alpha = active ? 0 : dAlpha;

    fill(true);
    stroke(false);
    fillColor(0,0,0,128 - alpha);
    drawRect(v->view, vertexSize + border);

    if (mouseOver) {
        stroke(true);
        fill(true);
        strokeColor(0, 255, 0, 200 - alpha);
        fillColor(0, 255, 0, 200 - alpha);
    }
    else if (v->selected) {
        stroke(true);
        fill(true);
        strokeColor(255, 255, 0, 200 - alpha);
        fillColor(255, 255, 0, 200 - alpha);
    }
    else {
        stroke(true);
        fill(false);
        strokeColor(255, 255, 255, 200 - alpha);
    }

    strokeWeight(1);
    drawRect(v->view, vertexSize);
}

void Primitives::drawVertexAttached(Vertex *v)
{
    fill(false);
    stroke(true);
    strokeColor(255,0,0,128);
    strokeWeight(1);
    drawRect(v->view, vertexSize + border * 2);
}


///////////////////////////////    FACE     //////////////////////////////////

void Primitives::drawFace(Face *face, int mouseOver /* = 0 */, int active)
{
    int alpha = active ? 0 : dAlpha;

    fill(true);
    stroke(true);
    strokeWeight(1);
    if (mouseOver) {
        strokeColor(255, 255, 0, 200 - alpha);
        fillColor(255, 255, 0, 50);
    }
    else {
        strokeColor(255, 255, 255, 200 - alpha);
        fillColor(0, 0, 0, 42);
    }
    drawTriangle(face->v[0]->view, face->v[1]->view, face->v[2]->view);
}

void Primitives::drawFaceWhileConnecting(const Vector2D& p1, const Vector2D& p2)
{
    stroke(true);
    strokeWeight(1);
    strokeColor(0, 255, 0, 200);
    drawLine(p1, p2);
}

void Primitives::fill(bool b)
{
    doFill = b;
}

void Primitives::stroke(bool b)
{
    doStroke = b;
}

void Primitives::strokeWeight(float w)
{
    strokeW=w;
}

void Primitives::drawRect(const Vector2D& pos, float size)
{
    size *= 0.5;
    Vector2D p1 = pos - size;
    Vector2D p2 = pos + size;

    if (doFill) {
        glColor4f(fillColorR, fillColorG, fillColorB, fillColorA);
        glRectf(p1.x, p1.y, p2.x, p2.y);
    }
    if (doStroke) {
        drawLine(p1.x, p1.y, p2.x, p1.y);
        drawLine(p2.x, p1.y, p2.x, p2.y);
        drawLine(p2.x, p2.y, p1.x, p2.y);
        drawLine(p1.x, p2.y, p1.x, p1.y);
    }
}

void Primitives::drawSelectionBox(const Vector2D& p1, const Vector2D& p2)
{
    glLineWidth(1);
    glLineStipple(1, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glColor4f(1.f, 1.f, 1.f, 1.f);
    glBegin(GL_LINE_LOOP);

    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p1.x, p2.y);

    glEnd();
    glDisable(GL_LINE_STIPPLE);
}

void Primitives::drawSelectionCircle(const Vector2D& c, float r)
{
    glLineWidth(1.5);
    glLineStipple(1, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glColor4f(1.f, 1.f, 1.f, 1.f);
    int segments = (int)(2 * M_PI * r / 10);
    float inc = 2 * M_PI/segments;
    float angle = 0;
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < segments; i++) {
            glVertex2f(c.x + r*cos(angle), c.y + r*sin(angle));
            angle += inc;
        }
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}

void Primitives::drawTriangle(const Vector2D& p1, const Vector2D& p2,
                              const Vector2D& p3)
{
    if (doFill) {
        glColor4f(fillColorR, fillColorG, fillColorB, fillColorA);
        glBegin(GL_TRIANGLES);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p3.x, p3.y);
        glEnd();
    }
    if (doStroke) {
        drawLine(p1, p2);
        drawLine(p2, p3);
        drawLine(p3, p1);
    }
}

void Primitives::drawLine(const Vector2D& p1, const Vector2D& p2)
{
    if (doStroke) {
        glLineWidth(strokeW);
        glColor4f(strokeColorR, strokeColorG, strokeColorB, strokeColorA);
        glBegin(GL_LINES);

        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);

        glEnd();
    }
}

void Primitives::drawLine(float x1, float y1, float x2, float y2)
{
    if (doStroke) {
        glLineWidth(strokeW);
        glColor4f(strokeColorR, strokeColorG, strokeColorB, strokeColorA);
        glBegin(GL_LINES);

        glVertex2f(x1, y1);
        glVertex2f(x2, y2);

        glEnd();
    }
}

void Primitives::drawCircle(const Vector2D& c, float r)
{
    const int num = 8;
    static float ca[num+1], sa[num+1];
    static bool trigInited = false;

    if (!trigInited) {
        float inc = 2 * M_PI/num;
        float angle = 0;
        for (int i = 0; i <= num; i++) {
            ca[i] = cos(angle);
            sa[i] = sin(angle);
            angle += inc;
        }
        trigInited = true;
    }

    if (doFill) {
        glColor4f(fillColorR, fillColorG, fillColorB, fillColorA);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(c.x, c.y);
        for (int i = 0; i < num; i++) {
            glVertex2f(c.x + r*ca[i], c.y + r*sa[i]);
        }
        glVertex2f(c.x + r, c.y);
        glEnd();
    }
    if (doStroke) {
        for (int i = 0; i < num; i++) {
            Primitives::drawLine(c.x + r * ca[i], c.y + r * sa[i],
                                 c.x + r * ca[i+1], c.y + r * sa[i+1]);
        }
    }
}


//////////////////////////////////////////////////////////////////////////////

