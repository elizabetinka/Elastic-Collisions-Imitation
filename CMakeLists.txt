cmake_minimum_required(VERSION 3.16)
project(PhysicsModel1  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(PhysicsModel1 src/main.cpp src/Model.h src/Model.cpp src/TextField/TextField.cpp src/TextField/TextField.h src/Button/Button.h src/Button/Button.cpp)
target_link_libraries(PhysicsModel1 PRIVATE sfml-graphics)
target_compile_features(PhysicsModel1 PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET PhysicsModel1
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:PhysicsModel1>
        VERBATIM)
endif()

install(TARGETS PhysicsModel1)
