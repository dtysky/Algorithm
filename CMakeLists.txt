cmake_minimum_required(VERSION 3.6)
project(Algorithm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#add_library(. DataStructures inked_list.hpp)

include_directories(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/DataStructures
        ${PROJECT_SOURCE_DIR}/Algorithm
        ${PROJECT_SOURCE_DIR}/Tests)

set(SOURCE_FILES
        Algorithm/bucket_sort.h
        Algorithm/radix_sort.h
        DataStructures/linked_list.h
        DataStructures/list_node.h
        DataStructures/polynomial.h
        DataStructures/polynomial_unit.h
        Tests/bucket_sort.test.h
        Tests/linked_list.test.h
        Tests/list_node.test.h
        Tests/polynomial.test.h
        Tests/radix_sort.test.h
    main.cpp
    main.hpp
        utils.h DataStructures/stack.h Tests/stack.test.h Algorithm/symbol_pair_checker.cpp Algorithm/symbol_pair_checker.h Tests/symbol_pair_checker.test.h Algorithm/postfix_expression_manager.h Tests/postfix_expression_manager.test.h DataStructures/queue.h Tests/queue.test.h DataStructures/queue_based_on_array.h Tests/queue_based_on_array.test.h)

add_executable(Algorithm ${SOURCE_FILES})
