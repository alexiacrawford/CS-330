#include <string>
#include <iostream>
#include "rcipher.h"

// -------------------------------------------------------
// ROT13 Cipher implementation
// -------------------------------------------------------

RCipher::RCipher() : CCipher(13){} //new subclass pass thorugh rot str
