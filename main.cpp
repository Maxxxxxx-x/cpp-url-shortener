#include "db/db.hpp"
#include "utils/utils.hpp"
#include <crow.h>
#include <crow/common.h>

#define PORT 8080
#define APP_URL "http://localhost"
#define UID_LENGTH 10

int main() {
    using namespace std;

    crow::SimpleApp app;
    Database        db;
    app.route_dynamic("/").methods("GET"_method)(
        [](const crow::request &req) { return crow::mustache::load_text("index.html"); });

    app.route_dynamic("/r/<string>")
        .methods("GET"_method)([&](const crow::request &req, crow::response &res, string id) {
            if (id.compare("shorten") == 0) {
                res = crow::response(crow::FOUND);
                res.redirect("/shorten");
                res.end();
                return;
            }

            string url = db.getUrlById(id);
            if (url.empty() || url.length() == 0) {
                res = crow::response(crow::NOT_FOUND);
                res.write("Not found");
                res.end();
                return;
            }

            res = crow::response(crow::FOUND);
            res.redirect(url);
            res.end();
            return;
        });

    app.route_dynamic("/shorten").methods("GET"_method)([](const crow::request &req) {
        return crow::mustache::load_text("shorten.html");
    });

    app.route_dynamic("/shorten").methods("POST"_method)([&](const crow::request &req, crow::response &res) {
        auto reqBody = crow::json::load(req.body);
        if (!reqBody) {
            crow::json::wvalue resJson({{"err_msg", "Invalid or Missing request body"}});
            res = crow::response(crow::BAD_REQUEST);
            res.write(resJson.dump());
            res.end();
            return resJson;
        }
        string url = reqBody["url"].s();

        std::ostringstream os;
        os << url;

        string       uid = generateUID(UID_LENGTH);
        ShortenedURL shortUrl;
        shortUrl.url = os.str();
        shortUrl.created_at = getTimestamp();

        db.insertShortenedUrl(uid, shortUrl);

        char newUrl[1024];
        sprintf(newUrl, "%s:%s/r/%s", APP_URL, to_string(PORT).c_str(), uid.c_str());

        CROW_LOG_INFO << "Generated " << newUrl << " for " << url;

        crow::json::wvalue resJson({{"shortened_url", newUrl}});
        res = crow::response(crow::OK);
        res.write(resJson.dump());
        res.end();
        return resJson;
    });

    app.port(PORT).multithreaded().run();
    return 0;
}
