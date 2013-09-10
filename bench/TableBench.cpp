/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "SkBenchmark.h"
#include "SkCanvas.h"
#include "SkRect.h"

static const SkScalar kCellWidth = SkIntToScalar(20);
static const SkScalar kCellHeight = SkIntToScalar(10);

// This bench draws a table in the manner of Google spreadsheet and sahadan.com.
//           ____________ ___
//          |     1      | 2 |
//          |____________|___|
//          |     3      | 4 |
//          |____________|___|
//
// Areas 1-4 are first all draw white. Areas 3&4 are then drawn grey. Areas
// 2&4 are then drawn grey. Areas 2&3 are thus double drawn while area 4 is
// triple drawn.
// This trio of drawRects is then repeat for the next cell.
class TableBench : public SkBenchmark {
public:
    static const int kNumRows = 48;
    static const int kNumCols = 32;

    TableBench(void* param)
        : INHERITED(param) {
    }

protected:
    virtual const char* onGetName() {
        return "tablebench";
    }

    virtual void onDraw(SkCanvas* canvas) {
        SkPaint cellPaint;
        cellPaint.setColor(0xFFFFFFF);

        SkPaint borderPaint;
        borderPaint.setColor(0xFFCCCCCC);

        for (int i = 0; i < this->getLoops(); ++i) {
            for (int row = 0; row < kNumRows; ++row) {
                for (int col = 0; col < kNumCols; ++col) {
                    SkRect cell = SkRect::MakeLTRB(col * kCellWidth,
                                                   row * kCellHeight,
                                                   (col+1) * kCellWidth,
                                                   (row+1) * kCellHeight);
                    canvas->drawRect(cell, cellPaint);

                    SkRect bottom = SkRect::MakeLTRB(col * kCellWidth,
                                                     row * kCellHeight + (kCellHeight-SK_Scalar1),
                                                     (col+1) * kCellWidth,
                                                     (row+1) * kCellHeight);
                    canvas->drawRect(bottom, borderPaint);

                    SkRect right = SkRect::MakeLTRB(col * kCellWidth + (kCellWidth-SK_Scalar1),
                                                    row * kCellHeight,
                                                    (col+1) * kCellWidth,
                                                    (row+1) * kCellHeight);
                    canvas->drawRect(right, borderPaint);
                }
            }
        }
    }

private:
    typedef SkBenchmark INHERITED;
};

static SkBenchmark* gFactory(void* p) { return new TableBench(p); }

static BenchRegistry gRegistry(gFactory);
