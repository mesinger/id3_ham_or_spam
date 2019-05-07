#pragma once

#include "frequencytable.hpp"
#include <memory>
#include <vector>
#include <string>
#include "sms.hpp"

namespace decisiontree {

	class node;
	typedef std::shared_ptr<node> PNODE;

	PNODE id3(SMSList& messages, PNODE root = nullptr, const int depth = 0);

	class node {

		friend PNODE id3(SMSList& messages, PNODE root, const int depth);

	public:

		node(const SMSList& messages);

		std::string classify(const PAnalyzedSMS msg);

	protected:

		SMSList messages;
		FrequencyTable ftable;

		std::string label;

		std::map<std::string, PNODE> children;

	private:

		void loadFTable();
	};
};


