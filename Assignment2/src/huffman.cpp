//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Emre Çamlıca
//---Student Number: 150210071
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-----------------------------------------------------//
//-----------Reads the key from text file--------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::readKey(const char* argv){
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if(readKeyFile.is_open()){
        while(!readKeyFile.eof()){
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------Sorts the key in an alpabetic order---------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::sortKey(){
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency(){
    //DO NOT CHANGE THIS
    sortKey();
    //DO NOT CHANGE THIS
    
    //TODO
    char temp = sortedKey[0];                                       // Initially set temp equal to first character in the sorted key.
    int val = 0;                                                    // And the val equal to 0.
    for(int i=1; i<=(int)sortedKey.length(); i++){                  // Check for each character appearance in the sorted key.
        val++;                                                      // Increment val for each loop.
        if(temp!=sortedKey[i]){                                     // If the character is different from the previous one:
            Node* t = new Node();                                   // Create a new node:
            t->token.symbol = temp;                                 // With the symbol before the change 
            t->token.val = val;                                     // and the value added up.
            this->queue.enque(t);                                   // enqueue the node after the symbol and value is set.
            temp = sortedKey[i];                                    // Set character to the new one for the next loop.
            val = 0;                                                // restart the value count.
        }
    }
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree(){
    //TODO
    findFrequency();                                                 // Form the priority queue before creating the tree.
    while(queue.head->next != NULL){                                 // Until one node remains in the queue:
        Node* temp1 = queue.dequeue();                               // Dequeue two Nodes one by one from (the head of) the queue
        Node* temp2 = queue.dequeue();
        queue.enque(huffmanTree.mergeNodes(temp1, temp2));           // Merge the two Nodes coming from the beginning of the queue
    }                                                                // and enqueue the merged Node.
    huffmanTree.root = queue.head;                                   // Set the only remaining node as the root of the tree,
};                                                                   // which includes all characters and has the highest value.
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printHuffmanTree(){
    huffmanTree.printTree(huffmanTree.root, 0);
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//
string Huffman::getTokenBinary(char tokenChar, Node* traverse, string tokenBinary){ 
    //TODO

    /* Base condition for returning tokenbinary where there is only one character in the symbol which equals to the given character. */

    if(traverse->token.symbol[0] == tokenChar && traverse->token.symbol.length() == 1)
    return tokenBinary;

    /* Look for whether the given character belongs to the left or the right sub-tree. If it belongs to the left, check for the same
    for the left sub-tree, appending "0" to the tokenBinary and returning tokenBinary, when the base condition is reached the 
    tokenBİnary string displays the path to the given character in the tree. If it belongs to the right, do the same appending "1". */

    for(int i=0; i<(int)traverse->left->token.symbol.length(); i++){
        if(traverse->left->token.symbol[i] == tokenChar){
            return tokenBinary = getTokenBinary(tokenChar, traverse->left, tokenBinary.append("0"));
        }
    }

    for(int i=0; i<(int)traverse->right->token.symbol.length(); i++){
        if(traverse->right->token.symbol[i] == tokenChar){
            return tokenBinary = getTokenBinary(tokenChar, traverse->right, tokenBinary.append("1"));
        }    
    }
    return 0;                                                       // "Return 0" is put to prevent errors.
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
void Huffman::encodePassword(string password){
    //TODO

    /*For each character in the given password: Append the binary path and the length of that path to the related encoded strings.
    Note that empty string is sent to getTokenBinary function in the beginning to be filled up.*/

    for(int i=0; i<(int)password.length(); i++){
        encodedBinaryPassword.append(getTokenBinary(password[i], huffmanTree.root, ""));
        encodedValPassword.append(to_string((getTokenBinary(password[i], huffmanTree.root, "")).length()));
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword(){
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword){
    //TODO
    int i,j;                                                        // Initialize i to start counting from the first index of the  
    i=0;                                                            // encoded binary password.
    int count=0;                                                    // count represents the end limit of each binary string
    string encodedToken;                                            // corresponding to each encoded character.
    for(j=0; j<(int)encodedValPassword.length(); j++){              // For each value in the value password: 
        count += (int)encodedValPassword[j]-48;                     // Increment count by size of the binary code for each character.
        for(;i<count; i++){                                         // i keeps incrementing until reaching the next character.
            encodedToken += encodedBinaryPassword[i];               // Append each binary value to the encoded token
        }                                                           //
        decodeToken(encodedToken);                                  // Find the corresponding character for the binary value stored.
        encodedToken.erase();                                       // restart encoding the token for the next character.
    }


};

//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
void Huffman::decodeToken(string encodedToken){
    //TODO
    Node *temp = huffmanTree.root;                                   // Initialize a temporary pointer to the root before searching
    for(int i=0; i<(int)encodedToken.length(); i++){                 // For each binary character in the encoded token:
        if((int)encodedToken[i]-48 == 0)                             // Go left if the binary value is "0", go right if it is "1"
        temp = temp->left;                                           // (-48 is put to make the ASCII conversion correctly.)
        else if((int)encodedToken[i]-48 == 1)
        temp = temp->right;
    }                                                                // At the end, temp reaches the encoded token character. 
    decodedPassword += temp->token.symbol;                           // Append the character found to the decoded password.
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword(){
    cout << "Decoded Password: " << decodedPassword << endl;
};