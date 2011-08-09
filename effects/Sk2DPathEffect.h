
/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef Sk2DPathEffect_DEFINED
#define Sk2DPathEffect_DEFINED

#include "SkPathEffect.h"
#include "SkMatrix.h"

//  This class is not exported to java.
class Sk2DPathEffect : public SkPathEffect {
public:
    Sk2DPathEffect(const SkMatrix& mat);

    // overrides
    //  This method is not exported to java.
    virtual bool filterPath(SkPath* dst, const SkPath& src, SkScalar* width);

    // overrides from SkFlattenable
    //  This method is not exported to java.
    virtual void flatten(SkFlattenableWriteBuffer&);
    
    //  This method is not exported to java.
    virtual Factory getFactory();

    static SkFlattenable* CreateProc(SkFlattenableReadBuffer&);

protected:
    /** New virtual, to be overridden by subclasses.
        This is called once from filterPath, and provides the
        uv parameter bounds for the path. Subsequent calls to
        next() will receive u and v values within these bounds,
        and then a call to end() will signal the end of processing.
    */
    virtual void begin(const SkIRect& uvBounds, SkPath* dst);
    virtual void next(const SkPoint& loc, int u, int v, SkPath* dst);
    virtual void end(SkPath* dst);

    /** Low-level virtual called per span of locations in the u-direction.
        The default implementation calls next() repeatedly with each
        location.
    */
    virtual void nextSpan(int u, int v, int ucount, SkPath* dst);

    const SkMatrix& getMatrix() const { return fMatrix; }

    // protected so that subclasses can call this during unflattening
    Sk2DPathEffect(SkFlattenableReadBuffer&);

private:
    SkMatrix    fMatrix, fInverse;
    // illegal
    Sk2DPathEffect(const Sk2DPathEffect&);
    Sk2DPathEffect& operator=(const Sk2DPathEffect&);

    friend class Sk2DPathEffectBlitter;
    typedef SkPathEffect INHERITED;
};

#endif
