//
// Created by nic on 06/08/22.
//

#ifndef GRAPHICS_TILING_H
#define GRAPHICS_TILING_H

#include <vector>
#include <stack>

#include "../types.h"
#include "../renderer/sdf_mix.h"


class UI {

  private:
    typedef RGB8 UIPixelType;

    struct DrawInfo {
        PixelBuffer<UIPixelType>& pixelBuffer;
    };

    struct WidgetData {
        std::function<UIPixelType(const vec2&)> drawFunction;
    };

    class TilingTree {
      public:
        enum TileOrientation {
            TILE_ORIENTATION_HORIZONTAL = 0,
            TILE_ORIENTATION_VERTICAL = 1
        };

        struct TileNode {
            Region2D size;
            TileOrientation childOrientation = TILE_ORIENTATION_HORIZONTAL;

            std::vector<TileNode> children{};
        };

      private:
        TileNode topmostNode;
        std::stack<TileNode*> currentNodeStack;

      public:
        explicit TilingTree(Region2D size);

        void newNode(bool enterNode = true);
        void leaveNode();
    };

    static TilingTree currentTiling;

  public:
    static void begin(PixelBuffer<UIPixelType>& pixelBuffer, Region2D region = {});
    static void end();

};

#endif //GRAPHICS_TILING_H
