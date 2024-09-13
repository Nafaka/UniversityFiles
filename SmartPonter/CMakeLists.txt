cmake_minimum_required(VERSION 3.27)
project(SmartPonter)

set(CMAKE_CXX_STANDARD 17)

add_executable(SmartPonter
        main.cpp
        player.h
        campaign.h
        hero_info.h
        hero.h
        monster.h)
