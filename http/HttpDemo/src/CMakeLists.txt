set(CMAKE_CXX_FLAGS "-std=c++0x -lpthread ${CMAKE_CXX_FLAGS}")

include_directories(../tnet)
include_directories(../tnet/http)
include_directories(../json)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable(ServerGuard main.cpp 
			Shm.cpp 
			Sem.cpp  
			ServerInfo.cpp 
			ServerManager.cpp 
			RenderInfo.cpp
			wlog.cpp)
target_link_libraries(ServerGuard tnet tnet_http)
