#include "parg.hh"
using Parg = OB::Parg;

#include "setcase.hh"
using Setcase = OB::Setcase;

#include <string>
#include <iostream>
#include <vector>
#include <map>

int program_options(Parg& pg);

int program_options(Parg& pg)
{
  pg.name("setcase").version("0.1.0 (02.24.2018)");
  pg.description("transform text to uppercase and lowercase");
  pg.usage("[flags] [options] [--] [arguments]");
  pg.usage("[-u|-l] [input text]");
  pg.usage("[-v|--version]");
  pg.usage("[-h|--help]");
  pg.info("Exit Codes", {"0 -> normal", "1 -> error"});
  pg.info("Examples", {
    "hr --help",
    "hr --version",
  });
  pg.author("Brett Robinson (octobanana) <octobanana.dev@gmail.com>");

  // flags
  pg.set("help,h", "print the help output");
  pg.set("version,v", "print the program version");
  pg.set("upper,u", "transforms the text to uppercase");
  pg.set("lower,l", "transforms the text to lowercase");

  pg.set_pos();
  pg.set_stdin();

  int status {pg.parse()};
  // uncomment if at least one argument is expected
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
  return 0;
}

int main(int argc, char *argv[])
{
  Parg pg {argc, argv};
  int pstatus {program_options(pg)};
  if (pstatus > 0)
  {
    return 0;
  }
  else if (pstatus < 0)
  {
    return 1;
  }

  Setcase sc;

  return 0;
}
