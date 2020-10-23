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
    DoubleNode<T> *Head;
    DoubleNode<T> *Tail;
    int len;
    DoubleNode<T>* getNode(int pos);
    bool verification(int index);
public:
    DoubleList();
    DoubleList(DoubleList<T>& List);
    ~DoubleList();
    void add(T &data);
    void erase(int pos);
    void set(int pos,T &data);
    T* get(int pos);
    int getLen();
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
    temp->setData(data);
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
    DoubleList<int>();
    T *temp;
    for (int i = 0; i < List.len; i++) {
        temp = new T(*List.get(i));
        add(*temp);
    }
}
