//            Copyright (c) Glyn Matthews 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE URI Normalization Test
#include <boost/config/warning_disable.hpp>
#include <boost/test/unit_test.hpp>
#include <network/uri/uri.hpp>
#include <network/uri/uri_io.hpp>

BOOST_AUTO_TEST_CASE(normalization_test) {
    network::uri uri_1("http://www.example.com/");
    network::uri uri_2("http://www.example.com/");
    BOOST_CHECK_EQUAL(uri_1, network::normalize(uri_2));
}
