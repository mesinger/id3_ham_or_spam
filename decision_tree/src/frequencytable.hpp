#pragma once

#include <string>
#include <map>

class IDecisionProcess {

public:

	virtual float entropy(const std::string& p) = 0;
	virtual float ig(const std::string& s) = 0;

protected:

	virtual float entropy(const std::string& s, const std::string& f) = 0;
};

class FrequencyTable : public std::map<std::string, std::map<std::string, std::map<std::string, int>>>, public IDecisionProcess {

public:

	FrequencyTable() = default;

	virtual float entropy(const std::string& p) override;
	virtual float ig(const std::string& s) override;

protected:

	virtual float entropy(const std::string& s, const std::string& f) override;
};


