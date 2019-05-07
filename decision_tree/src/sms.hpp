#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>
#include <memory>

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

typedef std::shared_ptr<AnalyzedSMS> PAnalyzedSMS;

class SMSList {

public:

	SMSList(const std::vector<PAnalyzedSMS>& messages, const std::set<std::string>& classifications);

	std::vector<PAnalyzedSMS>* get();
	std::set<std::string> getClassifications();
	float getAverage(const std::string& type);

	SMSList splitBelow(const std::string& type);
	SMSList splitAbove(const std::string& type);

	bool decideSingle() const;

	std::string hamOrSpam() const;

protected:

	float avgOf(const std::string& type);

	void numberOfElements(const std::string& type, float threshold, int* pbelow, int* pabove);

	std::vector<PAnalyzedSMS> messages;
	std::set<std::string> classifications;
	std::map<std::string, float> averages;
};
