//             Copyright 2012 Glyn Matthews.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __NETWORK_URI_DETAIL_RANGES_INC__
# define __NETWORK_URI_DETAIL_RANGES_INC__

# pragma once

namespace network {
  namespace detail {

    struct range_base {

# if defined(BOOST_WINDOWS)
      typedef wchar_t value_type;
# else
      typedef char value_type;
# endif // defined(BOOST_WINDOWS)

      typedef std::basic_string<value_type> string_type;
      typedef string_type::const_iterator iterator;
      typedef string_type::const_iterator const_iterator;

      typedef bool (range_base::*unspecified_bool_type)() const;

      range_base() {

      }

      range_base(const_iterator first, const_iterator last)
        : first_(first), last_(last) {

      }

      iterator begin() {
        return first_;
      }

      const_iterator begin() const {
        return first_;
      }

      iterator end() {
        return last_;
      }

      const_iterator end() const {
        return last_;
      }

      bool empty() const {
        return (first_ == last_);
      }

      operator unspecified_bool_type () const {
        return !empty()? &range_base::empty : nullptr;
      }

    private:

      const_iterator first_, last_;

    };

    struct scheme_range : range_base {

      scheme_range() {

      }

      scheme_range(const_iterator first, const_iterator last)
        : range_base(first, last) {

      }

    };

    struct user_info_range : range_base {

      user_info_range() {

      }

      user_info_range(const_iterator first, const_iterator last)
        : range_base(first, last) {

      }

    };

    struct host_range : range_base {

      host_range() {

      }

      host_range(const_iterator first, const_iterator last)
        : range_base(first, last) {

      }

    };

    struct port_range : range_base {

      port_range() {

      }

      port_range(const_iterator first, const_iterator last)
        : range_base(first, last) {

      }

    };

    struct path_range : range_base {

      path_range() {

      }

      path_range(const_iterator first, const_iterator last)
        : range_base(first, last) {

      }

    };

    struct query_range : range_base {

      query_range() {

      }

      query_range(const_iterator first, const_iterator last)
        : range_base(first, last) {

      }

    };

    struct fragment_range : range_base {

      fragment_range() {

      }

      fragment_range(const_iterator first, const_iterator last)
        : range_base(first, last) {

      }

    };
  } // namespace detail
} // namespace network

#endif // __NETWORK_URI_DETAIL_RANGES_INC__
