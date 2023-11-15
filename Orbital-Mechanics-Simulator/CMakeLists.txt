cmake_minimum_required(VERSION 3.14)

project(Orbital-Mechanics-Simulator)

# Enable testing for the project.
enable_testing()

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the Google Test submodule.
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add an interface library for header-only includes
add_library(header_interface INTERFACE)

# Add your header files directories here
target_include_directories(header_interface INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/core
    ${CMAKE_CURRENT_SOURCE_DIR}/include/physics
    # Add any other directories here
)

# Specify your source files here
set(SOURCE_FILES
    src/core/Body.cpp
    src/physics/PhysicsEngine.cpp
    src/core/Vector3D.cpp
    # Add any other .cpp files here
)

# Add the executable for your application code
add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE header_interface)

# Add the executable for the test code
add_executable(${PROJECT_NAME}_tests
    test/core/test_Body.cpp
    test/core/test_Vector3D.cpp
    # test/physics/PhysicsEngine_test.cpp
    # Add any other test .cpp files here
    ${SOURCE_FILES}
)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE header_interface gtest_main)

# Discover the unit tests
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)

add_custom_target(run-verbose-tests 
    COMMAND ${CMAKE_CTEST_COMMAND} --rerun-failed --output-on-failure
)