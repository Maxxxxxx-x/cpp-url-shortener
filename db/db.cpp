#include <string>

#include "db.hpp"

string Database::getUrlById(string id) {
    auto shortened = database.find(id);
    if (shortened != database.end()) {
        return shortened->second.url;
    }
    return "";
}

bool Database::insertShortenedUrl(string id, ShortenedURL shortUrl) {
    if (shortUrl.url.empty()) {
        return false;
    }
    if (shortUrl.created_at.empty()) {
        return false;
    }

    string exists = getUrlById(id);
    if (!exists.empty()) {
        return false;
    }

    database[id] = shortUrl;

    return true;
}

void Database::deleteShortenedUrl(string id) {
    database.erase(id);
}
