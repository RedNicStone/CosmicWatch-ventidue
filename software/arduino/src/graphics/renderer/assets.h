//
// Created by nic on 04/08/22.
//

#ifndef GRAPHICS_ASSET_H
#define GRAPHICS_ASSET_H

#include "../types.h"
#include "sdf_mix.h"


template<typename PixelType>
class Asset {
  protected:
    Point2D size;
    PixelBuffer<PixelType>* assetBuffer{};

  public:
    /// Load asset into memory
    virtual void load() {
        if (!assetBuffer)
            assetBuffer = new PixelBuffer<PixelType>(size);
    };

    /// Frees asset from memory
    virtual void free() {
        delete assetBuffer;
        assetBuffer = 0;
    };

    inline bool isLoaded() { return assetBuffer; }

    inline Point2D getSize() { return size; }
    inline const PixelBuffer<PixelType>& getBuffer() { return *assetBuffer; }

    explicit Asset(Point2D size) : size(size) {};

    virtual ~Asset() { delete assetBuffer; }
};

template<typename PixelType>
class StoredAsset : public Asset<PixelType> {
  private:

  public:
    //todo
};

template<typename PixelType, SDF::MixSignature<PixelType> FT>
class SDFAsset : public Asset<PixelType>, FT {
  public:
    void load() override {
        if (!Asset<PixelType>::assetBuffer)
            Asset<PixelType>::load();

        const Point2D region = Asset<PixelType>::size;

        for (unsigned int x = 0; x < region.x(); ++x) {
            for (unsigned int y = 0; y < region.y(); ++y) {
                auto pos = Point2D(x, y);
                Asset<PixelType>::assetBuffer->setPixel(pos, FT::operator() ({ (float) x, (float) y }));
            }
        }
    }

    explicit SDFAsset(const FT& f, Point2D size) : Asset<PixelType>(size), FT(std::move(f)) {};
    explicit SDFAsset(const FT&& f, Point2D size) : Asset<PixelType>(size), FT(std::move(f)) {};
};

#endif //GRAPHICS_ASSET_H
