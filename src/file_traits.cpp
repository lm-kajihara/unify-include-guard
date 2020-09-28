#include "file_traits.hpp"

namespace unify_include_guard
{
  void replace(fs::path const &path, std::string const &guard_name)
  {
    impl::replace_pragma_once(path, guard_name) ||
        impl::replace_ifndef_guard(path, guard_name);
  }
} // namespace unify_include_guard
