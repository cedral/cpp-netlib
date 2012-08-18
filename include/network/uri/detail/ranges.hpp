//             Copyright 2012 Glyn Matthews.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __NETWORK_URI_DETAIL_RANGES_INC__
# define __NETWORK_URI_DETAIL_RANGES_INC__

# pragma once

# include <boost/range/iterator_range.hpp>

namespace network {
  namespace detail {
    template <
      typename FwdIter
      >
    struct range_base<FwdIter> {

      typedef FwdIter iterator;
      typedef FwdIter const_iterator;

      scheme_range() {

      }

      scheme_range(FwdIter first, FwdIter last)
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
      : boost::iterator_range<FwdIter> {

      scheme_range() {

      }

      scheme_range(FwdIter first, FwdIter last)
        : boost::iterator_range<FwdIter>(first, last) {

      }

    };

    template <
      typename FwdIter
      >
    struct user_info_range
      : boost::iterator_range<FwdIter> {

      user_info_range() {

      }

      user_info_range(FwdIter first, FwdIter last)
        : boost::iterator_range<FwdIter>(first, last) {

      }

    };

    template <
      typename FwdIter
      >
    struct host_range
      : boost::iterator_range<FwdIter> {

      host_range() {

      }

      host_range(FwdIter first, FwdIter last)
        : boost::iterator_range<FwdIter>(first, last) {

      }

    };

    template <
      typename FwdIter
      >
    struct port_range
      : boost::iterator_range<FwdIter> {

      port_range() {

      }

      port_range(FwdIter first, FwdIter last)
        : boost::iterator_range<FwdIter>(first, last) {

      }

    };

    template <
      typename FwdIter
      >
    struct path_range
      : boost::iterator_range<FwdIter> {

      path_range() {

      }

      path_range(FwdIter first, FwdIter last)
        : boost::iterator_range<FwdIter>(first, last) {

      }

    };

    template <
      typename FwdIter
      >
    struct query_range
      : boost::iterator_range<FwdIter> {

      query_range() {

      }

      query_range(FwdIter first, FwdIter last)
        : boost::iterator_range<FwdIter>(first, last) {

      }

    };

    template <
      typename FwdIter
      >
    struct fragment_range
      : boost::iterator_range<FwdIter> {

      fragment_range() {

      }

      fragment_range(FwdIter first, FwdIter last)
        : boost::iterator_range<FwdIter>(first, last) {

      }

    };
  } // namespace detail
} // namespace network

#endif // __NETWORK_URI_DETAIL_RANGES_INC__
