// Demo Application
// Copyright (C) ferraith. All rights reserved.

#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>

///
/// @brief         A macro to disallow the copy constructor and operator= function. This should be used in the private
///                declarations for a class
/// @param[in]     class_name The name of the class
/// @return        None
///
#define DISALLOW_COPY_AND_ASSIGN(class_name) \
  class_name(const class_name&);             \
  void operator=(const class_name&)

#endif  // TYPES_H_
