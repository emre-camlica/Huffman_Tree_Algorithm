//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Emre Çamlıca
//---Student Number: 150210071
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue(){
    //TODO
    this->head = NULL;
};

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node* newnode){                                          
    //TODO                                                                                
    if(this->head == NULL){                                                          // If the queue is empty, first node to come             
    this->head = newnode;                                                            // becomes the head.
    return;                                                                           
    }           

    if(newnode->token.val < this->head->token.val){                                  // Before traversing, check if the newnode's 
    newnode->next = this->head;                                                      // value is smaller than head's value, if so;   
    this->head = newnode;                                                            // it becomes the new head.
    return;
    }

    Node* temp = head;

    while(temp->next != NULL && temp->next->token.val <= newnode->token.val){        // Traverse the queue starting from the head
        temp = temp->next;                                                           // until finding a node with a bigger value
    }                                                                                // or until the end of the queue is reached.
    newnode->next = temp->next;                                                      // Then, add the node before the one with the
    temp->next = newnode;                                                            // bigger value (or after the last node).
};                                                                                   // Note that "<=" includes the possibility of 
                                                                                     // two values being equal.
//-------------Remove Node From Priority Queue-------------//
Node* PriorityQueue::dequeue(){
    //TODO    
    Node* temp = this->head;                                                         // Remove the first element from the queue, 
    this->head = this->head->next;                                                   // make the next of it as the new head and 
    temp->next = NULL;                                                               // make the previous head's next NULL to avoid
    return temp;                                                                     // possible conflicts in the future.
};

//-------------Initialize Tree-------------//
Tree::Tree(){
    //TODO
    this->root = NULL;
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree(){                                                                       // Send the root to the deletetree function,
    //TODO                                                                           // which deletes the tree recursively starting
    deleteTree(this->root);                                                          // from the root.
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node* node){                                                   // Recursively deletes the tree starting from 
    //-------------This Function Is Not Necessary-------------//                     // the given node (root) using a post order
    //-----------------Use It At Your Own Will----------------//                     // traversal.
    if(node->left!=NULL){
        deleteTree(node->left);
    }

    if(node->right!=NULL){
        deleteTree(node->right);
    }

    delete node;
}

//-------------Merges Two Node Into One-------------//
Node* Tree::mergeNodes(Node* temp1, Node* temp2){                                     
   //TODO
   Node* merged = new Node();                                                         // Allocate memory for the Node to be returned.
   merged->left = temp1;
   merged->right = temp2;
   merged->token.symbol = temp1->token.symbol + temp2->token.symbol;                  // Concatenate two strings (token symbols).
   merged->token.val = temp1->token.val + temp2->token.val;                           // Add the two given token values.
   return merged;                                                                       
};

void Tree::printTree(Node* traverse, int level){
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t"; 

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if(traverse->left)
        printTree(traverse->left, level + 1);  
    if(traverse->right)
        printTree(traverse->right, level + 1);
};