//            Copyright (c) Glyn Matthews 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


# include <network/uri/normalize.hpp>
# include <vector>
# include <stack>
# include <boost/algorithm/string/split.hpp>
# include <boost/algorithm/string/join.hpp>
# include <boost/algorithm/string/predicate.hpp>
# include <boost/algorithm/string/classification.hpp>
# include <boost/algorithm/string/case_conv.hpp>
# include <boost/range/as_literal.hpp>
# include <boost/range/algorithm_ext/erase.hpp>
# include <boost/range/algorithm/for_each.hpp>

namespace network {
  uri::string_type normalize(const uri::scheme_range &scheme) {
    using namespace boost::algorithm;

    uri::string_type normalized_scheme(std::begin(scheme), std::end(scheme));
    to_lower<uri::string_type>(normalized_scheme);
    return std::move(normalized_scheme);
  }

  uri::string_type normalize(const uri::user_info_range &user_info) {
    return uri::string_type(std::begin(user_info), std::end(user_info));
  }

  uri::string_type normalize(const uri::host_range &host) {
    using namespace boost::algorithm;

    uri::string_type normalized_host(std::begin(host), std::end(host));
    to_lower<uri::string_type>(normalized_host);
    return std::move(normalized_host);
  }

  uri::string_type normalize(const uri::port_range &port) {
    return uri::string_type(std::begin(port), std::end(port));
  }

  uri::string_type normalize(const uri::path_range &path) {
    using namespace boost;
    using namespace boost::algorithm;

    // add trailing /
    if (empty(path)) {
      return uri::string_type("/");
    }

    std::vector<uri::string_type> path_segments;
    split(path_segments, path, is_any_of("/"));

    // remove single dot segments
    remove_erase_if(path_segments, [] (const uri::string_type &s) {
        return equal(s, boost::as_literal("."));
      });

    // remove double dot segments
    std::vector<std::string> normalized_segments;
    auto depth = 0;
    for_each(path_segments, [&normalized_segments, &depth] (const uri::string_type &s) {
        assert(depth >= 0);
        if (equal(s, boost::as_literal(".."))) {
          normalized_segments.pop_back();
        }
        else {
          normalized_segments.push_back(s);
        }
      });

    if (!empty(normalized_segments.back()) &&
        !contains(normalized_segments.back(), as_literal("."))) {
      normalized_segments.push_back(uri::string_type());
    }

    return join(normalized_segments, "/");
  }

  uri::string_type normalize(const uri::query_range &query) {
    return uri::string_type(std::begin(query), std::end(query));
  }

  uri::string_type normalize(const uri::fragment_range &fragment) {
    return uri::string_type(std::begin(fragment), std::end(fragment));
  }

  uri normalize(const uri &uri_) {
    uri normalized_uri;
    builder(normalized_uri)
      .scheme(normalize(uri_.scheme()))
      .user_info(normalize(uri_.user_info()))
      .host(normalize(uri_.host()))
      .port(normalize(uri_.port()))
      .path(normalize(uri_.path()))
      .query(normalize(uri_.query()))
      .fragment(normalize(uri_.fragment()))
      ;
    return std::move(normalized_uri);
  }
} // namespace network
