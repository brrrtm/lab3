#include "JsonHandler.h"
#include <random>
#include <ctime>
#include <Windows.h>

JsonKey::JsonKey() {
}
JsonKey::JsonKey(string path) {
    Json::Value arg;
    ifstream file(path);
    file >> arg;
    file.close();
    type = arg["type"].asString();
}
string JsonKey::get_type()
{
    return this->type;
}
void JsonKey::get_text(string path) {
    ifstream file(path);
    while (!file.eof()) {
        getline(file, decrypted);
        decrypted += '\n';
    }
    decrypted.pop_back();
    file.close();
}
void JsonKey::load_en_text(string path) {
    Json::Value arg;
    ifstream file(path);
    file >> arg;
    file.close();
    type = arg["type"].asString();
    encrypted = arg["text"].asString();
}
string JsonKey::get_dec_text() {
    return decrypted;
}
string JsonKey::get_en_text() {
    return encrypted;
}
void JsonKey::set_dec_text(string text) {
    decrypted = text;
}
void JsonKey::set_en_text(string text) {
    encrypted = text;
}
void JsonKey::set_type(string t) {
    type = t;
}
void JsonKey::get_dec_text_from_file(string txt) {
    ifstream file(txt);
    string text;
    while (!file.eof()) {
        getline(file, text);
        text += '\n';
    }
    file.close();
    text.pop_back();
    
    decrypted = text;
}
JsonKey::~JsonKey() {};

// change

JsonChangeKey::JsonChangeKey() {
    this->set_type("change");
};
JsonChangeKey::JsonChangeKey(string path) {
    Json::Value arg;
    ifstream file(path);
    file >> arg;
    file.close();
    this->get_type() = arg["type"].asString();
    int idx = 0;
    for (Json::Value::iterator it = arg["key"].begin(); it != arg["key"].end(); it++) {
        int s1 = arg["key"][idx][0].asInt(), s2 = arg["key"][idx++][1].asInt();
        key.push_back(make_pair((char)s1, (char)s2));
    }
}
Json::Value JsonChangeKey::get_key_arguments() {
    Json::Value arg;
    arg["type"] = this->get_type();
    for (int i = 0; i < key.size(); i++) {
        arg["key"][i][0] = key[i].first;
        arg["key"][i][1] = key[i].second;
    }
    return arg;
}
void JsonChangeKey::generate_key() {
    srand(time(NULL));
    vector<char> temp_alph = alphabet;
    vector<char> alr;
    string en = get_dec_text();
    for (int i = 0; i < en.size(); i++) {
        for (int j = i + 1; j < en.size(); j++) {
            if (en[i] == en[j]) {
                en.erase(en.begin() + j);
                j--;
            }
        }
    }
    for (int i = 0; i < en.size(); i++) {
        int id = rand() % temp_alph.size();
        while (!check_alr(alr, temp_alph[id])) {
             id = rand() % temp_alph.size();
        }
        alr.push_back(temp_alph[id]);
        key.push_back(make_pair(en[i], temp_alph[id]));
    }
    save_key();
}
void JsonChangeKey::code() {
    string text = get_dec_text();
    for (int i = 0; i < text.size(); i++) {
        for (int j = 0; j < key.size(); j++) {
            if (text[i] == key[j].first) {
                text[i] = key[j].second;
                break;
            }
        }
    }
    set_en_text(text);
    save_encrypt();
}
void JsonChangeKey::decode() {
    string text = get_en_text();
    vector<pair<char, char>> k = this->key;

    for (int i = 0; i < text.size(); i++) {
        for (int j = 0; j < k.size(); j++) {
            if (text[i] == k[j].second) {
                text[i] = k[j].first;
                break;
            }
        }
    }


    set_dec_text(text);
    save_decrypt();
}
bool JsonChangeKey::is_keys_generated() {
    return !key.empty();
}
bool JsonChangeKey::check_alr(vector<char> v, char c) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == c) return false;
    }
    return true;
}
void JsonChangeKey::save_key() {
    string name = "ChangeKey.key";
    Json::Value arg = this->get_key_arguments();
    ofstream file(name);
    file << arg;
    file.close();
}
void JsonChangeKey::save_encrypt() {
    Json::Value arg;
    arg["type"] = this->get_type();
    arg["text"] = this->get_en_text();
    ofstream file("text.encrypt");
    file << arg;
    file.close();
}
void JsonChangeKey::save_decrypt() {
    ofstream file("decrypted_change.txt");
    file << this->get_dec_text();
    file.close();
}
JsonChangeKey::~JsonChangeKey() {};

// transposition

