add_executable(snake "main.cpp")
target_sources(snake
        PUBLIC
            Globals.cpp
            Graphics.cpp
            Game.cpp
            Input.cpp
            Level.cpp
            Player.cpp
            Rect.cpp
        PRIVATE
            Globals.h
            Graphics.h
            Game.h
            Input.h
            Level.h
            Player.h
            Rect.h
)

find_package(SDL2 REQUIRED)
target_include_directories(snake PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(snake ${SDL2_LIBRARIES})