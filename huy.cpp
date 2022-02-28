#include<iostream>
using namespace std;
int main(){
    int n,arr[100];
    cin>>n;
    for(int i=0;i<n;i++) cin>>arr[i];
    for(int i=0;i<n;i++){
        for(int j=n-1;j>0;j--)
            if(arr[j]<arr[j-1]){
                int a=arr[j];
                arr[j]=arr[j-1];
                arr[j-1]=a;
            }
    }
    int a=1,b=2,c=3;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++)
            for(int t=j+1;t<n;t++){
                if(arr[i]+arr[j]+arr[t]==0){
                    if(arr[i]!=a||arr[j]!=b||arr[t]!=c)
                        cout<<arr[i]<<arr[j]<<arr[t]<<endl;
                    a=arr[i];
                    b=arr[j];
                    c=arr[t];
                }
            }  
    }
    return 0;
}