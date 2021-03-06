/*
Assignment 15
Anagrams.
The user enters a string.
Write a program that checks a (given) dictionary for occurrences of anagrams of this string.
For example, ANGLE and GALEN are anagrams.
Use a dictionary for crosswords’ solvers.
*/

#include "stdafx.h"
#include <iostream>
using namespace std;

#include <fstream> //to manage files
#define L 30 //length of arrays. longest word has 28 characters on line 2109 "antidisestablishmentarianism", so 30 is enough.

//FUNCTIONS-----------------------------------------------

int word_length(char word[]) { //returns the number of characters in string (length without the terminator)
	int index = 0;
	while (word[index] != '\0') {
		index++;
	}
	return index;
}

bool equals(char a[], char b[]) { //compares words. returns true if the same
	int aSize = word_length(a);
	int bSize = word_length(b);
	if (bSize != aSize) { return false; } //if words' lengths are different, then words aren't the same
	for (int i = 0; i < aSize; i++) {
		if (tolower(a[i]) != tolower(b[i])) { return false; } //compares letters after lowering them. it makes the function be non-case sensitive
	}
	return true;
}

int count_of_letter_in_word(char word[], char letter) { //counts occurrences of a letter
	int count = 0;
	int dataLength = word_length(word);
	for (int i = 0; i < dataLength; i++) {
		if (tolower(word[i]) == tolower(letter)) { //compares letters after lowering them. it makes the function be non-case sensitive
			count++;
		}
	}
	return count;
}

void info(bool ifWordExists, int numberOfAnagrams) { //displays info of the count of anagrams
	if (numberOfAnagrams) {
		if (ifWordExists) {
			cout << endl << "Given word has " << numberOfAnagrams;
		} else {
			cout << endl << "Given word doesn't exist, but has " << numberOfAnagrams;
		}
		if (numberOfAnagrams == 1) { cout << " anagram." << endl << endl; }
		else { cout << " anagrams." << endl << endl; }
	} else if (!numberOfAnagrams) {
		if (ifWordExists) {
			cout << "Given word doesn't have any anagrams." << endl << endl;
		} else {
			cout << "Given word doesn't exist and doesn't have any anagrams." << endl << endl;
		}
	}
}

void look_for_anagrams(char word[]) { //main algorithm of finding anagrams
	char data[L];
	int wordLength = word_length(word);
	bool ifAnagram;
	int numberOfAnagrams = 0;
	bool ifWordExists = false;
	ifstream file;
	file.open("words.txt", ios::in);
	if (file.fail()) {
		cout << "Failed to open a file." << endl;
		return; //exit the function if the file could not be opened
	}
	while (!file.eof()) {
		ifAnagram = true; //I tried to use "continue;" instead of a flag, but the "for" loop prevents me from using "continue" on outer loop "while"
		file >> data; //copies a line from file into an array of chars
		int dataLength = word_length(data);
		if (dataLength != wordLength) {
			ifAnagram = false;	//if words have different lengths, then they aren't anagrams
		} else {
			for (int i = 0; i < wordLength; i++) {
				if (count_of_letter_in_word(data, word[i]) != count_of_letter_in_word(word, word[i])) {
					ifAnagram = false; //if words don't have the same count of each letter, than they aren't anagrams
				}
				if (!ifAnagram) break; //optimization. breaks loop if we already know it's not an anagram. the app already is incredibely fast, so it's not necessary
			}
		}
		if (ifAnagram) {
			if (equals(data, word)) { ifWordExists = true; }
			else {
				cout << data << endl; //print anagram to screen
				numberOfAnagrams++;
			}
		}
	}
	info(ifWordExists, numberOfAnagrams);
	file.close();
}

//MAIN-----------------------------------------------------
int main() {
	char word[L] = "";
	cout << "Which word's anagrams would you like to find?" << endl << "(maximum of 29 characters.)" << endl << endl;
	cin >> word;
	cout << endl;
	look_for_anagrams(word);
	system("pause");
    return 0;
}