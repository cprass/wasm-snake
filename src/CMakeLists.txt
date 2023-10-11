add_executable(snake "main.cpp")
target_sources(snake
        PUBLIC
            Graphics.cpp
            Game.cpp
        PRIVATE
            Graphics.h
            Game.h
)

find_package(SDL2 REQUIRED)
target_include_directories(snake PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(snake ${SDL2_LIBRARIES})