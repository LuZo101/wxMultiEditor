# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.0)

# Define the project name
project(MULTIEDITOR)

# Add the include directory for header files
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find the necessary wxWidgets packages
find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})

# List source files for the main app
set(MAIN_APP_SOURCE_FILES
  src/App.cpp
  src/MainFrame.cpp
  src/Logic.cpp
)

# Create an executable for our main app
add_executable(${PROJECT_NAME} ${MAIN_APP_SOURCE_FILES})

# Link the main app with the wxWidgets libraries
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

# Set the output directory for the app's executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# Enable testing
enable_testing()

# List source files for our tests
set(TEST_SOURCE_FILES
  tests/unit_test.cpp
  tests/catch_amalgamated.cpp
  src/Logic.cpp # If our tests depend on this file
)

# Create an executable for our tests
add_executable(tests_exe ${TEST_SOURCE_FILES})

# Include the Catch2 amalgamated version
target_include_directories(tests_exe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link tests_exe with the wxWidgets libraries
target_link_libraries(tests_exe ${wxWidgets_LIBRARIES})

# Name the test and specify which executable to run for it
add_test(NAME UnitTests COMMAND tests_exe)

# Automatically run tests after building
add_custom_command(
  TARGET tests_exe
  POST_BUILD
  COMMAND tests_exe
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
