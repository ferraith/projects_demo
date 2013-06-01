// AOAA Board Library
// Copyright (C) ferraith. All rights reserved.

#ifndef AOAA_BOARD_TRIMPOT_H_
#define AOAA_BOARD_TRIMPOT_H_

#include <stdint.h>

#include "common/class_helper.h"

namespace aoaa_board {

///
/// @brief         Provides methods to connect the trimming potentiometer to the microcontroller and read the value
///                of the trimming potentiometer.
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
  ~Trimpot() {}

  ///
  /// @brief         Deinitialize analog input for trimming potentiometer.
  /// @return        None
  ///
  void Deinit();
  ///
  /// @brief         Initialize analog input for trimming potentiometer.
  /// @param[in]     sample_rate  ADC sample rate in Hz (should be <= 200 KHz).
  /// @return        None
  ///
  void Init(uint32_t sample_rate);
  ///
  /// @brief         Read value from the trimming potentiometer.
  /// @param[out]    value  Converted analog input from trimming potentiometer.
  /// @return        True if value is valid.
  bool Get(uint16_t *value);

 private:
  /// Timeout to convert an analog input by ADC
  uint8_t kConversionTimeout;
  /// Disables the copy constructor and assignment operator
  DISALLOW_COPY_AND_ASSIGN(Trimpot);
};

}  // namespace aoaa_board

#endif  // AOAA_BOARD_TRIMPOT_H_
