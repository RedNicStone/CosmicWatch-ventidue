//
// Created by nic on 07/08/22.
//

#include "tiling.h"


UI::TilingTree::TilingTree(Region2D size) {
    topmostNode.size = size;
    currentNodeStack.push(&topmostNode);
}

void UI::TilingTree::newNode(bool enterNode) {
    auto node = TileNode();
    node.childOrientation = (TileOrientation) !currentNodeStack.top()->childOrientation;

    currentNodeStack.top()->children.push_back(node);
    if (enterNode) currentNodeStack.push(&currentNodeStack.top()->children.back());
}

void UI::TilingTree::leaveNode() {
    currentNodeStack.pop();
}

void UI::begin(PixelBuffer<UIPixelType> &pixelBuffer, Region2D region) {
    //UI::currentTiling = TilingTree(region);
}

void UI::end() {

}
