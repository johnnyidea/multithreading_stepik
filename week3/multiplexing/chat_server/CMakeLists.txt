project(chat_server)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        server.cpp)