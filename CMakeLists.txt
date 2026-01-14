project(halolib)

set(LibraryVersion "1.0")
add_definitions(-DLIBRARY_VERSION=\"${LibraryVersion}\")

file(GLOB_RECURSE SOURCES src/*.cxx src/*.cc src/*.cpp)
file(GLOB_RECURSE HEADERS inc/*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

# Include local and REST framework headers
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/source/framework/core/inc
        ${CMAKE_SOURCE_DIR}/source/framework/inc
        /home/sophia/rest-install/include
)

# Link against the REST framework
target_link_libraries(${PROJECT_NAME} PUBLIC RestFramework)

# Install the library and headers
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY inc/ DESTINATION include/${PROJECT_NAME})

## --- Tests --------------------------------------------------------------
# Build a small unit test for TRestPowerEvent
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test)
    add_executable(TRestPowerEvent_test test/TRestPowerEvent_test.cxx)
    target_include_directories(TRestPowerEvent_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
    target_link_libraries(TRestPowerEvent_test PRIVATE ${PROJECT_NAME})
    enable_testing()
    add_test(NAME TRestPowerEvent_test COMMAND TRestPowerEvent_test)
endif()

