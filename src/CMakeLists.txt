add_executable("${PROJECT_NAME}" Cell.cpp Cell.h Group.cpp Group.h lgen.cpp Maze.cpp Maze.h)

target_link_libraries("${PROJECT_NAME}" jsoncpp_lib)
install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
