#include "sms.hpp"

SMS::SMS(const std::string& type, const std::string& msg)
	:type(type), msg(msg)
{
}

AnalyzedSMS::AnalyzedSMS(const std::string& type, const std::string& msg)
	:SMS(type, msg)
{
}

void AnalyzedSMS::setAnalyzedValue(const std::string& property, float newValue)
{
	analyzedValues[property] = newValue;
}

float AnalyzedSMS::getAnalyzedValue(const std::string& type)
{
	return analyzedValues[type];
}

SMSList::SMSList(const std::vector<PAnalyzedSMS>& messages, const std::set<std::string>& classifications)
	: messages(messages), classifications(classifications)
{
	for (const auto& classification : classifications) {
		averages[classification] = avgOf(classification);
	}
}

float SMSList::avgOf(const std::string& type)
{
	if (messages.size() == 0) return 0;

	float avg = 0;

	for (auto& msg : messages) {

		avg += msg->getAnalyzedValue(type);
	}

	return avg / messages.size();
}

void SMSList::numberOfElements(const std::string& type, float threshold, int* pbelow, int* pabove)
{
	int below = 0;
	int above = 0;

	for (auto& msg : messages) {

		if (msg->getAnalyzedValue(type) <= threshold) below++;
		else above++;
	}

	(*pbelow) = below;
	(*pabove) = above;
}

std::vector<PAnalyzedSMS>* SMSList::get()
{
	return &messages;
}

std::set<std::string> SMSList::getClassifications()
{
	return classifications;
}

float SMSList::getAverage(const std::string& type)
{
	return averages[type];
}

SMSList SMSList::splitBelow(const std::string& type)
{
	float avg = avgOf(type);

	std::vector<PAnalyzedSMS> belowAvg;

	for (const auto msg : messages) {
		if (msg->getAnalyzedValue(type) <= avg) {
			belowAvg.emplace_back(msg);
		}
	}

	return SMSList(belowAvg, classifications);
}

SMSList SMSList::splitAbove(const std::string& type)
{
	float avg = avgOf(type);

	std::vector<PAnalyzedSMS> aboveAvg;

	for (const auto msg : messages) {
		if (msg->getAnalyzedValue(type) > avg) {
			aboveAvg.emplace_back(msg);
		}
	}

	return SMSList(aboveAvg, classifications);
}

bool SMSList::decideSingle() const
{
	if (messages.size() == 0) return true;

	const std::string first = messages[0]->getType();

	for (const auto& msg : messages) {

		if (msg->getType() != first) return false;
	}

	return true;
}

std::string SMSList::hamOrSpam() const
{
	int ham = 0;
	int spam = 0;

	for (const auto& msg : messages) {

		if (msg->getType() == "\"ham\"") {
			ham++;
		}
		else if (msg->getType() == "\"spam\"") {
			spam++;
		}
	}

	return ham >= spam ? "ham" : "spam";
}
