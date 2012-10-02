// Copyright 2009-2012 Dean Michael Berris, Jeroen Habraken, Glyn Matthews.
// Copyright 2012 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef NETWORK_URI_INC
#define NETWORK_URI_INC

#include <network/uri/config.hpp>
#include <network/uri/detail/uri_parts.hpp>
#include <network/uri/schemes.hpp>
#include <boost/utility/swap.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/range/algorithm/copy.hpp>
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

    typedef std::string string_type;
    typedef string_type::value_type value_type;
    typedef string_type::const_iterator const_iterator;
    typedef boost::iterator_range<const_iterator> const_range_type;

	struct scheme_type
		: boost::iterator_range<const_iterator> {

		scheme_type() {

		}

		scheme_type(const_iterator first, const_iterator last)
			: boost::iterator_range<const_iterator>(first, last) {

		}

		scheme_type(boost::iterator_range<const_iterator> range)
			: boost::iterator_range<const_iterator>(range) {

		}

	};

	struct user_info_type
		: boost::iterator_range<const_iterator> {

		user_info_type() {

		}

		user_info_type(const_iterator first, const_iterator last)
			: boost::iterator_range<const_iterator>(first, last) {

		}

		user_info_type(boost::iterator_range<const_iterator> range)
			: boost::iterator_range<const_iterator>(range) {

		}

	};

	struct host_type
		: boost::iterator_range<const_iterator> {

		host_type() {

		}

		host_type(const_iterator first, const_iterator last)
			: boost::iterator_range<const_iterator>(first, last) {

		}

		host_type(boost::iterator_range<const_iterator> range)
			: boost::iterator_range<const_iterator>(range) {

		}

	};

	struct port_type
		: boost::iterator_range<const_iterator> {

		port_type() {

		}

		port_type(const_iterator first, const_iterator last)
			: boost::iterator_range<const_iterator>(first, last) {

		}

		port_type(boost::iterator_range<const_iterator> range)
			: boost::iterator_range<const_iterator>(range) {

		}

	};

	struct path_type
		: boost::iterator_range<const_iterator> {

		path_type() {

		}

		path_type(boost::iterator_range<const_iterator> range)
			: boost::iterator_range<const_iterator>(range) {

		}

	};

	struct query_type
		: boost::iterator_range<const_iterator> {

		query_type() {

		}

		query_type(const_iterator first, const_iterator last)
			: boost::iterator_range<const_iterator>(first, last) {

		}

		query_type(boost::iterator_range<const_iterator> range)
			: boost::iterator_range<const_iterator>(range) {

		}

	};

	struct fragment_type
		: boost::iterator_range<const_iterator> {

		fragment_type() {

		}

		fragment_type(const_iterator first, const_iterator last)
			: boost::iterator_range<const_iterator>(first, last) {

		}

		fragment_type(boost::iterator_range<const_iterator> range)
			: boost::iterator_range<const_iterator>(range) {

		}

	};

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
        boost::swap(uri_, other.uri_);
        boost::swap(uri_parts_, other.uri_parts_);
        boost::swap(is_valid_, other.is_valid_);
    }

    const_iterator begin() const {
        return uri_.begin();
    }

    const_iterator end() const {
        return uri_.end();
    }

    scheme_type scheme_range() const {
        return scheme_type(uri_parts_.scheme);
    }

    user_info_type user_info_range() const {
        return uri_parts_.hier_part.user_info?
            user_info_type(uri_parts_.hier_part.user_info.get())
			: user_info_type();
    }

    host_type host_range() const {
        return uri_parts_.hier_part.host?
            host_type(uri_parts_.hier_part.host.get()) : host_type();
    }

    port_type port_range() const {
        return uri_parts_.hier_part.port?
            port_type(uri_parts_.hier_part.port.get()) : port_type();
    }

    path_type path_range() const {
        return uri_parts_.hier_part.path?
            path_type(uri_parts_.hier_part.path.get()) : path_type();
    }

    query_type query_range() const {
        return uri_parts_.query ?
            query_type(uri_parts_.query.get()) : query_type();
    }

    fragment_type fragment_range() const {
        return uri_parts_.fragment?
            fragment_type(uri_parts_.fragment.get()) : fragment_type();
    }

    string_type scheme() const {
        auto range = scheme_range();
        return range? string_type(boost::begin(range), boost::end(range)) : string_type();
    }

    string_type user_info() const {
        auto range = user_info_range();
        return range? string_type(boost::begin(range), boost::end(range)) : string_type();
    }

    string_type host() const {
        auto range = host_range();
        return range? string_type(boost::begin(range), boost::end(range)) : string_type();
    }

    string_type port() const {
        auto range = port_range();
        return range? string_type(boost::begin(range), boost::end(range)) : string_type();
    }

    string_type path() const {
        auto range = path_range();
        return range? string_type(boost::begin(range), boost::end(range)) : string_type();
    }

    string_type query() const {
        auto range = query_range();
        return range? string_type(boost::begin(range), boost::end(range)) : string_type();
    }

    string_type fragment() const {
        auto range = fragment_range();
        return range? string_type(boost::begin(range), boost::end(range)) : string_type();
    }

    string_type string() const {
        return uri_;
    }

    bool is_valid() const {
        return is_valid_;
    }

    void append(const string_type &data) {
        uri_.append(data);
        parse();
    }

    template <
        class FwdIter
        >
    void append(const FwdIter &first, const FwdIter &last) {
        uri_.append(first, last);
        parse();
    }

