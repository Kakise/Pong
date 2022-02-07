cmake_minimum_required(VERSION 3.10)
project(Pong)

set(CMAKE_CXX_STANDARD 17)

add_executable(Pong main.cpp Logic/AI.cpp Logic/AI.h Logic/Player.cpp Logic/Player.h Logic/Balls.cpp Logic/Balls.h Levels/DifficultySelection.cpp Levels/DifficultySelection.h Levels/LoadLevel.cpp Levels/LoadLevel.h)

file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR})
file(GLOB_RECURSE RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Assets/*")

# Get a list of all of the files in the data-folder.

# Individually set the file's path properties.
foreach (FILE ${RESOURCES})
    # Get the relative path from the data-folder to the particular file.
    file(RELATIVE_PATH NEW_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Assets" ${FILE})

    # Get the relative path to the file.
    get_filename_component(NEW_FILE_PATH ${NEW_FILE} DIRECTORY)

    # Set it's location inside the app package (under Resources).
    set_property(SOURCE ${FILE} PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${NEW_FILE_PATH}")

    # Optional: Add the file to the 'Resources' folder group in Xcode.
    #           This also preserves folder structure.
    source_group("Resources/${NEW_FILE_PATH}" FILES "${FILE}")
endforeach ()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)

set(CUR_TARGET PongOSX)
add_executable(${CUR_TARGET} MACOSX_BUNDLE main.cpp Logic/AI.cpp Logic/AI.h Logic/Player.cpp Logic/Player.h Logic/Balls.cpp Logic/Balls.h Levels/DifficultySelection.cpp Levels/DifficultySelection.h Levels/LoadLevel.cpp Levels/LoadLevel.h ${RESOURCES})
set_target_properties(${CUR_TARGET} PROPERTIES
        BUNDLE True
        MACOSX_BUNDLE_GUI_IDENTIFIER my.domain.style.identifier.${CUR_TARGET}
        MACOSX_BUNDLE_BUNDLE_NAME ${CUR_TARGET}
        MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
        )

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Pong ${SFML_LIBRARIES})
    target_link_libraries(PongOSX ${SFML_LIBRARIES})
endif ()

