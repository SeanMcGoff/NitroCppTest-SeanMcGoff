add_executable(
        NitroCppTest_SeanMcGoff
        main.cpp
        json.h
        json.cpp
        rectangle.h
        rectangle.cpp
)
target_link_libraries(NitroCppTest_SeanMcGoff PRIVATE nlohmann_json::nlohmann_json)