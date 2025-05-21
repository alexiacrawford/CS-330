#include <string>
#include <iostream>
#include <algorithm>
#include "ccipher.h"


// -------------------------------------------------------
// Caesar Cipher implementation

string rot_alpha(int offset) {
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    rotate_string(alpha, offset);
    return alpha;
}

CCipher::CCipher(int offset) : Cipher(rot_alpha(offset)) {}


// -------------------------------------------------------


// Rotates the input string in_str by rot positions
void rotate_string(string& in_str, int rot)
{
    // TODO DONE: You will likely need this function. Implement it.
    string firstHalf = "";
    string secondHalf = "";
    int normalizedOffset = rot % 26;
    int counter = 0;
    for (char c : in_str) {
        if (counter < normalizedOffset) {
            firstHalf += c;
        } else {
            secondHalf += c;
        }
        counter += 1;
    }
    reverse(firstHalf.begin(), firstHalf.end());
    reverse(secondHalf.begin(), secondHalf.end());
    string tmp = firstHalf + secondHalf;
    reverse(tmp.begin(), tmp.end());
    in_str = tmp;
}
    

