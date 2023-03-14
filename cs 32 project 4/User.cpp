#include "User.h"

#include <string>
#include <vector>
using namespace std;

User::User(const string &full_name, const string &email,
           const vector<string> &watch_history)
    : fullName(full_name), email(email), watch_history(watch_history)
{
    // nothing
}

string User::get_full_name() const
{
    return fullName;
}

string User::get_email() const
{
    return email;
}

vector<string> User::get_watch_history() const
{
    return watch_history;
}
