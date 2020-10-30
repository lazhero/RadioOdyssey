#pragma once
/**
  *@file DoubleList.hpp
  * @version 1.0
  * @date 25/09/2020
  * @author Luis Andrey Zuniga
  * @title Generic DoubleList
  */



#include "../DoubleNode/DoubleNode.hpp"
#define EmptyLen 0
#define minIndex 0
#define singleElement 1
#define OutIndex "index out of bounds"
struct OutIndexException : public std::exception {
    const char * what () const throw () {
        return OutIndex;
    }
};

template<typename T>
class DoubleList {
private:
    /**
     * @brief HeadNode
     */
    DoubleNode<T> *Head;
    /**
     * @brief TailNode
     */
    DoubleNode<T> *Tail;
    /**
     * @brief len of the list
     */
    int len;
    /**
     * @brief getNode at the indicated position
     * @param pos of the node
     * @return  a DoubleNode of the selected position
     */
    DoubleNode<T>* getNode(int pos);
    /**
     * @brief verification of the position given, whenever is between [0:len[ returns true, else returns false
     * @param index
     * @return  a boolean
     */
    bool verification(int index);
public:
    /**
     * @brief The constructor of the DoubleList
     */
    DoubleList();
    /**
     * @brief DoubleList Copy Constructor
     * @param another object of the same class
     */
    DoubleList(DoubleList<T>& List);
    ~DoubleList();
    /**
     * @brief Add data to the list
     * @param The data to be added
     */
    void add(T &data);
    /**
     * @brief Erase the data at an specific position
     * @param the position to be erased
     */
    void erase(int pos);
    /**
     * @brief replace the data at the specified position for another passed to this method
     * @param position to be replaced
     * @param Data to be putted instead
     */
    void set(int pos,T &data);
    /**
     * @brief get the data at a position
     * @param position to get the dada
     * @return  the data at the given position
     */
    T* get(int pos);
    /**
     * @brief get the length of the list
     * @return  a integer that represents the length of the list
     */
    int getLen();

    void addFront(T &data);
};
template <typename T>
DoubleList<T>::DoubleList() {
    len=EmptyLen;
    Tail=NULL;
    Head=NULL;
}
template <typename T>
DoubleList<T>::~DoubleList(){
    if(Tail!=NULL)free(Tail);
    if(Head!=NULL)free(Head);
    //DoubleNode<T>* temp,Saved;
/*
    for(temp=Head;temp!=NULL;){
       // Saved=&temp->getFront();
        //free(temp);
        //temp=Saved;
    }
    */
}
template<typename T>
bool DoubleList<T>::verification(int index) {
    if(index<minIndex || index>=len)return false;
    return true;
}
template<typename T>
DoubleNode<T>* DoubleList<T>::getNode(int pos) {
    if(!DoubleList<T>::verification(pos))throw  OutIndexException();
    DoubleNode<T>* temp=Head;
    for(int i=0;i<pos;i++){
        temp=&temp->getFront();
    }
    return temp;
}

template <typename T>
int DoubleList<T>::getLen() {
    return len;
}
template<typename T>
void DoubleList<T>::add(T &data) {
    DoubleNode<T> *temp=new DoubleNode<T>;
    len++;
    temp->setData(*new T(data));
    if(Tail==NULL){
        Head=temp;
        Tail=temp;
    }
    else{
        Tail->setFront(*temp);
        temp->setBack(*Tail);
        Tail=temp;
    }
}
template<typename T>
void DoubleList<T>::addFront(T& data){
    DoubleNode<T>* temp=new DoubleNode<T>();
    temp->setData(*new T(data));
    if(Head==NULL){
        Head=Tail=temp;
        return;
    }
    Head->setBack(*temp);
    temp->setFront(*Head);
    Head=temp;



}
template<typename T>
T* DoubleList<T>::get(int pos) {
    DoubleNode<T>* Signaled=DoubleList<T>::getNode(pos);
    return Signaled->getData();
}
template <typename T>
void DoubleList<T>::erase(int pos) {
    DoubleNode<T>* Signaled=DoubleList<T>::getNode(pos);
    if(len==singleElement){
        Head=Tail=NULL;
    }
    else if(pos==minIndex){
        Head=&Head->getFront();
    }
    else if(pos==len-1){
        Tail=&Tail->getBack();
    }
    else{
        Signaled->getBack().setFront(Signaled->getFront());
        Signaled->getFront().setBack(Signaled->getBack());
    }
    free(Signaled);
    len--;
}template<typename T>
void DoubleList<T>::set(int pos,T &data) {
    DoubleNode<T>* temp=getNode(pos);
    temp->setData(data);

}
template<typename T>
DoubleList<T>::DoubleList(DoubleList<T> &List) {
    Tail=NULL;
    Head=NULL;
    len=EmptyLen;
    T *temp;
    for (int i = 0; i < List.len; i++) {
        temp = new T(*List.get(i));
        add(*temp);
    }
}
