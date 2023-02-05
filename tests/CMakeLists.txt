include_directories(../src)

add_executable(test_find_PLL test_find_PLL.cpp  )
target_link_libraries(test_find_PLL libCube)

add_executable(test_find_OLL test_find_OLL.cpp  )
target_link_libraries(test_find_OLL libCube)

add_executable(test_find_Period test_find_Period.cpp  )
target_link_libraries(test_find_Period libCube)

add_executable(test_PLL test_PLL.cpp  )
target_link_libraries(test_PLL libCube)

add_executable(test_sequence test_sequence.cpp  )
target_link_libraries(test_sequence libCube)