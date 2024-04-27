FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
        test-json
        json/test-json.cpp
        # Modules Used
        ../src/json.h
        ../src/json.cpp
)

# There's definitely a better way of doing this
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/json/hello.json ${CMAKE_CURRENT_BINARY_DIR}/hello.json COPYONLY)

target_link_libraries(
        test-json
        GTest::gtest_main
        nlohmann_json::nlohmann_json
)

include(GoogleTest)
gtest_discover_tests(test-json)