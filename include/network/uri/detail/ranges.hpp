//             copyright 2012 Glyn Matthews.
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
struct scheme_range
	: boost::iterator_range<FwdIter> {

	scheme_range() {

	}

	scheme_range(FwdIter first, FwdIter last)
		: boost::iterator_range<FwdIter>(first, last) {

	}

};

template <
	class FwdIter
	>
FwdIter begin(scheme_range<FwdIter> &range) {

}

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
