cmake_minimum_required(VERSION 3.9)
project(RegexEngine)

set(CMAKE_CXX_STANDARD 11)

add_executable(RegexEngine main.cc nfa.cc regex_parser.cc test.cc)