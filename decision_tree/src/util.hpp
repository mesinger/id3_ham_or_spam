#pragma once

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#else
#define popen popen
#define pclose pclose
#endif

namespace aym {

	float rateOfUpperCase(const std::string& s) {

		int len = s.length();

		auto upplinstr = [](const std::string& s) -> int {

			int res = 0;

			for (unsigned char c : s) {
				if (isupper(c)) {
					res++;
				}
			}

			return res;
		};

		return (float)upplinstr(s) / len;
	}

	float rateOfDigits(const std::string& s) {

		int len = s.length();

		auto diginstr = [](const std::string& s) -> int {

			int res = 0;

			for (unsigned char c : s)
				if(isdigit(c)) res++ ;

			return res;
		};

		return (float)diginstr(s) / len;
	}

	bool containsUrl(const std::string& s) {

		std::vector<std::string> toplevelDomains = { ".com", ".org", ".uk", ".net", ".ca", ".de", ".us", ".edu", ".ly", ".biz" };

		return contains(toplevelDomains, s);
	}	
	
	bool containsCurrencySymbol(const std::string& s) {

		std::vector<std::string> currencies = { "$", "USD", "€", "EUR", "£", "GBP", "¥", "YEN", "HKD"};

		return contains(currencies, s);
	}

	bool contains(const std::vector<std::string>& patterns, const std::string& s) {

		for (const auto& pattern : patterns) {

			if (s.find(pattern) != std::string::npos)
				return true;
		}

		return false;
	}
}

namespace sh {

	std::string exec(const char* cmd) {
		std::array<char, 128> buffer;
		std::string result;
		std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
		if (!pipe) {
			throw std::runtime_error("popen() failed!");
		}
		while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
			result += buffer.data();
		}
		return result;
	}

	std::string aym(
		const std::string& mode, // upp or dig
		const std::string& msg
	) {

		std::string cmd = "aym " + mode + " " + msg;
		return exec(cmd.c_str());
	}
}
