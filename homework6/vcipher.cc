#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"
#include "vcipher.h"


// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------

string multStr(string word){
    string adds = "";
    for (int i = 0; i < 30; i++){
        adds += word;
    }
    return adds;
}

VCipher::VCipher(string word) : KCipher(multStr(word)) {}
VCipher::VCipher() : KCipher() {}