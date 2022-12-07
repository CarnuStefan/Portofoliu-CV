
#include "Domain/Message.h"
#include "Domain/Friendship.h"
#include "Domain/User.h"
#include "Repository/RepoFileUser.h"
#include "Repository/RepoFileFriendships.h"
#include "UI/UI.h"

int main() {
    RepoFileUser repoUser(R"(C:\Users\crnst\Desktop\SDD\Project\Users.txt)");
    RepoFileFriendships repoFriend(R"(C:\Users\crnst\Desktop\SDD\Project\Friends.txt)");
    Service service(repoUser,repoFriend);
    UI ui(service);
    ui.runUI();
    return 0;
}
