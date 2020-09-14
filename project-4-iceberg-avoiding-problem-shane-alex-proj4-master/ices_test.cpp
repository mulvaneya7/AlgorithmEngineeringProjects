///////////////////////////////////////////////////////////////////////////////
// ices_test.cpp
//
// Unit tests for ices_algs.hpp
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <random>

#include "rubrictest.hpp"

#include "ices_types.hpp"
#include "ices_algs.hpp"

int main() {

  Rubric rubric;

  ices::grid empty2(2, 2), empty4(4, 4);
  unsigned int empty2_solution = 2, empty4_solution = 20;

  ices::grid horizontal(4, 4);
  horizontal.set(0, 3, ices::CELL_ICEBERG);
  unsigned int horizontal_solution = 19;

  ices::grid vertical(4, 4);
  vertical.set(1, 0, ices::CELL_ICEBERG);
  vertical.set(2, 0, ices::CELL_ICEBERG);
  vertical.set(3, 0, ices::CELL_ICEBERG);
  unsigned int vertical_solution = 10;

  ices::grid all_ices(4, 4);
  for (ices::coordinate r = 0; r < 4; ++r) {
    for (ices::coordinate c = 0; c < 4; ++c) {
      if (!(r == 0 && c == 0)) {
        all_ices.set(r, c, ices::CELL_ICEBERG);
      }
    }
  }
  unsigned int all_ices_solution = 0;

  ices::grid maze(4, 4);
  /*    ..XX
        X..X
        XX..
        XXX.   */
  maze.set(0, 2, ices::CELL_ICEBERG);
  maze.set(0, 3, ices::CELL_ICEBERG);
  maze.set(1, 0, ices::CELL_ICEBERG);
  maze.set(1, 3, ices::CELL_ICEBERG);
  maze.set(2, 0, ices::CELL_ICEBERG);
  maze.set(2, 1, ices::CELL_ICEBERG);
  maze.set(3, 0, ices::CELL_ICEBERG);
  maze.set(3, 1, ices::CELL_ICEBERG);
  maze.set(3, 2, ices::CELL_ICEBERG);

  unsigned int maze_solution = 1;

  std::mt19937 gen;
  ices::grid small_random =  ices::grid::random(4, 5, 4, gen),
               medium_random = ices::grid::random(12, 25, 50, gen),
               large_random =  ices::grid::random(20, 79, 211, gen);
      
  rubric.criterion("exhaustive search - simple cases", 4, [&]() {
      TEST_EQUAL("empty2", empty2_solution, iceberg_avoiding_exhaustive(empty2));
      TEST_EQUAL("empty4", empty4_solution, iceberg_avoiding_exhaustive(empty4));
      TEST_EQUAL("horizontal", horizontal_solution, iceberg_avoiding_exhaustive(horizontal));
      TEST_EQUAL("vertical", vertical_solution, iceberg_avoiding_exhaustive(vertical));
      TEST_EQUAL("all_ices no. of paths", all_ices_solution, iceberg_avoiding_exhaustive(all_ices));
    });

 
  rubric.criterion("exhaustive search - maze", 1, [&]() {
      TEST_EQUAL("correct", maze_solution, iceberg_avoiding_exhaustive(maze));
    });
  
  rubric.criterion("dynamic programming - simple cases", 4, [&]() {
      TEST_EQUAL("empty2", empty2_solution, iceberg_avoiding_dyn_prog(empty2));
      TEST_EQUAL("empty4", empty4_solution, iceberg_avoiding_dyn_prog(empty4));
      TEST_EQUAL("horizontal", horizontal_solution, iceberg_avoiding_dyn_prog(horizontal));
      TEST_EQUAL("vertical", vertical_solution, iceberg_avoiding_dyn_prog(vertical));
      auto output = iceberg_avoiding_dyn_prog(all_ices);
      TEST_EQUAL("all_ices no. of paths", 0, output);
    });
   
  rubric.criterion("dynamic programming - maze", 1, [&]() {
      TEST_EQUAL("correct", maze_solution, iceberg_avoiding_dyn_prog(maze));
    });

  rubric.criterion("dynamic programming - random instances", 1, [&]() {
      std::cout << std::endl;
     
      auto small_output = iceberg_avoiding_dyn_prog(small_random);
      TEST_EQUAL("small", 5, small_output);
      
      auto medium_output = iceberg_avoiding_dyn_prog(medium_random);
      TEST_EQUAL("medium", 384638, medium_output);
      
      auto large_output = iceberg_avoiding_dyn_prog(large_random);
      TEST_EQUAL("large", 1098385592, large_output);
    });

  rubric.criterion("stress test", 2,[&]() {
      const ices::coordinate ROWS = 5,
	MAX_COLUMNS = 15;
      const unsigned SEED = 20181130;
      
      std::mt19937 gen(SEED);
      
      for (ices::coordinate columns = 1; columns <= MAX_COLUMNS; ++columns) {
	auto area = ROWS * columns,
	  thick = area / 10;
	ices::grid setting = ices::grid::random(ROWS, columns, 
							thick, gen);
	TEST_EQUAL("random grid with " + std::to_string(columns) + " columns",
		   ices::iceberg_avoiding_exhaustive(setting),
		   ices::iceberg_avoiding_dyn_prog(setting));
      }
    });
  
  return rubric.run();
}
