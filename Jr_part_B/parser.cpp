#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* INSTRUCTION:  Complete all ** parts.
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
//    to display syntax error messages as specified by me.  

// Type of error: **
// Done by: ** 
void syntaxerror1(  ){    }
// Type of error: **
// Done by: ** 
void syntaxerror2(  ) {    }

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: **
// Done by: **
//token_type next_token(){}

// Purpose: **
// Done by: **
//boolean match(tokentype expected) {}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: <story> ::= <s> { <s> } // stay in the loop as long as a possible start
// Done by: **
void story()
{
   cout << "Processing <story>\n\n";
   S();
   while(true)
   {
      switch(next_token())
      {
         case CONNECTOR:
            S();
            break;
         case WORD1:
            S();
            break;
         case PRONOUN:
            S();
            break;
         default:
            return;
      } //end of switch
   } // end of while
}
// Grammar: <s> ::= [CONNECTOR] <noun> SUBJECT <after subject>
// Done by:
void S()
{
   cout << "Processing <s>\n";
   if(token_type == CONNECTOR)
   {
      match(CONNECTOR);
   }
   noun();
   match(SUBJECT);
   after_subject();
}

// Grammar: <after subject> ::= <verb> <tense> PERIOD | <noun> <after noun>
// Done by:
void after_subject()
{
   cout << "Processing <after subject>\n";
   switch (next_token())
   {
      case WORD2:
         verb();
         tense();
         match(PERIOD);
         break;
      case WORD1:
      case PRONOUN:
         noun();
         after_noun();
         break;
      default:
         return;
   }
}
// Grammar: <after noun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <after object>
// Done by:
void after_noun()
{
   cout << "Processing <after noun>\n";
   switch (next_token())
   {
      case IS:
      case WAS:
         be();
         match(PERIOD);
         break;
      case DESTINATION:
         match(DESTINATION);
         verb();
         tense();
         match(PERIOD);
         break;
      case OBJECT:
         match(OBJECT);
         after_object();
         break;
      default:
         return;
   }
}

// Grammar: <after object> ::= <verb> <tense> PERIOD  |  <noun> DESTINATION <verb> <tense> PERIOD
// Done by:
void after_object()
{
   cout << "Processing <after object>\n";
   switch (next_token())
   {
      case WORD2:
         verb();
         tense();
         match(PERIOD);
         break;
      case WORD1:
      case PRONOUN:
         noun();
         match(DESTINATION);
         verb();
         tense();
         match(PERIOD);
         break;
      default:
         return;
   }
}

// Grammar: <noun> ::= WORD1 | PRONOUN
// Done by:
void noun()
{
   cout << "Processing <noun>\n";
   if(token_type == WORD1)
   {
      match(WORD1);
   }
   else if (token_type == PRONOUN)
   {
      match(PRONOUN);
   }
}

// Grammar: <verb> ::= WORD2
// Done by:
void verb()
{
   cout << "Processing <verb>\n";
   match(WORD2);
}

// Grammar: <be> ::= IS | WAS
// Done by:
void be()
{
   cout << "Processing <be>\n";
   if(token_type == IS)
   {
      match(IS);
   }
   else if (token_type == WAS)
   {
      match(WAS);
   }
}

// Grammar: <tense> := VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by:
void tense()
{
   cout << "Processing <tense>\n";
   if(token_type == VERBPAST)
   {
      match(VERBPAST);
   }
   else if (token_type == VERBPASTNEG)
   {
      match(VERBPASTNEG);
   }
   else if(token_type == VERB)
   {
      match(VERB);
   }
   else if (token_type == VERBNEG)
   {
      match(VERBNEG);
   }
}

string filename;

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  Jose Romero
int main()
{
   fstream fin;
   cout << "Enter the input file name: ";
   cin >> filename;
   fin.open(filename.c_str());

  //** calls the <story> to start parsing
  story();
  while (true)
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
  //** closes the input file 
   cout << "End of File encountered" << endl;  
   fin.close();
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
