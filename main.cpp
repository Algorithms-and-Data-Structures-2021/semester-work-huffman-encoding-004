#include <iostream>

#include "HuffmanTree.hpp"

using namespace std;

int main(int argc, char *argv[]) {
	itis::HuffmanTree* huffmanTree = new itis::HuffmanTree("aaabbc");
	cout<<huffmanTree->encode()<<"\n";
	for (auto ht : huffmanTree->getHuffmanCoding()){
		cout<<ht.first<<" "<<ht.second<<"\n";
	}

	return 0;
}