#ifndef JSON_HPP
#define JSON_HPP
#include <iostream>
#include <map>
#include <vector>
#include <string>

namespace nlohmann {
    struct json {
        std::map<std::string, std::string> data;
        struct Entry {
            std::string& ref;
            void operator=(int v) { ref = std::to_string(v); }
            void operator=(const std::vector<int>& v) {
                ref = "[";
                for(size_t i=0; i<v.size(); ++i) ref += std::to_string(v[i]) + (i+1==v.size()?"":",");
                ref += "]";
            }
        };
        Entry operator[](std::string k) { return {data[k]}; }
        std::string dump(int) {
            std::string s = "{\n";
            for(auto it = data.begin(); it != data.end(); ++it) {
                s += "  \"" + it->first + "\": " + it->second;
                auto next_it = it; ++next_it;
                if(next_it != data.end()) s += ",";
                s += "\n";
            }
            return s + "}";
        }
    };
}
#endif
