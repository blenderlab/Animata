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

#ifndef __LAYER_H__
#define __LAYER_H__

#include "Skeleton.h"
#include "Mesh.h"
#include "Matrix.h"
#include "Vector3D.h"
#include "Angle3D.h"

using namespace std;

namespace Animata
{

/**
 * Layer holding Skeleton and Mesh data
 **/
class Layer
{
private:
    Layer *parent;                  ///< pointer to the parent if not the root
    std::vector<Layer *> *layers;   ///< vector storing the sublayers

    Mesh *mesh;                     ///< the mesh belonging to this layer
    Skeleton *skeleton;             ///< the skeleton belonging to this layer

    char name[16];                  ///< name of layer

    Vector3D position;              ///< position of the layer origin

    Vector3D offset;                ///< layer scale and rotation offset
    float scale;                    ///< layer scale
    Angle3D angle;                  ///< layer rotation angle

    float alpha;                    ///< layer alpha
    bool visible;                   ///< visibility on/off

    /** Counts the created layers so far. Used for automatic naming of layers */
    static int layerCount;

    /** transformation matrix returned by getTransformationMatrix() */
    Matrix transformation;

public:

    Layer(Layer *p = NULL);
    ~Layer();

    void eraseLayers();

    /** Returns sublayers.
     * \return pointer to Layer * vector
     **/
    inline std::vector<Layer *> *getLayers() { return layers; }

    /// overwrites sublayers
    void setLayers(std::vector<Layer *> *newLayers);

    void addSublayer(Layer *layers);

    void addSublayers(std::vector<Layer *> *layers);

    int deleteSublayer(Layer *layer);

    void drawWithoutRecursion(int mode);

    void simulate(int times = 1);

    /// makes a new layer
    Layer *makeLayer();

    /**
     * Calculates the transformation matrix based on the transformations of this
     * layer. Also recalculates transformation matrices of the sublayers
     **/
    void calcTransformationMatrix();

    /**
     * Returns the transformation matrix of this layer.
     * \return pointer to the transformation matrix which is held in a static
     * storage place by each layer. Subsequent calls overwrite the content where
     * the returned pointer points to.
     **/
    inline Matrix *getTransformationMatrix() { return &transformation; }

    const char *getName(void) const;
    void setName(const char *str);

    /// Returns mesh.
    inline Mesh *getMesh() { return mesh; }
    /// Returns skeleton.
    inline Skeleton *getSkeleton() { return skeleton; }

    /// Returns parent of layer.
    inline Layer *getParent() { return parent; }
    /// Sets layer parent.
    inline void setParent(Layer *p) { parent = p; }

    /// Returns position.
    inline Vector3D getPosition(void) const { return position; }

    /// Returns cummulated z position.
    inline float getTotalDepth() const { return transformation.f[14]; }

    /// Returns offset
    inline Vector3D getOffset(void) const { return offset; }
    /// Returns scale.
    inline float getScale(void) const { return scale; }
    /// Returns theta.
    inline Angle3D getAngle(void) const { return angle; }

    /// Returns alpha.
    inline float getAlpha(void) const { return alpha; }

    float getAccumulatedAlpha(void) const;

    /// Returns visibility.
    inline bool getVisibility() const { return visible; }

    /// Sets x position.
    inline void setPosition(const Vector3D& v)
        { this->position = v; /* calcTransformationMatrix(); */ }
    inline void setPosition(const Vector2D& v)
        { this->position = v; /* calcTransformationMatrix(); */ }
    inline void setPositionElement(float value, int index)
        { this->position.setElement(value, index); }

    /// Sets offset
    inline void setOffset(const Vector3D& v)
        { this->offset = v; calcTransformationMatrix(); }
    inline void setOffset(const Vector2D& v)
        { this->offset = v; calcTransformationMatrix(); }
    inline void setOffsetElement(float value, int index)
        { this->offset.setElement(value, index); }

        /// Sets scale.
    inline void setScale(float scale)
        { this->scale = scale; calcTransformationMatrix(); }

    /// Sets angle.
    inline void setAngle(const Angle3D& angle)
        { this->angle = angle; calcTransformationMatrix(); }
    inline void setAngleElement(float value, int index)
        { this->angle.setElement(value, index); }

    /// Sets alpha.
    inline void setAlpha(float alpha)
        { this->alpha = alpha; }
    void setVisibility(bool v);

    /**
     * Moves layer.
     * \param d distance to move by
     **/
    inline void move(const Vector3D& d)
        { this->position += d; calcTransformationMatrix(); }
    inline void move(const Vector2D& d)
        { this->position += d; calcTransformationMatrix(); }

    /**
     * Resizes layer.
     * \param s value added to scale
     **/
    inline void resize(float s)
        { this->scale += s; calcTransformationMatrix(); }

    /**
     * Rotates layer.
     * \param s value added to theta
     **/
    inline void rotate(const Angle3D& angle)
        { this->angle += angle; calcTransformationMatrix(); }

    void scaleAroundPoint(float s, const Vector3D& p);

    void setup(const Vector3D& position, const Vector3D& offset, float scale,
               const Angle3D& angle, float alpha);

    inline static bool zorder(const Layer *a, const Layer *b)
        { return a->getTotalDepth() > b->getTotalDepth(); }
};

} /* namespace Animata */

#endif

