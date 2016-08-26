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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "animata.h"
#include "animataUI.h"
#include "Bone.h"
#include "Primitives.h"

using namespace Animata;

/**
 * Constructs a bone from the two given joints.
 * \param j0 pointer to joint 0
 * \param j1 pointer to joint 1
 **/
Bone::Bone(Joint *j0, Joint *j1)
{
    this->j0 = j0;
    this->j1 = j1;

    damp = BONE_DEFAULT_DAMP;

    setName("");

    Vector2D diff(j1->position - j0->position);
    dOrig = diff.size();;

    selected = false;

    dsts = weights = sa = ca = NULL;
    attachedVertices = new vector<Vertex *>;

    attachRadiusMult = 1.0;
    falloff = 1.0;

    lengthMult = BONE_DEFAULT_LENGTH_MULT;
    lengthMultMin = BONE_DEFAULT_LENGTH_MULT_MIN;
    lengthMultMax = BONE_DEFAULT_LENGTH_MULT_MAX;

    tempo = 0.0;
    time = M_PI_2; // pi/2 -> bone animation starts at maximum length

}

Bone::~Bone()
{
    detachVertices();
    delete attachedVertices;
}

/**
 * Runs the spring simulation on the bone.
 **/
void Bone::simulate(void)
{
    if (tempo > 0) {
        time += tempo / 42.0f;    // FIXME
        animateLengthMult(0.5 + sin(time) * 0.5f);
    }

    Vector2D d(j1->position - j0->position);
    float dCurrent = d.size();
    d.normalize();

    float m = ((dOrig * lengthMult) - dCurrent) * damp;

    d *= m;
    if (!j0->fixed && !j0->dragged) {
        j0->position -= d;
    }
    if (!j1->fixed && !j1->dragged) {
        j1->position += d;
    }

}

/**
 * Sets bone length multiplier.
 * \param lm multiplier value
 * \remark Bone length multiplier is clamped between the minimum and maximum
 *        bone lengths.
 **/
void Bone::setLengthMult(float lm)
{
    if (lm < lengthMultMin)
        lm = lengthMultMin;
    else if (lm > lengthMultMax)
        lm = lengthMultMax;

    lengthMult = lm;
}

/**
 * Animates length multiplier between the minimum and maximum values.
 * \param t value between 0 and 1
 **/
void Bone::animateLengthMult(float t)
{
    lengthMult = lengthMultMin + (lengthMultMax - lengthMultMin) * t;

    // TODO: find a place for this call
    if (selected) {
        ui->boneLengthMult->value(lengthMult);
    }
}

/**
 * Animates bone. Changes bone length multiplier between the minimum and
 * maximum.
 * \param t float number that will be clamped between 0 and 1
 **/
void Bone::animateBone(float t)
{
    if (t != t)
        return;
    if (t < 0.0f)
        t = 0.0f;
    else if (t > 1.0f)
        t = 1.0f;
    animateLengthMult(t);
}

/**
 * Translates attached vertices of bone.
 * Attached vertices try to maintain their relative position to
 * the bone centre.
 **/
void Bone::translateVertices(void)
{
    Vector2D d(j1->position - j0->position);
    d.normalize();
    Vector2D c = getCenter();

    for (unsigned i = 0; i < attachedVertices->size(); i++) {
        Vertex *v = (*attachedVertices)[i];
        Vector2D t;
        t.x = c.x + (d.x * ca[i] - d.y * sa[i]);
        t.y = c.y + (d.x * sa[i] + d.y * ca[i]);
        t -= v->coord;
        t *= weights[i];
        v->coord += t;
    }
}

/**
 * Moves bone by the given vector.
 * \param d distance vector
 * \param timeStamp timestamp to prevent moving joints multiple times when
 *        they belong to several bones
 **/
void Bone::drag(const Vector2D& d, int timeStamp /* = 0*/)
{
    j0->drag(d, timeStamp);
    j1->drag(d, timeStamp);
}

/**
 * Releases bone after dragging.
 **/
void Bone::release(void)
{
    j0->dragged = false;
    j1->dragged = false;
}

/**
 * Draws bone.
 * \param mouseOver 1 if the mouse is over the bone
 * \param active 1 if it is active
 **/
void Bone::draw(int mouseOver, int active)
{
    Primitives::drawBone(this, mouseOver, active);

    // FIXME: screws up selection
    if (ui->settings.mode == ANIMATA_MODE_ATTACH_VERTICES) {
        // cannot use getRadius(), as it isn't view-dependent
        int r = (int)(getViewRadius());
        if (selected) {
            Vector2D c(getViewCenter());
            Primitives::drawSelectionCircle(c, r);
            for (unsigned i = 0; i < attachedVertices->size(); i++) {
                Vertex *v = (*attachedVertices)[i];
                Primitives::drawVertexAttached(v);
            }
        }
    }
}

/**
 * Inverts the bone's state of selection.
 **/
void Bone::flipSelection(void)
{
    selected = !selected;
}

/**
 * Returns the name of the bone.
 * \return pointer to name
 **/
const char *Bone::getName(void) const
{
    return name;
}

/**
 * Sets the name of the bone.
 * \param str pointer to name string
 * \remark Only the first 15 characters will be used.
 **/
void Bone::setName(const char *str)
{
    strncpy(name, str, 15);
    name[15] = 0;
}

/**
 * Gets bone center coordinates.
 * \return center vector
 **/
