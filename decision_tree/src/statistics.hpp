#pragma once

#include <map>
#include <string>
#include <iostream>

namespace statistics {

	//[actual][predicted]
	typedef std::map<std::string, std::map<std::string, float>> ConfusionMatrix;

	void printConfusionMatrix(const ConfusionMatrix& matrix) {

		for (const auto& [actual, val] : matrix) {

			std::cout << actual << std::endl;

			for (const auto& [predicted, count] : val) {

				std::cout << predicted << ": " << count << std::endl;
			}

			std::cout << std::endl;
		}
	}

	struct ConfusionMetrics {
		int tp, fp, fn, tn;
	};

	void getConfusionMetrices(const ConfusionMatrix& matrix, const std::string& classification, ConfusionMetrics& metrices) {

		int tp = 0;
		int fp = 0;
		int fn = 0;
		int tn = 0;

		for (const auto& [actual, val] : matrix) {

			if (actual == classification) {

				for (const auto& [predicted, count] : val) {

					if (predicted == classification) tp += count;
					else fn += count;
				}
			}
			else {

				for (const auto& [predicted, count] : val) {

					if (predicted == classification) fp += count;
					else tn += count;
				}
			}
		}

		metrices.tp = tp;
		metrices.fp = fp;
		metrices.fn = fn;
		metrices.tn = tn;
	}

	float getAcc(const ConfusionMetrics& metrices) {

		return ((float)(metrices.tp) + metrices.tn) / (metrices.tp + metrices.fp + metrices.fn + metrices.tn);
	}
}
