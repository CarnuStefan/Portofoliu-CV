cmake_minimum_required(VERSION 3.22)
project(Lab9_10)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab9_10 main.cpp Domain/Carte.cpp Domain/Carte.h Repository/Repo.cpp Repository/Repo.h Tests/Teste.cpp Tests/Teste.h Service/Service.cpp Service/Service.h UI/UI.cpp UI/UI.h Repository/RepoFile.cpp Repository/RepoFile.h Service/ServiceFile.cpp Service/ServiceFile.h "Exceptions and Validators/MyException.cpp" "Exceptions and Validators/MyException.h" "Exceptions and Validators/ValidatorCarte.cpp" "Exceptions and Validators/ValidatorCarte.h")
