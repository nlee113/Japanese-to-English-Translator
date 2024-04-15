#include<iostream>
#include<fstream>
#include<string>
#include "scanner.cpp"
using namespace std;

/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/

//Array for the English words
string eWords[47][2] = { {"watashi","I/me"},{"anata", "you"},
{"kare", "he/him"},{"kanojo","she/her"},{"sore","it"},
{"mata","Also"},{"soshite","Then"},{"shikashi","However"},
{"dakara","Therefore"},{"daigaku","college"},{"kurasu", "class"},
{"hon","book"},{"tesuto","test"},{"ie","home"},
{"isu", "chair"},{"seito","student"},{"sensei","teacher"},
{"tomodachi","friend"},{"jidoosha", "car"},{"gyuunyuu","milk"},
{"biiru","beer"},{"choucho","butterfly"},{"ryouri", "cooking"},
{"toire","restroom"},{"gohan","meal"},{"yasashii","easy"},
{"muzukashii", "difficult"},{"ureshii","pleased"},{"shiawase","happy"},
{"kanashii","sad"},{"omoi", "heavy"},{"oishii","delicious"},
{"tennen","natural"},{"nakI","cry"},{"ikI", "go"},
{"tabE","eat"},{"ukE","take"},{"kakI","write"},
{"yomI", "read"},{"nomI","drink"},{"agE","give"},
{"moraI","receive"},{"butsI", "hit"},{"kerI","kick"},
{"shaberI","talk"},{"yarI","do"},{"yorokobI","enjoy"} };

//=================================================
// File translator.cpp written by Group Number: ** 4
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: **  


// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
//  Done by: ** Francesca Sosa
//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: ** Nalani Dela Rosa

// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.

//================================================================

bool syntaxerror1 = false;
bool syntaxerror2 = false;
tokentype saved_token; //token
string saved_lexeme; //word
bool token_available = false; //global flag indicating whether we have saved a token to eat up or not
string saved_eWord; //english translation


void s();
void after_subject();
void after_noun();
void after_object();
void noun();
void verb();
void be();
void tense();

ofstream outFile;

//getEword()
// Done by: ** Francesca Sosa
                                                        //match Japanese word to corresponding English word
void getEword() {
    for (int i = 0; i < 47; i++)
    {                                                   //go through array of Japanese and English words
        if (saved_lexeme.compare(eWords[i][0]) == 0)
        {                                               //compare saved word with japanese word
            saved_eWord = eWords[i][1];
            return;
        }
    }
    saved_eWord = saved_lexeme;
    return;
}

//gen(line_type)
// Done by: ** Nalani Dela Rosa
// gen sends a line of an IR to translated.txt
void gen(string line_type) {
    if (line_type == "TENSE") {
        outFile << line_type << "  " << tokenName[saved_token] << endl; // Assuming tokenName[] holds the token names
    }
    else {
        outFile << line_type << " " << saved_eWord << endl; // Write line_type to the file
    }
}

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .
       and then append the two files into one:
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: ** 4
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.

//moved "bool syntaxerror1 = false" & "bool syntaxerror2 = false" above

