cmake_minimum_required(VERSION 3.2)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(print_ip VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(print_ip VERSION 0.0.1)
endif()

find_package(Threads REQUIRED)
find_package(GTest   REQUIRED)

add_executable(print_ip       sources/main.cpp)
add_executable(print_ip_gtest tests/print_ip_gtest.cpp)

set_target_properties(print_ip PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(print_ip_gtest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/sources
)

target_link_libraries(print_ip_gtest
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

if (MSVC)
    target_compile_options(print_ip PRIVATE
        /W4 -O3
    )
    target_compile_options(print_ip_gtest PRIVATE
        /W4 -O3
    )
else ()
    target_compile_options(print_ip PRIVATE
        -Wall -Wextra -pedantic -Werror -O3
    )
    target_compile_options(print_ip_gtest PRIVATE
        -Wall -Wextra -pedantic -Werror -O3
    )
endif()

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT alexpoligon@mail.ru)

include(CPack)

enable_testing()

add_test(print_ip_gtest print_ip_gtest)

add_custom_command(
    TARGET print_ip_gtest
    POST_BUILD 
    COMMAND ./print_ip_gtest
    COMMENT "Run test..."
)