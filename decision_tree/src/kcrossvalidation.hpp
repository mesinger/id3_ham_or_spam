#pragma once

#include <vector>

template<typename T>
class kcrossfold {

public:

	void split(int k, int pickTest, const std::vector<T>& data, std::vector<T>& training, std::vector<T>& test) const {

		std::size_t splitsize = data.size() / k;

		training.reserve(splitsize * (k - 1));
		test.reserve(splitsize);

		for (int i = 0; i < k; i++) {

			auto start = std::next(data.cbegin(), splitsize * i);
			auto end = std::next(data.cbegin(), splitsize * i + splitsize);

			std::vector<T> dataset;
			dataset.resize(splitsize);

			if (i == (pickTest - 1))
				test.insert(test.end(), start, end);
			else
				training.insert(training.end(), start, end);
		}
	}
};
