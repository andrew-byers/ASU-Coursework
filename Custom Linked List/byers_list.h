/*
Author: Andrew Byers
Date: 11/24/21
Description: Linked List data structure, templated to be able to hold any kind of data
*/

#pragma once
#include <iostream>
#include "byers_node.h"
using namespace std;

template<typename T>
class LinkedList {
    public:
        LinkedList();
        ~LinkedList();
        void addToFront(T data);
        void addToEnd(T data);
        bool addAtIndex(T data, int index);
        T removeFromFront();
        T removeFromEnd();
        void removeTheFirst(T data);
        void removeAllOf(T data);
        bool elementExists(T data);
        Node<T>* find(T data);
        int indexOf(T data);
        T retrieveFront();
        T retrieveEnd();
        T retrieve(int index);
        void printList();
        void empty();
        int length();
    private:
        Node<T>* head;
        Node<T>* tail;
};

//CONSTRUCTOR
template<typename T>
LinkedList<T>::LinkedList(){
    this->head = nullptr;
    this->tail = nullptr;
}

//DESTRUCTOR
template<typename T>
LinkedList<T>::~LinkedList(){
    int count = 0;
    while(count < this->length()){
        Node<T>* curr = head;
        this->head = curr->getNext();
        curr = nullptr;;
    }
    
}

//Add an item to the front of the Linked List
template<typename T>
void LinkedList<T>::addToFront(T data){
    Node<T>* newHead = new Node<T>(data);
    Node<T>* temp = head;
    if(head != nullptr){
        this->head = newHead;
        newHead->setNext(temp); 
    }
    else{
        head = newHead; 
        tail = newHead;
    }
}

//Add an item to the back of the Linked List
template<typename T>
void LinkedList<T>::addToEnd(T data){
    //If it's an empty list
    if(this->head == nullptr){
        this->addToFront(data);
        this->tail = head;
    }

    //Otherwise...
    else{
        Node<T>* newNode = new Node<T>(data);
        Node<T>* temp = this->head;
        while(temp != this->tail){
            temp = temp->getNext();
        }
        temp->setNext(newNode);
        this->tail = newNode;
    }
}

//At an item to a specific index in the list
template<typename T>
bool LinkedList<T>::addAtIndex(T data, int index){
    //We already have a way to add to the front...
    if(index == 0){
        this->addToFront(data);
        return true;
    }
    //... and the end
    else if(index == this->length()){
        this->addToEnd(data);
        return true;
    }

    //If it's not the front or back
    Node<T>* newNode = new Node<T>(data);
    Node<T>* curr = this->head;
    Node<T>* prev = curr;

    //if index is past the length
    if(index > this->length() || index < 0){
        cout << "Index input out of bounds!" << endl;
        return false;
    }

    //Index to right before the insert
    for(int i = 0; i < index; i++){
        prev = curr;
        curr = curr->getNext();
    }
        prev->setNext(newNode);
        newNode->setNext(curr);
    
        return true;
        
}

//Remove the first item in the list, and return its contents
template<typename T>
T LinkedList<T>::removeFromFront(){
    if(this->head == nullptr){
        cout << "Head is nullptr!" << endl;
        return nullptr;
    }
    Node<T>* temp = this->head;
    this->head = this->head->getNext();
    T value = temp->getValue();
    return value;
}

//Remove the last item in the list, and return its contents
template<typename T>
T LinkedList<T>::removeFromEnd(){
    if(this->tail == nullptr){
        cout << "Tail is nullptr!" << endl;
        return nullptr;
    }
    Node<T>* temp = this->head;  
    Node<T>* prev = temp;
    while(temp != this->tail){
        prev = temp;
        temp = temp->getNext();
    }
    T value = temp->getValue();
    this->tail = prev;
    this->tail->setNext(nullptr);
    return value;
}

