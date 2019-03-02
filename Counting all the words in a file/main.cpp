#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>

using namespace std;

set<string> stopWords;
map<string, int> freq;
int total_words = 0;

bool CharacterChecking(char);
bool ReadStopWordFile();
bool ReadInputFile();
string FixTheWord(string);

int main() {
	multimap<int, string> freq_rev;
	map<string, int>::iterator it;
	multimap <int, string>::reverse_iterator myit; 
	int count;
	
	if (!ReadStopWordFile())	return 1;
	if(!ReadInputFile())	return 1;
 
	for (it = freq.begin(); it != freq.end(); it++)	// inserting all elements of the map into the multimap
		freq_rev.insert(make_pair(it->second, it->first));

	for (myit = freq_rev.rbegin(), count = 0; count<10; myit++, count++)	// printing max 10 repeated words
		cout << (*myit).second << '\t' << (*myit).first << "\t%" << (*myit).first * 100 / float(total_words) << endl;

	cout << "Total words: " << total_words << endl;
	
	getchar();
	return 0;
}

bool CharacterChecking(char character) {
	return (character != ' ' && character != '\n');
}

bool ReadStopWordFile() {
	ifstream stopWordsFile("stopwords.txt");
	string word;
	if (stopWordsFile.is_open()) {
		while (getline(stopWordsFile, word)) {
			if (word.length() > 0)
				stopWords.insert(word);
		}
		stopWordsFile.close();	// closing the file
		return true;
	}
	else {
		cout << "Could not open the file!";
		return false;;
	}
}

bool ReadInputFile() {
	ifstream inputFile("input.txt");
	char character;
	string word;
	bool is_in, flag = false;
	if (inputFile.is_open()) {
		while (!inputFile.eof()) {
			inputFile.get(character);

			if (CharacterChecking(character))
				word += tolower(character);
			else {
				word = FixTheWord(word);
				if (word.length() > 0)
					total_words++;	// increment the word counter
				is_in = stopWords.find(word) != stopWords.end();	// checking if word is in the set or not
				if (is_in)	// if the word is in the stopWords, then add it to the map
					freq[word]++;
				word.clear();	// reset the string
			}
		}
		inputFile.close();	// closing the file
		return true;
	}
	else {
		cout << "Could not open the file!";
		return false;
	}
}
// this function takes the word, and removes the punctuations from it
string FixTheWord(string word) {
	string new_word;
	for (int i = 0; i < word.length(); i++) {
		if (ispunct(word[i])) {
			if (i == 0) {
				if (ispunct(word[1]))
					i++;
			}
			else if ((i == word.length() - 2)) {
				if (ispunct(word[word.length() - 1]))
					i++;
				else
					new_word += word[i];
			}
			else if ((i == word.length() - 1)) {
				break;
			}
			else
				new_word += word[i];
		}
		else
			new_word += word[i];
	}
	new_word[new_word.length()] = '\0';
	return new_word;
}
