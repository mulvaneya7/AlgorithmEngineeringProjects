///////////////////////////////////////////////////////////////////////////////
// subsequence_test.cpp
//
// Unit tests for subsequence.hpp
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iostream>

#include "rubrictest.hpp"

#include "subsequence.hpp"

int main() {

  Rubric rubric;

  const sequence 
    input1{2, 12, 4, 8, 0},
    solution1{12, 4, 0},
    input2{15, 7, 11, 3, 13, 5, 9, 1, 14, 6, 10, 2, 12, 4, 8, 4, 0},
    solution2{15, 11, 9, 6, 4, 4, 0},
    input3{617, 93, 56, 54, 934, 401, 77, 752, 459, 631},
    solution3{617, 93, 56, 54},
    input4{848, 713, 231, 810, 709, 611, 840, 530, 748, 530, 114},
    solution4{848, 713, 709, 611, 530, 530, 114},
    input5{299, 995, 396, 993, 366, 978, 691, 264, 81, 224},
    solution5{995, 993, 978, 691, 264, 81},
    input6{5, 4, 4, 3, 2, 1},
      solution6{5, 4, 4, 3, 2, 1},
    input7{1, 2, 3, 4},
    solution7{1};

  rubric.criterion("end-to-beginning example 1", 1,
		   [&]() {
         TEST_EQUAL("first input", solution1, longest_nonincreasing_end_to_beginning(input1));
           });
    
  rubric.criterion("end-to-beginning example 2", 1,
           [&]() {
         TEST_EQUAL("second input", solution2, longest_nonincreasing_end_to_beginning(input2));
		   });

  rubric.criterion("end-to-beginning additional cases", 1,
		   [&]() {
         TEST_EQUAL("input3", solution3, longest_nonincreasing_end_to_beginning(input3));
         TEST_EQUAL("input4", solution4, longest_nonincreasing_end_to_beginning(input4));
         TEST_EQUAL("input5", solution5, longest_nonincreasing_end_to_beginning(input5));
         TEST_EQUAL("input6", solution6, longest_nonincreasing_end_to_beginning(input6));
         TEST_EQUAL("input7", solution7, longest_nonincreasing_end_to_beginning(input7));
		   });

  rubric.criterion("powerset example 1", 1,
		   [&]() {
         TEST_EQUAL("first input", solution1, longest_nonincreasing_powerset(input1));
           });

    rubric.criterion("powerset example 2", 1,
                     [&]() {
         TEST_EQUAL("second input", solution2, longest_nonincreasing_powerset(input2));
		   });

  rubric.criterion("powerset additional cases", 1,
		   [&]() {
         TEST_EQUAL("input3", solution3, longest_nonincreasing_powerset(input3));
         TEST_EQUAL("input4", solution4, longest_nonincreasing_powerset(input4));
         TEST_EQUAL("input5", solution5, longest_nonincreasing_powerset(input5));
         TEST_EQUAL("input6", solution6, longest_nonincreasing_powerset(input6));
         TEST_EQUAL("input7", solution7, longest_nonincreasing_powerset(input7));
		   });

  return rubric.run();
}
