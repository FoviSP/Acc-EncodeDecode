#pragma once
#pragma once
#ifndef ENCODERDECORED_H
#define ENCODERDECORED_H

#include <fstream>
#include <vector>
#include <string>

#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <bitset>
/*
	Acceleration League Hex-Encoded Stream (ALHES)
	- зашифрований пот≥к даних, що базуЇтьс€ на ш≥стнадц€тков≥й
	систем≥ численн€.
*/
using namespace std;

class ALHES {
private:
	std::string datconv, datorignal;
	size_t fsize;
	bool enco = false;
	int hex_value(unsigned char hex_digit){
		static const signed char hex_values[256] = {
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
			-1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		};
		int value = hex_values[hex_digit];
		if (value == -1) throw std::invalid_argument("invalid hex digit");
		return value;
	}
	string ToString(const std::string& input){
		const auto len = input.length();
		if (len & 1) throw std::invalid_argument("odd length");
		std::string output;
		output.reserve(len / 2);
		for (auto it = input.begin(); it != input.end(); ){
			int hi = hex_value(*it++);
			int lo = hex_value(*it++);
			output.push_back(hi << 4 | lo);
		}
		return output;
	}
	string ToHex(const string& s, bool upper_case) {
		ostringstream ret;
		for (string::size_type i = 0; i < s.length(); ++i) {
			int z = s[i] & 0xff;
			ret << std::hex << std::setfill('0') << std::setw(2) << (upper_case ? std::uppercase : std::nouppercase) << z;
		}
		return ret.str();
	}
public:
	static const string FRMT;
	ALHES() {}
	bool read(std::string path) {
		if (path.substr(path.find_last_of('.')+1) == FRMT) {
			enco = true;
		}
		ifstream file(path, std::ios::binary);
		if (!file.is_open()) {
			return false;
		}
		fsize = file.tellg();
		if (fsize < 0) return false;
		file.seekg(0, std::ios::beg);
		datorignal = string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		if (enco) {
			datconv = ToString(datorignal);
		}else {
			datconv = ToHex(string(datorignal.begin(), datorignal.end()), datorignal.size());
		}
		file.close();
		return true;
	}
	bool xport(string path) {
		ofstream file(path, std::ios::out | std::ios::binary | std::ios::ate);
		if (!file.is_open()) return false;
		file.write(&datconv[0], datconv.size());
		file.close();
		return true;
	}
	void reset() {
		datconv = "";
		datorignal = "";
		enco = false;
		fsize = 0;
	}
	bool isEncoded() {
		return enco;
	}
	size_t size() {
		return datorignal.size();
	}
};

const string ALHES::FRMT = "alhes";
#endif