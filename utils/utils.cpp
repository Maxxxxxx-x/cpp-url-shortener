#include <chrono>
#include <iomanip>
#include <regex>
#include <string>

#include "utils.hpp"

bool isValidUrl(string url) {
    const regex pattern(
        "((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
    if (url.empty()) {
        return false;
    }

    if (!regex_match(url, pattern)) {
        return false;
    }

    return true;
}

string generateUID(const int len) {
    static const char characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string tmp;
    tmp.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp += characters[rand() % (sizeof(characters) - 1)];
    }

    return tmp;
}

string getTimestamp() {
    const auto ms = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
    const auto sec = chrono::time_point_cast<chrono::seconds>(ms);
    const auto milis = ms - sec;
    const auto c_now = chrono::system_clock::to_time_t(sec);

    stringstream strstream;
    strstream << put_time(gmtime(&c_now), "%FT%T") << '.' << setfill('0') << setw(3) << milis.count() << 'Z';

    return strstream.str();
}
