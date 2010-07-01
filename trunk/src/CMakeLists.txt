set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(themazegame_SOURCES main.cpp audio.cpp game_state.cpp menu_state.cpp render_world.cpp texture.cpp)

add_executable(themazegame ${themazegame_SOURCES})

TARGET_LINK_LIBRARIES(themazegame SDL SOIL GL GLU glut alut openal)


