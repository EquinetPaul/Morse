#include "morse.hpp"

#include <iostream>
#include <string>
#include "../nlohmann/json.hpp"
using namespace std;
using json = nlohmann::json;

string convertSentence(string base, json alphabet) {
    string result;
    string id;

    for (char i : base)
    {
        id = i;
        result += alphabet[id];
        result += " ";
    }

    return result;
}