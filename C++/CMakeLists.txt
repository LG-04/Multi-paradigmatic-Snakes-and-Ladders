cmake_minimum_required(VERSION 4.0)
project(C__)

set(CMAKE_CXX_STANDARD 20)

add_executable(C__ main.cpp
        source/Player.cc
        header/Player.h
        source/Game.cc
        header/Game.h
        source/Die.cc
        header/Die.h
        source/GameBoard.cc
        header/GameBoard.h
        source/HumanPlayer.cc
        header/HumanPlayer.h
        source/ComputerPlayer.cc
        header/ComputerPlayer.h)
