#include<iostream>
#include<vector>
using namespace std; 
//A function to sort the array using insertion sort
void inSort(vector<int>*a)
{
    int n=(*a).size();
    int i,j, k;  
    for (i = 1; i < n; i++) 
    {  
        k = (*a)[i];  
        j = i - 1;  
        /*Move elements of arr[0..i-1], that are  
        greater than k, to one position ahead  
        of their current position */
        while (j >= 0 && (*a)[j] > k) 
        {  
            (*a)[j + 1] = (*a)[j];  
            j = j - 1;  
        }  
        (*a)[j + 1] = k;  
    }  
}  

void print(vector<int>list){
    for (int i=0;i<list.size();i++){
        cout << list[i] << ",";
    } cout << endl;
}

int main(){
    vector<int> test{5,2,8,7,3,5,4,1};
    print(test);
    inSort(&test);
    print(test);
    return 0; 
}