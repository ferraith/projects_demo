// AOAA Board Library
// Copyright (C) ferraith. All rights reserved.

#ifndef TRIMPOT_H_
#define TRIMPOT_H_

#include "types.h"

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
  /// @brief         Destructor
  ///
  virtual ~Trimpot() {}
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

#endif  // TRIMPOT_H_
