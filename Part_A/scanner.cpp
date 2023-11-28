#include<iostream>
#include<fstream>
#include<string>
#include <unordered_map>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 8
//=====================================================

// TABLES Done by: Ruben Cerda, Jose Romero

std::unordered_map<std::string, std::string> reservedWords = {
        {"masu", "VERB"},
        {"masen", "VERBNEG"},
        {"mashita", "VERBPAST"},
        {"masendeshita", "VERBPASTNEG"},
        {"desu", "IS"},
        {"deshita", "WAS"},
        {"o", "OBJECT"},
        {"wa", "SUBJECT"},
        {"ni", "DESTINATION"},
        {"watashi", "PRONOUN"},
        {"anata", "PRONOUN"},
        {"kare", "PRONOUN"},
        {"kanojo", "PRONOUN"},
        {"sore", "PRONOUN"},
        {"mata", "CONNECTOR"},
        {"soshite", "CONNECTOR"},
        {"shikashi", "CONNECTOR"},
        {"dakara", "CONNECTOR"},
        {"EOFM", "EOFM"},
        {"eofm", "eofm"}
    };


/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: **
//=====================================================

// --------- Two DFAs ---------------------------------



bool isReserveWord(string& token_type,string &str)
{
  if (reservedWords.find(str) != reservedWords.end()) { //found in the hash table
    token_type = reservedWords[str]; //get the type of token based on the word
    return true; //found
  }else {
    return false; //not found
  }
}

//helper functions 
bool isConsonant(char c){ //consonant
    return (c == 'b' || c == 'g' || c == 'h' || c == 'k' || c == 'm' || c == 'n' || c == 'p' || c == 'r' ||
    c == 's' || c == 't' );
}

bool NonConsonantPairs(char c){ //non-consonant
  return (c == 'd' || c == 'j' || c == 'w' || c == 'y' || c == 'z');
}
void word1(string& token_type,char c){ //is word 1 based on last character
    if(c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o' || c == 'n'){
      token_type = "WORD1"; 
    }
}

void word2(string& token_type,char c){ //is word 2 based on last character
    if( c == 'I' || c == 'E'){
      token_type = "WORD2";
    }
}

