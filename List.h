/*
 * Author: R. Shore
 * Date: 9-28-2016
 * Class: CSC-2710
 *
 *
 */
#ifndef LIST
#define LIST

#include<stdexcept>
#include<iterator>
#include<iostream>
using namespace std;
//A class to assist in catching exceptions - subscript out of range.
#define MEM_ERR 1
#define EMPTY_LIST 2
#define ITEM_NOT_FOUND 3

class list_err{
public:
    list_err ( int ec ):err_code(ec){}
    const string error_desc ( void){
        switch (err_code)
        {
            case MEM_ERR:    return "Out Of Memory";
            case EMPTY_LIST: return "List is empty";
            case ITEM_NOT_FOUND: return "Item is not in list";
            default:         return "Unknown Error";
        }
    }
private:
    int err_code;
};

template <class T>
class List
{
    class Node {
    public:
        T data;
        Node * next;
    };

private:
    Node * headNode;
    int len;  //keep up with the number of elements in the list.
public:

    //constructor
    List()
    {
        len=0;
        headNode=new Node;
        if(headNode == NULL)
            throw list_err(MEM_ERR);
        else
            headNode->next = NULL;
    }

    //destructor-must clean up dynamic stuff
    ~List()
    {
        Node * curptr = headNode;
        Node * prevptr;
        while(curptr != NULL) {
            prevptr = curptr;
            curptr = curptr->next;
            delete prevptr;
        }
    }

    //add an element between the dummy header and the first real
    //node in the list
    bool add(const T & item)
    {
        Node * newNode = new Node;
        if(newNode == NULL)
            throw list_err(MEM_ERR);
        len++;
        newNode->next = headNode->next;
        newNode->data = item;
        headNode->next = newNode;
        return true;

    }

    //remove the item immediately after the dummy header unless empty
    T remove()
    {

        /*****Left as an exercise*******/

    }

    //remove the specific "item" from the list if present
    void remove(const T & item)
    {

        /*****Left as an exercise*******/

    }

    //is the "item" in the list?
    bool contains(const T & item)
    {
        Node * curptr = headNode->next;
        while(curptr != NULL && curptr->data != item)
            curptr=curptr->next;
        return curptr!=NULL;
    }

    //print all of the items.
    void print() const
    {
        Node * curptr = headNode->next;
        while(curptr != NULL) {
            cout<<curptr->data<<endl;
            curptr = curptr->next;
        }
    }

    //is the list full? i.e. out of memory
    inline bool isFull() const
    {
        Node * newNode = new Node;
        if(newNode != NULL) {
            delete newNode;
            return false;
        } else
            return true;
    }

    //is the list empty?
    inline bool isEmpty() const
    {
        return headNode->next==NULL;
    }

    //How many elements in the list?  len keeps track of the number of
    //elements.  When an element is added, len++.  When an element is
    //removed, len--.
    inline int length() const
    {
        return len;
    }

    // Here is my custom iterator.  The only kind of iterator this data
    // structure can reasonably support is a forward iterator, so that's
    // what I provide.  I embedded the definition of the iterator within
    // the class it will iterate through for convenience.
    class Iterator :
            public std::iterator<std::forward_iterator_tag, T> {

    private:
        Node* curptr;
    public:
        Iterator(Node* p) : curptr(p) {}
        ~Iterator() {}

        // The assignment and relational operators are straightforward
        Iterator& operator=(const Iterator& other)
        {
            curptr = other.curptr;
            return(*this);
        }

        bool operator==(const Iterator& other)
        {
            return(curptr == other.curptr);
        }

        bool operator!=(const Iterator& other)
        {
            return(curptr != other.curptr);
        }

        // Update my state such that I refer to the next element in the
        Iterator& operator++()
        {
            if (curptr != NULL)
            {
                curptr = curptr->next;
            }
            return(*this);
        }

        Iterator& operator++(int)
        {
            Iterator tmp(*this);
            ++(*this);
            return(tmp);
        }

        // Return a reference to the value in the node.  I do this instead
        // of returning by value so a caller can update the value in the
        // node directly.
        T& operator*()
        {
            return curptr->data ;
        }

        T* operator->()
        {
            return &curptr->data;
        }

    };

    Iterator begin()
    {
        return(Iterator(headNode->next));
    }

    Iterator end()
    {
        return(Iterator(NULL));
    }
};
#endif
