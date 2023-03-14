#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include "treemm.h"
#include <map>
class User;

class UserDatabase
{
public:
  UserDatabase();
  bool load(const std::string &filename);
  User *get_user_from_email(const std::string &email) const;

private:
  std::map<std::string, User *> m_map;
};

#endif // USERDATABASE_INCLUDED
