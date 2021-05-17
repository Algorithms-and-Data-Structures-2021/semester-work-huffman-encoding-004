#include "HuffmanTree.hpp"

namespace itis {



	HuffmanTree::HuffmanTree(string text) {
		this->chars.resize(text.size());
		for (int i = 0; i < text.size(); i++) {
			chars[i] = text.at(i);
		}
		this->frequency = searchFrequency(chars);
		this->huffmanCode = encodeChars();
	}


	map<char, int> HuffmanTree::searchFrequency(vector<char> chVector) {
		map<char, int> frequencyMap = map<char, int>();
		for (int i = 0; i < chVector.size(); i++) {
			frequencyMap.insert(make_pair(chVector.at(i), 0));
		}
		for (int i = 0; i < chVector.size(); i++) {
			frequencyMap.insert(make_pair(chVector.at(i), frequencyMap.at(chVector.at(i)) + 1));
		}
		frequencyMap;
	}


	map<char, string>
	HuffmanTree::encodeChars(map<char, string> tempHoffmanCode, map<vector<char>, int> communitiesCode) {
		vector<char> leftChars;
		int leftCount = INT_MAX;
		vector<char> rightChars;
		int rightCount = INT_MAX;

		/*
		 * находим 2 самых редко используемых символа (векторов символов)
		 */
		for (auto vectorChars: communitiesCode) {
			if (leftCount >= vectorChars.second) {
				leftCount = vectorChars.second;
				leftChars = vectorChars.first;
			}
		}

		for (auto vectorChars: communitiesCode) {
			if (rightCount >= vectorChars.second && vectorChars.first != leftChars) {
				rightCount = vectorChars.second;
				leftChars = vectorChars.first;
			}
		}

		communitiesCode.erase(leftChars);
		communitiesCode.erase(rightChars);

		for (auto vectorChars : leftChars) {
			tempHoffmanCode.insert(make_pair(vectorChars, tempHoffmanCode.at(vectorChars) + "0"));
		}
		for (auto vectorChars : rightChars) {
			tempHoffmanCode.insert(make_pair(vectorChars, tempHoffmanCode.at(vectorChars) + "1"));
		}
		//объединяем 2 вектора
		leftChars.insert(leftChars.end(), rightChars.begin(), rightChars.end());

		communitiesCode.insert(make_pair(leftChars, leftCount + rightCount));

		if (communitiesCode.size() == 1) {
			return tempHoffmanCode;
		}
		return encodeChars(tempHoffmanCode, communitiesCode);
	}

	map<char, string> HuffmanTree::encodeChars() {
		map<char, string> HoffmanCode;
		map<vector<char>, int> communitiesCode;
		vector<char> community;
		
		for (auto fr : frequency) {
			HoffmanCode.insert(make_pair(fr.first, ""));
			community.clear();
			community.resize(1);
			
			community.push_back(fr.first);
			communitiesCode.insert(make_pair(community, 0));
		}
		
		return encodeChars(HoffmanCode, communitiesCode);
	}

	string HuffmanTree::encode() {
		string code = "";
		for (int i = 0; i < chars.size(); ++i) {
			code += huffmanCode.at(chars.at(i));
		}
		return code;
	}

	map<char, int> HuffmanTree::getHuffmanCoding() {
		map<char, int> hC;
		for (auto node : huffmanCode){
			hC.insert(make_pair(node.first,stoi(node.second)));
		}
		return hC;
	}

}  // namespace itis