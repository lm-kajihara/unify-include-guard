#include "file_traits.hpp"
#include "guard_name_creator.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
  if (argc < 3)
  {
    std::cerr << "./unify_include_guard root_directory prefix" << std::endl;
    return 1;
  }
  unify_include_guard::guard_name_creator creator(argv[2], argv[1]);
  for (auto const &path : std::filesystem::recursive_directory_iterator(argv[1]))
  {
    if (std::filesystem::is_regular_file(path))
    {
      unify_include_guard::replace(path.path(), creator.get(path.path()));
    }
  }
}