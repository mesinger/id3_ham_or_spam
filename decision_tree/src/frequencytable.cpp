#include "frequencytable.hpp"
#include <cmath>

float _log2(float f) {
	return f == 0 ? 0 : log2(f);
}

float FrequencyTable::entropy(const std::string& p)
{
	float e = 0;

	int totalYes = 0, totalNo = 0;
	float pyes, pno;

	for (auto& [specification, v] : (*this)[p]) {

		totalYes += v["yes"];
		totalNo += v["no"];
	}

	pyes = (float)totalYes / (totalYes + totalNo);
	pno = (float)totalNo / (totalYes + totalNo);

	e = -pyes * _log2(pyes) - pno * _log2(pno);

	return e;
}

float FrequencyTable::ig(const std::string& s)
{
	float ig = entropy(s);

	for (auto& [specification, v] : (*this)[s]) {

		float entrSf = entropy(s, specification);
		float sf_s = (float)v["yes"] / (v["yes"] + v["no"]);

		ig -= sf_s * entrSf;
	}

	return ig;
}

float FrequencyTable::entropy(const std::string& s, const std::string& f)
{
	float e;

	int totalYes = (*this)[s][f]["yes"];
	int totalNo = (*this)[s][f]["no"];

	float pyes = (float)totalYes / (totalYes + totalNo);
	float pno = (float)totalNo / (totalYes + totalNo);

	e = -pyes * _log2(pyes) - pno * _log2(pno);

	return e;
}
