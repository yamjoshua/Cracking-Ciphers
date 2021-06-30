//
//  main.cpp
//  Applied Cryptography
//  Project 1
//  Nowsha Islam, Harish Saravanakumar, Joshua Yam
//


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <fstream>
#include <algorithm>
using namespace std;
string plainText1_string = "surrenderee document spunkiest coquetted abatis leasehold nuclei fogginess genoa traitors blockbuster superpositions flams surprized honcho cetera to transmit psychol wintered gruntingly cheapness translation laborer lissomeness caravansaries reflexes overextends bitter uplift strate filler cupolaed automatic machree nonparasitic unashamed braggy typier potencies greyness gulped masonwork blandisher disks fadeaway origamis manurer olives engine looted whitehall imperils shadowbox jabbing exports";
string plainText2_string = "tumble cooked twirled absinths ceca cheatery raters redeploy niacinamide offeree preventively tangibleness beamy oligarchical microbus intends galvanize indelible tubings overcools rollover maladroit logways frilling skinks affirmatively flatfoots oversleeps consignors completes espadrille booms repaved ofays keens dinosaurs rerouted consignments victimless psychophysical chuckle admissibility muleteer deescalating ovary bowwow assisi fore tubbiest vocatively filially preestablish lacquerers spr";
string plainText3_string = "harmonizations pratique defoliated brashly elegancy henpeck ecumenicism valuta lingers acrobatic mismarriage fruitlessness pattering enables travois nymphs fratricides awakener ordure tribulation elicit nonviable guiles raucously euclidean evangelist preoperative pathogeny frames medium inviabilities retrains crankcase awkwarder stopwatch subclinical irrigators lettuce skidooed fonder teem funguses purviews longshot affaires wearing judo resettle antedate inoperable pinworm pumper annul anteposi";
string plainText4_string = "hark reascended recedes inebriate flowery awkwarder waterbed complacency sikh compartmented dependably alliterations headache basketfuls malocclusions cubistic hint headdresses unfrocks keloidal translucent fidelities instructional graphed baker superb spectroscopies bismark uncanniest detachability letdown querulously unstack curdling chained pointy drippers larch spermicide inextricability anteed improvising jape imponderably lithographic winglets advents triplicating growling fescue salabilit";
string plainText5_string = "enrollee pins datively armiger bisect installs taffeta compliances governorship laceworks preciousness bedizens immaculately disinfect nucleonics biremes mailbags behaves enhance floppiest brutisms registered silenced tuques oryxes coddler undersigned mackintosh misemployment peacemakers pleadings dandification platypuses swig doer reshowed quadrangles locutory encapsules bawdies woolpack valuated malodorously shill cryogenies known distr bonsai morale mirage skit aquacades pi overcommon flippan";

// this function is used to find the frequencies for the plaintexts. Loops 500 time
vector<int> frequencyCounter(vector<char> total, int pos) {
    // frequency vectors are [0,a,..,z]
    vector<int> frequency(27);
    int ascii;
    for (int j = pos; j < (pos+500); j++) {
        ascii = int(total[j]);
        //cout << total[j];
        if (total[j] == ' ') {
            frequency[0]++;
        }
        else {
            frequency[ascii - 96]++;
        }
    }
    //cout << '\n';
    return frequency;
}

// this function is used to find frequencies for texts that are not of length 500
vector<int> frequencyCounter2(vector<char> total, int pos) {
    // frequency vectors are [0,a,..,z]
    vector<int> frequency(27);
    int ascii;
    for (int j = pos; j < total.size(); j++) {
        ascii = int(total[j]);
        //cout << total[j];
        if (total[j] == ' ') {
            frequency[0]++;
        }
        else {
            frequency[ascii - 96]++;
        }
    }
    //cout << '\n';
    return frequency;
}

float getIC(vector<char>& seq){
    int N = seq.size(); //Size of Alphabet
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
    vector<vector<vector<char>>> manyKeys; //3-D Vector stroring all possible key lengths and their sequences
    vector<vector<char>> aKey; //2-D Vector storing a key length and its sequences
    vector<char> seq; //One Sequence
    vector<float> avgIC; //Avg Index of Coincidence for each possible Key Length
    vector<float> individualIC; //Index of Coincidence for each Sequence
    int counter=26;
    
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
    return max_element(avgIC.begin(),avgIC.end()) - avgIC.begin()+1;
}

