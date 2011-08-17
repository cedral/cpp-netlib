//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "client.hpp"


namespace oauth = boost::network::oauth;
namespace uri = boost::network::uri;


int
main(int argc, char *argv[]) {

    oauth::client client;
    oauth::request request("https;//photos.example.net/request_token");
    oauth::response response = client.fetch_request_token(request);

    return 0;
}
