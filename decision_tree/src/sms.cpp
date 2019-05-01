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
