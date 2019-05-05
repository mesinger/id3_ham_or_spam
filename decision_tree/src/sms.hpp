#pragma once

#include <string>
#include <map>
#include <vector>

class SMS {
public:

	explicit SMS(const std::string& type, const std::string& msg);

	inline std::string getType() const {
		return type;
	}

	inline std::string getMessage() const {
		return msg;
	}

protected:
	std::string type;
	std::string msg;
};

class AnalyzedSMS : public SMS{

public:

	explicit AnalyzedSMS(const std::string& type, const std::string& msg);

	void setAnalyzedValue(const std::string& property, float newValue);

	float getAnalyzedValue(const std::string& type);

private:

	std::map<std::string, float> analyzedValues;
};

class SMSList {

public:

	SMSList(const std::vector<AnalyzedSMS>& messages);

	float avgOf(const std::string& type);

	void numberOfElements(const std::string& type, float threshold, int* pbelow, int* pabove);

protected:

	std::vector<AnalyzedSMS> messages;
};
