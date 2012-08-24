//             Copyright 2012 Glyn Matthews.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __NETWORK_URI_DETAIL_RANGES_INC__
# define __NETWORK_URI_DETAIL_RANGES_INC__

# pragma once

namespace network {
  namespace detail {
    template <
      typename FwdIter
      >
    struct range_base {

      typedef FwdIter iterator;
      typedef FwdIter const_iterator;
      typedef bool (range_base<FwdIter>::*unspecified_bool_type)() const;

      range_base() {

      }

      range_base(FwdIter first, FwdIter last)
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
        return !empty()? &range_base<FwdIter>::empty : nullptr;
      }

      //template <
      //	class String
      //	>
      //String string() const;
      //
      //std::string string() const;
      //
      //std::wstring wstring() const;
      //
      //std::u16string u16string() const;
      //
      //std::u32string u32string() const;

    private:

      FwdIter first_, last_;

    };

    template <
      typename FwdIter
      >
    struct scheme_range
      : range_base<FwdIter> {

      scheme_range() {

      }

      scheme_range(FwdIter first, FwdIter last)
        : range_base<FwdIter>(first, last) {

      }

    };

    template <
      typename FwdIter
      >
    struct user_info_range
      : range_base<FwdIter> {

      user_info_range() {

      }

      user_info_range(FwdIter first, FwdIter last)
        : range_base<FwdIter>(first, last) {

      }

    };

    template <
      typename FwdIter
      >
    struct host_range
      : range_base<FwdIter> {

      host_range() {

      }

      host_range(FwdIter first, FwdIter last)
        : range_base<FwdIter>(first, last) {

      }

    };

    template <
      typename FwdIter
      >
    struct port_range
      : range_base<FwdIter> {

      port_range() {

      }

      port_range(FwdIter first, FwdIter last)
        : range_base<FwdIter>(first, last) {

      }

    };

    template <
      typename FwdIter
      >
    struct path_range
      : range_base<FwdIter> {

      path_range() {

      }

      path_range(FwdIter first, FwdIter last)
        : range_base<FwdIter>(first, last) {

      }

    };

    template <
      typename FwdIter
      >
    struct query_range
      : range_base<FwdIter> {

      query_range() {

      }

      query_range(FwdIter first, FwdIter last)
        : range_base<FwdIter>(first, last) {

      }

    };

    template <
      typename FwdIter
      >
    struct fragment_range
      : range_base<FwdIter> {

      fragment_range() {

      }

      fragment_range(FwdIter first, FwdIter last)
        : range_base<FwdIter>(first, last) {

      }

    };
  } // namespace detail
} // namespace network

#endif // __NETWORK_URI_DETAIL_RANGES_INC__