Vector2D Bone::getCenter(void) const
{
    Vector2D c((j0->position + j1->position) * 0.5f);
    return c;
}

/**
 * Gets bone center coordinates.
 * \return center vector
 **/
Vector2D Bone::getViewCenter(void) const
{
    Vector2D c((j0->viewPosition + j1->viewPosition) * 0.5f);
    return c;
}

/**
 * Gets radius of vertex selection circle in view coordinate-system.
 * \return The radius of the selection circle in view coordinate-system.
 */
float Bone::getViewRadius() const
{
    /* Distance has to be recalculated every time as it's based on the view
     * position of the joints. */
    Vector2D d(j1->viewPosition - j0->viewPosition);
    return d.size() * 0.5f * attachRadiusMult;
}

/**
 * Attaches vertices from given vector to the bone.
 * \param verts pointer to vector of vertices
 **/
void Bone::attachVertices(vector<Vertex *> *verts)
{
    unsigned count = verts->size();

    /* clear previously attached vertices */
    detachVertices();

    dsts = new float[count];
    weights = new float[count];
    sa = new float[count];
    ca = new float[count];

    Vector2D d(j1->position - j0->position);
    float alpha = d.atan2();
    Vector2D c = getCenter();
    d.normalize();

    for (unsigned i = 0; i < count; i++) {
        Vertex *v = (*verts)[i];
        if (v->selected) {
            Vector2D s = Vector2D(v->coord - c);
            float vd = s.size();

            dsts[i] = vd;

            float vdnorm = vd / (attachRadiusMult * dOrig * .5f);

            if (vdnorm >= 1) {
                weights[i] = BONE_MINIMAL_WEIGHT;
            }
            else {
                weights[i] = pow(1.0 - vdnorm, 1.0 / falloff);
            }

            float a = s.atan2() - alpha;
            sa[i] = vd * (sin(a));
            ca[i] = vd * (cos(a));

            attachedVertices->push_back(v);
        }
    }
}

/**
 * Attaches vertices with given parameters.
 * \param verts pointer to vector of vertices
 * \param dsts distance array holding distance from bone centre for all vertices
 * \param weights array holding vertex weights
 * \param ca array of cosinus angles
 * \param sa array of sinus angles
 **/
void Bone::attachVertices(vector<Vertex *> *verts, float *dsts,
        float *weights, float *ca, float *sa)
{
    unsigned count = verts->size();

    /* clear previously attached vertices */
    detachVertices();

    for (unsigned i = 0; i < count; i++) {
        attachedVertices->push_back((*verts)[i]);
    }
    this->dsts = dsts;
    this->weights = weights;
    this->ca = ca;
    this->sa = sa;
}

/**
 * Recalculates weights of attached vertices.
 **/
void Bone::recalculateWeights(void)
{
    unsigned count = attachedVertices->size();
    for (unsigned i = 0; i < count; i++) {
        float vd = dsts[i];

        float vdnorm = vd / (attachRadiusMult * dOrig * .5f);
        if (vdnorm >= 1) {
            weights[i] = BONE_MINIMAL_WEIGHT;
        }
        else {
            weights[i] = pow(1.0 - vdnorm, 1.0 / falloff);
        }
    }
}

/**
 * Detach vertex from bone.
 * \param v pointer to vertex
 **/
void Bone::detachVertex(Vertex *v)
{
    if (attachedVertices->empty() || v == NULL)
        return;

    // delete vertex pointer from vector
    int lasti = attachedVertices->size() - 1; // index of last element
    for (int vi = 0; vi <= lasti; vi++) {
        if ((*attachedVertices)[vi] == v) {
            // move last vertex to the place of the deleted one
            (*attachedVertices)[vi] = (*attachedVertices)[lasti];

            // rearrange helper arrays
            dsts[vi] = dsts[lasti];
            weights[vi] = weights[lasti];
            sa[vi] = sa[lasti];
            ca[vi] = ca[lasti];

            // remove last element of the vertices vector
            attachedVertices->pop_back();
            break;
        }
    }
}

/**
 * Selects attached vertices.
 * \param s bool, select/deselect
 **/
void Bone::selectAttachedVertices(bool s /* = true */)
{
    for (unsigned i = 0; i < attachedVertices->size(); i++) {
        ((*attachedVertices)[i])->selected = s;
    }
}

/**
 * Detaches vertices.
 **/
void Bone::detachVertices(void)
{
    /* clear previously attached vertices */
    attachedVertices->clear();

    if (dsts) {
        delete [] dsts;
        dsts = NULL;
    }

    if (weights) {
        delete [] weights;
        weights = NULL;
    }

    if (sa) {
        delete [] sa;
        sa = NULL;
    }

    if (ca) {
        delete [] ca;
        ca = NULL;
    }
}

/**
 * Returns the vector of attached vertices.
 * \param dsts pointer to return distance array
 * \param weights pointer to return weights array
 * \param sa pointer to sinus values array
 * \param ca pointer to cosinus values array
 * \return attached vertices, their weight and distance from the bone centre
 *            as arrays
 **/
vector<Vertex *> *Bone::getAttachedVertices(float **dsts, float **weights,
        float **ca, float **sa) const
{
    *dsts = this->dsts;
    *weights = this->weights;
    *ca = this->ca;
    *sa = this->sa;
    return attachedVertices;
}

/**
 * Gets the number of attached vertices.
 * \return number of attached vertices
 **/
int Bone::getAttachedVerticesCount(void) const
{
    return (int)(attachedVertices->size());
}

