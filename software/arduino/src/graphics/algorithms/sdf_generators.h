//
// Created by nic on 02/08/22.
//

#pragma once

#ifndef GRAPHICS_G_GENERATORS_H
#define GRAPHICS_G_GENERATORS_H

#include "sdf_primitives.h"


namespace SDF {

  class GCircle : public PType {
    private:
      float radius;

    public:
      inline float operator()(const vec2& pos) const {
          return (SDFDistance) pos.getLength() - radius;
      }

      explicit GCircle(float radius) : radius(radius) {};
  };

  class GSquare : public PType {
    protected:
      vec2 size;

    public:
      inline float operator()(const vec2& pos) const {
          vec2 d = pos.absolute() - size;
          return max(d, vec2(0.0f)).getLength() + min(max(d.x(), d.y()), 0.0f);
      }

      explicit GSquare(vec2 size) : size(size) {};
  };

  class GSquareFast : public PType {
    protected:
      vec2 size;

    public:
      inline float operator()(const vec2& pos) const {
          vec2 componentWiseEdgeDistance = pos.absolute() - size;
          return max(componentWiseEdgeDistance.x(), componentWiseEdgeDistance.y());
      }

      explicit GSquareFast(vec2 size) : size(size) {};
  };

  class GRoundedSquare : public PType {
    private:
      vec4 corners;
      vec2 size;

    public:
      float operator()(const vec2& pos) const {
          vec2 d = (pos.x() > 0.0) ?
                   vec2(corners.x(), corners.y()) : vec2(corners.z(), corners.w());
          d.x() = (pos.y() > 0.0) ? d.x() : d.y();
          vec2 q = pos.absolute() - size + vec2(d.x());
          return min(max(q.x(), q.y()), 0.0f) + max(q, vec2(0.0f)).getLength() - d.x();
      }

      explicit GRoundedSquare(vec2 size, vec4 corners) : corners(corners), size(size) {};
  };

  class GSegment : public PType {
    private:
      vec2 a;
      vec2 b;
      float radius;

    public:
      float operator()(const vec2& pos) const {
          vec2 pa = pos - a, ba = b - a;
          float h = clamp(dot(pa,ba) / dot(ba,ba), 0.0f, 1.0f);
          return length(pa - ba * h) - radius;
      }

      explicit GSegment(vec2 begin, vec2 end, float radius) : a(begin), b(end), radius(radius) {};
  };

}

#endif //GRAPHICS_G_GENERATORS_H
