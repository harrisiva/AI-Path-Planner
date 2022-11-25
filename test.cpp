#include<iostream>
#include<vector>
using namespace std; 
//A function to sort the array using insertion sort
void inSort(vector<int*>*a)
{
    int n=(*a).size();
    int i,j;
    int k;  
    for (i = 1; i < n; i++) 
    {  
        k = (*(*a)[i]); 
        cout << "k" << k << endl; 
        j = i - 1;  
        /*Move elements of arr[0..i-1], that are  
        greater than k, to one position ahead  
        of their current position */
        while (j >= 0 && (*(*a)[j]) > k) 
        {  
            *((*a)[j + 1]) = *((*a)[j]);  
            j = j - 1;  
        }  
        cout << "j " << j << endl;
        *((*a)[j + 1]) = k;  
    }  
}  

void print(vector<int*> *list){
    for (int i=0;i<(*list).size();i++){
        cout << (*(*list)[i]) << ",";
    } cout << endl;
}

int main(){
    int a=5;
    int b=2;
    int c=8;
    int d=7;
    int e=3;
    int f=5;
    int g=4;
    int h=1;

    vector<int*> test;
    test.push_back(&a);
    test.push_back(&b);
    test.push_back(&c);
    test.push_back(&d);
    test.push_back(&e);
    test.push_back(&f);
    test.push_back(&g);
    test.push_back(&h);
    print(&test);
    inSort(&test);
    print(&test);
    return 0; 
}