bool Vowel(char c){ // vowel
    return (c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o' || c == 'I' || c == 'E' );
}

/*ALL STATE NUMBERS*/
//q0 = State 0 => final state
//q1 = State 1
//qy = State 2
//qt = State 3
//qs = State 4
//qc = State 5
//qsa = State 6
//q0q1 = State 7 => final state
//q0qy = State 8 => final state

// WORD DFA
// Done by: Alexa McGinnis
// RE: ** (vowel | vowel n | consonant vowel | consonant vowel n |
// consonant-pair vowel | consonant-pair vowel n)^+

bool word(string& token_type,string& s)
{ 
  int state = 0; //starting state
  int charpos = 0; //get current position


  word1(token_type,s.back()); //check if string is word1
  word2(token_type,s.back()); //check if string is word2

  //iteriate the characters of the string
  while (s[charpos] != '\0') 
    {

      //q0 transitions
      if(state == 0){
        if(isConsonant(s[charpos])){ //bghkmpr
          state = 2;
        }
        else if(NonConsonantPairs(s[charpos])){ //dwzyi
          state = 6;
        }
        else if(Vowel(s[charpos])){ //aeiouIE
          state = 7; //new state
        }
        else if(s[charpos] == 'n'){
          state = 2;
        }
         else if(s[charpos] == 't'){
          state = 3;
        }
         else if(s[charpos] == 's'){
          state = 4;
        }
         else if(s[charpos] == 'c'){
          state = 5;
        }
        else{
          state = -1;
        }
      }
      //q1 transitions
      else if(state == 1){
        if(s[charpos] == 'n'){
          state = 0;
        }
        
        else{
          state = -1;
        }
      }
       // qy transitions
      else if(state == 2){
        if(Vowel(s[charpos])){
          state = 7;
        }
        else if(s[charpos] == 'y'){
          state = 6;
        }
        else{
          state = -1;
        }
      }
      //qt transitions
      else if(state == 3){
        if(Vowel(s[charpos])){
          state = 7;
        }
        else if(s[charpos] == 's'){
          state = 6;
        }
        else{
          state = -1;
        }
      }
      //qs Transitions
      else if(state == 4){
        if(Vowel(s[charpos])){
          state = 7;
        }
        else if(s[charpos] == 'h'){
          state = 6;
        }
        else{
          state = -1;
        }
      }
      //qc Transitions
      else if(state == 5){
        if(s[charpos] == 'h'){
          state = 6;
        }
        else{
          state = -1;
        }
      }
      //qsa Transitions
      else if(state == 6){
        if(Vowel(s[charpos])){
          state = 7;
        }
        else{
          state = -1;
        }
      }
      //q0q1 Transitions
      else if(state == 7){
        if(state = 7 && Vowel(s[charpos])){ //looping back to same state
          state = 7;
        }
        else if(s[charpos] == 'n'){
          state = 8; //new state
        }
        else if(NonConsonantPairs(s[charpos])){
          state = 6;
        }
        else if(s[charpos] == 't'){
          state = 3; 
        }
         else if(s[charpos] == 's'){
          state = 4; 
        }
         else if(s[charpos] == 'c'){
          state = 5; 
        }
        else if(isConsonant(s[charpos])){
          state = 2;
        }
        else{
          state = -1;
        }
      }
      //q0qy Transitions
      else if(state == 8){
        if(Vowel(s[charpos])){
          state = 7;
        }
        else if(NonConsonantPairs(s[charpos])){
          state = 6;
        }
        else if(s[charpos] == 't'){
          state = 3; 
        }
         else if(s[charpos] == 's'){
          state = 4; 
        }
         else if(s[charpos] == 'c'){
          state = 5; 
        }
        else if(isConsonant(s[charpos])){
          state = 2;
        }
        else{
          state = -1;
        }
      }
      else
	  {
    //no valid input from string
	  return(false);
	  }
      charpos++;
    }//end of while


  // where did I end up????
  if (state == 0 || state == 7 || state == 8) return(true);  
   else return(false);
}// end of mytoken


// PERIOD DFA
// ** Done by:Alexa McGinnis
bool period(string s)
{
  int state = 0;   //starting state
  int charpos = 0; 
  while (s[charpos] != '\0')
  {
    if (state == 0 && s[charpos]  == '.'){ // check for '.'
      state = 1;
    }
    else{
      return false; //not found
    }
    charpos++; 
  }            // End of loop

  if (state == 1)return true;  // end in a final state 
  else return false; 
}


unordered_map<string, string> position; //global hashtable(WILL NOT BE USED FOR SUBMISSION)
//Token and reserved words tables //global tables
int scannerForReadingFile(string& , string& );//(WILL NOT BE USED FOR SUBMISSION) only for reading from a file
void read(); //(WILL NOT BE USED FOR SUBMISSION)
//Token and reserved words tables //global tables
int scanner(string& ,string& );  // to be called by main
fstream fin;   // file stream to use
int main()
{ string filename;
  string theword; //string to get input
  cout << "Enter the input file name:"; //get the name of the file to read from
  cin >> filename; 
  string token_type;
  fin.open( filename.c_str(), fstream::in);
  read(); //read in the file from ReservedWords.txt(note this is only used for reading from a file, in our case we are hardcoding reservedwords when submitting)
  while (true)  // keep on going 
    {
      //call scanner to check the input string 
      scanner(token_type,theword);  

      //file use only
      //scannerForReadingFile(InputWord);
      if (theword == "eofm") {
        break; // Exit the loop when EOFM or eofm is encountered
      }
      cout << "is token type " << token_type << endl;


    }

  cout << "End of File encountered" << endl;  
  fin.close();
}// end of main 

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Ruben Cerda, Jose Romero

int scanner(string& token_type,string& w)
{
  cout << endl;
  fin >> w;  // grab next word 
  //check if token
  if(isReserveWord(token_type,w)){//check for any reserved words, so we don't start checking for word1, word2, and final states
    cout << "\"" << w << "\" ";  
    return 0;
  }
  if(word(token_type,w)){ //check transition for final states
    cout << "\"" << w << "\" ";  
    return 0;
  }
  else if (period(w)) //period case
  {
    cout << "\"" << w << "\" ";  
    token_type = "PERIOD";
    return 0;
  }
  else if( w == "EOFM" || w  == "eofm"){
      return 0;
  }

  else //none of the FAs returned true
    { cout << "Lexical Error: " << w << " is not a valid token" << endl;
      cout << "\"" << w << "\" ";
      token_type = "ERROR";
      return -1;
      }

}//the very end of scanner



//populate hash table with reserved words
//(WILL NOT BE USED FOR SUBMISSION)
void read(){
  ifstream fin;
  string word, token;
  fin.open("ReservedWords.txt");
  while (fin >> word >> token && (word != "eofm" || token != "EOFM")) {
    //Map the word to its corresponding token type string and store it in the unordered_map.
    position[word] = token;
  }
  //testing purposes
  //Traversing an unordered map 
  /*
  for (auto x : position){
     cout << x.first << " " << x.second << endl;
  }
  */
  fin.close();
}


//(WILL NOT BE USED FOR SUBMISSION) only use when reading from a file
int scannerForReadingFile(string& token_type, string& w)
{
  cout << endl;
  cout << ".....ScannerForReadingFile was called..." << endl;

  fin >> w;  // grab next word 
  cout << "\"" << w << "\" ";  
  //check if token
   if(position.find(w) != position.end()) {
    token_type = position[w];
    return 0;
  }
  if (word(token_type,w)) {
    return 0;
  } 
  else if (period(w)) {
    token_type = "PERIOD";
    return 0;
  } 
   // Check if identifier using the unordered_map

  // Add other if-then cases here to go through other FAs and set the_type to IDENT, REAL, or INT.
  else {
    cout << "Lexical Error: " << w << " is not a valid token" << endl;
    cout << "\"" << w << "\"";
    token_type = "ERROR";
    return -1;
  }

}//the very end of scanner


