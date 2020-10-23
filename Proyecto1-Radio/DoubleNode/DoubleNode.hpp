#include <string>
template<typename T>
class DoubleNode {
private:
    T *Data;
    DoubleNode<T> *Front;
    DoubleNode<T> *Back;
public:
    DoubleNode();
    ~DoubleNode();
    void setData(T &data);
    T* getData();
    void setFront(DoubleNode<T> &Node);
    void setBack(DoubleNode<T> &Node);
    DoubleNode<T>& getBack();
    DoubleNode<T>& getFront();
    bool emptyFront();
    bool emptyBack();
    void makeFrontEmpty();
    void makeBackEmpty();
};
template <typename T>
DoubleNode<T>::DoubleNode() {
    Data=(T*)malloc(sizeof(T));
    Front=NULL;
    Back=NULL;
}
template <typename T>
DoubleNode<T>::~DoubleNode() {
    free(Data);
    if(Front!=NULL)free(Front);
    if(Back!=NULL)free(Back);
}
template <typename T>
void DoubleNode<T>::setData(T &data) {
    *Data=data;
}
template <typename T>
T* DoubleNode<T>::getData() {
    return Data;
}
template <typename T>
DoubleNode<T>& DoubleNode<T>::getBack() {
    //if(Back==NULL)return emptyReturn;
    return *Back;
}
template <typename T>
DoubleNode<T>& DoubleNode<T>::getFront() {
    //if(Front==NULL)return emptyReturn;
    return *Front;
}
template <typename T>
void DoubleNode<T>::setBack(DoubleNode<T> &Node) {
    Back=&Node;
}
template <typename T>
void DoubleNode<T>::setFront(DoubleNode<T> &Node) {
    Front=&Node;
}
template <typename T>
bool DoubleNode<T>::emptyBack() {
    if(Back==NULL)return true;
    return false;
}
template <typename T>
bool DoubleNode<T>::emptyFront() {
    if(Front==NULL)return true;
    return false;
}
template <typename T>
void DoubleNode<T>::makeBackEmpty() {
    Back=NULL;
}
template <typename T>
void DoubleNode<T>::makeFrontEmpty() {
    Front==NULL;
}
