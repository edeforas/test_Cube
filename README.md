# test_Cube

This small library simulate 3x3x3 Rubik's cube rotations and sequence,
For example, you can do:

	`c.rotate("R'UL' U2 RU'R' U2 RLU'");`

and test if its solved or PLL ready:

	`cout << "solved?:" << c.is_solved() << " pll_state?:" << c.is_ready_for_pll();`
  
Work in progress.

Only plain C++, using CMake project files