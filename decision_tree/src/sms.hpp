#pragma once

#include <string>
#include <map>

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

private:

	std::map<std::string, float> analyzedValues;
};
