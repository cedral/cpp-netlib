// Copyright (c) Glyn Matthews 2012.
// Copyright 2012 Dean Michael Berris <dberris@google.com>
// Copyright 2012 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef NETWORK_URI_BUILDER_INC
#define NETWORK_URI_BUILDER_INC

#include <boost/asio/ip/address.hpp>

namespace network {
  class builder {

  public:

    builder(uri &uri_)
      : uri_(uri_) {

    }

    builder &scheme(const std::string &scheme) {
      uri_.uri_.append(std::begin(scheme), std::end(scheme));
      if (opaque_schemes::exists(scheme)) {
        uri_.uri_.append(opaque_separator());
      }
      else {
        uri_.uri_.append(hierarchical_separator());
      }
      uri_.parse();
      return *this;
    }

	builder &scheme(const std::wstring &scheme) {
		return this->scheme(std::string(std::begin(scheme), std::end(scheme)));
	}

    builder &user_info(const std::string &user_info) {
      uri_.uri_.append(std::begin(user_info), std::end(user_info));
      uri_.uri_.append(user_info_separator());
      uri_.parse();
      return *this;
    }

	builder &user_info(const std::wstring &user_info) {
		return this->user_info(std::string(std::begin(user_info), std::end(user_info)));
	}

    builder &host(const std::string &host) {
      uri_.uri_.append(std::begin(host), std::end(host));
      uri_.parse();
      return *this;
    }

	builder &host(const std::wstring &host) {
		return this->host(std::string(std::begin(host), std::end(host)));
	}

    builder &host(const boost::asio::ip::address &host) {
      this->host(host.to_string());
      return *this;
    }

    builder &host(const boost::asio::ip::address_v4 &host) {
      this->host(host.to_string());
      return *this;
    }

    builder &host(const boost::asio::ip::address_v6 &host) {
      //uri_.uri_.append("[");
      //uri_.uri_.append(host.to_string());
      //uri_.uri_.append("]");
      //uri_.parse();
      return *this;
    }

    builder &port(const std::string &port) {
      uri_.uri_.append(port_separator());
      uri_.uri_.append(std::begin(port), std::end(port));
      uri_.parse();
      return *this;
    }

	builder &port(const std::wstring &port) {
		return this->port(std::string(std::begin(port), std::end(port)));
	}

    builder &port(uint16_t port) {
      return this->port(boost::lexical_cast<std::string>(port));
    }

    builder &path(const std::string &path) {
      uri_.uri_.append(std::begin(path), std::end(path));
      uri_.parse();
      return *this;
    }

	builder &path(const std::wstring &path) {
		return this->path(std::string(std::begin(path), std::end(path)));
	}

    builder &encoded_path(const std::string &path) {
      std::string encoded_path;
      encode(path, std::back_inserter(encoded_path));
      return this->path(encoded_path);
    }

    builder &query(const std::string &query) {
      uri_.uri_.append(query_begin_separator());
      uri_.uri_.append(std::begin(query), std::end(query));
      uri_.parse();
      return *this;
    }

	builder &query(const std::wstring &query) {
		return this->query(std::string(std::begin(query), std::end(query)));
	}

    builder &query(const std::string &key, const std::string &value) {
      if (!uri_.query()) {
      	uri_.uri_.append(query_begin_separator());
      }
      else {
      	uri_.uri_.append(query_separator());
      }
      uri_.uri_.append(std::begin(key), std::end(key));
      uri_.uri_.append(query_value_separator());
      uri_.uri_.append(std::begin(value), std::end(value));
      uri_.parse();
      return *this;
    }

    builder &fragment(const std::string &fragment) {
      uri_.uri_.append(fragment_separator());
      uri_.uri_.append(std::begin(fragment), std::end(fragment));
      uri_.parse();
      return *this;
    }

	builder &fragment(const std::wstring &fragment) {
		return this->fragment(std::string(std::begin(fragment), std::end(fragment)));
	}

  private:

    static const uri::string_type &opaque_separator() {
# if defined(BOOST_WINDOWS)
      static uri::string_type v = L":";
# else
      static uri::string_type v = ":";
# endif // defined(BOOST_WINDOWS)
      return v;
    }

    static const uri::string_type &hierarchical_separator() {
# if defined(BOOST_WINDOWS)
      static uri::string_type v = L"://";
# else
      static uri::string_type v = "://";
# endif // defined(BOOST_WINDOWS)
      return v;
    }

    static const uri::string_type &user_info_separator() {
# if defined(BOOST_WINDOWS)
      static uri::string_type v = L"@";
# else
      static uri::string_type v = "@";
# endif // defined(BOOST_WINDOWS)
      return v;
    }

    static const uri::string_type &port_separator() {
# if defined(BOOST_WINDOWS)
      static uri::string_type v = L":";
# else
      static uri::string_type v = ":";
# endif // defined(BOOST_WINDOWS)
      return v;
    }

    static const uri::string_type &query_begin_separator() {
# if defined(BOOST_WINDOWS)
      static uri::string_type v = L"?";
# else
      static uri::string_type v = "?";
# endif // defined(BOOST_WINDOWS)
      return v;
    }

    static const uri::string_type &query_separator() {
# if defined(BOOST_WINDOWS)
      static uri::string_type v = L"&";
# else
      static uri::string_type v = "&";
# endif // defined(BOOST_WINDOWS)
      return v;
    }

    static const uri::string_type &query_value_separator() {
# if defined(BOOST_WINDOWS)
      static uri::string_type v = L"=";
# else
      static uri::string_type v = "=";
# endif // defined(BOOST_WINDOWS)
      return v;
    }

    static const uri::string_type &fragment_separator() {
# if defined(BOOST_WINDOWS)
      static uri::string_type v = L"#";
# else
      static uri::string_type v = "#";
# endif // defined(BOOST_WINDOWS)
      return v;
    }

    uri &uri_;

  };
} // namespace network


#endif // NETWORK_URI_BUILDER_INC
