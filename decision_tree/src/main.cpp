#include <iostream>
#include "util.hpp"
#include "rapidcsv.h"
#include "sms.hpp"

int main(int argc, char** argv) {

	if (argc != 2) return EXIT_FAILURE;

	rapidcsv::Document file(argv[1]);

	std::vector<AnalyzedSMS> messages;

	for (const auto& line : file.getData()) {

		messages.emplace_back(line[0], line[1]);
	}

	for (auto& sms : messages) {

		sms.setAnalyzedValue("upper", aym::rateOfUpperCase(sms.getMessage()));
		sms.setAnalyzedValue("digit", aym::rateOfDigits(sms.getMessage()));
		sms.setAnalyzedValue("url", aym::containsUrl(sms.getMessage()) ? 1.f : 0.f);
		sms.setAnalyzedValue("currency", aym::containsCurrencySymbol(sms.getMessage()) ? 1.f : 0.f);
	}



	return EXIT_SUCCESS;
}