// CS 3304 - Data Structures with Dr. Gayler
// Nathaniel Klein
// Assignment 8, Convert List To Balanced Binary Search Tree
// 03/25/16

// I implemented this assignment with this file (list_to_bbstree.cpp). I would
// have tested it with an exam file had I figured out how (and finished sooner).  
// This file was created using the bintree.h, and bintree.template files created 
// by the authors of our class textbook, Michael Main and Walter Savitch. 

// DON'T FORGET TO DO TIME ANALYSES, PRE- AND POST-CONDITIONS, CLASS INVARIANT (if necessary)

#include <iostream>
#include <list>
#include <vector>
#include "bintree.h"

using namespace std;
using namespace main_savitch_10;


template <class Item>
void display(list<int> list1);

template <class Item>
vector<int> new_structure(list<int> list1);

template <class Item>
binary_tree_node<int>* create_tree(vector<int> v, int start, int finish);

unsigned int middle(int begin, int end);

template <class Item>
int tree_depth(binary_tree_node<int>* root);


int main(int argc, char **argv)
// Library facilities used: iostream, list, vector
{
    /* Other lists:
     * 
     * Even number items
     * const list<int> ordered_num_list1 (5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100);

     * Odd number items
     * const list<int> ordered_num_list2 (5,10,15,20,25,30,35);

     * Unsorted list - odd number items:
     * list<int> list1 = {42,16,234,78,-43,45,-17,18,12,-9};
     * 
     * List of chars:
     * list<char> ordered_char_list;
     * 
	 */
     
    list<int> list1;
    
	list1.push_back(16);
	list1.push_back(234);
	list1.push_back(78);
	list1.push_back(-43);
	list1.push_back(45);
	list1.push_back(-17);
	list1.push_back(18);
	list1.push_back(12);
	list1.push_back(-9);
	list1.sort();

    cout << "Here is your original unordered list, but re-ordered:" << endl;
	display<int>(list1);
    cout << "\n\n";
        
    vector<int> v = new_structure<int>(list1);

    //cout << "Front item: " << v.front() << endl;                // For debugging purposes
    //cout << "Back item: " << v.back() << "\n" << endl;          // For debugging purposes

    int begin = 0;
    int end = list1.size()-1;
    
    binary_tree_node<int>* root = create_tree<int>(v, begin, end);

    cout << "Here is your tree: \n\n" << endl;
    int d = tree_depth<int>(root);
    print(root, d);
    
    return EXIT_SUCCESS;
}


// Postcondition: The values in the list have been pushed into
// a vector structure, and the vector structure has been returned
template <class Item>
vector<int> new_structure(list<int> list1)
// Library facilities used: list, vector
{

	vector<int> collection;
	typename list<int>::const_iterator itr;
	for(itr = list1.begin(); itr != list1.end(); ++itr){
		collection.push_back(*itr);
	}

	return collection;
    
}   // Time Analysis: Linear O(n) due to iteration through the list


// Postcondition: Tree has been created and its root has been returned
template <class Item>
binary_tree_node<int>* create_tree(vector<int> v, int begin, int end)
// Library facilities used: vector
{

	/* ALGORITHM:
	 *
	 * 1. Find middle index and set root to middle index
	 * 2. Find value at middle index and set root to that value
	 * 3. Call function recursively with mid-1 as adjusted end for left-wise recursion 
	 * 4. Set root's left child (root moves down the left side of tree with each recursive call)
     * 5. Call function recursively with mid+1 as adjusted begin for right-wise recursion
	 * 6. Set root's right child (root moves down the right side of tree with each recursive call)
     * 7. Return root
     *
	 */

	int mid = middle(begin,end);

    if(begin <= end){

        binary_tree_node<int>* root = new binary_tree_node<int>(mid);
    	int value = v[mid];
    	root->set_data(value);
        
    	binary_tree_node<int>* l_child = create_tree<int>(v, begin, mid-1);
    	root->set_left(l_child);
                
    	binary_tree_node<int>* r_child = create_tree<int>(v, mid+1, end);
    	root->set_right(r_child);
        
    	return root;
    }
    
    else
        return NULL;
        
}   // Time Analysis: Constant Time O(1)


// Postcondition: index was returned as an unsigned int
unsigned int middle(int beginning, int end){
    
	int size = (end-beginning)+1;
    unsigned int index;
    
    if(size != 0){
        index = (size/2) + beginning;
    }
    
    return index;
    
}   // Time Analysis: Constant time O(1)


// Postcondition: tree_depth was returned as an int
template <class Item>
int tree_depth(binary_tree_node<int>* root){

	int level = 0;
    if(root == NULL)
        return 0;
        
    else{
        int l_depth = tree_depth<int>(root->left());
        int r_depth = tree_depth<int>(root->right());
        if(l_depth >= r_depth)
            level = l_depth + 1;
            
        else if(l_depth < r_depth)
            level = r_depth + 1;
    }

	return level;

}   // Time Analysis: Constant time O(1)


// Postcondition: list has been sent to standard output
template <class Item>
void display(list<int> list1)
// Library facilities used: iostream, list
{

	typename list<int>::const_iterator itr;
	for(itr = list1.begin(); itr != list1.end(); ++itr){
		 cout << *itr << " ";
	 }
     
}   // Time Analysis: Linear O(n) due to iteration through the list
