#pragma once

#include <string>
#include <map>

class FrequencyTable : public std::map<std::string, std::map<std::string, int>> {

public:

	FrequencyTable() = default;
	explicit FrequencyTable(const std::string& label);

	void addToTable(const std::string& classification, const std::string& decision, int v);

protected:

	std::string label;
};