JsonTransposKey::JsonTransposKey() {
    this->set_type("transposition");
}
JsonTransposKey::JsonTransposKey(string path) {
    Json::Value arg;
    ifstream file(path);
    file >> arg;
    file.close();
    this->set_type(arg["type"].asString());
    int idx = 0;
    for (Json::Value::iterator it = arg["key"].begin(); it != arg["key"].end(); it++) {
        int s1 = arg["key"][idx][0].asInt(), s2 = arg["key"][idx++][1].asInt();
        key.push_back(make_pair(s1, s2));
    }
}
Json::Value JsonTransposKey::get_key_arguments()
{
    Json::Value arg;
    arg["type"] = this->get_type();
    for (int i = 0; i < key.size(); i++) {
        arg["key"][i][0] = key[i].first;
        arg["key"][i][1] = key[i].second;
    }
    return arg;
}
void JsonTransposKey::generate_key() {
    srand(time(NULL));
    vector<int> ks, already;
    for (int i = 0; i < get_dec_text().size(); i++) {
        ks.push_back(i);
    }
    for (int i = 0; i < get_dec_text().size() / 2; i++) {
        int id1 = rand() % ks.size();
        while (!check_alr(already, id1))
            id1 = rand() % ks.size();
        already.push_back(id1);
        int id2 = rand() % ks.size();
        while (!check_alr(already, id2))
            id2 = rand() % ks.size();
        already.push_back(id2);
        key.push_back(make_pair(id1, id2));
    }

    save_key();
}
void JsonTransposKey::code(){
    string text = get_dec_text();
    for (int i = 0; i < key.size(); i++) {
        swap(text[key[i].first], text[key[i].second]);
    }
    set_en_text(text);
    save_encrypt();
}
void JsonTransposKey::decode(){
    string text = get_en_text();
    for (int i = 0; i < key.size(); i++) {
        swap(text[key[i].second], text[key[i].first]);
    }
    set_dec_text(text);
    save_decrypt();
}
bool JsonTransposKey::is_keys_generated() {
    return !key.empty();
}
bool JsonTransposKey::check_alr(vector<int> v, int c) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == c) return false;
    }
    return true;
}
JsonTransposKey::~JsonTransposKey(){

}
void JsonTransposKey::save_key(){
    ofstream file("TransposKey.key");
    Json::Value arg = this->get_key_arguments();
    file << arg;
    file.close();
}
void JsonTransposKey::save_encrypt(){
    Json::Value arg;
    arg["type"] = this->get_type();
    arg["text"] = this->get_en_text();
    ofstream file("text.encrypt");
    file << arg;
    file.close();
}

void JsonTransposKey::save_decrypt() {
    ofstream file("dectypted_transposition.txt");
    file << this->get_dec_text();
    file.close();
}

// gamma

Gamma::Gamma() { 
    this->set_type("gamma");
}

Gamma::Gamma(string path) {
    Json::Value arg;
    ifstream file(path);
    file >> arg;
    file.close();
    this->set_type(arg["type"].asString());
    string k;
    int idx = 0;
    for (Json::Value::iterator it = arg["key"].begin(); it != arg["key"].end(); it++) {
        k += (char)(arg["key"][idx++].asInt());
    }
    this->key = k;
}

Json::Value Gamma::get_key_arguments() {
    Json::Value arg;
    arg["type"] = this->get_type();
    for (int i = 0; i < key.size(); i++) {
        arg["key"][i] = (int)key[i];
    }
    return arg;
}

void Gamma::generate_key() {
    srand(time(NULL));
    int size = rand() % 10;
    for (int i = 0; i < size; i++) {
        char ch = alphabet_g[(rand() % (alphabet_g.size() - 1)) + 1];
        key += ch;
    }

    if (key.size() == this->get_dec_text().size()) {
        save_key();
    }
    while (key.size() > this->get_dec_text().size()) {
        if (key.size() == this->get_dec_text().size()) {
            break;
        }
        key.pop_back();
    }
    if (key.size() < this->get_dec_text().size()) {
        int im = 0;
        int end = key.size();
        for (int i = 0; i < this->get_dec_text().size(); i++) {
            if (key.size() == this->get_dec_text().size()) {
                break;
            }
            key += key[im++];
            if (im == end)im = 0;
        }
    }

    save_key();
}

void Gamma::code() {
    vector<int> text_i;
    vector<int> gamma_i;
    string text = this->get_dec_text();
    for (int i = 0; i < text.size(); i++) {
        for (int j = 0; j < alphabet_g.size(); j++) {
            if (text[i] == alphabet_g[j]) text_i.push_back(j);
            if (key[i] == alphabet_g[j]) gamma_i.push_back(j);
        }
    }
    for (int i = 0; i < text.size(); i++) {
        int idx = (text_i[i] + gamma_i[i]) % alphabet_g.size();
        text[i] = alphabet_g[idx];
    }
    this->set_en_text(text);
    save_encrypt();
}

void Gamma::decode() {
    vector<int> text_i;
    vector<int> gamma_i;
    string text = this->get_en_text();
    for (int i = 0; i < text.size(); i++) {
        for (int j = 0; j < alphabet_g.size(); j++) {
            if (text[i] == alphabet_g[j]) text_i.push_back(j);
            if (key[i] == alphabet_g[j]) gamma_i.push_back(j);
        }
    }
    for (int i = 0; i < text.size(); i++) {
        if (text_i[i] == 0) text_i[i] = alphabet_g.size() - 1;
        int idx = (text_i[i] - gamma_i[i] + alphabet_g.size()) % alphabet_g.size();
        text[i] = alphabet_g[idx];
    }
    set_dec_text(text);
    save_decrypt();
}

bool Gamma::is_keys_generated() {
    return !key.empty();
}

Gamma::~Gamma() {}
void Gamma::save_key() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Json::Value arg = this->get_key_arguments();
    ofstream file("GammaKey.key");
    file << arg;
    file.close();
}

void Gamma::save_encrypt() {
    Json::Value arg;
    arg["type"] = this->get_type();
    arg["text"] = this->get_en_text();
    ofstream file("text.encrypt");
    file << arg;
    file.close();
}

void Gamma::save_decrypt() {
    ofstream file("decrypted_gamma.txt");
    file << this->get_dec_text();
    file.close();
}