// Type of error: ** Token not found/doesn't match
// Done by: ** Francesca Sosa
void syntax_error1(string saved_lexeme, tokentype tkn_type)
{
    cout << "SYNTAX ERROR 1 OCCURED: " << tokenName[tkn_type] << " was not found, but found " << saved_lexeme << " instead." << endl;
    syntaxerror1 = true; //syntaxerror1 intitally set to false -> turned true when token isn't found/doesn't match
    exit(1);

}
// Type of error: ** Lexeme doesn't match tokentype
// Done by: ** Francesca Sosa
void syntax_error2(string saved_lexeme, string parserFunct)
{
    cout << "SYNTAX ERROR 2 OCCURED: " << saved_lexeme << " is found in " << parserFunct << endl;
    syntaxerror2 = true; //syntaxerror2 intitally set to false -> turned true when lexeme found in parser function
    exit(1);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

//moved "tokentype saved_token," "string saved_lexeme," and "bool token_available = false" above

// Purpose: **calls scanner & updates token and lexeme
// Done by: **Valentyn Protsyuk
tokentype next_token() {
    if (!token_available) { //no token yet
        scanner(saved_token, saved_lexeme); // call scanner to grab a new token
        token_available = true; // mark that fact that you have saved it
    }
    return saved_token; // return the saved token
}

// Purpose: **compares tokens and eats it up a to keep parsing, or displays syntax error
// Done by: **Valentyn Protsyuk
bool match(tokentype expected) {
    if (next_token() != expected) { // mismatch
      // calls a syntax error function here to generate a syntax error message here and do recovery
        syntax_error1(saved_lexeme, expected);
        return false;
    }
    else { // match
        token_available = false; // eat up the token
        return true;
    }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: **1. <story>::= <s> {<s>}
// Done by: ** Valentyn Protsyuk
void story() {
    cout << "processing <story>" << endl;
    s();
    while (true && (saved_lexeme != "eofm")) {
        switch (next_token()) {
            //s starts with either connector or a noun
        case CONNECTOR:
            s();
            break;
            //noun can be word1 or pronoun
        case WORD1:
            s();
            break;
        case PRONOUN:
            s();
            break;
            //handle error
        default:
            return; //exit the loop no need for error
        }
        cout << "\nsuccessfully parsed story" << endl;
    }
}

// -------------------------------------------------------------------

// Grammar: **2. <s> ::= [CONNECTOR #getEword# #gen ("CONNECTOR")#] <noun> #getEword# SUBJECT #gen("ACTOR")# <after subject>
// Done by: ** Valentyn Protsyuk
void s() {
    cout << "processing <s>" << endl;
    //optional [CONNECTOR]
    if (next_token() == CONNECTOR) { // if there is a CONNECTOR match it
        match(CONNECTOR);
        getEword();
        gen("CONNECTOR");
    }

    //handle <noun>
    noun();

    //match SUBJECT
    match(SUBJECT);

    gen("ACTOR");

    //handle everything <after subject>
    after_subject();
}

// -------------------------------------------------------------------

// Grammar: ** <noun> ::= WORD1 | PRONOUN
// Done by: ** Francesca Sosa
void noun()
{
    cout << "processing <noun>" << endl;
    switch (next_token())  // look ahead at next token                                                                        
    {
    case  WORD1:
        match(WORD1);
        getEword();
        break;
    case  PRONOUN:
        match(PRONOUN);
        getEword();
        break;
    default:
        syntax_error2(saved_lexeme, "noun");  // handling error, no alternatives fit                                                                                                                            
    }
}

// -------------------------------------------------------------------


// Grammar: **3. <after subject>::= <verb>#getEword# #gen("ACTION")# <tense> #gen("TENSE")# PERIOD | <noun> #getEword# <after noun>
// Done by: ** Valentyn Protsyuk
void after_subject() {
    cout << "processing <after subject>" << endl;
    //handle options <noun> / <verb>
    switch (next_token()) {
    case WORD2:  //verb can be only WORD2
        verb();
        tense();
        match(PERIOD);
        break;
        //noun can be word1 or pronoun
    case WORD1:
        noun();
        after_noun();
        break;
    case PRONOUN:
        noun();
        after_noun();
        break;
        //handle error
    default:
        syntax_error2(saved_lexeme, " after_subject()"); //unexpected word
        break;
    }
}

// -------------------------------------------------------------------

// Grammar: ** <verb> ::= WORD2
// Done by: ** Francesca Sosa
void verb()
{
    cout << "processing <verb>" << endl;
    switch (next_token())
    {
    case  WORD2:
        match(WORD2);
        getEword();
        gen("ACTION");
        break;
    default:
        syntax_error2(saved_lexeme, "verb");
    }
}

// -------------------------------------------------------------------

// Grammar: ** <be> ::= IS | WAS
// Done by: ** Nalani Dela Rosa
void be() {
    cout << "processing <be>" << endl;
    switch (next_token()) {
    case IS:
        match(IS);
        gen("TENSE");
        break;
    case WAS:
        match(WAS);
        gen("TENSE");
        break;
    default:
        syntax_error2(saved_lexeme, "be");
    }
}

// -------------------------------------------------------------------

// Grammar: ** <after noun> ::= <be> #gen("DESCRIPTION")# #gen("TENSE")# <tense> #gen("TENSE")# PERIOD | DESTINATION #gen("TO")# <verb> #getEword# #gen("ACTION")# <tense> #gen("TENSE")# PERIOD|OBJECT #gen("OBJECT")# <after object>
// Done by: ** Francesca Sosa
void after_noun()
{
    cout << "processing <after noun>" << endl;
    switch (next_token()) //check next token       
    {
    case  IS:
        be();
        gen("DESCRIPTION");
        match(PERIOD);
        break;

    case  WAS:
        be();
        gen("DESCRIPTION");
        match(PERIOD);
        break;

    case DESTINATION:
        match(DESTINATION);
        gen("TO");
        verb();
        tense();
        match(PERIOD);
        break;

    case OBJECT:
        match(OBJECT);
        gen("OBJECT");
        after_object();
        break;

    default:
        syntax_error2(saved_lexeme, "after_noun"); //handling error -> needed b/c using switch               
    }
}


// -------------------------------------------------------------------

// Grammar: ** <after object>::= <verb> #getEword# #gen(â€œACTIONâ€)# <tense> #gen(â€œTENSEâ€)# PERIOD | <noun>#getEword# DESTINATION #gen(â€œTOâ€)# <verb> #getEword# #gen(â€œACTIONâ€)# <tense> #gen(â€œTENSEâ€)# PERIOD
// Done by: ** Nalani Dela Rosa
void after_object() {
    cout << "processing <after object>" << endl;
    switch (next_token()) {
    case WORD2:
        verb();
        tense();
        match(PERIOD);
        break;
    case WORD1:
        noun();
        match(DESTINATION);
        gen("TO");
        verb(); //added 
        tense(); //added
        match(PERIOD); // forgot this part -> partBtest1 fails. stopped after agE mashita . 
        break;
    case PRONOUN:
        noun();
        match(DESTINATION);
        getEword();
        gen("TO");
        verb(); //added
        tense(); //added 
        match(PERIOD); //added
        break;
    default:
        syntax_error2(saved_lexeme, "after_object");
    }
}

// -------------------------------------------------------------------

// Grammar: ** <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: ** Nalani Dela Rosa
void tense() {
    cout << "processing <tense>" << endl;
    switch (next_token()) {
    case VERBPAST:
        match(VERBPAST);
        getEword();
        gen("TENSE");
        break;
    case VERBPASTNEG:
        match(VERBPASTNEG);
        getEword();
        gen("TENSE");
        break;
    case VERB:
        match(VERB);
        getEword();
        gen("TENSE");
        break;
    case VERBNEG:
        match(VERBNEG);
        getEword();
        gen("TENSE");
        break;
    default:
        syntax_error2(saved_lexeme, "tense");
    }
}

int const R = 47; // number of rows
int const C = 2; // number of columns
vector<string> dictionary[R][C]; // 47 rows and 2 columns table
// ------------------ Functions --------------------------------

void populateDictionary()
{
    int col; // row and col numbers
    int counter = 0;
    int row = 0;

    ifstream lex("lexicon.txt", ios::in);
    // Read in the file into T
    while (!lex.eof())
    {
        string lw; // one word from the file
        vector<string> v; // a vector to fill
        col = counter % 2;//col changes between 0 and 1

        lex >> lw;                         //copy letter from file to c
        v.push_back(lw);                   //add c to the vector

        dictionary[row][col] = v;

        if (counter % 2 == 1) {//next row when second column was filled
            row++;
        }

        counter++;
    }//end of while
    lex.close();
}
// Displays a single vector entry 
//japanese words in column 0, english words in column 1
//ex:showVector(dictionary[row][col]);
string getWord(vector<string> v)
{
    for (auto word : v) { return word; }
}
/*
//not needed for part C
// Displays lexon table
void displayDictionary()
{
  for (int i = 0; i < R; i++){      //go through rows
    cout << "\n" << i << "| ";      //start a new line & print row#
    for(int j = 0; j < C; j++){     //go through columns
      cout<< getWord(dictionary[i][j]);          //display each vector
      cout <<"| ";                  //sepaarate vectors
    }
  }
}
*/


// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by:  **
int main()
{
    string filename;
    //** opens the lexicon.txt file and reads it into Lexicon
    //** closes lexicon.txt 

    //** opens the output file translated.txt
    populateDictionary();//fills the table must be in main
    //displayDictionary();//not needed for part C: displays lexicon table

    /* //Dictionary use case example
    cout<< getWord(dictionary[46][0])<<endl;
    if(getWord(dictionary[46][0])=="yorokobI"){
      cout<<"enjoy"<<endl;
    }
    */
    outFile.open("translated.txt");

    cout << "Enter the input file name: ";
    cin >> filename;
    fin.open(filename.c_str());

    //** calls the <story> to start parsing
    story();
    ifstream inFile("translated.txt");
    string line;
    while (getline(inFile, line)) {
        cout << line << std::endl;
    }
    //** closes the input file 
    fin.close();
    //** closes traslated.txt
    outFile.close();
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
