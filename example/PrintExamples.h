/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation,
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file     print_examples.h
 * @brief    Example library file
 * @author   Richard Roberts
 */

#pragma once

#include <boost/shared_ptr.hpp>
#include <iostream>
#include <string>

namespace example {

template <typename T, typename U>
class Counter {
 public:
  size_t count = 0;
};

template <typename T, typename U>
class Fun {
 public:
  Counter<T, U> getCounter() const { return Counter<T, U>(); }
};

class PrintExample {
 public:
  ///< Helper method for Matlab
  void print(const std::string& s = "") const;

  ///< Print a greeting
  void sayHello() const;

  ///< Print a farewell
  void sayGoodbye() const;
};

namespace internal {

std::string getHelloString();

std::string getGoodbyeString();

}  // namespace internal

void consumePrinter(boost::shared_ptr<PrintExample>& pe) {}

}  // namespace example
