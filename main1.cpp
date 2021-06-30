//
//  main.cpp
//  Cryptography
//
//  Created by Joshua Yam on 3/15/19.
//  Copyright © 2019 Joshua Yam. All rights reserved.
//
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <fstream>
#include <algorithm>
using namespace std;

string getCipherText(const string& inputText){
    srand(time(NULL));
    int t = rand() % 24 + 1; //key length
    vector<int> key;
    for (size_t i =1; i<=t;i++){
        key.push_back(1+(i%t));
    }
    cout <<"Key is: ";
    for (auto a:key){
        cout << a << ' ';
    }
    cout <<endl;
    
    static const char* alph = " abcdefghijklmnopqrstuvwxyz";
    vector<char> vectAlph(alph, alph+27);
    string cipherText;
    for (int i =0; i<inputText.size();i++){
        int pos = find(vectAlph.begin(), vectAlph.end(), inputText[i]) - vectAlph.begin();
        cipherText+=vectAlph[pos+key[i%key.size()]];
    }
    cout << "CipherText: ";
    return cipherText;
}


vector<int> frequencyCounter(vector<char> total, int pos) {
    // frequency vectors are [0,a,..,z]
    vector<int> frequency(27);
    int ascii;
    for (int j = pos; j < (pos+500); j++) {
        ascii = int(total[j]);
        cout << total[j];
        if (total[j] == ' ') {
            frequency[0]++;
        }
        else {
            frequency[ascii - 96]++;
        }
    }
    cout << '\n';
    return frequency;
}

float getIC(vector<char>& seq){
    int N = int(seq.size()); //Size of Alphabet
    map<char, int> freq; //Frequency of each letter in a sequence
    static const char* alph = " abcdefghijklmnopqrstuvwxyz";
    vector<char> vectAlph(alph, alph+27);
    float freqsum = 0.0;
    float IC;
    for ( int i = 0; i < vectAlph.size(); i++ ){
        freq[ vectAlph[i]]=0;
    }
    for ( int i = 0; i < seq.size(); i++ ){
        freq[ seq[i] ] ++;
    }
   
    for (char& a : vectAlph){
        freqsum += freq[a] * (freq[a]-1);
    }
    IC=freqsum/((N*(N-1))/vectAlph.size());
    return IC;
}


int getKeyLength(const string& cipherText){
    vector<vector<vector<char> > > manyKeys; //3-D Vector stroring all possible key lengths and their sequences
    vector<vector<char> > aKey; //2-D Vector storing a key length and its sequences
    vector<char> seq; //One Sequence
    vector<float> avgIC; //Avg Index of Coincidence for each possible Key Length
    vector<float> individualIC; //Index of Coincidence for each Sequence
    int counter=24;
    
    for (int i =1; i<=counter;i++){
        for (int j =0; j<i;j++){
            for(int k=0; k<cipherText.length();k+=i){
                seq.push_back(cipherText[k+j]);
            }
            aKey.push_back(seq);
            individualIC.push_back(getIC(seq));
            seq.clear();
        }
        manyKeys.push_back(aKey);
        float avg = accumulate( individualIC.begin(), individualIC.end(), 0.0)/individualIC.size();
        avgIC.push_back(avg);
        aKey.clear();
    }
    //////////////////////////////////////////////////TEST
//    int count = 1;
//    for( vector<vector<vector<char>>>::const_iterator i = manyKeys.begin(); i != manyKeys.end(); ++i)
//    {
//        cout << "Key Length: " << count<<endl;
//        for( vector<vector<char>>::const_iterator j = i->begin(); j != i->end(); ++j)
//        {
//            cout<<"\t";
//            for( vector<char>::const_iterator k = j->begin(); k != j->end(); ++k)
//            {
//                cout<<*k << ' ';
//            }
//            cout <<endl;
//        }
//        count++;
//    }
    /////////////////////////////////////////////
    
//    for (auto a:avgIC){
//        cout <<a <<endl;
//    }
    return int(max_element(avgIC.begin(),avgIC.end()) - avgIC.begin()+1);
}
int main(int argc, const char * argv[]) {
//    ifstream ifs("dictionary.txt");
//    if (!ifs) {
//        cerr << "Couldn't open 'dictionary.txt'\n";
//        exit(1);
//    }
//
//    vector<char> temp;
//    char x;
//    while (ifs >> noskipws >> x) {
//        temp.push_back(x);
//    }
//    cout << endl;
//
//    // each vector contains the frequency of each char
//    vector<int> plainText1 = frequencyCounter(temp, 0);
//    vector<int> plainText2 = frequencyCounter(temp, 501);
//    vector<int> plainText3 = frequencyCounter(temp, 1002);
//    vector<int> plainText4 = frequencyCounter(temp, 1503);
//    vector<int> plainText5 = frequencyCounter(temp, 2004);
//
//    for (int k = 1; k < plainText1.size(); k++) {
//        cout << char(k+96) << ' ' << plainText1[k] << '\n';
//    }
//
//    cout << "Cyphertext: ";//Prompts user for the ciphertext to be decrpyted
    cout << "Text to be Encrypted: ";
    string input;
    getline(cin,input);
    string cipherText=getCipherText(input);
    cout<<cipherText <<endl;
    int keyLength=getKeyLength(cipherText);
    cout <<"Key Length is: " <<keyLength <<endl;
    
    return 0;
}
