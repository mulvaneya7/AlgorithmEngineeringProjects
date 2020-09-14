///////////////////////////////////////////////////////////////////////////////
// disks.hpp
//
// Definitions for two algorithms that each solve the 
// alternating disks problem.
//
// As provided, this header has four functions marked with 
// TODO comments.
// You need to write in your own implementation of these 
// functions.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

// State of one disk, either light or dark.
enum disk_color { DISK_LIGHT, DISK_DARK };

// Data structure for the state of one row of disks.
class disk_state {
private:
  std::vector<disk_color> _colors;

public:

  disk_state(size_t light_count)
    : _colors(light_count * 2, DISK_LIGHT) {

      assert(dark_count() > 0);

      for (size_t i = 1; i < _colors.size(); i += 2) {
        _colors[i] = DISK_DARK;
      }
  }

  // Equality operator for unit tests.
  bool operator== (const disk_state& rhs) const {
    return std::equal(_colors.begin(), _colors.end(), rhs._colors.begin());
  }

  size_t total_count() const {
    return _colors.size();
  }

  size_t dark_count() const {
    return total_count() / 2;
  }

  size_t light_count() const {
    return dark_count();
  }

  bool is_index(size_t i) const {
    return (i < total_count());
  }

  disk_color get(size_t index) const {
    assert(is_index(index));
    return _colors[index];
  }

  void swap(size_t left_index) {
    assert(is_index(left_index));
    auto right_index = left_index + 1;
    assert(is_index(right_index));
    std::swap(_colors[left_index], _colors[right_index]);
  }

  std::string to_string() const {
    std::stringstream ss;
    bool first = true;
    for (auto color : _colors) {
      if (!first) {
        ss << " ";
      }

      if (color == DISK_LIGHT) {
        ss << "L";
      } else {
        ss << "D";
      }

      first = false;
    }
    return ss.str();
  }

  // Return true when this disk_state is in alternating format. That means
  // that the first disk at index 0 is light, the second disk at index 1
  // is dark, and so on for the entire row of disks.
  bool is_alternating() const {
    // We only need to check if all even indexes are light.
    for (auto iter = _colors.begin(); iter != _colors.end(); iter = iter + 2) {
      if (*iter == DISK_DARK) {
        return false;
      }
    }
    return true;
  }

  // Return true when this disk_state is fully sorted, with all light disks
  // on the left (low indices) and all dark disks on the right (high
  // indices).
  bool is_sorted() const {
    size_t middle = _colors.size()/2;

    // We only need to check if the first half contains only light disks.
    for (size_t i = 0; i < middle; i++) {
      if (_colors[i] == DISK_DARK) {
        return false;
      }
    }
    return true;
  }
};

// Data structure for the output of the alternating disks problem. That
// includes both the final disk_state, as well as a count of the number
// of swaps performed.
class sorted_disks {
private:
  disk_state _after;
  unsigned _swap_count;

public:

  sorted_disks(const disk_state& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }

  sorted_disks(disk_state&& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }

  const disk_state& after() const {
    return _after;
  }

  unsigned swap_count() const {
    return _swap_count;
  }
};

// Algorithm that sorts disks using the left-to-right algorithm.
sorted_disks sort_left_to_right(const disk_state& before) {
  // check that the input is in alternating format  
  assert(before.is_alternating());

  // Do nothing if the number of disks is 2.
  if (before.total_count() == 2) {
    return sorted_disks(before, 0);
  }

  disk_state after = disk_state(before.light_count());
  
  // We know our algorithm will only need to run n times, where n is the
  // number of light disks.
  size_t max_iter = after.light_count();

  // This implementation will not attempt to sort sections of the vector
  // which are already sorted.
  // We start out with one disk already sorted on each end.
  size_t left_sorted = 1;
  size_t right_sorted = after.total_count() - 1;

  unsigned swap_count = 0;

  for (size_t i = 0; i < max_iter; i++) {
    // Perform disk_state::swap on every other element within the
    // unsorted section of the vector.
    for (size_t j = left_sorted; j < right_sorted; j = j + 2) {
      after.swap(j);
      swap_count++;
    }
    // One more disk has been sorted on each end.
    left_sorted++;
    right_sorted--;
  }

  return sorted_disks(after, swap_count);
}

// Algorithm that sorts disks using the lawnmower algorithm.
sorted_disks sort_lawnmower(const disk_state& before) {
  // check that the input is in alternating format
  assert(before.is_alternating());

  // Do nothing if the number of disks is 2.
  if (before.total_count() == 2) {
    return sorted_disks(before, 0);
  }

  // Perform a single swap if the number of disks is 4.
  if (before.total_count() == 4) {
    disk_state after = disk_state(before.light_count());
    after.swap(1);
    return sorted_disks(after, 1);
  }

  disk_state after = disk_state(before.light_count());

  // This implementation will not attempt to sort sections of the vector
  // which are already sorted. One iteration is complete after scanning
  // left, then right. We only need n/2 iterations.
  // We start out with one disk already sorted on each end.
  size_t max_iter = after.light_count()/2;
  size_t left_sorted = 1;
  size_t right_sorted = after.total_count() - 1;

  unsigned swap_count = 0;

  for (size_t i = 0; i < max_iter; i++) {
    // Perform disk_state::swap on every other element within the
    // unsorted section of the vector.
    for (size_t j = left_sorted; j < right_sorted; j = j + 2) {
      after.swap(j);
      swap_count++;
    }
    // One more disk has been sorted on each end.
    left_sorted++;
    right_sorted--;

    // We can now reverse the previous for loop.
    // Since our swap function accepts the left disk in the swap pair, 
    // we need to start an additional 2 disks to the left.
    for (size_t k = right_sorted - 2; k >= left_sorted; k = k - 2) {
      after.swap(k);
      swap_count++;
    }
    // One more disk has been sorted on each end.
    left_sorted++;
    right_sorted--;
  }

  return sorted_disks(after, swap_count);
}
