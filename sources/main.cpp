
#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <tuple>

#include "print_ip.hpp"

// ------------------------------------------------------------------
int main(int, char**) {

    std::cout << ip_to_string<char>(-1) << '\n'
              << ip_to_string<short>(0) << '\n'
              << ip_to_string<int>(2130706433) << '\n'
              << ip_to_string<long>(8875824491850138409) << std::endl;
    
    std::string localhost{"127.0.0.1"};
    std::cout << ip_to_string(localhost) << std::endl;
          
    std::vector<int> v_ip{127, 0, 0, 1};
    std::cout << ip_to_string(v_ip) << std::endl;

    std::list<int> l_ip{127, 0, 0, 1};
    std::cout << ip_to_string(l_ip) << std::endl;

    std::forward_list<int> fl_ip{127, 0, 0, 1};
    std::cout << ip_to_string(fl_ip) << std::endl;

    std::tuple<int, int, int, int> t{127, 0, 0, 1};
    std::cout << ip_to_string(t) << std::endl;

    return 0;
}