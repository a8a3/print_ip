#include <gtest/gtest.h>

#include <vector>
#include <list>
#include <forward_list>
#include <tuple>

#include "print_ip.hpp"


// ------------------------------------------------------------------
TEST(IPtoStringTest, are_same_test) {
    static_assert(are_same(),      "no type is not same");
    static_assert(are_same<int>(), "one int type is not same" );
    static_assert(are_same<int, int>(), "int, int types are not same" );
    static_assert(are_same<int, int, int>(), "int, int, int types are not same" );
    static_assert(!are_same<float, int>(), "float, int types are same" );
    static_assert(!are_same<int, int, int, float>(), "int, int, int, float types are same" );
}

// ------------------------------------------------------------------
TEST(IPtoStringTest, IPtoStringTest) {
    ASSERT_EQ(ip_to_string<int32_t>(0xFF'FF'FF'FF), "255.255.255.255");
    ASSERT_EQ(ip_to_string<int32_t>(0x00'00'00'FF), "0.0.0.255");
    ASSERT_EQ(ip_to_string<int32_t>(0xFF'00'00'00), "255.0.0.0");

    ASSERT_EQ(ip_to_string<int32_t>(0x7F'00'00'01), "127.0.0.1");
    
    ASSERT_EQ(ip_to_string<uint16_t>(0xFF'00), "255.0");
    ASSERT_EQ(ip_to_string<uint16_t>(0x00'FF), "0.255");

    ASSERT_EQ(ip_to_string(true),  "1");
    ASSERT_EQ(ip_to_string(false), "0");

    ASSERT_EQ(ip_to_string<char>(-1),                  "255");
    ASSERT_EQ(ip_to_string<short>(0),                  "0.0");
    ASSERT_EQ(ip_to_string<int>(2130706433),           "127.0.0.1");
    ASSERT_EQ(ip_to_string<long>(8875824491850138409), "123.45.67.89.101.112.131.41");
    
    std::string localhost{"127.0.0.1"};
    ASSERT_EQ(ip_to_string(localhost), "127.0.0.1");
    
    ASSERT_EQ(ip_to_string(std::string{"127.0.0.1"}), "127.0.0.1");
        
    std::vector<int> v_ip{127, 0, 0, 1};
    ASSERT_EQ(ip_to_string(v_ip), "127.0.0.1");

    std::list<int> l_ip{127, 0, 0, 1};
    ASSERT_EQ(ip_to_string(l_ip), "127.0.0.1");

    std::forward_list<int> fl_ip{127, 0, 0, 1};
    ASSERT_EQ(ip_to_string(fl_ip), "127.0.0.1");

    std::tuple<int, int, int, int> t{127, 0, 0, 1};
    ASSERT_EQ(ip_to_string(t), "127.0.0.1");

 // std::tuple<int, int, int, float> t1{127, 0, 0, 1.5};
 // ASSERT_EQ(ip_to_string(t1), "127.0.0.1");
}

// ------------------------------------------------------------------
int main( int argc, char* argv[] ) {
    testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}