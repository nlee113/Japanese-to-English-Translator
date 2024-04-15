#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: ** 4
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA
// Done by: Francesca, Valentyn

/*States 
    q0 = 0
    q0q1 = 1
    qsa = 2
    qy = 3
    qoqy = 4
    qt = 5
    qs = 6
    qc = 7

    V = a, e, i, o, u, I, E
    D = d, w, z, y, j
    B = b, g, h, k, m, p, r
    final states q0, q0q1, q0qy = 0, 1, 4
    */
bool word(string s)
{
    int state = 0;
    int charpos = 0;
    transform(s.begin(), s.end(), s.begin(), ::tolower);

    while (s[charpos] != '\0') {
        // q0 on a V to q0q1
        if 
            (state == 0 && s[charpos] == 'a' ||
            state == 0 && s[charpos] == 'e' ||
            state == 0 && s[charpos] == 'i' ||
            state == 0 && s[charpos] == 'o' ||
            state == 0 && s[charpos] == 'u' ||
            state == 0 && s[charpos] == 'I' ||
            state == 0 && s[charpos] == 'E'){
            state = 1;
        }

      // q0 on a D to QSA
      else if (state == 0 && s[charpos] == 'd' ||
          state == 0 && s[charpos] == 'w' ||
          state == 0 && s[charpos] == 'z' ||
          state == 0 && s[charpos] == 'y' ||
          state == 0 && s[charpos] == 'j'){
            state = 2;
        }
      
      //q0 on B,n to qy
        else if (state == 0 && s[charpos] == 'b' ||
          state == 0 && s[charpos] == 'g' ||
          state == 0 && s[charpos] == 'h' ||
          state == 0 && s[charpos] == 'k' ||
          state == 0 && s[charpos] == 'm' ||
          state == 0 && s[charpos] == 'p' ||
          state == 0 && s[charpos] == 'r' ||
          state == 0 && s[charpos] == 'n'){
            state = 3;
        }

          //q0 on t to qt
          else if (state == 0 && s[charpos] == 't'){
          state = 5;
          }
            //q0 on s to qs
            else if (state == 0 && s[charpos] == 's'){
            state = 6;
            }
              //q0 on c to qc
              else if (state == 0 && s[charpos] == 'c'){
              state = 7;
              }


      //q0q1 on a V to q0q1
      else if (state == 1 && s[charpos] == 'a' ||
          state == 1 && s[charpos] == 'e' ||
          state == 1 && s[charpos] == 'i' ||
          state == 1 && s[charpos] == 'o' ||
          state == 1 && s[charpos] == 'u' ||
          state == 1 && s[charpos] == 'I' ||
          state == 1 && s[charpos] == 'E'){
            state = 1;
            }
        //q0q1 on a B to qy
        else if (state == 1 && s[charpos] == 'b' ||
            state == 1 && s[charpos] == 'g' ||
            state == 1 && s[charpos] == 'h' ||
            state == 1 && s[charpos] == 'k' ||
            state == 1 && s[charpos] == 'm' ||
            state == 1 && s[charpos] == 'p' ||
            state == 1 && s[charpos] == 'r'){

        state = 3;

        }

          //q0q1 on a D to qsa
          else if (state == 1 && s[charpos] == 'd' ||
              state == 1 && s[charpos] == 'w' ||
              state == 1 && s[charpos] == 'z' ||
              state == 1 && s[charpos] == 'y' ||
              state == 1 && s[charpos] == 'j'){

          state = 2;

          }

            //q0q1 on a D to qsa
            else if (state == 1 && s[charpos] == 'd' ||
                state == 1 && s[charpos] == 'w' ||
                state == 1 && s[charpos] == 'z' ||
                state == 1 && s[charpos] == 'y' ||
                state == 1 && s[charpos] == 'j'){

            state = 2;

            }

              //q0q1 on t to qt
              else if (state == 1 && s[charpos] == 't'){

              state = 5;

              }
                //q0q1 on s to qs
                else if (state == 1 && s[charpos] == 's'){

                state = 6;

                }
                  //q0q1 on c to qc
                  else if (state == 1 && s[charpos] == 'c'){

                  state = 7;

                  }
                    //q0q1 on n to q0qy
                    else if (state == 1 && s[charpos] == 'n'){

                    state = 4;

                    }
                      //qsa on a V to q0q1
                      else if (state == 2 && s[charpos] == 'a' ||
                          state == 2 && s[charpos] == 'e' ||
                          state == 2 && s[charpos] == 'i' ||
                          state == 2 && s[charpos] == 'o' ||
                          state == 2 && s[charpos] == 'u' ||
                          state == 2 && s[charpos] == 'I' ||
                          state == 2 && s[charpos] == 'E'){

                      state = 1;

                      }
                        //qy on a V to q0q1
                        else if (state == 3 && s[charpos] == 'a' ||
                            state == 3 && s[charpos] == 'e' ||
                            state == 3 && s[charpos] == 'i' ||
                            state == 3 && s[charpos] == 'o' ||
                            state == 3 && s[charpos] == 'u' ||
                            state == 3 && s[charpos] == 'I' ||
                            state == 3 && s[charpos] == 'E'){

                        state = 1;

                        }

                          //qy on a y to qsa
                          else if (state == 3 && s[charpos] == 'y'){

                          state = 2;

                          }

                            //q0qy on a V to q0q1
                            else if (state == 4 && s[charpos] == 'a' ||
                                state == 4 && s[charpos] == 'e' ||
                                state == 4 && s[charpos] == 'i' ||
                                state == 4 && s[charpos] == 'o' ||
                                state == 4 && s[charpos] == 'u' ||
                                state == 4 && s[charpos] == 'I' ||
                                state == 4 && s[charpos] == 'E'){

                            state = 1;

                            }

                              //q0qy on a D to qsa
                              else if (state == 4 && s[charpos] == 'd' ||
                                  state == 4 && s[charpos] == 'w' ||
                                  state == 4 && s[charpos] == 'z' ||
                                  state == 4 && s[charpos] == 'y' ||
                                  state == 4 && s[charpos] == 'j'){

                              state = 2;

                              }

                                //q0qy on B,n to qy
                                else if (state == 4 && s[charpos] == 'b' ||
                                  state == 4 && s[charpos] == 'g' ||
                                  state == 4 && s[charpos] == 'h' ||
                                  state == 4 && s[charpos] == 'k' ||
                                  state == 4 && s[charpos] == 'm' ||
                                  state == 4 && s[charpos] == 'p' ||
                                  state == 4 && s[charpos] == 'r' ||
                                  state == 4 && s[charpos] == 'n'){

                                state = 3;

                                }

                                  //q0qy on t to qt
                                  else if (state == 4 && s[charpos] == 't'){

                                  state = 5;

                                  }
                                    //q0qy on s to qs
                                    else if (state == 4 && s[charpos] == 's'){

                                    state = 6;

                                    }
                                      //q0qy on c to qc
                                      else if (state == 4 && s[charpos] == 'c'){

                                      state = 7;

                                      }

                                        // qt on a V to q0q1
                                        else if (state == 5 && s[charpos] == 'a' ||
                                          state == 5 && s[charpos] == 'e' ||
                                          state == 5 && s[charpos] == 'i' ||
                                          state == 5 && s[charpos] == 'o' ||
                                          state == 5 && s[charpos] == 'u' ||
                                          state == 5 && s[charpos] == 'I' ||
                                          state == 5 && s[charpos] == 'E'){

                                        state = 1;

                                        }

                                          //qt on s to qsa
                                          else if (state == 5 && s[charpos] == 's'){

                                          state = 2;

                                          }

                                            //qs on a V to q0q1
                                            else if (state == 6 && s[charpos] == 'a' ||
                                                state == 6 && s[charpos] == 'e' ||
                                                state == 6 && s[charpos] == 'i' ||
                                                state == 6 && s[charpos] == 'o' ||
                                                state == 6 && s[charpos] == 'u' ||
                                                state == 6 && s[charpos] == 'I' ||
                                                state == 6 && s[charpos] == 'E'){

                                            state = 1;

                                            }
                                              //qs on h to qsa
                                              else if (state == 6 && s[charpos] == 'h'){

                                              state = 2;

                                              }

                                                //qc on h to qsa
                                                else if (state == 7 && s[charpos] == 'h'){

                                                state = 2;

                                                }
      
      else{
	       return(false);
      }
      charpos++;
    }//end of while

  // where did I end up????
  if (state == 4){ return(true);}  // end in a final state
   else if (state == 1){ return(true);}
     else if (state == 0){ return(true);}
   else { return(false);}
  
}

