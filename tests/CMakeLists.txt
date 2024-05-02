include_directories(../src)

add_executable(test_find_Jb test_find_Jb.cpp  )
target_link_libraries(test_find_Jb libCube)

add_executable(test_find_PLL test_find_PLL.cpp  )
target_link_libraries(test_find_PLL libCube)

add_executable(test_find_U_PLL test_find_U_PLL.cpp  )
target_link_libraries(test_find_U_PLL libCube)

add_executable(test_find_OLL test_find_OLL.cpp  )
target_link_libraries(test_find_OLL libCube)

add_executable(test_find_order test_find_order.cpp  )
target_link_libraries(test_find_order libCube)

add_executable(test_PLL test_PLL.cpp  )
target_link_libraries(test_PLL libCube)

add_executable(test_sequence test_sequence.cpp  )
target_link_libraries(test_sequence libCube)