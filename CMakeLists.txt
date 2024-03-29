cmake_minimum_required(VERSION 3.28.0)
project(P06_Personen_Verwaltung_Linked_List VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

set(MAIN_SOURCES)
file(GLOB_RECURSE MAIN_SOURCES "src/*.c")
set(TEST_SOURCES)
file(GLOB_RECURSE TEST_SOURCES "tests/*.c")
set(HEADERS)
file(GLOB HEADERS "include/*.h" "include/command/*.h")

include_directories(include)
add_executable(P06_Personen_Verwaltung_Linked_List ${MAIN_SOURCES} ${HEADERS})

add_executable(tests ${TEST_SOURCES} ${HEADERS})
add_test(NAME ${PROJECT_NAME}_tests COMMAND tests)
set_target_properties(tests PROPERTIES LINKER_LANGUAGE C)
target_link_options(tests PRIVATE -Wl,-subsystem,console)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)