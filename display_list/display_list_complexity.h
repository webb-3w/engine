// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_FLOW_DISPLAY_LIST_COMPLEXITY_H_
#define FLUTTER_FLOW_DISPLAY_LIST_COMPLEXITY_H_

#include "flutter/display_list/display_list.h"
#include "flutter/display_list/types.h"
#include "third_party/skia/include/gpu/GrTypes.h"

namespace flutter {

class DisplayListComplexityCalculator {
 public:
  static DisplayListComplexityCalculator* GetForSoftware();
  static DisplayListComplexityCalculator* GetForBackend(GrBackendApi backend);

  virtual ~DisplayListComplexityCalculator() = default;

  // Returns a calculated complexity score for a given DisplayList object
  virtual unsigned int compute(DisplayList* display_list) = 0;

  // Returns whether a given complexity score meets the threshold for
  // cacheability for this particular ComplexityCalculator
  virtual bool should_be_cached(unsigned int complexity_score) = 0;
};

class DisplayListNaiveComplexityCalculator
    : public DisplayListComplexityCalculator {
 public:
  static DisplayListComplexityCalculator* GetInstance();

  unsigned int compute(DisplayList* display_list) override {
    return display_list->op_count(true);
  }

  bool should_be_cached(unsigned int complexity_score) override {
    return complexity_score > 5u;
  }

 private:
  DisplayListNaiveComplexityCalculator() {}
  static DisplayListNaiveComplexityCalculator* instance_;
};

}  // namespace flutter

#endif  // FLUTTER_FLOW_DISPLAY_LIST_COMPLEXITY_H_
