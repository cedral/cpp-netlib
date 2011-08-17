//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef __BOOST_NETWORK_OAUTH_CLIENT_INC__
# define __BOOST_NETWORK_OAUTH_CLIENT_INC__


# include <boost/network/protocol/http/client.hpp>

namespace boost {
namespace network {
namespace oauth {
class request : public http::client::request {

public:

    request(const std::string &uri)
        : http::client::request(uri) {

    }

};

class response : public http::client::response {

public:

    response() {

    }

    response(const http::client::response &response_)
        : http::client::response(response_) {

    }

};

class client {
public:

    response fetch_request_token(const request &request_) {
        return client_.get(request_);
    }

    response fetch_access_token(const request &request_) {
        return client_.get(request_);
    }

    response authorize_token(const request &request_) {
        return client_.get(request_);
    }

    response access_resource(const request &request_) {
        return client_.get(request_);
    }

private:

    http::client client_;

};
} // namespace oauth
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_OAUTH_CLIENT_INC__