private:

    void parse();

    string_type uri_;
    detail::uri_parts<const_iterator> uri_parts_;
    bool is_valid_;

};

inline
void uri::parse() {
    auto first(boost::begin(uri_)), last(boost::end(uri_));
    is_valid_ = detail::parse(first, last, uri_parts_);
    if (is_valid_) {
        if (!uri_parts_.scheme) {
            uri_parts_.scheme = scheme_type(boost::begin(uri_),
											boost::begin(uri_));
        }
        uri_parts_.update();
    }
}

inline
uri::string_type scheme(const uri &uri_) {
    return uri_.scheme();
}

inline
uri::string_type user_info(const uri &uri_) {
    return uri_.user_info();
}

inline
uri::string_type host(const uri &uri_) {
    return uri_.host();
}

inline
uri::string_type port(const uri &uri_) {
    return uri_.port();
}

inline
boost::optional<unsigned short> port_us(const uri &uri_) {
    auto port = uri_.port();
    return (port.empty())?
        boost::optional<unsigned short>() :
        boost::optional<unsigned short>(boost::lexical_cast<unsigned short>(port));
}

inline
uri::string_type path(const uri &uri_) {
    return uri_.path();
}

inline
uri::string_type query(const uri &uri_) {
    return uri_.query();
}

inline
uri::string_type fragment(const uri &uri_) {
    return uri_.fragment();
}

inline
uri::string_type hierarchical_part(const uri &uri_) {
    return uri::string_type(boost::begin(uri_.user_info_range()),
                            boost::end(uri_.path_range()));
}

inline
uri::string_type authority(const uri &uri_) {
    return uri::string_type(boost::begin(uri_.user_info_range()),
                            boost::end(uri_.port_range()));
}

inline
bool valid(const uri &uri_) {
    return uri_.is_valid();
}

inline
bool is_absolute(const uri &uri_) {
    return uri_.is_valid() && !boost::empty(uri_.scheme_range());
}

inline
bool is_relative(const uri &uri_) {
    return uri_.is_valid() && boost::empty(uri_.scheme_range());
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
std::size_t hash_value(const uri &uri_)
{
    std::size_t seed = 0;
    for (auto it = boost::begin(uri_); it != boost::end(uri_); ++it) {
        boost::hash_combine(seed, *it);
    }
    return seed;
}

//inline
//bool operator == (const uri &lhs, const uri &rhs) {
//    return boost::equal(lhs, rhs);
//}

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
#include <network/uri/directives.hpp>
#include <network/uri/builder.hpp>


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
