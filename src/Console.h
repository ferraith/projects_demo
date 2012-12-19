// AOAA Board Library
// Copyright (C) ferraith. All rights reserved.

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <stdint.h>

///
///
///
class Console {
 public:
  ///
  /// @brief      Constructor
  ///
  Console();
  ///
  /// @brief      Destructor
  ///
  virtual ~Console();
  ///
  ///
  ///
  bool Init();
  ///
  ///
  ///
  uint32_t SendData();
  ///
  ///
  ///
  uint32_t SendString();
  ///
  ///
  ///
  uint32_t ReceiveData();
};

#endif  // CONSOLE_H_
