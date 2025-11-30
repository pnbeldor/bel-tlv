
add_library(TLV-utils)

file(GLOB_RECURSE UTILS_SOURCES CONFIG_DEPENDS "src/*.cpp")
target_sources(TLV-utils PRIVATE ${UTILS_SOURCES})

target_include_directories(TLV-utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# if(BUILD_TESTING)
#     add_subdirectory(tests)
# endif()
