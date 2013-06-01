// Common Source Files
// Copyright (C) ferraith. All rights reserved.

#ifndef COMMON_CLASS_HELPER_H_
#define COMMON_CLASS_HELPER_H_

///
/// @brief         A macro to disallow the copy constructor and operator= function. This should be used in the private
///                declarations for a class
/// @param[in]     class_name  The name of the class.
/// @return        None
///
#define DISALLOW_COPY_AND_ASSIGN(class_name) \
  class_name(const class_name&);             \
  void operator=(const class_name&)

#endif  // COMMON_CLASS_HELPER_H_
