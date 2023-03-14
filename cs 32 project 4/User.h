#ifndef USER_INCLUDED
#define USER_INCLUDED

#include <string>
#include <vector>

class User
{
public:
  User(const std::string &full_name, const std::string &email,
       const std::vector<std::string> &watch_history);
  std::string get_full_name() const;
  std::string get_email() const;
  std::vector<std::string> get_watch_history() const;

private:
  std::string fullName;
  std::string email;
  std::vector<std::string> watch_history; // vector of movie ID strings that indicates what movies the user has watched
};

#endif // USER_INCLUDED