//Remove the first instance of an item with user given data
template<typename T>
void LinkedList<T>::removeTheFirst(T data){
    if(this->head->getValue() == data){
        this->removeFromFront();
        return;
    }
    bool notFound = true;
    Node<T>* temp = this->head;
    Node<T>* prev = temp;
    while(temp != nullptr && notFound){
        if(temp->getValue() == data){
            notFound = false;
        }
        else{
            prev = temp;
            temp = temp->getNext();
        }
    }
    if(!notFound){
        prev->setNext(temp->getNext());
        if(temp->getNext() == nullptr){
            this->tail = prev;
        }
    }
    else{
        cout << "Value not found in list" << endl;
    }

}

//Remove all instances of an item with user given data
template<typename T>
void LinkedList<T>::removeAllOf(T data){
    Node<T>* temp = this->head;
    Node<T>* prev = temp;
    while(temp != nullptr){
        if(temp->getValue() == data){
            cout << "SIMILAR VALUE FOUND" << endl;
            prev->setNext(temp->getNext());
            temp = prev->getNext();
        }
        else{
            prev = temp;
            temp = temp->getNext();
        }
    }
}

//Return true or false depending on whether or not an element exists in the list
template<typename T>
bool LinkedList<T>::elementExists(T data){
    Node<T>* temp = this->head;
    while(temp != nullptr){
        if(temp->getValue() == data){
            return true;
        }
        else{
            temp = temp->getNext();
        }
    }
    return false;
}

//Return the pointer to the first item in the linked list with the user given data
template<typename T>
Node<T>* LinkedList<T>::find(T data){
    Node<T>* temp = this->head;
    while(temp != nullptr){
        if(temp->getValue() == data){
            cout << "Found!" << endl;
            return temp;
        }
        else{
            temp = temp->getNext();
        }
    }
    cout << "Not found" << endl;
    return nullptr;
}

//Return the index of the first instance of an item with the user given data
template<typename T>
int LinkedList<T>::indexOf(T data){
    int index = 0;
    Node<T>* temp = this->head;
    while(temp != nullptr){
        if(temp->getValue() == data){
            return index;
        }
        temp = temp->getNext();
        index++;
    }
    cout << "Doesn't exist!" << endl;
    return -1;
}

//Return the first item in the list (head)
template<typename T>
T LinkedList<T>::retrieveFront(){
    return this->head->getValue();
}

//Return the last item in the list (tail)
template<typename T>
T LinkedList<T>::retrieveEnd(){
    return this->tail->getValue();
}

//Return the item at a user inputted index
template<typename T>
T LinkedList<T>::retrieve(int index){
    if(index == 0){
        return this->retrieveFront();
    }
    else if(index == this->length()-1){
        return this->retrieveEnd();
    }
    else if(index > 0 && index < this->length()){
        Node<T>* temp = this->head;
        for(int i = 0; i < index; i++){
            temp = temp->getNext();
        }
        return temp->getValue();
    }
    else{
        cout << "Cannot retrieve value: out of bounds" << endl;
        return nullptr;
    }
    
}

//Print the list of items in the Linked List
template<typename T>
void LinkedList<T>::printList(){
    if(this->head == nullptr){
        cout << "List is empty!" << endl;
        return;
    }
    Node<T>* temp = this->head;
    while(temp != nullptr){
        cout << temp->getValue();
        /*if(temp->getNext() != nullptr){
            cout << ", ";
        }*/
        temp = temp->getNext();
    }
    cout << endl;
}

//Set every item in the list to a nullptr
template<typename T>
void LinkedList<T>::empty(){
    Node<T>* temp = this->head;
    Node<T>* nextNode = nullptr;
    while(temp != nullptr){
        nextNode = temp->getNext();
        temp = nullptr;
        temp = nextNode;
    }
    this->head = nullptr;
    this->tail = nullptr;
}

//Return the length of the Linked List
template<typename T>
int LinkedList<T>::length(){
    int count = 0;
    Node<T>* temp = this->head;  
    while(temp != nullptr){
        count++;
        temp = temp->getNext();
    }
    temp = nullptr;
    return count;
}