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

SMSList::SMSList(const std::vector<AnalyzedSMS>& messages)
	:messages(messages)
{
}

float SMSList::avgOf(const std::string& type)
{
	if (messages.size() == 0) return 0;

	float avg = 0;

	for (auto& msg : messages) {

		avg += msg.getAnalyzedValue(type);
	}

	return avg / messages.size();
}

void SMSList::numberOfElements(const std::string& type, float threshold, int* pbelow, int* pabove)
{
	int below = 0;
	int above = 0;

	for (auto& msg : messages) {

		if (msg.getAnalyzedValue(type) <= threshold) below++;
		else above++;
	}

	(*pbelow) = below;
	(*pabove) = above;
}
