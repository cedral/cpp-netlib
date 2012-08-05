//            Copyright (c) Glyn Matthews 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <network/uri/uri_io.hpp>
#include <network/uri/uri.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <iterator>


namespace network {
std::ostream &operator << (std::ostream &os, const uri &uri_) {
    return os << uri_.string();
}


std::ostream &operator << (std::ostream &os, const uri::scheme_range &scheme) {
	boost::copy(scheme, std::ostream_iterator<uri::value_type>(os));
	return os;
}

std::ostream &operator << (std::ostream &os, const uri::user_info_range &user_info) {
	boost::copy(user_info, std::ostream_iterator<uri::value_type>(os));
	return os;
}

std::ostream &operator << (std::ostream &os, const uri::host_range &host) {
	boost::copy(host, std::ostream_iterator<uri::value_type>(os));
	return os;
}

std::ostream &operator << (std::ostream &os, const uri::port_range &port) {
	boost::copy(port, std::ostream_iterator<uri::value_type>(os));
	return os;
}

std::ostream &operator << (std::ostream &os, const uri::path_range &path) {
	boost::copy(path, std::ostream_iterator<uri::value_type>(os));
	return os;
}

std::ostream &operator << (std::ostream &os, const uri::query_range &query) {
	boost::copy(query, std::ostream_iterator<uri::value_type>(os));
	return os;
}

std::ostream &operator << (std::ostream &os, const uri::fragment_range &fragment) {
	boost::copy(fragment, std::ostream_iterator<uri::value_type>(os));
	return os;
}
} // namespace network

