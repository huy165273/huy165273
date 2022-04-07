#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
using namespace std;
const int mMax=100, nMax=100;
void enterArray(bool (*arr)[mMax], int (*map2)[nMax], int m, int n);
void bombMap(bool (*arr)[mMax], int (*map)[mMax], int m, int n);
bool checkBomb(int x, int y, bool (*arr)[mMax]);
void editMap2( int x, int y, int (*map1)[mMax], int (*map2)[nMax], int m, int n);
bool checkMap( int (*map1)[mMax], int (*map2)[nMax], int m, int n );
void printMap(int (*map2)[mMax], int m, int n);
void printBombMap(int (*map1)[mMax], int m, int n);
void randomBombMap( bool (*arr)[mMax], int m, int n);
void enterMap2(int (*map2)[mMax], int m, int n);
void playBombDetection();
int main(){
    string str;
    do{
        playBombDetection();
        cout<<"Play again (Yes/No): ";
        cin>>str;
    }while(str=="Yes");
    return 0;
}
void playBombDetection(){
    int m,n,x,y;
    bool arr[mMax][nMax];
    int map1[mMax][nMax],// bản đồ bom
        map2[mMax][nMax];// bản đồ sau mỗi lần người chơi đoán 
    cout<<"Enter map size: ";
    cin>>m>>n;
    randomBombMap(arr, m, n);
    //enterArray(arr, map2, m, n);
    bombMap(arr, map1, m, n);
    bool check=true ; 
    enterMap2(map2, m, n);
    printMap(map2, m, n);
    while(check){
        cout<<"Enter the coordinates of your choice: ";
        cin>>x>>y;
        if(checkBomb(x, y, arr)==true){
            check=false ;
            cout<<"You are dead! You lose!"<<endl;
            cout<<"Bomb map: "<<endl;
            printBombMap(map1, m, n);
        }
        else{
            editMap2(x, y, map1, map2, m, n);
            printMap(map2, m, n);
        }
        if(checkMap(map1, map2, m, n)){
            check=false;
            cout<<"Congratulate! You win!"<<endl;
            cout<<"Bomb map: "<<endl;
            printBombMap(map1, m, n);
        }
    }
}
void enterArray(bool (*arr)[mMax],int (*map2)[nMax],  int m, int n){
    for(int i=1;i<=m;i++){
        string str;
        cin>>str;
        for(int j=1;j<=n;j++) {
            arr[i][j]=str[j-1];
            map2[i][j]=-1;
        }
    }
    for(int i=0;i<=n;i++) map2[0][i]=i;
    for(int i=1;i<=m;i++) map2[i][0]=i;
}
void bombMap(bool (*arr)[mMax], int (*map1)[mMax], int m, int n){
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
           int count=0;
            bool check=false;
            for(int k=i-1;k<=i+1;k++){
                for(int t=j-1;t<=j+1;t++){
                    if(k==i && t==j){
                        if(arr[k][t]==true) {
                            count =-1;
                            check=true;
                            break;
                        }
                    } 
                    else if(k>0 && k<=m && t>0 && t<=n){
                        if(arr[k][t]==true) count++;
                    }
                }
                if(check) break;
            }
            map1[i][j]=count;   
        }
    }
    for(int i=0;i<=n;i++) map1[0][i]=i;
    for(int i=1;i<=m;i++) map1[i][0]=i;
}
bool checkBomb(int x, int y, bool (*arr)[mMax]){
    if(arr[x][y]==true) return true;
    return false;
}
bool checkMap( int (*map1)[mMax], int (*map2)[nMax], int m, int n ){
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            if(map1[i][j]!=map2[i][j]) return false;
    return true;
}
void editMap2( int x, int y, int (*map1)[mMax], int (*map2)[nMax], int m, int n){
    if(map1[x][y]>0) map2[x][y]=map1[x][y];
    else{
        map2[x][y]=0;
        for(int i=x-1;i<=x+1;i++)
            for(int j=y-1;j<=y+1;j++){
                if(i>0 && i<=m && j>0 && j<=n && (i!=x || j!=y)) 
                    if(map2[i][j]==-1) editMap2(i, j, map1, map2, m, n);
            }
    }
}
void printMap(int (*map2)[mMax], int m, int n){
    for(int i=0;i<=m;i++) {
        for(int j=0;j<=n;j++){
            if(i==0 && j==0) cout<<"    ";
            else{
                if(j==0) {
                    if(map2[i][j]<10 && map2[i][j]>=0) cout<<" "<<map2[i][j]<<"  ";
                    else cout<<map2[i][j]<<"  ";
                }
                else {
                    if(map2[i][j]<10 && map2[i][j]>=0) cout<<" "<<map2[i][j]<<" ";
                    else cout<<map2[i][j]<<" ";
                }
            }
        }
        if(i==0) cout<<endl<<endl;
        else cout<<endl;
    }
}
void printBombMap(int (*map1)[mMax], int m, int n){
    for(int i=0;i<=m;i++) {
        for(int j=0;j<=n;j++){
            if(i==0 && j==0) cout<<"    ";
            else{
                if(j==0) {
                    if(map1[i][j]<10 && map1[i][j]>=0) cout<<" "<<map1[i][j]<<"  ";
                    else cout<<map1[i][j]<<"  ";
                }
                else {
                    if(map1[i][j]!=-1) cout<<" "<<map1[i][j]<<" ";
                    else cout<<" * ";
                }
            }
        }
        if(i==0) cout<<endl<<endl;
        else cout<<endl;
    }
}
void randomBombMap( bool (*arr)[mMax], int m, int n){
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++) arr[i][j]=false;
    int count=1;
    while(count<=m){
        srand(time(nullptr));
        int x=rand()%m + 1;
        int y=rand()%n + 1;
        if(arr[x][y]==false) {
            arr[x][y]=true;
            count++;
        }
    }
}
void enterMap2(int (*map2)[mMax], int m, int n){
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++) map2[i][j]=-1;
        map2[0][i]=i;
        map2[i][0]=i;
    }
        
}