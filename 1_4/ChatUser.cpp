#include "ChatUser.h"
#include <iostream>
#include <algorithm>
using namespace std;

void ChatUser::addFriend(ChatUser *user)
{
    if (!user)
        return;
    if (find(friends.begin(), friends.end(), user) != friends.end())
    {
        cout << name << " and " << user->name << " are already friends" << endl;
        return;
    }
    friends.push_back(user);
    cout << name << " -> add friend -> " << user->name << endl;
}

void ChatUser::removeFriend(ChatUser *user)
{
    if (!user)
        return;
    auto it = find(friends.begin(), friends.end(), user);
    if (it == friends.end())
    {
        cout << name << " and " << user->name << " are not yet friends" << endl;
        return;
    }
    friends.erase(it);
    cout << name << " -> remove friend -> " << user->name << endl;
}

void ChatUser::sendMessage(ChatUser *user, string message)
{
    if (!user)
        return;
    cout << name << " -> send message -> " << user->name << " : " << message << endl;
    user->receiveMessage(this, message);
}

void ChatUser::receiveMessage(ChatUser *user, string message)
{
    if (!user)
        return;

    // 查找是否已经存在该用户的消息记录
    for (auto &entry : messageQueue)
    {
        if (entry.first == user) // 找到对应的用户
        {
            entry.second.push_back(message); // 将消息追加到该用户的消息列表
            cout << name << " -> receive message -> " << user->name << " : " << message << endl;
            return;
        }
    }

    // 如果没有找到该用户，创建新的消息记录
    messageQueue.push_back({user, {message}});
    cout << name << " -> receive message -> " << user->name << " : " << message << endl;
}

void ChatUser::showMessage()
{
    cout << "Chat " << name << ":" << endl;
    for (auto &entry : messageQueue) // 替换结构化绑定
    {
        ChatUser *sender = entry.first;
        vector<string> &msgs = entry.second;
        cout << ">> From " << sender->name << ":" << endl;
        for (const auto &msg : msgs)
        {
            cout << ">> " << msg << endl;
        }
    }
}

void ChatUser::showFriends()
{
    cout << name << "'s friend:";
    for (const auto &friendUser : friends)
    {
        cout << " " << friendUser->name;
    }
    cout << endl;
}
