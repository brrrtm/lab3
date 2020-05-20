#pragma once
#include "json/json.h"
#include "json/value.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class JsonKey {
public:
	vector<char> alphabet = {' ', 'a','b','c','d', 'e','f', 'g','h', 'i','j', 'k','l', 'm','n', 'o','p', 'q','r', 
		's','t', 'u','v', 'w','x', 'y','z'};
	JsonKey();
	JsonKey(string);
	string get_type();
	void get_text(string);
	void load_en_text(string);
	string get_dec_text();
	string get_en_text();
	void set_dec_text(string);
	void set_en_text(string);
	void set_type(string);
	void get_dec_text_from_file(string);
	~JsonKey();
private:
	string type;
	string encrypted;
	string decrypted;
};

class JsonChangeKey : public JsonKey{
public:
	JsonChangeKey();
	JsonChangeKey(string);
	void generate_key();
	void code();
	void decode();
	bool is_keys_generated();
	bool check_alr(vector<char>, char);
	~JsonChangeKey();
private:
	Json::Value get_key_arguments();
	void save_key();
	void save_encrypt();
	void save_decrypt();
	vector<pair<char, char>> key;
};

class JsonTransposKey : public JsonKey{
public:
	JsonTransposKey();
	JsonTransposKey(string);
	Json::Value get_key_arguments();
	void generate_key();
	void code();
	void decode();
	bool is_keys_generated();
	bool check_alr(vector<int>, int);
	~JsonTransposKey();
private:
	void save_key();
	void save_encrypt();
	void save_decrypt();
	vector<pair<int, int>> key;
};

class Gamma : public JsonKey {
public:
	Gamma();
	Gamma(string);
	Json::Value get_key_arguments();
	void generate_key();
	void code();
	void decode();
	bool is_keys_generated();
	~Gamma();
private:
	void save_key();
	void save_encrypt();
	void save_decrypt();
	string key;
	string alphabet_g = "#abcdefghijklmnopqrstuvwxyz 0123456789";
};