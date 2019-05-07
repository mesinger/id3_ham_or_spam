#include <iostream>
#include "util.hpp"
#include "rapidcsv.h"
#include "sms.hpp"
#include "frequencytable.hpp"
#include <map>
#include "decisiontree.hpp"
#include "kcrossvalidation.hpp"
#include "statistics.hpp"

int main(int argc, char** argv) {

	if (argc != 2) return EXIT_FAILURE;

	rapidcsv::Document file(argv[1]);

	std::vector<PAnalyzedSMS> messages;

	for (auto& line : file.getData()) {

		std::string type = line[0].substr(1, line[0].length() - 2);
		messages.emplace_back(std::make_shared<AnalyzedSMS>(type, line[1]));
	}

	for (auto& sms : messages) {

		sms->setAnalyzedValue("upper", aym::rateOfUpperCase(sms->getMessage()));
		sms->setAnalyzedValue("digit", aym::rateOfDigits(sms->getMessage()));
		sms->setAnalyzedValue("url", aym::containsUrl(sms->getMessage()) ? 1.f : 0.f);
		sms->setAnalyzedValue("currency", aym::containsCurrencySymbol(sms->getMessage()) ? 1.f : 0.f);
		sms->setAnalyzedValue("free", aym::contains({"free", "Free", "FREE"}, sms->getMessage()) ? 1.f : 0.f);
	}
	std::vector<PAnalyzedSMS> training;
	std::vector<PAnalyzedSMS> test;

	kcrossfold<PAnalyzedSMS> kcrossy;
	kcrossy.split(5, 1, messages, training, test);

	SMSList trainingList(training, { "upper", "digit", "url", "currency", "free" });

	auto tree = decisiontree::id3(trainingList);

	statistics::ConfusionMatrix matrix;

	for (const auto msg : test) {
		 
		std::string actual = msg->getType();
		std::string expected = tree->classify(msg);

		matrix[actual][expected]++;
	}

	statistics::ConfusionMetrics metrices;
	statistics::getConfusionMetrices(matrix, "ham", metrices);

	std::cout << "Messages tested = " << test.size() << std::endl;

	statistics::printConfusionMatrix(matrix);

	std::cout << "Accuracy = " << statistics::getAcc(metrices) << "%" << std::endl;

	return EXIT_SUCCESS;
}