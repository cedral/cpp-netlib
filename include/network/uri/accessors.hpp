// Copyright (c) Glyn Matthews 2011, 2012.
// Copyright 2012 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef NETWORK_URI_URI_ACCESSORS_INC
#define NETWORK_URI_URI_ACCESSORS_INC


#include <network/uri/uri.hpp>
#include <network/uri/encode.hpp>
#include <network/uri/decode.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>

namespace network {
namespace details {
template <
    typename Map
    >
struct key_value_sequence
    : boost::spirit::qi::grammar<uri::const_iterator, Map()>
{
    typedef typename Map::key_type key_type;
    typedef typename Map::mapped_type mapped_type;
    typedef std::pair<key_type, mapped_type> pair_type;

    key_value_sequence()
        : key_value_sequence::base_type(query)
    {
        query =  pair >> *((boost::spirit::qi::lit(';') | '&') >> pair);
        pair  =  key >> -('=' >> value);
        key   =  boost::spirit::qi::char_("a-zA-Z_") >> *boost::spirit::qi::char_("a-zA-Z_0-9/%");
        value = +boost::spirit::qi::char_("a-zA-Z_0-9/%");
    }

    boost::spirit::qi::rule<uri::const_iterator, Map()> query;
    boost::spirit::qi::rule<uri::const_iterator, pair_type()> pair;
    boost::spirit::qi::rule<uri::const_iterator, key_type()> key;
    boost::spirit::qi::rule<uri::const_iterator, mapped_type()> value;
};
} // namespace details

template <
    class Map
    >
inline
Map &query_map(const uri &uri_, Map &map) {
    auto range = uri_.query_range();
    details::key_value_sequence<Map> parser;
    boost::spirit::qi::parse(std::begin(range), std::end(range), parser, map);
    return map;
}

inline
uri::string_type username(const uri &uri_) {
    auto user_info = uri_.user_info_range();
    auto it(std::begin(user_info)), end(std::end(user_info));
    for (; it != end; ++it) {
        if (*it == ':') {
            break;
        }
    }
    return uri::string_type(std::begin(user_info), it);
}

inline
uri::string_type password(const uri &uri_) {
    auto user_info = uri_.user_info_range();
    auto it(std::begin(user_info)), end(std::end(user_info));
    for (; it != end; ++it) {
        if (*it == ':') {
            ++it;
            break;
        }
    }
    return uri::string_type(it, std::end(user_info));
}

inline
uri::string_type decoded(const uri::path_type &path) {
	uri::string_type decoded;
	decode(path, std::back_inserter(decoded));
	return std::move(decoded);
}

inline
uri::string_type decoded(const uri::query_type &query) {
	uri::string_type decoded;
	decode(query, std::back_inserter(decoded));
	return std::move(decoded);
}

inline
uri::string_type decoded(const uri::fragment_type &fragment) {
	uri::string_type decoded;
	decode(fragment, std::back_inserter(decoded));
	return std::move(decoded);
}
} // namespace network

#endif // NETWORK_URI_URI_ACCESSORS_INC
