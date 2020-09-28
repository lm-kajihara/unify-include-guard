#include "guard_name_creator.hpp"

namespace unify_include_guard
{
  guard_name_creator::guard_name_creator(const char *_prefix, const char *_root) : prefix(_prefix), root(_root)
  {
    if (prefix.size())
    {
      auto last = prefix.back();
      if (last != '.' && last != '/' && last != '_')
      {
        prefix += '_';
      }
    }
  }
  std::string guard_name_creator::get(fs::path const &path) const
  {
    auto rel_path = fs::relative(path, root);
    auto guard_name = prefix + rel_path.native();
    for (auto &c : guard_name)
    {
      if ('a' <= c && c <= 'z')
      {
        c = static_cast<char>(c - 'a' + 'A');
      }
      else if (c == '.' || c == '/')
      {
        c = '_';
      }
    }
    return guard_name;
  }
} // namespace unify_include_guard