// PERIOD DFA
// Done by: ** Francesca, Valentyn
bool period(string s) {
    int state = 0; // Initial state
    int charpos = 0; // Character position

    while (s[charpos] != '\0') {
        if (state == 0 && s[charpos] == '.')
        state = 1;
        else {
            return false; // If the state is not 0, return false
        }
        charpos++; // Move to the next character
    }
  // where did I end up????
  if (state == 1) return(true); // end in a final state
  else return(false);
}
// ------ Three  Tables -------------------------------------

// TABLES Done by: ** Nalani 

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype { ERROR, WORD1, WORD2, PERIOD, EOFM, 
                VERB, VERBNEG, VERBPAST, VERBPASTNEG, 
                IS, WAS, OBJECT, SUBJECT, DESTINATION, 
                PRONOUN, CONNECTOR };
// ** For the display names of tokens - must be in the same order as the tokentype.                                                                                                                                               
string tokenName[30] = { "ERROR", "WORD1", "WORD2", "PERIOD", "EOFM", 
                        "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", 
                        "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", 
                        "PRONOUN", "CONNECTOR" };

// ** Need the reservedwords table to be set up here.
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.

struct reserved
{
    const char* string;
    tokentype tokenT; 
}

reserved[] = {
  {"masu",VERB},
  {"masen",VERBNEG},
  {"mashita",VERBPAST},
  {"masendeshita",VERBPASTNEG},
  {"desu",IS},
  {"deshita",WAS},
  {"o", OBJECT},
  {"wa", SUBJECT},
  {"ni", DESTINATION},
  {"watashi",PRONOUN},
  {"anata",PRONOUN},
  {"kare",PRONOUN},
  {"kanojo", PRONOUN},
  {"sore", PRONOUN},
  {"mata",CONNECTOR},
  {"soshite", CONNECTOR},
  {"shikashi", CONNECTOR},
  { "dakara", CONNECTOR}
};


