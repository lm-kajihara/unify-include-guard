#ifndef UNIFY_INCLUDE_GUARD_FILE_TRAITS
#define UNIFY_INCLUDE_GUARD_FILE_TRAITS
#include "guard_name_creator.hpp"
#include "utility.hpp"
#include <fstream>
#include <optional>
#include <regex>
#include <sstream>
#include <variant>

namespace unify_include_guard
{
  namespace impl
  {
    bool replace_pragma_once(fs::path const &path, std::string const &guard_name);
    bool replace_ifndef_guard(fs::path const &path, std::string const &guard_name);
  } // namespace impl
  void replace(fs::path const &path, std::string const &guard_name);
} // namespace unify_include_guard

#endif //UNIFY_INCLUDE_GUARD_FILE_TRAITS