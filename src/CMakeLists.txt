set(CUBE_FILES
	Cube.cpp Cube.h
	Sequence.cpp Sequence.h
	CubeHelper.h
	CubeSolver.cpp CubeSolver.h
	SequenceOrder.h
)

include_directories(.)
add_library( libCube STATIC ${CUBE_FILES})