// ------------ Scanner and Driver ----------------------- 

fstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Nalani and Valentyn
int scanner(tokentype& tt, string& w)
{

  fin >> w; // ** Grab next word from fain.txt
  // 1. If it is eofm, return right now.
  
  //if EOF return to main
  if (w == "eofm") { 
    tt = EOFM;
    return 0;
    } 

  /*  **
  2. Call the token functions (word and period) 
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.

  3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.

  4. Return the token type & string  (pass by reference)
  */
  int rowCount = sizeof reserved/ sizeof reserved[0];
	//cout<<"Row Count"<< rowCount <<endl;

        cout<<"\n";

	if(word(w)) // call word 
	  {
	    for (int i = 0; i < rowCount; i++)
		{
		  if (w == reserved[i].string) // reserved word
			{
				tt = reserved[i].tokenT;
                cout <<"\""<< w << "\" is token type " << tokenName[tt] << endl;
				return 0;
			}
		}
	    
	    char lastLetter = ' ';
	      lastLetter = w[(w.length()-1)];

	      // not reserved
	    if (lastLetter == 'I' || lastLetter == 'E')
	      {
		tt = WORD2;
        cout <<"\""<< w << "\" is token type " << tokenName[tt] << endl;
	      }
	    else
	      {
		tt = WORD1;
        cout <<"\""<< w << "\" is token type " << tokenName[tt] << endl;
	      }
	}
	else if(period(w)) // call period
	  {
	    tt = PERIOD;
        cout <<"\""<< w << "\" is token type " << tokenName[tt] << endl;
	  }
	else if(w == "eofm")
	  { //do nothing
	  }
	else
	  {
	    cout << "LEXICAL ERROR: "<< w <<" is not a valid token \n";
	    tt = ERROR;
	  }


	return 0;
}