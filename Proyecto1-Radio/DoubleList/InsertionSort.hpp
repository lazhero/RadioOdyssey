#include<DoubleList/DoubleList.hpp>
template<typename T>
void swap(DoubleList<T> *List,int position1, int position2){
    if(List ==NULL || position1<0 || position1>=List->getLen()  || position2<0 || position2>= List->getLen())return;
    T  temp=*List->get(position1);
    List->set(position1,*List->get(position2));
    List->set(position2,temp);
}


template <typename T>
void sort(DoubleList<T> *List){
    if(List==NULL)return;
    if(List->getLen()<=1)return;
    int j;
    for(int i=1;i<List->getLen();i++){
        j=i;
        while(j>0 && *List->get(j)<* List->get(j-1)){
            swap(List,j,j-1);
            j--;
        }
    }

}
