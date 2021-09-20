#ifndef BNODE_H
#define BNODE_H

#include <iostream> 
#include <cassert>

/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BinaryNode
{
public:
   // return size (i.e. number of nodes in tree)
   int size() const
   {
      return 1 +
         (pLeft== NULL? 0 : pLeft->size()) +
         (pRight == NULL ? 0 : pRight->size());
   }
   // default constructor and non-default constructors
   BinaryNode();
   BinaryNode(const T & t);
   
   // add a node to the left/right
   void addLeft (BinaryNode <T> * pNode);
   void addRight(BinaryNode <T> * pNode);

   // create a node and add it to the left/right
   void addLeft (const T & t) throw (const char *);
   void addRight(const T & t) throw (const char *);
   
   // delete tree
   
   
   //insertion operator overload
   std::ostream operator<<(BinaryNode<T> *rhs);
   
   // since no validation is done, everything is public
   BinaryNode <T> * pLeft;
   BinaryNode <T> * pRight;
   BinaryNode <T> * pParent;
   T data;
};

template <class T>
void deleteBinaryTree(BinaryNode<T> *pNode);

/*****************************************************************
 * DEFAULT CONSTRUCTOR
 *****************************************************************/
template <class T>
BinaryNode<T>::BinaryNode()
{
   pLeft = NULL;
   pRight = NULL;
   pParent = NULL;
}

/*****************************************************************
 * NON-DEFAULT CONSTRUCTOR
 *****************************************************************/
template <class T>
BinaryNode<T>::BinaryNode(const T &t)
{
   pLeft = NULL;
   pRight = NULL;
   pParent = NULL;
   data = t;
}

/*****************************************************************
 *
 *****************************************************************/
template <class T>
void BinaryNode<T>::addLeft(BinaryNode <T> * pNode)
{
   pLeft = pNode;
   if (pLeft != NULL)
      pLeft->pParent = this;
}

/*****************************************************************
 *
 *****************************************************************/
template <class T>
void BinaryNode<T>::addLeft(const T &t) throw (const char*)
{
   pLeft = new BinaryNode(t);
   pLeft->pParent = this;
}

/*****************************************************************
 *
 *****************************************************************/
template <class T>
void BinaryNode<T>::addRight(BinaryNode<T> * pNode)
{
   pRight = pNode;
   if (pRight != NULL)
      pRight->pParent = this;
}

/*****************************************************************
 *
 *****************************************************************/
template <class T>
void BinaryNode<T>::addRight(const T &t) throw (const char*)
{
   pRight = new BinaryNode(t);
   pRight->pParent = this;
}

/*****************************************************************
 * LRV
 *****************************************************************/
template <class T>
void deleteBinaryTree(BinaryNode<T> *pNode)
{
   if(pNode != NULL)
   {
      deleteBinaryTree(pNode->pLeft);
      deleteBinaryTree(pNode->pRight);
      delete pNode;
      pNode = NULL;
   }
}

/*****************************************************************
 *
 *****************************************************************/
template <class T>
std::ostream & operator<<(std::ostream & out, BinaryNode <T> *rhs)
{
   if(rhs != NULL)
   {
      out << rhs->pLeft;
      out << rhs->data;
      out << " ";
      out << rhs->pRight;

   }
   return out;
}
#endif // BNODE_H
