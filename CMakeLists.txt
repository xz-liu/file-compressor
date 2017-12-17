cmake_minimum_required(VERSION 3.8)
project(DATA_STRUCTURE_EXP)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp vector.h basic.h list_node.h list.h stack.h queue.h exp_1.h exp_2.h expression_evaluate.cpp bintree_node.h bin_tree.h exp_3.h rb_tree.h graph.h bst.h huffman.h exp_5.h exp_4.h)
add_executable(DATA_STRUCTURE_EXP ${SOURCE_FILES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")