//
// Created by RedNicStone for ProtonAnticheat-server on 9/4/22.
//

#pragma once

#ifndef GRAPHICS_WIDGETS_H
#define GRAPHICS_WIDGETS_H

#include <functional>
#include <string>
#include <utility>

#include "../types.h"
#include "../font/font.h"
#include "style.h"

#define DRAW_SIGNATURE UIPixelType renderFunction(const Point2D& pos)


namespace UI {
  typedef vec4 UIPixelType;

  typedef std::function<UIPixelType(const Point2D&)> RenderFunction;
  static UIPixelType emptyDraw(const Point2D&) { return {}; }

  bool AABB(const Point2D& pos, const Region2D& bBox) {
      return (pos > bBox.begin && pos < bBox.end);
  }

  class Widget {
    protected:
      Point2D size{};

    public:
      virtual void setVisible(bool) {}
      [[nodiscard]] virtual bool isVisible() { return false; }

      [[nodiscard]] virtual bool canGetFocus() const { return false; }
      virtual void setFocused(bool) {}
      [[nodiscard]] virtual bool isFocused() const { return false; }

      virtual void setSensitive(bool) {}
      [[nodiscard]] virtual bool isSensitive() const { return false; }

      [[nodiscard]] virtual RenderFunction getDrawFunction() const { return emptyDraw; }
  };
  
  class Drawable : public Widget {
    protected:
      bool visible = true;
      
    public:
      void setVisible(bool value) override { visible = value; }
      bool isVisible() override { return visible; }

      [[nodiscard]] bool canGetFocus() const override { return false; }
      void setFocused(bool) override {}
      [[nodiscard]] bool isFocused() const override { return false; }

      void setSensitive(bool) override {}
      [[nodiscard]] bool isSensitive() const override { return false; }

      [[nodiscard]] RenderFunction getDrawFunction() const override { return emptyDraw; }
  };
  
  class Interactable : public Drawable {
    protected:
      bool selected = false;
      bool sensitive = false;
      
    public:
      [[nodiscard]] bool canGetFocus() const override { return true; }
      void setFocused(bool value) override { selected = value; }
      [[nodiscard]] bool isFocused() const override { return selected; }

      void setSensitive(bool value) override { sensitive = value; }
      [[nodiscard]] bool isSensitive() const override { return sensitive; }

      [[nodiscard]] RenderFunction getDrawFunction() const override { return emptyDraw; }
  };

  class Button : public Interactable {
    private:
      UIPixelType renderFunction(const vec2& pos);

    protected:
      bool active;
      TextObject text;
      StyleSheet* style;

      DRAW_SIGNATURE;

    public:
      explicit Button(const std::string& description, StyleSheet* style, bool activated = false);

      [[nodiscard]] RenderFunction getDrawFunction() const override { return emptyDraw; }
  };

}

#endif //GRAPHICS_WIDGETS_H
