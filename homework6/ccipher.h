#ifndef CCIPHER_H_
#define CCIPHER_H_
#include "cipher.h"

using namespace std;

/* A class that implements a
   Caesar cipher class. It 
   inherits the Cipher class */
   
// TODO DONE: Implement this class

class CCipher  : public Cipher {
    public:
        CCipher(int offset = 0);
};

/* Helper function headers 
 */
void rotate_string(string& in_str, int rot);
#endif