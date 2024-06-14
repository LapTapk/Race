target_include_directories(main PUBLIC include)
file(GLOB_RECURSE SOURCES "src/*")
target_sources(main PUBLIC ${SOURCES})

file(GLOB_RECURSE TEST_SOURCES "tests/*")
add_executable(test ${TEST_SOURCES} ${SOURCES})
target_include_directories(test PUBLIC include ../external)
