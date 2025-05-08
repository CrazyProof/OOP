#include "ChatSession.h"
#include <iostream>
#include <algorithm>
using namespace std;

void ChatSession::addUser(ChatUser *user)
{
    if (!user)
        return;
    users.push_back(user);
    cout << "Add user: " << user->getName() << endl;
}

void ChatSession::removeUser(ChatUser *user)
{
    if (!user)
        return;
    auto it = find(users.begin(), users.end(), user);
    if (it != users.end())
    {
        users.erase(it);
        cout << "Remove user: " << user->getName() << endl;
    }
}

ChatUser *ChatSession::getUserByName(string name)
{
    for (auto &user : users)
    {
        if (user->getName() == name) // 使用 getName() 获取用户名称
        {
            return user;
        }
    }
    cout << name << " not in chat" << endl;
    return nullptr;
}
