
if(BUILD_TESTING)
    project(TLVTests LANGUAGES CXX)
    find_package(GTest REQUIRED)

    file(GLOB SOURCES CONFIG_DEPENDS "*Tests.cpp")

    add_executable(TLVTests ${SOURCES})

    target_link_libraries(TLV PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

    add_test(NAME TLV_tests COMMAND TLVTests)
    include(GoogleTest)
endif()