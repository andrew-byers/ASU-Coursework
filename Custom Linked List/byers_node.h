/*
Author: Andrew Byers
Date: 11/24/21
Description: Node class to be used in partnership with the Linked List, templated to hold any data type as a node
*/ 

#pragma once
#include <iostream>
using namespace std;

template<typename T>
class Node {
    public:
        Node();
        Node(T userValue);
        ~Node();
        T getValue();
        Node<T>* getNext();
        void setNext(Node* userNext);
        void setValue(T userNode);
    protected:
        Node* next;
        T value;
};

//DEFAULT CONSTRUCTOR
template<typename T>
Node<T>::Node(){
    this->next = NULL;
    this->value = NULL;
}

//PARAMETERIZED CONSTRUCTOR
template<typename T>
Node<T>::Node(T userValue){
    this->next = NULL;
    this->value = userValue;
}

//DESTRUCTOR
template<typename T>
Node<T>::~Node(){
    delete next;
}

//GETTERS
template<typename T>
T Node<T>::getValue(){
    return this->value;
}

template<typename T>
Node<T>* Node<T>::getNext(){
    return this->next;
}

//SETTERS
template<typename T>
void Node<T>::setValue(T userNode){
    this->value = userNode;
}


template<typename T>
void Node<T>::setNext(Node<T>* userNext){
    this->next = userNext;
}



