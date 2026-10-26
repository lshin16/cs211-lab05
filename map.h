/*map.h*/

/**
  * @brief implementation of std::map using binary search trees
  *
  * Our implementation of std::map. Note that since map
  * is templated, there is no separate .cpp file --- the code
  * must also be placed in the .h file.
  * 
  * @author Prof. Joe Hummel
  * @author ?
  * @author ?
  * @author ?
  * @note Northwestern University
 */
#pragma once

#include <iostream>
#include <utility>  // pair, make_pair()

using std::pair;
using std::make_pair;
using std::cout;
using std::endl;

//
// class map:
//
template<typename KeyT, typename ValueT>
class map {
private:

  struct NODE {
    pair<KeyT, ValueT> Pair;
    NODE*              Left;
    NODE*              Right;

    NODE(KeyT key, ValueT value)
      : Pair(make_pair(key, value)), Left(nullptr), Right(nullptr)
    { }
  };

  //
  // data members:
  //
  NODE*   Root;  // pointer to root of tree
  size_t  Size;  // # of nodes in tree

public:
  // 
  // constructor:
  //
  map()
    : Root(nullptr), Size(0)
  { }

  //
  // copy constructor:
  //
  map(const map& other)
  {
    this->Root= nullptr;
    this->Size= 0;
    _copy(other.Root);
  }

  //
  // destructor:
  //
  ~map()
  {
    _destroy(this->Root);
  }

  //
  // size:
  //
  size_t size() 
  {
    return this->Size;
  }

  //
  // []: search, insert if not found
  //
  ValueT& operator[](KeyT key)
  {
    // 
    // Step 1: search for key, return value if found:
    //
    NODE* prev = nullptr;
    NODE* cur  = this->Root;

    while (cur != nullptr) {

      if (key == cur->Pair.first) {
        return cur->Pair.second;
      }
      else if (key < cur->Pair.first) {
        prev = cur;
        cur  = cur->Left;
      }
      else {
        prev = cur;
        cur  = cur->Right;
      }
    }

    //
    // Step 2: if get here, insert where we fell out of tree:
    //
    ValueT default_value = ValueT();
    NODE* newNode = new NODE(key, default_value);
    if (prev == nullptr){
      this-> Root = newNode;
    }

    else if (key < prev->Pair.first)
      prev->Left = newNode;
    else
      prev->Right = newNode;

    Size++;

    //
    // Step 3: return value in the new node:
    //
    return newNode->Pair.second;
  }

  // 
  // print: for debugging output to console
  //
private:
  //
  // recursive helper function to do actual printing:
  //
  void _print(NODE* cur)
  {
    if (cur == nullptr)
      return;
    else {
      _print(cur->Left);

      cout << "(" << cur->Pair.first 
           << ", " << cur->Pair.second
           << ")" << endl;

      _print(cur->Right);
    }
  }
  void _destroy(NODE* cur){
    if (cur == nullptr){
      return;
    }
    _destroy(cur->Left);
    _destroy(cur->Right);
    delete cur;
  }
  void _copy(NODE* cur){
    if (cur==nullptr){
      return;
    }
    (*this)[cur -> Pair.first] = cur -> Pair.second;
    _copy(cur->Left);
    _copy(cur->Right);
  }

public:
  void print()
  {
    cout << "**Tree Contents**" << endl;

    _print(this->Root);
  }
    
};
