#include "file_traits.hpp"
#include <stack>

namespace unify_include_guard::impl
{
  namespace
  {
    std::regex startif(R"(\s*#\s*if\s+.*)");
    std::regex startifdef(R"(^\s*#\s*ifdef\s+*)");
    std::regex startifndef(R"(^\s*#\s*ifndef\s+)");
    std::regex endif(R"(^\s*#\s*endif)");
    std::regex define(R"(^\s*#\s*define\s+)");
    std::regex name(R"(^\w+)");

    std::optional<std::string> is_if_line(std::string const &line)
    {
      std::smatch match;
      if (std::regex_match(line, startif))
      {
        return "";
      }
      else if (std::regex_search(line.begin(), line.end(), match, startifdef))
      {
        return "";
      }
      else if (std::regex_search(line.begin(), line.end(), match, startifndef))
      {
        if (std::regex_search(match[0].second, line.end(), match, name))
        {
          return match[0].str();
        }
      }
      return std::nullopt;
    }
    std::optional<std::string> is_define(std::string const &line)
    {
      std::smatch match;
      if (std::regex_search(line.begin(), line.end(), match, define))
      {
        if (std::regex_search(match[0].second, line.end(), match, name))
        {
          return match[0].str();
        }
      }
      return std::nullopt;
    }
  } // namespace
  bool replace_ifndef_guard(fs::path const &path, std::string const &guard_name)
  {
    std::stack<std::string> stack;
    std::string line;
    std::fstream fst(path);
    std::optional<std::string> before;
    while (std::getline(fst, line))
    {
      std::optional<std::string> opt;
      if (opt = is_if_line(line))
      {
        stack.emplace(*opt);
      }
      else if (opt = is_define(line))
      {
        if (!before && *opt == stack.top())
        {
          before = opt;
        }
      }
      else if (std::regex_search(line, endif))
      {
        if (!stack.size())
        {
          return false;
        }
        stack.pop();
      }
    }
    if (stack.size() || !before)
    {
      return false;
    }
    std::stringstream ss;
    fst.clear();
    fst.seekp(std::ios::beg);
    while (std::getline(fst, line))
    {
      std::optional<std::string> opt;
      if (opt = is_if_line(line))
      {
        stack.emplace(*opt);
        if (opt == before)
        {
          ss << "#ifndef " << guard_name << std::endl;
          continue;
        }
      }
      if (opt = is_define(line))
      {
        if (opt == before)
        {
          ss << "#define " << guard_name << std::endl;
          continue;
        }
      }
      if (std::regex_search(line, endif))
      {
        if (stack.top() == before)
        {
          ss << "#endif //" << guard_name << std::endl;
          stack.pop();
          continue;
        }
        stack.pop();
      }
      ss << line << std::endl;
    }
    fst.close();
    fst.open(path, std::ios_base::out);
    fst << ss.str();
    return true;
  }
} // namespace unify_include_guard::impl