string decryptCipher(string cipherText, vector<int> key, int keyLength) {
    string plainText = " ";
    vector<char> alphaString = {' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int posInKey = 0;
    for (int i = 0 ; i < cipherText.length(); i++) {
        if (posInKey > keyLength-1) {
            posInKey = 0;
        }
        char plainChar = ':';
        int plainNum = 0;
        vector<char>::iterator it = find(alphaString.begin(), alphaString.end(), cipherText[i]);
        int currChar = it - alphaString.begin();
        plainNum = currChar - key[posInKey];
        if(plainNum < 0){
            plainNum = (27 + plainNum);
        }
        plainChar = alphaString[plainNum];
        plainText += plainChar;
        posInKey++;
    }
    return plainText;
}
int letterMatches (string cipherText, string plainText){
    int numMatches = 0;
    for (int i = 0; i < cipherText.length(); i++){
        if (cipherText[i] == plainText[i]){
            numMatches++;
        }
    }
    return numMatches;
}
int plainTextMatch(string cipherText){
    int theMatch = 0;
    int text1Matches,text2Matches,text3Matches,text4Matches,text5Matches = 0;
    text1Matches = letterMatches(cipherText, plainText1_string);
    text2Matches = letterMatches(cipherText, plainText2_string);
    text3Matches = letterMatches(cipherText, plainText3_string);
    text4Matches = letterMatches(cipherText, plainText4_string);
    text5Matches = letterMatches(cipherText, plainText5_string);
    vector<int> allTextMatches = {text1Matches, text2Matches, text3Matches, text4Matches, text5Matches};
    for(int i = 0; i < allTextMatches.size(); i++){
        if(allTextMatches[i] >= theMatch){
            theMatch = i;
        }
    }
    return theMatch;
}



int main(int argc, const char * argv[]) {
    ifstream ifs("dictionary.txt");
    if (!ifs) {
        cerr << "Couldn't open 'dictionary.txt'\n";
        exit(1);
    }
    
    vector<char> temp;
    char x;
    while (ifs >> noskipws >> x) {
        temp.push_back(x);
    }
    cout << endl;
    
    // each vector contains the frequency of each char
    vector<int> plainText1 = frequencyCounter(temp, 0);
    vector<int> plainText2 = frequencyCounter(temp, 501);
    vector<int> plainText3 = frequencyCounter(temp, 1002);
    vector<int> plainText4 = frequencyCounter(temp, 1503);
    vector<int> plainText5 = frequencyCounter(temp, 2004);
    
    cout << "Cyphertext: ";//Prompts user for the ciphertext to be decrpyted
    string input;
    getline(cin,input);
    int keyLength=getKeyLength(input);
    cout <<"Key Length is: " <<keyLength <<endl;
    
    // real frequencies of <space, a, ..., z>
    vector<double> alphabetFreq = {18.28846265, 6.53216702, 1.25888074, 2.23367596, 3.28292310, 10.26665037, 1.98306716, 1.62490441, 4.97856396, 5.66844326, 0.09752181, 0.56096272, 3.31754796, 2.02656783, 5.71201113, 6.15957725, 1.50432428, 0.08367550, 4.98790855, 5.31700534, 7.51699827, 2.27579536, 0.79611644, 1.70389377, 0.14092016, 1.42766662, 0.05128469}; //space to Z
    
    //convert cipherText string to vector<char> (frequencyCounter takes vector<char> as parameter)
    vector<char> cipherText;
    for (int i = 0; i < input.length(); i++){
        cipherText.push_back(input[i]);
    }
    
    // frequencies for the ciphertext
    vector<int> cipherTextFrequencies = frequencyCounter(cipherText,0);
    
    vector<int> keyValues;
    int pointer = 0;
    
    // finding each value in the key
    for (int j = 0; j < keyLength; j++) {
        // double = frequency (for cipherText), int = ascii
        vector<tuple<double, int>> thisShift;
        // double = sum, int = position in vector
        vector<tuple<double, int>> sumsForThisShift;
        
        vector<tuple<double, int>> rotatedSumsForThisShift;
        int jump = pointer;
        int ascii = 0;
        double freq = 0;
        
        // calculating this rows/shifts frequencies
        vector<char> charsForThisRound;
        for (int k = pointer; k <= (500/keyLength); k++) {
            if ( jump < 500) {
                charsForThisRound.push_back(input[jump]);
                jump += keyLength;
            }
        }
        
        vector<int> freqForThisRound = frequencyCounter2(charsForThisRound, 0);
        
        // to normalize the frequencies for this subset (so they are just a fraction)
        double ratio = (500-pointer)/keyLength;
        
        for (int y = 0; y < freqForThisRound.size(); y++){
            vector<double> sumsForThisShift1;
            for (int x = 0; x < freqForThisRound.size(); x++) {
                // divide alphabetFreq by 100 to normalize it
                double num = freqForThisRound[x]/ratio * alphabetFreq[x]/100;
                sumsForThisShift1.push_back(num);
            }
            double sum = 0;
            for (int w =0; w < sumsForThisShift1.size(); w++) {
                sum += sumsForThisShift1[w];
            }
            
            rotatedSumsForThisShift.push_back(make_tuple(sum, y));
            rotate(freqForThisRound.begin(),freqForThisRound.end()-1,freqForThisRound.end());
        }
        
        tuple<double, int> maxAndPos = rotatedSumsForThisShift[1];
        
        for (int q = 1; q < rotatedSumsForThisShift.size(); q++){
            if (get<0>(rotatedSumsForThisShift[q]) >= get<0>(maxAndPos) ) {
                maxAndPos = rotatedSumsForThisShift[q];
            }
        }
        
        keyValues.push_back(get<1>(maxAndPos)%24);
        pointer++;
    }

    string possiblePlainText = decryptCipher(input, keyValues, keyLength);
    cout << "Possible plainText: " << possiblePlainText << '\n';
    cout << "Matched with PlainText " << plainTextMatch(input) << '\n';
    
    return 0;
}
