#include <iostream>
#include <stdio.h>
#include <string>
#include <limits.h>
#include <vector>
#include <string>
#include <math.h>

#define MIN(x,y) ((x) < (y) ? (x) : (y))

using namespace std;

class FuzzySearch {
public:
	void Levenstein_Distance(string source_word, string target_word) {
		int m, n, temp, tracker;
		int D[40][40]; //Create a table to store intermediate results

		m = source_word.length(); //Provem m value doiny words
		n = target_word.length(); //Provem n value doiny words

		for (int i = 0; i <= m; i++) {
			D[0][i] = i;
		}
		for (int j = 0; j <= n; j++) {
			D[j][0] = j;
		}
		//Filling the table from the top down
		for (int j = 1; j <= m; j++) {
			for (int i = 1; i <= n; i++) {
				/*Look, do I need to take some action. 0 - the letters match, 1 - mismatch*/
				if (source_word[i - 1] == target_word[i - 1]) {  
					tracker = 0;
				}
				else {
					tracker = 1;
				}
				//Choose which operation is more preferable
				//D[i - 1][j] - delete, D[i][j - 1] - insert
				temp = MIN((D[i - 1][j] + 1), (D[i][j - 1] + 1)); // Choose min value
				D[i][j] = MIN(temp, (D[i - 1][j - 1] + tracker)); // D[i - 1][j - 1] - coincidence or delete
			}
		}
		/*Print the number of operations that need to be done to the word is made to coincide with the desired*/
		printf_s("The Levenshtein distance (the number of operations that need to be done to the word is made to coincide with the target): %d\n", D[n][m]);
	}

	/*The Hamming distance indicates how many characters differ between the compared words*/
	void Hamming_Distance(const char* source, const char* target) {
		int i = 0, j = 0, count = 0;

		while (source[i] != '\0') { //Do not check whether the empty word  
			if (source[i] != target[j]) {//If the value does not match, then increase count by 1 
				count++;
			}
			else {
				j++;
			}
			i++;
		}
		cout << "The Hamming distance (how many characters differ between the compared words): " << count << endl;
	}

	/*Search word in the text*/
	void FuzSearch(const char *string, const char *substring) {
		int  sl, ssl; /*String length*/
		int res = -1; /*Make it so that the program knew that there was nothing here*/
		sl = strlen(string);
		ssl = strlen(substring);
		if (sl == 0) /*Check for correct input*/
			cout << "Incorrect string\n";
		else if (ssl == 0)
			cout << "Incorrect substring\n";
		else { /*If everything is correct, proceed to the counting*/
			int  i, j = 0, k = -1;
			int  *d;
			d = new int[1000];
			d[0] = -1;/*Nothing in this cell*/
			while (j < ssl - 1) {
				while (k >= 0 && substring[j] != substring[k])
					k = d[k];
				j++;
				k++;
				if (substring[j] == substring[k])
					d[j] = d[k];
				else
					d[j] = k;
			}
			i = 0;
			j = 0;
			/*Go through the text*/
			while (j < ssl && i < sl) {
				while (j >= 0 && string[i] != substring[j])
					j = d[j];
				i++;
				j++;
			}
			/*Clean memory*/
			delete[] d;
			res = j == ssl ? i - ssl : -1;
		}
		cout << "The word was found on " << res << " position." << endl;
	}
};

void main() {
	string source_word;
	string target_word;
	const char *source1 = source_word.c_str(); // Here is the type string to a char array
	const char *target1 = target_word.c_str();
	const char *target = target_word.c_str();

	setlocale(LC_ALL, "rus"); /*Russian language support*/

	FuzzySearch Fuz;

	cout << "Enter a source word: \n";
	cin >> source_word; cout << endl;

	cout << "Enter a target word for compare to source: \n";
	cin >> target_word; cout << endl;

	cout << "1." << source1 << ". 2. " << target1 << ".\n";

	Fuz.Levenstein_Distance(source_word, target_word); cout << endl;
	Fuz.Hamming_Distance(source1, target1); cout << endl;

	
	const char source[] = "There are five types of schools in the US educational system. They are: kindergarten, elementary school, middle school, high school and private school. Children go to kindergarten when they are 5 years old They go to elementary school from ages 6 through 11 (1-5 grades), middle school from ages 12 through 14 (6-8 grades) and high school from ages 15 through 19 (9-12 grades).";
	cout << source << endl;
	cout << "Enter a word to compare: ";
	cin >> target_word; cout << endl;
	cout << target << endl;

	Fuz.FuzSearch(source, target); cout << endl;

	system("pause");
}