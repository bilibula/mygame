#include <iostream>
#include <algorithm>
#include <cstring>
#define MAX 1001
using namespace std;
int N;
char ch[MAX];
char goal[MAX];
int dp[MAX]{0};//标记到前i个位置处时最少要替换的次数
int M=0,m=0x7f;
void Result(){
    if (strlen(ch) > strlen(goal))
        swap(ch,goal);
    int len = strlen(ch);



}
int main() {
    scanf("%d",&N);
    while (N--) {
        cin >> ch >> goal;
        Result();
    }

    return 0;
}