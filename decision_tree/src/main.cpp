#include <iostream>
#include "util.hpp"
#include "rapidcsv.h"
#include "sms.hpp"
#include "frequencytable.hpp"
#include <map>
#include "decisiontree.hpp"

int main(int argc, char** argv) {

	if (argc != 2) return EXIT_FAILURE;

	rapidcsv::Document file(argv[1]);

	std::vector<PAnalyzedSMS> messages;

	for (const auto& line : file.getData()) {

		messages.emplace_back(std::make_shared<AnalyzedSMS>(line[0], line[1]));
	}

	for (auto& sms : messages) {

		sms->setAnalyzedValue("upper", aym::rateOfUpperCase(sms->getMessage()));
		sms->setAnalyzedValue("digit", aym::rateOfDigits(sms->getMessage()));
		sms->setAnalyzedValue("url", aym::containsUrl(sms->getMessage()) ? 1.f : 0.f);
		sms->setAnalyzedValue("currency", aym::containsCurrencySymbol(sms->getMessage()) ? 1.f : 0.f);
		sms->setAnalyzedValue("free", aym::contains({"free", "Free", "FREE"}, sms->getMessage()) ? 1.f : 0.f);
	}

	SMSList list(messages, { "upper", "digit", "url", "currency", "free" });

	auto tree = decisiontree::id3(list);

	return EXIT_SUCCESS;
}