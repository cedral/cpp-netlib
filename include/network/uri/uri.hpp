// Copyright 2009-2012 Dean Michael Berris, Jeroen Habraken, Glyn Matthews.
// Copyright 2012 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef NETWORK_URI_INC
#define NETWORK_URI_INC


#include <network/uri/config.hpp>
#include <network/uri/detail/uri_parts.hpp>
#include <network/uri/detail/ranges.hpp>
#include <network/uri/schemes.hpp>
#include <boost/utility/swap.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/as_literal.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/functional/hash_fwd.hpp>

namespace network {
  namespace detail {
    bool parse(std::string::const_iterator first,
               std::string::const_iterator last,
               uri_parts<std::string::const_iterator> &parts);
  } // namespace detail


  class uri {

    friend class builder;

  public:

    typedef char value_type;
    typedef std::basic_string<value_type> string_type;
    typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_type;
    typedef string_type::const_iterator const_iterator;

    typedef detail::scheme_range<const_iterator> scheme_range;
    typedef detail::user_info_range<const_iterator> user_info_range;
    typedef detail::host_range<const_iterator> host_range;
    typedef detail::port_range<const_iterator> port_range;
    typedef detail::path_range<const_iterator> path_range;
    typedef detail::query_range<const_iterator> query_range;
    typedef detail::fragment_range<const_iterator> fragment_range;

    uri()
      : is_valid_(false) {

    }

    uri(const string_type &uri)
      : uri_(uri), is_valid_(false) {
      parse();
    }

    template <
      class FwdIter
      >
      uri(const FwdIter &first, const FwdIter &last)
      : uri_(first, last), is_valid_(false) {
      parse();
    }

    uri(const uri &other)
      : uri_(other.uri_) {
      parse();
    }

    uri(uri &&other)
      : uri_(std::move(other.uri_))
      , uri_parts_(std::move(other.uri_parts_))
      , is_valid_(std::move(other.is_valid_)) {

    }

    uri &operator = (const uri &other) {
      uri_ = other.uri_;
      parse();
      return *this;
    }

    uri &operator = (const string_type &uri_string) {
      uri_ = uri_string;
      parse();
      return *this;
    }

    ~uri() {

    }

    void swap(uri &other) {
      std::swap(uri_, other.uri_);
      std::swap(uri_parts_, other.uri_parts_);
      std::swap(is_valid_, other.is_valid_);
    }

    const_iterator begin() const {
      return uri_.begin();
    }

    const_iterator end() const {
      return uri_.end();
    }

    scheme_range scheme() const {
      return scheme_range(std::begin(uri_parts_.scheme), std::end(uri_parts_.scheme));
    }

    user_info_range user_info() const {
      return uri_parts_.hier_part.user_info?
        user_info_range(std::begin(uri_parts_.hier_part.user_info.get()),
                        std::end(uri_parts_.hier_part.user_info.get()))
        : user_info_range();
    }

    host_range host() const {
      return uri_parts_.hier_part.host?
        host_range(std::begin(uri_parts_.hier_part.host.get()),
                   std::end(uri_parts_.hier_part.host.get()))
        : host_range();
    }

    port_range port() const {
      return uri_parts_.hier_part.port?
        port_range(std::begin(uri_parts_.hier_part.port.get()),
                   std::end(uri_parts_.hier_part.port.get()))
        : port_range();
    }

    path_range path() const {
      return uri_parts_.hier_part.path?
        path_range(std::begin(uri_parts_.hier_part.path.get()),
                   std::end(uri_parts_.hier_part.path.get()))
        : path_range();
    }

    query_range query() const {
      return uri_parts_.query ?
        query_range(std::begin(uri_parts_.query.get()),
                    std::end(uri_parts_.query.get()))
        : query_range();
    }

    fragment_range fragment() const {
      return uri_parts_.fragment?
        fragment_range(std::begin(uri_parts_.fragment.get()),
                       std::end(uri_parts_.fragment.get()))
        : fragment_range();
    }

    const string_type &native() const {
      return uri_;
    }

    const value_type *c_str() const {
      return uri_.c_str();
    }

    std::string string(const codecvt_type &cvt = codecvt()) const {
      return uri_;
    }

    std::wstring wstring(const codecvt_type &cvt = codecvt()) const {
      return std::wstring(std::begin(uri_), std::end(uri_));
    }

    bool is_valid() const {
      return is_valid_;
    }

    // encoding conversion
    static std::locale imbue(const std::locale& loc);

    static const codecvt_type &codecvt();

  private:

    void parse();

    string_type uri_;
    detail::uri_parts<const_iterator> uri_parts_;
    bool is_valid_;

  };

  inline
  void uri::parse() {
    auto first(std::begin(uri_)), last(std::end(uri_));
    is_valid_ = detail::parse(first, last, uri_parts_);
    if (is_valid_) {
      if (!uri_parts_.scheme) {
        uri_parts_.scheme = scheme_range(std::begin(uri_),
                                         std::begin(uri_));
      }
      uri_parts_.update();
    }
  }

  inline
  uri::string_type scheme(const uri &uri_) {
    auto range = uri_.scheme();
    return range? uri::string_type(std::begin(range), std::end(range)) : uri::string_type();
  }

