//            Copyright (c) Glyn Matthews 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE URI Equality Test
#include <boost/config/warning_disable.hpp>
#include <boost/test/unit_test.hpp>
#include <network/uri/uri.hpp>
#include <network/uri/uri_io.hpp>

BOOST_AUTO_TEST_CASE(equality_test) {
    network::uri uri_1("http://www.example.com/");
    network::uri uri_2("http://www.example.com/");
    BOOST_CHECK_EQUAL(uri_1, uri_2);
}

BOOST_AUTO_TEST_CASE(equality_test_1) {
    network::uri uri_1("http://www.example.com/");
    std::string uri_2("http://www.example.com/");
    BOOST_CHECK_EQUAL(uri_1, uri_2);
}

BOOST_AUTO_TEST_CASE(equality_test_2) {
    std::string uri_1("http://www.example.com/");
    network::uri uri_2("http://www.example.com/");
    BOOST_CHECK_EQUAL(uri_1, uri_2);
}

BOOST_AUTO_TEST_CASE(equality_test_3) {
    network::uri uri_1("http://www.example.com/");
    std::string uri_2("http://www.example.com/");
    BOOST_CHECK(uri_1 == uri_2.c_str());
}

BOOST_AUTO_TEST_CASE(equality_test_4) {
    std::string uri_1("http://www.example.com/");
    network::uri uri_2("http://www.example.com/");
    BOOST_CHECK(uri_1.c_str() == uri_2);
}

BOOST_AUTO_TEST_CASE(equality_test_reordered_query) {
	network::uri uri_1("http://www.example.com/?a=1&b=2");
	network::uri uri_2("http://www.example.com/?b=2&a=1");
    BOOST_CHECK_EQUAL(uri_1, uri_2);
}

BOOST_AUTO_TEST_CASE(equality_test_capitalized_scheme) {
	network::uri uri_1("http://www.example.com/");
	network::uri uri_2("HTTP://www.example.com/");
    BOOST_CHECK_EQUAL(uri_1, uri_2);
}

BOOST_AUTO_TEST_CASE(equality_test_capitalized_host) {
	network::uri uri_1("http://www.example.com/");
	network::uri uri_2("http://WWW.EXAMPLE.COM/");
    BOOST_CHECK_EQUAL(uri_1, uri_2);
}

BOOST_AUTO_TEST_CASE(equality_test_user_info) {
    network::uri uri_1("ftp://john.doe@ftp.example.com/");
    network::uri uri_2("ftp://JOHN.DOE@ftp.example.com/");
    BOOST_CHECK_PREDICATE(std::not_equal_to<network::uri>(), (uri_1)(uri_2));
}

BOOST_AUTO_TEST_CASE(equality_test_default_http_port) {
	network::uri uri_1("http://www.example.com/");
	network::uri uri_2("http://www.example.com:80/");
    BOOST_CHECK_EQUAL(uri_1, uri_2);
}

BOOST_AUTO_TEST_CASE(equality_test_default_http_port_2) {
	network::uri uri_1("http://www.example.com:80/");
	network::uri uri_2("http://www.example.com/");
    BOOST_CHECK_EQUAL(uri_1, uri_2);
}

BOOST_AUTO_TEST_CASE(equality_test_default_https_port) {
	network::uri uri_1("https://www.example.com/");
	network::uri uri_2("https://www.example.com:443/");
    BOOST_CHECK_EQUAL(uri_1, uri_2);
}

BOOST_AUTO_TEST_CASE(equality_test_default_https_port_2) {
	network::uri uri_1("https://www.example.com:443/");
	network::uri uri_2("https://www.example.com/");
    BOOST_CHECK_EQUAL(uri_1, uri_2);
}

BOOST_AUTO_TEST_CASE(equality_test_empty_path_with_trailing_slash) {
	network::uri uri_1("http://www.example.com/");
	network::uri uri_2("http://www.example.com");
    BOOST_CHECK_EQUAL(uri_1, uri_2);
}

BOOST_AUTO_TEST_CASE(equality_test_with_single_dot_segment) {
	network::uri uri_1("http://www.example.com/./path");
	network::uri uri_2("http://www.example.com/path");
    BOOST_CHECK_EQUAL(uri_1, uri_2);
}

BOOST_AUTO_TEST_CASE(equality_test_with_double_dot_segment) {
	network::uri uri_1("http://www.example.com/1/../2/");
	network::uri uri_2("http://www.example.com/2/");
    BOOST_CHECK_EQUAL(uri_1, uri_2);
}

BOOST_AUTO_TEST_CASE(equality_test_with_trailing_slash) {
	network::uri uri_1("http://www.example.com/path/");
	network::uri uri_2("http://www.example.com/path");
    BOOST_CHECK_EQUAL(uri_1, uri_2);
}

BOOST_AUTO_TEST_CASE(equality_test_with_file_ext) {
	network::uri uri_1("http://www.example.com/filename.txt");
	network::uri uri_2("http://www.example.com/filename.txt/");
    BOOST_CHECK_PREDICATE(std::not_equal_to<network::uri>(), (uri_1)(uri_2));
}

BOOST_AUTO_TEST_CASE(inequality_test) {
    network::uri uri_1("http://www.example.com/");
    network::uri uri_2("http://www.example.com/");
	BOOST_CHECK(!(uri_1 != uri_2));
}
