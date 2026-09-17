cmake_minimum_required(VERSION 4.2)
project(AngrySnail)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

if (APPLE)
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/lib)
endif ()

add_executable(AngrySnail src/main.cpp
        src/Application.cpp
        src/Graphics.cpp
        src/Graphics.h
        src/Physics/Vec2.h
        src/Physics/Vec2.cpp
        src/Physics/Particle.h
        src/Physics/Particle.cpp
        src/Physics/Constants.h
        src/Physics/Force.h
        src/Physics/Force.cpp
        src/Creator/Actions.cpp
        src/Creator/Actions.h
        src/SystemServices/InputProcessor.cpp
        src/SystemServices/InputProcessor.h
        src/Creator/EnvironmentalForces.cpp
        src/Creator/EnvironmentalForces.h
        src/SystemServices/CollisionsObserver.cpp
        src/SystemServices/CollisionsObserver.h
        src/Physics/CollisionResolver.cpp
        src/Physics/CollisionResolver.h
        src/Physics/Material.cpp
        src/Physics/Material.h
        src/Physics/CollisionPair.h
        src/Physics/Boundary.h
)

target_include_directories(AngrySnail PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(AngrySnail PRIVATE
        ${SDL2_LIBRARIES}
        SDL2_image
        SDL2_gfx
)