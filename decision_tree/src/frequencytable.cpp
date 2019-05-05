#include "frequencytable.hpp"

FrequencyTable::FrequencyTable(const std::string& label)
	:label(label)
{
}

void FrequencyTable::addToTable(const std::string& classification, const std::string& decision, int v)
{
	(*this)[classification][decision] = v;
}
