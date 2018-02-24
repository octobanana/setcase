#ifndef OB_SETCASE_HH
#define OB_SETCASE_HH

#include <string>

namespace OB
{

class Setcase
{
public:
  enum ctype
  {
    Lower,
    Upper
  };

  Setcase(std::string const& str = {});

  std::string get(ctype type);

private:
  std::string str_;

  char to_lower(char c) const;
  char to_upper(char c) const;
  std::string to_lower(std::string s) const;
  std::string to_upper(std::string s) const;

}; // class Setcase

} // namespace OB

#endif // OB_SETCASE_HH
