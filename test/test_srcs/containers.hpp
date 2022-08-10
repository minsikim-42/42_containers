#ifndef CONTAINERS_HPP
# define CONTAINERS_HPP

# include <iostream>
# include <string.h>

#if 1
    # define NAMESPACE "STD"
    # include <stack>
    # include <vector>
    # include <map>
    namespace ft = std;
#else
    # define NAMESPACE "FT"
    # include "../../../containers/iterator.hpp"
    # include "../../../containers/map.hpp"
    // # include "../../../containers/stack.hpp"
    # include "../../../containers/tree.hpp"
    # include "../../../containers/utils.hpp"
    # include "../../../containers/vector.hpp"
#endif

void heading(std::string name);

#endif
