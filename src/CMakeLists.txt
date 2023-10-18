add_executable(snake "main.cpp")

INCLUDE(FindPkgConfig)
find_package(SDL2 REQUIRED)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED)

target_sources(snake
        PRIVATE
            Globals.cpp
            Graphics.cpp
            Game.cpp
            Input.cpp
            Level.cpp
            Player.cpp
            Rect.cpp
            Menu.cpp
)



target_include_directories(snake PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(snake PRIVATE ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES})