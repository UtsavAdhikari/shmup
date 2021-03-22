cmake_minimum_required(VERSION 3.19)

project(shmup)

set(EXECUTABLE_NAME shmup)

include_directories(
    .
)

add_executable(${EXECUTABLE_NAME}
    main.cpp
    CommandQueue.cpp
    Entity.cpp
    Game.cpp
    MainWindow.cpp
    PlayerAircraft.cpp
    SceneNode.cpp
    SpriteNode.cpp
    World.cpp
)

# sfml
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIRS})
    target_link_libraries(${EXECUTABLE_NAME}
        sfml-network
        sfml-audio
        sfml-graphics
        sfml-window
        sfml-system)
endif()


