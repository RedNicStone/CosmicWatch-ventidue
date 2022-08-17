//
// Created by nic on 03/08/22.
//

#ifndef GRAPHICS_SDF_COMBIANTORICS_H
#define GRAPHICS_SDF_COMBIANTORICS_H

#include "sdf_primitives.h"


namespace SDF {

  template <DistanceSignature FT>
  class CInvert : FT {
    public:
      inline float operator()(const vec2& pos) const {
          return -FT::operator() (pos);
      }

      explicit CInvert(FT&& f) : FT(std::move(f)) {}
  };

  template<typename T> struct SDFContainer : public T {
    public: explicit SDFContainer(T&& t) : T(std::move(t)) {}
  };

  template <DistanceSignature F1, DistanceSignature F2>
  class CBooleanUnion : SDFContainer<F1>, SDFContainer<F2> {
    public:
      inline float operator()(const vec2& pos) const {
          return min(SDFContainer<F1>::operator() (pos), SDFContainer<F2>::operator() (pos));
      }

      explicit CBooleanUnion(F1& f1, F2& f2) : SDFContainer<F1>(std::move(f1)), SDFContainer<F2>(std::move(f2)) {}
      explicit CBooleanUnion(F1&& f1, F2& f2) : SDFContainer<F1>(std::move(f1)), SDFContainer<F2>(std::move(f2)) {}
      explicit CBooleanUnion(F1& f1, F2&& f2) : SDFContainer<F1>(std::move(f1)), SDFContainer<F2>(std::move(f2)) {}
      explicit CBooleanUnion(F1&& f1, F2&& f2) : SDFContainer<F1>(std::move(f1)), SDFContainer<F2>(std::move(f2)) {}
  };

  template <DistanceSignature F1, DistanceSignature F2>
  class CBooleanIntersect : SDFContainer<F1>, SDFContainer<F2> {
    public:
      inline float operator()(const vec2& pos) const {
          return max(SDFContainer<F1>::operator() (pos), SDFContainer<F2>::operator() (pos));
      }

      explicit CBooleanIntersect(F1& f1, F2& f2) : SDFContainer<F1>(std::move(f1)), SDFContainer<F2>(std::move(f2)) {}
      explicit CBooleanIntersect(F1& f1, F2&& f2) : SDFContainer<F1>(std::move(f1)), SDFContainer<F2>(std::move(f2)) {}
      explicit CBooleanIntersect(F1&& f1, F2& f2) : SDFContainer<F1>(std::move(f1)), SDFContainer<F2>(std::move(f2)) {}
      explicit CBooleanIntersect(F1&& f1, F2&& f2) : SDFContainer<F1>(std::move(f1)), SDFContainer<F2>(std::move(f2)) {}
  };



  template <DistanceSignature F1, DistanceSignature F2>
  class CBooleanDifference : SDFContainer<F1>, SDFContainer<F2> {
    public:
      inline float operator()(const vec2& pos) const {
          return min(max(SDFContainer<F1>::operator() (pos), -SDFContainer<F2>::operator() (pos)),
                     max(SDFContainer<F2>::operator() (pos), -SDFContainer<F1>::operator() (pos)));
      }
      explicit CBooleanDifference(F1& f1, F2& f2) : SDFContainer<F1>(std::move(f1)), SDFContainer<F2>(std::move(f2))
        {}
      explicit CBooleanDifference(F1& f1, F2&& f2) : SDFContainer<F1>(std::move(f1)), SDFContainer<F2>(std::move(f2))
        {}
      explicit CBooleanDifference(F1&& f1, F2& f2) : SDFContainer<F1>(std::move(f1)), SDFContainer<F2>(std::move(f2))
        {}
      explicit CBooleanDifference(F1&& f1, F2&& f2) : SDFContainer<F1>(std::move(f1)), SDFContainer<F2>(std::move(f2))
        {}
  };

  template <DistanceSignature F1, DistanceSignature F2>
  class CBooleanSubtract : SDFContainer<F1>, SDFContainer<F2> {
    public:
      inline float operator()(const vec2& pos) const {
          return max(SDFContainer<F1>::operator() (pos), -SDFContainer<F2>::operator() (pos));
      }

      explicit CBooleanSubtract(F1& f1, F2& f2) : SDFContainer<F1>(std::move(f1)), SDFContainer<F2>(std::move(f2)) {}
      explicit CBooleanSubtract(F1& f1, F2&& f2) : SDFContainer<F1>(std::move(f1)), SDFContainer<F2>(std::move(f2)) {}
      explicit CBooleanSubtract(F1&& f1, F2& f2) : SDFContainer<F1>(std::move(f1)), SDFContainer<F2>(std::move(f2)) {}
      explicit CBooleanSubtract(F1&& f1, F2&& f2) : SDFContainer<F1>(std::move(f1)), SDFContainer<F2>(std::move(f2)) {}
  };


  template <DistanceSignature F1, DistanceSignature F2>
  class CInterpolate : SDFContainer<F1>, SDFContainer<F2> {
    private:
      float amount;

    public:
      inline float operator()(const vec2& pos) const {
          return std::lerp(SDFContainer<F1>::operator() (pos), -SDFContainer<F2>::operator() (pos), amount);
      }

      explicit CInterpolate(F1& f1, F2& f2, float amount) : SDFContainer<F1>(std::move(f1)),
                                                              SDFContainer<F2>(std::move(f2)), amount(amount) {}
      explicit CInterpolate(F1& f1, F2&& f2, float amount) : SDFContainer<F1>(std::move(f1)),
                                                              SDFContainer<F2>(std::move(f2)), amount(amount) {}
      explicit CInterpolate(F1&& f1, F2& f2, float amount) : SDFContainer<F1>(std::move(f1)),
                                                              SDFContainer<F2>(std::move(f2)), amount(amount) {}
      explicit CInterpolate(F1&& f1, F2&& f2, float amount) : SDFContainer<F1>(std::move(f1)),
                                                              SDFContainer<F2>(std::move(f2)), amount(amount) {}
  };

}

#endif //GRAPHICS_SDF_COMBIANTORICS_H
