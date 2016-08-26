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
#include <stdio.h>

#if defined(__APPLE__)
    #include <OPENGL/gl.h>
    #include <OPENGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include "Camera.h"

using namespace Animata;

/**
 * Creates a new camera with default parameters.
 * - \a target = (0, 0, 0)
 * - \a orientation = (0, 0, 0)
 * - \a upvector = (0, -1, 0)
 * - \a distance = 150
 * - \a fov = 90
 * - \a zNear = 0.1
 * - \a zFar = 1000
 */
Camera::Camera()
{
    target.set(0.f, 0.f, 0.f);
    orientation.set(0.f, 0.f, 0.f);
    upvector.set(0.f, -1.f, 0.f);

    distance = 150.f;
    fov = 90.f;

    zNear = 0.1f;
    zFar = 1000.f;

    init = false;

    parent = NULL;
}

/**
 * Sets up the camera-picture's aspect, and calculates the picture's size.
 * Positions the camera's target if it hasn't been already positioned.
 * If this \a parent of this camera is already set every calculation will be
 * based on the parent's parameters.
 * /param w Width of the view.
 * /param h Height of the view.
 **/
void Camera::setSize(const Vector2D& d)
{
    dim = pictureDim = d;

    if (!init) {
        target = dim * 0.5;

        setAspect(dim);

        if (parent) {
            target = parent->getTarget();
            distance = parent->getDistance();
            fov = parent->getFOV();
        }

        init = true;
    }

    // setAspect(width, height);
    aspect = dim.y > 0 ? (double)dim.x / (double)dim.y : 1.0;

    if (parent) {
        Vector2D p = parent->getDimensions();

        // setAspect(pw, ph);
        aspect = p.y > 0 ? (double)p.x / (double)p.y : 1.0;

        if (dim.x / aspect > dim.y) {
            pictureDim.y = dim.y;
            pictureDim.x = (int)(pictureDim.y * aspect);
        }
        else {
            pictureDim.x = dim.x;
            pictureDim.y = (int)(pictureDim.x / aspect);
        }
    }

    setupPerspective();
}

/**
 * Calculates the aspect of the picture based on the given parameters.
 * The vertical field-of-view gets also calculated and stored, what is required
 * for an undistorted picture.
 * \param d Dimensions of the picture at camera distance from the target.
 */
void Camera::setAspect(const Vector2D& d)
{
    aspect = d.y > 0 ? (double)d.x / (double)d.y : 1.0;

    double radtheta, degtheta;
    radtheta = 2.0 * atan2(d.y / 2, distance);
    degtheta = (180.0 * radtheta) / M_PI;

    fov = degtheta;
}

/**
 * Sets up the projection matrix by perspective transformation.
 * Also the viewport is set.
 * In the beginning the projection matrix gets cleared.
 */
void Camera::setupPerspective()
{
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(fov, aspect, zNear, zFar);

    setupViewport();
}

/**
 * Sets up the projection matrix by orthographic transformation.
 * Also the viewport is set.
 * In the beginning the projection matrix gets cleared.
 */
void Camera::setupOrtho()
{
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    Vector2D p1 = (dim - pictureDim) * 0.5;
    Vector2D p2 = p1 + dim;
    glOrtho(p1.x, p2.x, p1.y, p2.y, -1, 1);

    setupViewport();
}

/**
 * Sets up the projection matrix which will be used by picking functions.
 * This is done via multiplying the a special picking matrix onto the current
 * projection matrix.
 * /param d         Coordinates of the picking position
 * /param radius    The radius around the given point where picking occures.
 */
void Camera::setupPickingProjection(const Vector2D& p, int radius)
{
    // get the boundaries of actual viewport
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPickMatrix((GLdouble)p.x, (GLdouble)(viewport[3] - p.y), (GLdouble)radius,
                  (GLdouble)radius, viewport);

    Vector2D p1 = (dim - pictureDim) * 0.5;
    Vector2D p2 = p1 + dim;
    glOrtho(p1.x, p2.x, p1.y, p2.y, -1, 1);
}

/**
 * Sets up the modelview matrix by gluLookAt(), based on the camera properties
 * \a target, \a distance and \a upvector.
 * In the beginning the modelview matrix gets cleared.
 */
void Camera::setupModelView()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(target.x, target.y, target.z - distance,
              target.x, target.y, target.z,
              upvector.x, upvector.y, upvector.z);
}

/**
 * Sets up the viewport to be the exact size as the camera-picture at \a distance.
 */
void Camera::setupViewport()
{
    Vector2D p = (dim - pictureDim) * 0.5;

    glViewport(p.x, p.y, pictureDim.x, pictureDim.y);
}

