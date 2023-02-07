add_definitions("-g -std=c++0x")

add_executable(test ./TestTimt.cpp ../src/log/LogMessage.cpp ../src/log/Timestamp.cpp ../src/log/Logger.cpp)
#add_executable(threadpool ./main.cpp)

target_link_libraries(test)