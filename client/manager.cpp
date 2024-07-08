#include "manager.h"

manager::manager() {}
QString manager::getCurrentUsername() {
    return currentUser;  // Assume currentUser is a static member variable updated during login
}
