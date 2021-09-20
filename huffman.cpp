
/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Andrew Hayes
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include "huffman.h"       // for HUFFMAN() prototype

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <list>
#include "pair.h"

using namespace std;

typedef Pair<string, float> HuffPair;
typedef BinaryNode<Pair <string, float> > BinHuffPair;
typedef list<BinaryNode <Pair <string, float> >* > HuffList;
typedef BinaryNode<Pair <string, float> >* pHuffPair;

/**********************************************************************
 * Compare()
 * compares two pairs.
 **********************************************************************/
bool compare(BinHuffPair * one, BinHuffPair * two)
{
   return (one->data.second < two->data.second);
}

/********************************************************************
 * Display()
 * Displays the huffman list.
 *********************************************************************/
void display(HuffList &theList)
{
   for (HuffList::iterator it = theList.begin(); it != theList.end(); it++)
   {
      for (int i = 0; i < (*it)->data.first.size(); i++)
      {
         if (i == 0)
            cout << (*it)->data.first[i] << " = ";
         else
         {
            cout << (*it)->data.first[i];
         }
      }
      cout << endl;
   }
}

/*********************************************************************
 * traverse()
 * traverses the binary tree
 **********************************************************************/
void traverse(pHuffPair root, string code, HuffList &theList)
{
   if (root->pLeft == NULL && root->pRight == NULL)
   {
      for (HuffList::iterator it = theList.begin(); it != theList.end(); it++)
      {
         string i;
         if (root->data.first == (*it)->data.first)
         {
            i = (*it)->data.first;
            i += code;
            (*it)->data.first = i;
         }
      }
      return;
   }
   else
   {
      traverse(root->pLeft, code + '0', theList);
      traverse(root->pRight, code + '1', theList);
   }
}

/**********************************************************************
 * buildTree()
 * builds the binary tree.
 ***********************************************************************/
pHuffPair buildTree(HuffList &tree)
{
   while (tree.size() > 1)
   {
      pHuffPair tmp = new BinHuffPair;
      tmp->pLeft = tree.front();
      tmp->data.second = tree.front()->data.second;
      tree.front()->pParent = tmp;
      tree.pop_front();
      tmp->pRight = tree.front();
      tmp->data.second += tree.front()->data.second;
      tree.front()->pParent = tmp;
      tree.pop_front();
      tree.push_back(tmp);
      tree.sort(compare);
   }
   
   pHuffPair root = tree.front();
   return root;
}

/*******************************************
 * Huffman()
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(string fileName)
{
   Pair<string, float> readData;
   HuffList nodes;
   ifstream fin(fileName.c_str());
   
   if (fin.fail())
   {
      cout << "Couldn't open the file: " << fileName << endl;
      return;
   }
   
   while (fin >> readData)
   {
      pHuffPair storeThis = new BinHuffPair(readData);
      nodes.push_back(storeThis);
   }
   
   HuffList newList = nodes;
   fin.close();
   nodes.sort(compare);
   pHuffPair root = buildTree(nodes);
   pHuffPair newRoot = root;
   string code;
   traverse(root, code, newList);
   
   display(newList);
   
   return;
}
