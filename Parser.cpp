#include<iostream>
#include<fstream>
#include<string>
#include <unordered_map>
using namespace std;
void story();
void S();
void after_subject();
void after_noun();
void after_object();
void noun();
void verb();
void be();
void tense();
/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 8
//=====================================================

// TABLES Done by: Ruben Cerda, Jose Romero
string saved_token, saved_lexeme;
bool token_available = false;
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
        if(state == 7 && Vowel(s[charpos])){ //looping back to same state
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
  if (state == 0 || state == 7 || state == 8){
    return(true);  
  }
  else 
    return(false);
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

void tense();
fstream fin;   // file stream to use
int scanner(string& token_type,string& w)
{
  cout << endl;
  fin >> w;  // grab next word 
  //check if token
  cout << "Scanner called using word: " << w << endl;
  if(isReserveWord(token_type,w)){//check for any reserved words, so we don't start checking for word1, word2, and final states
    return 0;
  }
  if(word(token_type,w)){ //check transition for final states
    return 0;
  }
  else if (period(w)) //period case
  {
    token_type = "PERIOD";
    return 0;
  }
  else if( w == "EOFM" || w  == "eofm"){
      token_type = "eofm";
      return 0;
  }

  else //none of the FAs returned true
    { cout << "Lexical Error: " << w << " is not a valid token" << endl;
      token_type = "ERROR";
      return -1;
      }

}//the very end of scanner
/* INSTRUCTION: Complete all ** parts.
You may use any method to connect this file to scanner.cpp
that you had written.
e.g. You can copy scanner.cpp here by:
cp ../ScannerFiles/scanner.cpp .
and then append the two files into one:
cat scanner.cpp parser.cpp > myparser.cpp
*/
//=================================================
// File parser.cpp written by Group Number: **
//=================================================
// ----- Four Utility Functions and Globals -----------------------------------
// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
// to display syntax error messages as specified by me.
// Type of error: **
// Done by: Alexa McGinnis
void syntaxerror1(string word, string unexpected){ 
  cout << "\nSYNTAX ERROR: expected " << word << " but found in " << unexpected << endl;
  exit(1);
}
// Type of error: **
// Done by: Alexa McGinnis
void syntaxerror2(string word, string unexpected ) { 
  cout << "\nSYNTAX ERROR: unexpected " << word << " found in " << unexpected << endl;
  exit(1);

}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme
// Purpose: **
// Done by: Ruben Cerda
string next_token(){

    if(!token_available){
        scanner(saved_token,saved_lexeme);
        token_available = true;
    }
    return saved_token;


}
// Purpose: **
// Done by: Ruben Cerda
bool match(string expected) {
    if(next_token() != expected){
      syntaxerror1(expected, saved_lexeme);
    }
    else{
        token_available = false;
        return true;
    }
}

// ----- RDP functions - one per non-term -------------------
// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function
// Grammar: <story> ::= <s> { <s> } // stay in the loop as long as a possible start
// Done by: Alexa McGinnis
void story()
{
   cout << "Processing <story>\n\n";
   S(); //calling S function , non terminal
   while(next_token() != "eofm") //repeatable, keep calling S() until end of file is reached 
   {
      if(next_token() == "CONNECTOR" ){ //|| next_token() == "WORD1" || next_token() =="PRONOUN"
        S(); 
      }
   } // end of while
}
// Function prototypes


// Grammar: <s> ::= [CONNECTOR] <noun> SUBJECT <after subject>
// Done by: Jose Romero
void S()
{
   cout << "Processing <s>"; 
   if(next_token() == "CONNECTOR") //optional case
   {
      match("CONNECTOR"); //terminal match
   }
   noun(); //non-terminal call
   match("SUBJECT"); //terminal match
   after_subject(); //non-terminal call
}

// Grammar: <after subject> ::= <verb> <tense> PERIOD | <noun> <after noun>
// Done by: Ruben Cerda
void after_subject()
{
   cout << "Processing <after subject>\n";
   //two different paths can be taken, <verb> or <noun>
   if(next_token() == "WORD2"){  //<verb> path
      verb(); 
      tense(); 
      match("PERIOD"); 
   }
   else if(next_token() == "WORD1" || next_token() == "PRONOUN"){ //<noun> path
      noun(); 
      after_noun(); 
   }
   else{
    syntaxerror2(saved_lexeme, "after subject"); //could not take either path
   }
   
}
// Grammar: <after noun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <after object>
// Done by: Ruben Cerda
void after_noun()
{
   cout << "Processing <after noun>\n";
   //three different paths can be taken, <be>, DESTINATION, or OBJECT
   if(next_token() == "IS" ||next_token() ==  "WAS"){ //<be> path
      be();
      match("PERIOD");
   }
   else if(next_token() == "DESTINATION"){ //Destination path
      match("DESTINATION");
      verb();
      tense();
      match("PERIOD");
   }
   else if(next_token() == "OBJECT"){ //Object path
      match("OBJECT");
      after_object();
   }
   else{
    syntaxerror2(saved_lexeme, "after noun"); //no paths could be taken
   }
}

// Grammar: <after object> ::= <verb> <tense> PERIOD  |  <noun> DESTINATION <verb> <tense> PERIOD
// Done by: Ruben Cerda
void after_object()
{
   cout << "Processing <after object>\n";
   //two different paths can be taken, <verb> or <noun>
   if(next_token() == "WORD2"){ //<verb> path
      verb();
      tense();
      match("PERIOD");
   }
   else if(next_token() == "WORD1" || next_token() == "PRONOUN"){ //<noun> path
      noun();
      match("DESTINATION");
      verb();
      tense();
      match("PERIOD");
   }
   else{
    syntaxerror2(saved_lexeme, "after object"); //no path could be taken
   }
}

// Grammar: <noun> ::= WORD1 | PRONOUN
// Done by: Ruben Cerda
void noun()
{
   cout << "Processing <noun>\n";
   //<noun> can be either WORD1 or PRONOUN (terminals)
   if(next_token() == "WORD1")
   {
      match("WORD1");
   }
   else if (next_token() == "PRONOUN")
   {
      match("PRONOUN");
   }
   else{
    syntaxerror2(saved_lexeme, "noun"); //no match
   }
}

// Grammar: <verb> ::= WORD2
// Done by: Jose Romero
void verb()
{
   cout << "Processing <verb>\n";
   match("WORD2");
}

// Grammar: <be> ::= IS | WAS
// Done by: Jose Romero
void be()
{
   cout << "Processing <be>\n";
  //<be> can be either IS or WAS (terminals)
   if(next_token() == "IS")
   {
      match("IS");
   }
   else if (next_token() == "WAS")
   {
      match("WAS");
   }
   else{
     syntaxerror2(saved_lexeme, "be"); //no match
   }
}

// Grammar: <tense> := VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: Jose Romero
void tense()
{
   cout << "Processing <tense>\n";
   //<tense> can be either VERBPAST, VERBPASTNEG, VERB, or VERBNEG (terminals)
   if(next_token() == "VERBPAST")
   {
      match("VERBPAST");
   }
   else if (next_token() == "VERBPASTNEG")
   {
      match("VERBPASTNEG");
   }
   else if(next_token() == "VERB")
   {
      match("VERB");
   }
   else if (next_token() == "VERBNEG")
   {
      match("VERBNEG");
   }
   else{
    syntaxerror2(saved_lexeme, "tense"); //no match
   }
}

string filename;

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  Jose Romero
int main()
{
   cout << "Enter the input file name: ";
   cin >> filename;
   fin.open(filename.c_str());
   //could not open file
   if (!fin.is_open()) { 
      cout << "Error opening file: " << filename << endl;
      return 1;  // Exit with an error code
    }
  //** calls the <story> to start parsing
  story();
  fin.close();
  return 0;
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
