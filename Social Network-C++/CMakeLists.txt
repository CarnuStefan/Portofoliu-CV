cmake_minimum_required(VERSION 3.22)
project(Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project main.cpp
                TAD TAD/Lista.h Domain/User.cpp Domain/User.h Domain/Friendship.cpp Domain/Friendship.h Domain/Message.cpp Domain/Message.h Service/Service.cpp Service/Service.h Repository/RepoFileUser.cpp Repository/RepoFileUser.h Repository/RepoFileFriendships.cpp Repository/RepoFileFriendships.h UI/UI.cpp UI/UI.h)
