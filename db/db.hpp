#ifndef DB_HPP
#define DB_HPP

#include <string>
#include <unordered_map>

using namespace std;

typedef struct {
    string url;
    string created_at;
} ShortenedURL;

class Database {
  public:
    string getUrlById(string id);
    bool   insertShortenedUrl(string id, ShortenedURL url);
    void   deleteShortenedUrl(string id);

  private:
    unordered_map<string, ShortenedURL> database;
};

#endif
