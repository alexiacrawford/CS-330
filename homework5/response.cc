/*
  Implementation of methods for classes Response, AngryResponse, HappyResponse
*/
#include <iostream>
#include <string>
#include <algorithm>

#include "response.h"

using namespace std;

/*
  Implementation of Word class
  Don't worry too hard about these implementations.
  If you'd like to learn more about STL see: 
    https://www.geeksforgeeks.org/the-c-standard-template-library-stl/
*/
string Word::upper()
{
  string result(theWord);
  transform(result.begin(), result.end(), result.begin(), ::toupper);
  return result;
}

string Word::lower()
{
  string result(theWord);
  transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

/*
  Implementation of Response methods
*/
bool Response::checkAndRespond(const string& inWord, ostream& toWhere)
{
  if (inWord.find(keyword.upper()) != string::npos) {
        respond(toWhere); // Call the appropriate response function
        return true;
    }
    return false;

    // TODO: DONE
    // This method should check if the current object's keyword is in the
    // input message (inWord), and send the proper response to the toWhere
    // output stream
    // String class provides the function 'find' which you might find useful
}

void Response::respond(ostream& toWhere)
{
  toWhere << "I am neither angry nor happy: " << response << endl;
    // TODO: DONE
    // This method should 'insert' "I am neither angry nor happy: " followed by
    // the object's response word to the toWhere output stream, along with
    // a newline at the end
}


void AngryResponse::respond(ostream& toWhere)
{
  toWhere << "I am angry: " << response << endl;
  // TODO: DONE
  // Implement the 'respond' member function for the AngryResponse class so that
  // the angry rseponse "I am angry: " followed by the object's response word 
  // is inserted to the toWhere output stream, along with a newline at the end
}


/*
  Implementation of HappyResponse methods
*/
// TODO: DONE BELOW
// Implement the 'respond' member function for the HappyResponse class so that
// the happy rseponse "I am happy: " followed by the object's response word 
// is inserted to the toWhere output stream, along with a newline at the end

void HappyResponse::respond(ostream& toWhere)
{
  toWhere << "I am happy: " << response << endl;
}