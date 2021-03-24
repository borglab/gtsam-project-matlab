/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation,
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file     example.i
 * @brief    Example wrapper interface file
 * @author   Richard Roberts, Varun Agrawal
 */

// This is an interface file for automatic MATLAB wrapper generation.
// See `wrap` for full documentation and more examples.

#include <example/PrintExamples.h>

namespace example {

template<T = {size_t, int}, U = {float, double}>
class Fun {
};

typedef example::Fun<size_t, double> FunCounter;

class PrintExample {
  PrintExample();
  void print(string s) const;
  void sayHello() const;
  void sayGoodbye() const;
};

void consumePrinter(example::PrintExample* pe);

}  // namespace example
