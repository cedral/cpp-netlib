// Copyright (c) Glyn Matthews 2012.
// Copyright 2012 Dean Michael Berris <dberris@google.com>
// Copyright 2012 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_URI_NORMALIZE_INC
#define NETWORK_URI_NORMALIZE_INC

#include <network/uri/uri.hpp>

namespace network {
uri::string_type normalize(const uri::scheme_type &scheme);

uri::string_type normalize(const uri::user_info_type &user_info);

uri::string_type normalize(const uri::host_type &host);

uri::string_type normalize(const uri::port_type &port);

uri::string_type normalize(const uri::path_type &path);

uri::string_type normalize(const uri::query_type &query);

uri::string_type normalize(const uri::fragment_type &fragment);

uri normalize(const uri &uri_);
} // namespace network

#endif // NETWORK_URI_NORMALIZE_INC
