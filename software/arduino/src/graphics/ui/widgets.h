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


namespace UI {
  typedef vec4 UIPixelType;

  class Widget {
    public:
      virtual void setVisible(bool) {}
      [[nodiscard]] virtual bool isVisible() { return false; }

      [[nodiscard]] virtual bool canGetFocus() const { return false; }
      virtual void setFocused(bool) {}
      [[nodiscard]] virtual bool isFocused() const { return false; }

      virtual void setSensitive(bool) {}
      [[nodiscard]] virtual bool isSensitive() const { return false; }

      [[nodiscard]] virtual std::function<UIPixelType(const vec2&)> getDrawFunction() const { 
          return [](const vec2&) { return UIPixelType(); }; }
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

      [[nodiscard]] std::function<UIPixelType(const vec2&)> getDrawFunction() const override {
          return [](const vec2&) { return UIPixelType(); }; }
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

      [[nodiscard]] std::function<UIPixelType(const vec2&)> getDrawFunction() const override {
          return [](const vec2&) { return UIPixelType(); }; }
  };

  class Button : public Interactable {
    private:
      UIPixelType renderFunction(const vec2& pos);

    protected:
      bool active;
      std::string description;

    public:
      explicit Button(std::string description) : description(std::move(description)) {};

      [[nodiscard]] std::function<UIPixelType(const vec2&)> getDrawFunction() const override {
          return [](const vec2&) { return UIPixelType(); }; }
  };

}

#endif //GRAPHICS_WIDGETS_H
