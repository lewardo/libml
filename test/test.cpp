#include <iostream>
#include <vector>

#include "libml.h"

libml_using(types);

auto main() -> int {
  test();
  std::cout << TEST << std::endl;

  detail::tensor_traits<3> traits({2, 3, 4});

  std::cout << traits.size << std::endl;
  std::cout << traits.calculate_offset(1, 2, 3) << std::endl;

  return EXIT_SUCCESS;
}