  inline
  uri::string_type user_info(const uri &uri_) {
    auto range = uri_.user_info();
    return range? uri::string_type(std::begin(range), std::end(range)) : uri::string_type();
  }

  inline
  uri::string_type host(const uri &uri_) {
    auto range = uri_.host();
    return range? uri::string_type(std::begin(range), std::end(range)) : uri::string_type();
  }

  inline
  uri::string_type port(const uri &uri_) {
    auto range = uri_.port();
    return range? uri::string_type(std::begin(range), std::end(range)) : uri::string_type();
  }

  inline
  boost::optional<unsigned short> port_us(const uri &uri_) {
    auto value = port(uri_);
    return (value.empty())?
      boost::optional<unsigned short>() :
      boost::optional<unsigned short>(boost::lexical_cast<unsigned short>(value));
  }

  inline
  uri::string_type path(const uri &uri_) {
    auto range = uri_.path();
    return range? uri::string_type(std::begin(range), std::end(range)) : uri::string_type();
  }

  inline
  uri::string_type query(const uri &uri_) {
    auto range = uri_.query();
    return range? uri::string_type(std::begin(range), std::end(range)) : uri::string_type();
  }

  inline
  uri::string_type fragment(const uri &uri_) {
    auto range = uri_.fragment();
    return range? uri::string_type(std::begin(range), std::end(range)) : uri::string_type();
  }

  inline
  uri::string_type hierarchical_part(const uri &uri_) {
    return uri::string_type(std::begin(uri_.user_info()),
                            std::end(uri_.path()));
  }

  inline
  uri::string_type authority(const uri &uri_) {
    return uri::string_type(std::begin(uri_.user_info()),
                            std::end(uri_.port()));
  }

  inline
  bool valid(const uri &uri_) {
    return uri_.is_valid();
  }

  inline
  bool is_absolute(const uri &uri_) {
    return uri_.is_valid() && !boost::empty(uri_.scheme());
  }

  inline
  bool is_relative(const uri &uri_) {
    return uri_.is_valid() && boost::empty(uri_.scheme());
  }

  inline
  bool is_hierarchical(const uri &uri_) {
    return is_absolute(uri_) && hierarchical_schemes::exists(scheme(uri_));
  }

  inline
  bool is_opaque(const uri &uri_) {
    return is_absolute(uri_) && opaque_schemes::exists(scheme(uri_));
  }

  inline
  bool is_valid(const uri &uri_) {
    return valid(uri_);
  }

  inline
  void swap(uri &lhs, uri &rhs) {
    lhs.swap(rhs);
  }

  inline
  std::size_t hash_value(const uri &uri_) {
    std::size_t seed = 0;
    boost::for_each(uri_, [&seed] (uri::value_type c)
		    { boost::hash_combine(seed, c); });
    return seed;
  }

  bool operator == (const uri &lhs, const uri &rhs);

  inline
  bool operator == (const uri &lhs, const uri::string_type &rhs) {
    return lhs == uri(rhs);
  }

  inline
  bool operator == (const uri::string_type &lhs, const uri &rhs) {
    return uri(lhs) == rhs;
  }

  inline
  bool operator == (const uri &lhs, const uri::value_type *rhs) {
    return lhs == uri(rhs);
  }

  inline
  bool operator == (const uri::value_type *lhs, const uri &rhs) {
    return uri(lhs) == rhs;
  }

  inline
  bool operator != (const uri &lhs, const uri &rhs) {
    return !(lhs == rhs);
  }

  inline
  bool operator < (const uri &lhs, const uri &rhs) {
    return lhs.string() < rhs.string();
  }
} // namespace network

#include <network/uri/accessors.hpp>
#include <network/uri/builder.hpp>
#include <network/uri/normalize.hpp>

namespace network {
  inline
  uri from_parts(const uri &base_uri,
                 const uri::string_type &path_,
                 const uri::string_type &query_,
                 const uri::string_type &fragment_) {
    uri uri_(base_uri);
    builder(uri_).path(path_).query(query_).fragment(fragment_);
    return uri_;
  }

  inline
  uri from_parts(const uri &base_uri,
                 const uri::string_type &path_,
                 const uri::string_type &query_) {
    uri uri_(base_uri);
    builder(uri_).path(path_).query(query_);
    return uri_;
  }

  inline
  uri from_parts(const uri &base_uri,
                 const uri::string_type &path_) {
    uri uri_(base_uri);
    builder(uri_).path(path_);
    return uri_;
  }

  inline
  uri from_parts(const uri::string_type &base_uri,
                 const uri::string_type &path,
                 const uri::string_type &query,
                 const uri::string_type &fragment) {
    return from_parts(uri(base_uri), path, query, fragment);
  }

  inline
  uri from_parts(const uri::string_type &base_uri,
                 const uri::string_type &path,
                 const uri::string_type &query) {
    return from_parts(uri(base_uri), path, query);
  }

  inline
  uri from_parts(const uri::string_type &base_uri,
                 const uri::string_type &path) {
    return from_parts(uri(base_uri), path);
  }
} // namespace network

#include <boost/filesystem/path.hpp>

namespace network {
  inline
  uri from_file(const boost::filesystem::path &path_) {
    uri uri_;
    builder(uri_).scheme("file").path(path_.string());
    return uri_;
  }
} // namespace network


#endif // NETWORK_URI_INC
