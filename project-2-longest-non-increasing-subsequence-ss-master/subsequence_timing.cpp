///////////////////////////////////////////////////////////////////////////////
// subsequence_timing.cpp
//
// Example code showing how to run each algorithm while measuring
// elapsed times precisely. You should modify this program to gather
// all of your experimental data.  
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <random>
#include <vector>

#include "timer.hpp"

#include "subsequence.hpp"

void print_bar() {
  std::cout << std::string(79, '-') << std::endl;
}

int main() {

  const size_t n = 20;

  assert(n > 0);

  // Use a hardcoded seed for reproducibility between runs.
  auto input = random_sequence(n, 0, 1000);

  Timer timer;
  double elapsed;

  print_bar();
  std::cout << "n = " << n << std::endl
            << sequence_to_string(input) << std::endl;

  print_bar();
  std::cout << "end to beginning" << std::endl;
  timer.reset();
  auto etb_output = longest_nonincreasing_end_to_beginning(input);
  elapsed = timer.elapsed();
  std::cout << "output = " << sequence_to_string(etb_output) << std::endl
            << "of length = " << etb_output.size() << std::endl;
  std::cout << "elapsed time=" << elapsed << " seconds" << std::endl;

  print_bar();
  std::cout << "powerset" << std::endl;
  timer.reset();
  auto powerset_output = longest_nonincreasing_powerset(input);
  elapsed = timer.elapsed();
  std::cout << "output = " << sequence_to_string(powerset_output) << std::endl
            << "of length = " << powerset_output.size() << std::endl;
  std::cout << "elapsed time=" << elapsed << " seconds" << std::endl;

  print_bar();

  return 0;
}
