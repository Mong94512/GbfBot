cmake_minimum_required(VERSION 3.0)
project(GBF_EXPlus_BOT)

find_package(OpenCV REQUIRED)

add_executable(bot main.cpp bot.cpp map.cpp detector.cpp function.cpp)
target_include_directories(bot PRIVATE ../include)
target_link_libraries(bot ${OpenCV_LIBS} winmm Gdiplus)