#ifndef MANAGER_H
#define MANAGER_H

#include<QString>
class manager
{
public:
    manager();
    static QString getCurrentUsername();

private:
    static QString currentUser;
};

#endif // MANAGER_H
