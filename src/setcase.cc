#include "setcase.hh"

#include <string>

namespace OB
{

Setcase::Setcase(std::string const& str):
  str_ {str}
{
}

std::string Setcase::get(Setcase::ctype type)
{
  std::string out;

  if (type == Setcase::Lower)
  {
    out = to_lower(str_);
  }
  else
  {
    out = to_upper(str_);
  }

  return out;
}

char Setcase::to_lower(char c) const
{
  if (c >= 'A' && c <= 'Z')
  {
    c += 'a' - 'A';
  }
  return c;
}

char Setcase::to_upper(char c) const
{
  if (c >= 'a' && c <= 'z')
  {
    c += 'A' - 'a';
  }
  return c;
}

std::string Setcase::to_lower(std::string s) const
{
  for (char &c : s)
  {
    c = Setcase::to_lower(c);
  }
  return s;
}

std::string Setcase::to_upper(std::string s) const
{
  for (char &c : s)
  {
    c = to_upper(c);
  }
  return s;
}

} // namespace OB
