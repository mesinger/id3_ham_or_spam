#include <iostream>
#include "util.hpp"
#include "rapidcsv.h"
#include "sms.hpp"
#include "frequencytable.hpp"
#include <map>

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
		sms.setAnalyzedValue("free", aym::contains({"free", "Free", "FREE"}, sms.getMessage()) ? 1.f : 0.f);
	}

	SMSList list = messages;

	std::vector<std::string> classifications = { "upper", "digit", "url", "currency", "free" };

	std::map<std::string, FrequencyTable> ftables;
	
	for (const auto& classification : classifications) {
		ftables[classification] = FrequencyTable(classification);
	}

	std::map<std::string, float> averages;

	for (const auto& classification : classifications) {
		averages[classification] = list.avgOf(classification);
	}

	for (const auto& classification : classifications) {
		
		
	}

	return EXIT_SUCCESS;
}