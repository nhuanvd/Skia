
/*
 * Copyright 2011 Google Inc.
 * Copyright (C) 2011 Research In Motion Limited. All rights reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef GrGLTexture_DEFINED
#define GrGLTexture_DEFINED

#include "../GrGpu.h"
#include "GrGLRenderTarget.h"

class GrEGLImage;

/**
 * A ref counted tex id that deletes the texture in its destructor.
 */
class GrGLTexID : public GrRefCnt {

public:
    GrGLTexID(const GrGLInterface* gl, GrGLuint texID, bool ownsID)
        : fGL(gl)
        , fTexID(texID)
        , fOwnsID(ownsID) {
    }

    virtual ~GrGLTexID() {
        if (0 != fTexID && fOwnsID) {
            GR_GL_CALL(fGL, DeleteTextures(1, &fTexID));
        }
    }

    void abandon() { fTexID = 0; }
    GrGLuint id() const { return fTexID; }

private:
    const GrGLInterface* fGL;
    GrGLuint             fTexID;
    bool                 fOwnsID;
};

////////////////////////////////////////////////////////////////////////////////


class GrGLTexture : public GrTexture {

public:
    enum Orientation {
        kBottomUp_Orientation,
        kTopDown_Orientation,
    };

    struct TexParams {
        GrGLenum fFilter;
        GrGLenum fWrapS;
        GrGLenum fWrapT;
        GrGLenum fSwizzleRGBA[4];
        void invalidate() { memset(this, 0xff, sizeof(TexParams)); }
    };

    struct Desc {
        int             fWidth;
        int             fHeight;
        GrPixelConfig   fConfig;
        GrGLuint        fTextureID;
        bool            fOwnsID;
        Orientation     fOrientation;
    };

    // creates a texture that is also an RT
    GrGLTexture(GrGpuGL* gpu,
                const Desc& textureDesc,
                const GrGLRenderTarget::Desc& rtDesc);

    // creates a non-RT texture
    GrGLTexture(GrGpuGL* gpu,
                const Desc& textureDesc,
                GrEGLImage* eglImage = 0);


    virtual ~GrGLTexture() { this->release(); }

    virtual intptr_t getTextureHandle() const;

    // these functions 
    const TexParams& getCachedTexParams(GrGpu::ResetTimestamp* timestamp) const {
        *timestamp = fTexParamsTimestamp;
        return fTexParams;
    }
    void setCachedTexParams(const TexParams& texParams,
                            GrGpu::ResetTimestamp timestamp) {
        fTexParams = texParams;
        fTexParamsTimestamp = timestamp;
    }
    GrGLuint textureID() const { return fTexIDObj->id(); }

    // Ganesh assumes texture coordinates have their origin
    // in the top-left corner of the image. OpenGL, however,
    // has the origin in the lower-left corner. For content that
    // is loaded by Ganesh we just push the content "upside down"
    // (by GL's understanding of the world) in glTex*Image and the
    // addressing just works out. However, content generated by GL
    // (FBO or externally imported texture) will be updside down
    // and it is up to the GrGpuGL derivative to handle y-mirroing.
    Orientation orientation() const { return fOrientation; }

    GrEGLImage* eglImage() const { return fEglImage; }

    static const GrGLenum* WrapMode2GLWrap();

protected:

    // overrides of GrTexture
    virtual void onAbandon();
    virtual void onRelease();

private:
    TexParams                       fTexParams;
    GrGpu::ResetTimestamp           fTexParamsTimestamp;
    GrGLTexID*                      fTexIDObj;
    Orientation                     fOrientation;
    GrEGLImage*                     fEglImage;

    void init(GrGpuGL* gpu,
              const Desc& textureDesc,
              const GrGLRenderTarget::Desc* rtDesc,
              GrEGLImage* eglImage);

    typedef GrTexture INHERITED;
};

#endif
