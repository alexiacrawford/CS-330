#ifndef VCIPHER_H_
#define VCIPHER_H_
//#include "cipher.h"
#include "kcipher.h"

using namespace std;

/* A class that implements a
   Vigenere cipher class. It 
   inherts KCipher */
// TODO DONE: Implement this class

class VCipher : public KCipher {
   public:
      VCipher(string word);
      VCipher();
};

#endif

