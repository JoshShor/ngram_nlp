#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <unordered_map>

using namespace std;

//read the file
void readFile(const string& filename, vector<string>& strVal) {
    ifstream infile(filename); // Open the file

    if (!infile) {
        cerr << "Failed to open the file: " << filename << endl;
        return;
    }

    string line;
    while (getline(infile, line)) { // Read each line from the file
        //cout << line << endl; // Print the line to the console
        istringstream getValues(line);
        string strVals;
        if(getValues >> strVals){
          //cout << "String: " << strVals << " Double: " << gValues << endl;
          strVal.push_back(strVals);
        } else {
          cerr << "error parsing line " << line << endl;
        }
    }

    infile.close(); // Close the file
}

// Function to compute trigram counts
void computeTrigramCounts(const vector<string>& str_val, unordered_map<string, int>& trigramCounts) {
    for (const string& word : str_val) {
        // Iterate through each trigram in the word
        for (size_t i = 2; i < word.length(); ++i) {
            string trigram = word.substr(i - 2, 3);
            trigramCounts[trigram]++;
        }
    }
}

// Function to compute bigram counts
void computeBigramCounts(const vector<string>& str_val, unordered_map<string, int>& bigramCounts) {
    for (const string& word : str_val) {
        // Iterate through each bigram in the word
        for (size_t i = 1; i < word.length(); ++i) {
            string bigram = word.substr(i - 1, 2);
            bigramCounts[bigram]++;
        }
    }
}

// Function to display trigram counts
void displayTrigramCounts(const unordered_map<string, int>& trigramCounts) {
    cout << "Trigram Counts:" << endl;
    for (const auto& entry : trigramCounts) {
        cout << entry.first << ": " << entry.second << endl;
    }
}

// Function to display bigram counts
void displayBigramCounts(const unordered_map<string, int>& bigramCounts) {
    cout << "Bigram Counts:" << endl;
    for (const auto& entry : bigramCounts) {
        cout << entry.first << ": " << entry.second << endl;
    }
}

// Function to compute and display conditional probabilities
void computeAndDisplayConditionalProbabilities(const unordered_map<string, int>& trigramCounts, const unordered_map<string, int>& bigramCounts) {
    // Conditional Probabilities calculation
    for (const auto& entry : trigramCounts) {
        string trigram = entry.first;
        int count_trigram = entry.second;
        // Extract preceding_chars from the trigram
        string preceding_chars = trigram.substr(0, 2);
        // Compute the probability only if there are preceding counts
        if (bigramCounts.count(preceding_chars) > 0) {
            int count_preceding = bigramCounts.at(preceding_chars);
            double probability = static_cast<double>(count_trigram) / count_preceding;
            cout << "P(" << trigram[2] << "|" << preceding_chars << ") = " << fixed << setprecision(3) << probability << endl;
        }
    }
}

// This program uses trigram probabilities to produce P(word) 
int main(){
    string fileName;
    string word;

    vector<string> str_val;

    /*
    long word_length;

    string c1 ="";
    string c2 ="";

    string gram_1 = "";
    string gram_2 = "";
    string gram_n = "";

    int idx = 0;

    double temp = 1.0;
    double totalProbability  = 1.0;
    */

    // ✓Ask the user for the input file name
    cout << "Enter a file name: ";
    cin >> fileName;
    //fileName = "tlist.txt";

    //read the files and load both values inside the two vectors
    readFile(fileName, str_val);
    cout << endl;

    /*
    cout << "String Values: " << endl;
    for(const string& str: str_val){
    cout << str << "\n";
    }
    cout << endl;
	*/


    // ✓ Read in the trigram probabilties

    // ✓ Repeat the following until the user
    //    wants to quit:

    cout << "Calculating probabilities for each word in the file:" << endl;
    // Map to store trigram counts
    unordered_map<string, int> trigramCounts;
    // Compute trigram counts
    computeTrigramCounts(str_val, trigramCounts);
    // Display trigram counts
    displayTrigramCounts(trigramCounts);


    // Map to store bigram counts
    unordered_map<string, int> bigramCounts;

    // Compute bigram counts
    computeBigramCounts(str_val, bigramCounts);
    // Iterate through each bigram in the word

    // Display bigram counts
    displayBigramCounts(bigramCounts);

    // Compute and display conditional probabilities
    cout << "Conditional Probabilities:" << endl;
    computeAndDisplayConditionalProbabilities(trigramCounts, bigramCounts);

  return 0;

}