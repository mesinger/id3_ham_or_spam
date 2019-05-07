#include "decisiontree.hpp"

using namespace decisiontree;

node::node(const SMSList& messages)
	:messages(messages)
{
	loadFTable();
}

std::string decisiontree::node::classify(const PAnalyzedSMS msg)
{
	if (children.size() == 0) {
		return label;
	}

	float avg = messages.getAverage(label);
	
	if (msg->getAnalyzedValue(label) <= avg) {

		return children["below"]->classify(msg);
	}
	else {

		return children["above"]->classify(msg);
	}
}

void node::loadFTable()
{
	for (auto& sms : *messages.get()) {

		for (const auto& classification : messages.getClassifications()) {

			std::string type = sms->getType() == "spam" ? "yes" : "no";
			std::string specification = sms->getAnalyzedValue(classification) <= messages.getAverage(classification) ? "below" : "above";

			ftable[classification][specification][type] += 1;
		}
	}
}

PNODE decisiontree::id3(SMSList& messages, PNODE root, const int depth)
{
	if (root == nullptr) {
		root = std::make_shared<node>(messages);
	}

	if (messages.decideSingle()) {

		root->label = messages.hamOrSpam();
		return root;
	}

	if (depth == messages.getClassifications().size()) {

		root->label = messages.hamOrSpam();
		return root;
	}

	std::string label;
	float highestIg = -FLT_MAX;

	for (const auto& classification : messages.getClassifications()) {

		float ig = root->ftable.ig(classification);

		if (ig > highestIg) {
			highestIg = ig;
			label = classification;
		}
	}

	root->label = label;

	SMSList splittedBelow = messages.splitBelow(label);
	SMSList splittedAbove = messages.splitAbove(label);

	PNODE belowAvgChild = std::make_shared<node>(splittedBelow);
	PNODE aboveAvgChild = std::make_shared<node>(splittedAbove);

	root->children.emplace("below", id3(splittedBelow, belowAvgChild, depth + 1));
	root->children.emplace("above", id3(splittedAbove, aboveAvgChild, depth + 1));

	//for (const auto& [k, v] : root->ftable[label]) {
	//	
	//	PNODE child = std::make_shared<node>();
	//	root->children.emplace_back(id3(, child, depth + 1));
	//}

	return root;
}
