#include <iostream>
#include "Tests/Teste.h"
#include "Service/Service.h"
#include "UI/UI.h"
#include "Repository/RepoFile.h"

int main() {
    testEntity();
    testRepo();
    testServ();
    testRepofile();
    std::cout << "test passed" << std::endl;
    RepoFile repofile(R"(C:\Users\crnst\Desktop\OOP\Labs\Lab9-10\Librarie.txt)");
    RepoFile cosrepofile(R"(C:\Users\crnst\Desktop\OOP\Labs\Lab9-10\Cos.txt)");
    ServiceFile serv(repofile);
    ServiceFile cos(cosrepofile);
    UI ui(serv,cos);
    ui.runUI();
    return 0;
}
