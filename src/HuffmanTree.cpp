#include <iostream>
#include "HuffmanTree.hpp"
using namespace std;
namespace itis {



	HuffmanTree::HuffmanTree(string text) {
		this->chars.resize(text.size());

		for (int i = 0; i < text.size(); i++) {
			chars.at(i) = text.at(i);
		}

		this->frequency = searchFrequency(chars);

		this->huffmanCode = encodeChars();
	}


	map<char, int> HuffmanTree::searchFrequency(vector<char> chVector) {
		map<char, int> frequencyMap;
		for (char ch : chVector) {
			frequencyMap.insert(make_pair(ch, 0));
		}
		for (char ch : chVector) {
			int t = frequencyMap.at(ch) + 1;
			frequencyMap.erase(ch);
			frequencyMap.insert(make_pair(ch, t));
		}
		return frequencyMap;
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
		for (const auto& vectorChars: communitiesCode) {
			if (leftCount >= vectorChars.second) {
				leftCount = vectorChars.second;
				leftChars = vectorChars.first;
			}
		}

		for (const auto& vectorChars: communitiesCode) {
			if (rightCount >= vectorChars.second && vectorChars.first != leftChars) {
				rightCount = vectorChars.second;
				rightChars = vectorChars.first;
			}
		}

		communitiesCode.erase(leftChars);
		communitiesCode.erase(rightChars);

		for (auto vectorChars : leftChars) {
			string  temp = tempHoffmanCode.at(vectorChars)+"0";
			tempHoffmanCode.erase(vectorChars);
			tempHoffmanCode.insert(make_pair(vectorChars, temp));
		}
		for (auto vectorChars : rightChars) {
			string  temp = tempHoffmanCode.at(vectorChars)+"1";
			tempHoffmanCode.erase(vectorChars);
			tempHoffmanCode.insert(make_pair(vectorChars, temp));
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
		map<char, string> codeHoffman;
		map<vector<char>, int> communitiesCode;
		vector<char> community;
		
		for (auto fr : frequency) {
			codeHoffman.insert(make_pair(fr.first, ""));
			community.clear();
			community.resize(1);
			
			community.at(community.size()-1) = fr.first;
			communitiesCode.insert(make_pair(community, fr.second));
		}
		
		return encodeChars(codeHoffman, communitiesCode);
	}

	string HuffmanTree::encode() {
		string code = "";
		for (auto ch : chars) {
			code += huffmanCode.at(ch);
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