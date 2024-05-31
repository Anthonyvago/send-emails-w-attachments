cmake_minimum_required(VERSION 3.10)
project(automated_mail_sender)

# Enable all warnings
add_compile_options(-Wall -Wextra -Wconversion -pedantic -pthread)

# Find wxWidgets package
find_package(wxWidgets REQUIRED core base)
find_package(Threads REQUIRED)

# Fetch JSON lib
set(JSON_REPO_GIT "https://github.com/nlohmann/json.git")
message(STATUS "Downloading JSON lib from: ${JSON_REPO_GIT}...")
include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY ${JSON_REPO_GIT}
    GIT_TAG v3.11.3)
    FetchContent_MakeAvailable(json)
    
# Download and unpack smtpclientlibrary at configure time
configure_file(CMakeLists.txt.in smtpclientlibrary-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/smtpclientlibrary-download )
if(result)
  message(FATAL_ERROR "CMake step for smtpclientlibrary failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/smtpclientlibrary-download )
if(result)
  message(FATAL_ERROR "Build step for smtpclientlibrary failed: ${result}")
endif()

#Add smtpclientlibrary directly to our build. This defines
#the smtpclient target.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/smtpclientlibrary-src
                 ${CMAKE_CURRENT_BINARY_DIR}/smtpclientlibrary-build
                 EXCLUDE_FROM_ALL)

# Include wxWidgets
include(${wxWidgets_USE_FILE})

include_directories(
    "include"
    ${CMAKE_CURRENT_BINARY_DIR}/smtpclientlibrary-src/src
)

# Add your source files
file(GLOB SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp" "src/**/*.cpp")

# Define the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link wxWidgets to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} nlohmann_json::nlohmann_json smtpclient)

# Add cppcheck target
add_custom_target(
    cppcheck
    COMMAND cppcheck
            --std=c++11 # Or the appropriate C++ standard you are using
            --enable=all
            --force
            --quiet
            --inline-suppr
            --template=gcc
            -I${CMAKE_SOURCE_DIR}/include
            ${CMAKE_SOURCE_DIR}/src
    COMMENT "Running cppcheck on source and header files"
    VERBATIM
)