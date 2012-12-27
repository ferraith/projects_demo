// AOAA Board Library
// Copyright (C) ferraith. All rights reserved.

#ifndef TRIMPOT_H_
#define TRIMPOT_H_

#include <stdint.h>

#include "class_helper.h"

namespace aoaa_board {

///
/// @brief         Provides methods to
///
class Trimpot {
 public:
  ///
  /// @brief         Constructor
  ///
  Trimpot();
  ///
  /// @brief         Initialize analog input for trimming potentiometer
  /// @return        None
  ///
  void Init();
  ///
  /// @brief         Read value from the trimming potentiometer
  /// @return        // read value from the trimming potentiometer
  uint16_t Get();
 private:
  /// Disables the copy constructor and assignment operator
  DISALLOW_COPY_AND_ASSIGN(Trimpot);
};

}  // namespace aoaa_board

#endif  // TRIMPOT_H_
