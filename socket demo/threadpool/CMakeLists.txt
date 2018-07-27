cmake_minimum_required(VERSION 3.6)
project(SERVER)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pthread")
set(APP_SRC 
	server.cpp
	command.cpp
	thread_pool.cpp
	thread_process.cpp
	)
add_executable(server ${APP_SRC})

