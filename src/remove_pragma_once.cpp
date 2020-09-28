#include "file_traits.hpp"
#include <fstream>
#include <regex>
namespace unify_include_guard::impl
{
  bool replace_pragma_once(fs::path const &path, std::string const &guard_name)
  {
    std::stringstream ss;
    std::fstream fst(path);
    std::regex target(R"(\s*#\s*pragma\s+once\s*)");
    std::string line;
    bool flag = false;
    while (std::getline(fst, line))
    {
      if (std::regex_match(line, target))
      {
        ss << "#ifndef " << guard_name << std::endl;
        ss << "#define " << guard_name << std::endl;
        flag = true;
      }
      else
      {
        ss << line << std::endl;
      }
    }
    fst.close();
    if (flag)
    {
      ss << "#endif //" << guard_name << std::endl;
      fst.open(path, std::ios_base::out);
      fst << ss.str();
    }
    return flag;
  }
} // namespace unify_include_guard::impl
