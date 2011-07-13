#import <UIKit/UIKit.h>

#include "SkMatrix.h"
#include "FlingState.h"

#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

class SkOSWindow;
class SkEvent;

@interface SkUIView : UIView <UIAccelerometerDelegate> {
    BOOL fRedrawRequestPending;
    SkMatrix    fMatrix, fLocalMatrix;
    bool        fNeedGestureEnded;

    SkMatrix    fRotateMatrix;

    float       fFirstPinchX, fFirstPinchY;
    bool        fNeedFirstPinch;

    float       fZoomAroundX, fZoomAroundY;
    bool        fZoomAround;

    FlingState  fFlingState;

    GrAnimateFloat  fWarpState;
    bool            fUseWarp;

    struct {
        EAGLContext*    fContext;
        GLuint          fRenderbuffer;
        GLuint          fStencilbuffer;
        GLuint          fFramebuffer;
        GLint           fWidth;
        GLint           fHeight;
    } fGL;
    
    enum Backend {
        kGL_Backend,
        kRaster_Backend,
    };

    // these are visible to DetailViewController
    Backend fBackend;
    bool    fComplexClip;
    
    UINavigationItem* fTitle;
    SkOSWindow* fWind;
}

@property (nonatomic, assign) SkOSWindow *fWind;
@property (nonatomic, retain) UINavigationItem* fTitle;
@property (nonatomic, assign) Backend fBackend;
@property (nonatomic, assign) bool fComplexClip;
@property (nonatomic, assign, setter=setWarpState) bool fUseWarp;

- (void)initGestures;
- (void)flushLocalMatrix;

- (void)setSkTitle:(const char*)title;
- (void)postInvalWithRect:(const SkIRect*)rectOrNil;
- (BOOL)onHandleEvent:(const SkEvent&)event;

@end

