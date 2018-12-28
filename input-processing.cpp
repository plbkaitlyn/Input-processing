/*
 Assignment 1
 Student name: Phuong Linh Bui
 Student number: 5624095
 Student login: plb070
 */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <locale>
#include <math.h>
#include <iomanip>
using namespace std;


int printCount = 0;

struct Node
{
    int left = -1;
    int right = -1;
    int count = 1;
    string data; //store the word read from text file
};

const int maxN = 50100;

Node arr[maxN];
Node temp[maxN];
Node tree[maxN];

int nindex = 0; //index of the array arr[]
int tindex = 0; //index of the BST tree[]
Node& insert_first(string word, Node arr[]);

void insert(string word, Node& node);
int compareWord(string w1, string w2);
void traverseTree(Node& node);

void mergeSort(Node tree[], int left, int right);
void merge(Node tree[], int left, int mid, int right);

void printFirstTenWords(Node* tree);
void printLastTenWords(Node* tree);

int main()
{
    cout << "Please enter the name of the text file: ";
    string fileName;
    string line;
    string word;
    
    cin >> fileName; //read the file name
    
    ifstream fin(fileName.c_str());
    
    if (!fin)
    {
        cerr << "Cannot open file";
        exit(1);
    }
    
    
    int i = 0;
    Node root;
    while (!fin.eof())
    {
        getline(fin, line); //read line by line
        stringstream ss(line); //split the words
        
        for(;;)
        {
            ss >> word; //read each word
            if(ss.fail())break; //if cannot read then jump out of the loop
            
            for (int a = 0; a < word.size(); a++) //iterate through each character of the word
            {
                if(!isalpha(word[a])) //if there is a punctuation then delete it
                {
                    word.erase(a,1);
                    a--;
                }
                word[a] = tolower(word[a]); //convert to lowercase
            }
            
            if(i == 0)
            {
                //create a root
                root = insert_first(word, tree);
            }
            else
                insert(word, root); //insert the nodes into the tree
            
            i++;
        }
    }
    
    fin.close();
    
    traverseTree(root);
    
    mergeSort(arr, 0, nindex-1);
    
    printFirstTenWords(arr);
    printLastTenWords(arr);
    
    return 0;
}

Node& insert_first(string word, Node tree[]) //insert a root node into a tree
{
    static Node start;
    start.data = word;
    tree[0] = start;
    return start;
}

void insert(string word, Node& node) 
{
    string a = node.data;
    
    //compare the word read from the text file with the node's data
	 
    if(compareWord(word, a) == 0)	//if they are the same (the word is repeated) then increase the count
    {
        node.count++;
        return;
    }
    else if(compareWord(word, a) < 0) //if the word is smaller than the node's data then insert it to the left branch
    {
        if(node.left == -1)  
        {
            tindex++;
            
            node.left = tindex; //assign the index of the node in the tree
            
            tree[tindex].data = word;
            
            tree[tindex].left = -1;
            tree[tindex].right = -1;
            return;
        }
        else //if there's a node exists in the left branch then continue to traverse its left branch
        {
            insert(word, tree[node.left]);
        }
    }
    else //if the word is smaller than the node's data then insert it to the right branch
    {
        if(node.right == -1)
        {
            tindex++;
            
            node.right = tindex; //assign the index of the node in the tree
            
            tree[tindex].data = word;
            
            tree[tindex].left = -1;
            tree[tindex].right = -1;
            return;
        }
        else //if there's a node exists in the left branch then continue to traverse its right branch
        {
            insert(word, tree[node.right]);
        }
    }
    
}

//compare two strings
int compareWord(string w1, string w2) 
{
    for (int i = 0; i < min(w1.size(), w2.size()); i++)
    {
        if(w1[i] < w2[i])
        {
            return -1;
        }
        else if (w1[i] > w2[i])
        {
            return 1;
        }   
    }
    
    if (w1.size() < w2.size())
        return -1;
    else if (w1.size() > w2.size())
        return 1;
    else
        return 0;
}

//traverse the tree then insert the nodes to the array
void traverseTree(Node& node)
{
    if (node.left != -1)
        traverseTree(tree[node.left]);
    
    arr[nindex] = node;
    nindex++;
    
    if (node.right != -1)
        traverseTree(tree[node.right]);
    return;
}

//sort the array according to the word count 
void mergeSort(Node tree[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left)/2;  //avoids overflow for large left and right
        
        mergeSort(tree, left, mid); //sort the first half
        mergeSort(tree, mid + 1, right); //sort the second half
        
        merge(tree, left, mid, right);
    }
}

void merge(Node tree[], int left, int mid, int right)
{
    for(int i = left; i <= right; i++)
        temp[i] = tree[i];
    
    int apos =left;
    int bpos = mid + 1;
    int cpos = left;
    
    while(apos <= mid && bpos <= right)
    {
    	//sort the count in descending order while keeping the words alphabetical order
        if ((temp[apos].count > temp[bpos].count) || (temp[apos].count == temp[bpos].count && compareWord(temp[apos].data, temp[bpos].data) < 0)) 
            tree[cpos++] = temp[apos++];
        else
            tree[cpos++] = temp[bpos++];
    }
    
    while(apos <= mid)
        tree[cpos++] = temp[apos++];
    
    while(bpos <= right)
        tree[cpos++] = temp[bpos++];
}

void printFirstTenWords(Node* tree)
{
    cout << "The first ten words in the sorted list:" <<endl;
    for(int i = 0; i < 10; i++)
    {
        cout << tree[i].data << "(";
        cout << tree[i].count << ") ";
    }
    cout <<endl;
}

void printLastTenWords(Node* tree)
{
    cout << "The last ten words in the sorted list:" <<endl;
    for(int i = nindex-10; i <= nindex - 1; i++)
    {
        cout << tree[i].data << "(";
        cout << tree[i].count << ") ";
    }
    cout <<endl;
}

