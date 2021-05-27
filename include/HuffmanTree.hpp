#pragma once

#include <map>
#include <vector>

using namespace std;

namespace itis {



	struct HuffmanTree {
	private:
		/*
		 * мапа шифров для каждого символа
		 */
		map<char, string> huffmanCode;

		/*
		 * мапа количества встречавшихся символов
		 */
		map<char, int> frequency;

		/*
		 * вектор символов строки
		 */
		vector<char> chars;

		/**
		 * вычисляет количество повторений каждого символа в строке
	 	* @param chVector вектор символов строки
	 	* @return map<char, int> мапа количества встречавшихся символов
	 	*/
		map<char, int> searchFrequency(vector<char> chVector);


		/**
	 	* по алгоритму Хоффмана находит оптимальное кодирование алфавита с минимальной избыточностью
		 * @param frequencyVector мапа количества встречавшихся символов
	 	* @return  map<char, int> шифр для каждого символа
	 	*/
		map<char, string>
		encodeChars(map<char, string> tempHoffmanCode, map<vector<char>, int> communitiesCode);
		/*
		 * перегрузка для рекурсии (ну, понял)
		 */
		map<char, string> encodeChars();

	public:
		/**
		 * конструктор, который принимает строку,
		 * по которой строит подходящий оптимальный код Хоффмана
		 * @param text строка, по которой производится кодирование
		 */
		HuffmanTree(string text);

		/**
		 * кодирует строку, переданную в конструкторе
		 * @return кодувую строку вида 11001011101010
		 */
		string encode();

		/**
		 * @return код для каждого символа в переданной строке
		 */
		map<char, string> getHuffmanCoding();



	};

}  // namespace itis