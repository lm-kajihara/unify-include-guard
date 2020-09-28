#ifndef UNIFY_INCLUDE_GUARD_GUARD_NAME_CREATOR_HPP
#define UNIFY_INCLUDE_GUARD_GUARD_NAME_CREATOR_HPP
#include "utility.hpp"
#include <string>

namespace unify_include_guard
{
  class guard_name_creator
  {
    std::string prefix;
    char const *root;

  public:
    guard_name_creator(const char *_prefix, const char *_root);

    std::string get(fs::path const &path) const;
  };
} // namespace unify_include_guard
#endif //UNIFY_INCLUDE_GUARD_GUARD_NAME_CREATOR_HPP