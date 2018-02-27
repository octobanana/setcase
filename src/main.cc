#include "parg.hh"
using Parg = OB::Parg;

#include "setcase.hh"
using Setcase = OB::Setcase;

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <unistd.h>

int program_options(Parg& pg);

int program_options(Parg& pg)
{
  pg.name("setcase").version("0.1.2 (27.02.2018)");
  pg.description("transform text to uppercase and lowercase");
  pg.usage("[flags] [options] [--] [arguments]");
  pg.usage("[-u|-l] [--] [input text]");
  pg.usage("[-v|--version]");
  pg.usage("[-h|--help]");
  pg.info("Examples", {
    "setcase -u uppercase string",
    "setcase -l 'LOWERCASE string'",
    "setcase -l LOWERCASE | xargs printf \"%s\"",
    "printf \"uppercase\" | setcase -u",
    "setcase --help",
    "setcase --version",
  });
  pg.info("Exit Codes", {"0 -> normal", "1 -> error"});
  pg.author("Brett Robinson (octobanana) <octobanana.dev@gmail.com>");

  // flags
  pg.set("help,h", "print the help output");
  pg.set("version,v", "print the program version");
  pg.set("upper,u", "transforms the text to uppercase");
  pg.set("lower,l", "transforms the text to lowercase");

  pg.set_pos();
  pg.set_stdin();

  int status {pg.parse()};
  if (status > 0 && pg.get_stdin().empty())
  {
    std::cout << pg.print_help() << "\n";
    std::cout << "Error: " << "expected arguments" << "\n";
    return -1;
  }
  if (status < 0)
  {
    std::cout << pg.print_help() << "\n";
    std::cout << "Error: " << pg.error() << "\n";
    return -1;
  }
  if (pg.get<bool>("help"))
  {
    std::cout << pg.print_help();
    return 1;
  }
  if (pg.get<bool>("version"))
  {
    std::cout << pg.print_version();
    return 1;
  }
  if (pg.get<bool>("lower") && pg.get<bool>("upper"))
  {
    std::cout << pg.print_help() << "\n";
    std::cout << "Error: " << "flags '-l' and '-u' are in conflict" << "\n";
    return -1;
  }
  if (pg.get_pos().empty() && pg.get_stdin().empty())
  {
    std::cout << pg.print_help() << "\n";
    std::cout << "Error: " << "no input text given" << "\n";
    return -1;
  }
  return 0;
}

int main(int argc, char *argv[])
{
  Parg pg {argc, argv};
  int pstatus {program_options(pg)};
  if (pstatus > 0) return 0;
  if (pstatus < 0) return 1;

  Setcase sc {pg.get_stdin() + pg.get_pos()};

  bool lower {pg.get<bool>("lower")};
  bool upper {pg.get<bool>("upper")};

  std::string out;

  if (lower || upper)
  {
    if (lower)
    {
      out = sc.get(Setcase::Lower);
    }
    else
    {
      out = sc.get(Setcase::Upper);
    }
  }
  else
  {
    out = sc.get(Setcase::Lower);
  }

  if (! isatty(STDOUT_FILENO))
  {
    std::cout << out;
  }
  else
  {
    std::cout << out << "\n";
  }

  return 0;
}
