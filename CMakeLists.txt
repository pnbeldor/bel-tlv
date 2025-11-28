cmake_minimum_required(VERSION 4.1.0)
project(bel-tlv VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_TESTING "Build unit tests" ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
  #GIT_TAG        f8d7d77c06936315286eb55f8de22cd23c188571 # release-1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|clang")
    #add_compile_options(-Wall -Werror -Wextra -Wpedantic -Wconversion)
    add_compile_options(-Wall -Werror -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /WX)    
endif()

include(CTest)
enable_testing()

add_executable(TLVPractice main.cpp)

include_directories("include")
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include)

file(GLOB_RECURSE ALL_TEST_SRC CONFIGURE_DEPENDS "tests/*.cpp")
add_executable(bel_tlv_tests ${ALL_TEST_SRC})
target_link_libraries(TLVPractice bel-tlv)
target_link_libraries(bel_tlv_tests bel-tlv GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(bel_tlv_tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
