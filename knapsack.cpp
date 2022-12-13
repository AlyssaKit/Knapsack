#include <iostream>
#include <ctime>
#include <vector>
using namespace std;
const int Weight = 200;
const int Ncap = 100;
int knapsackRec(int W, int wt[],int val[], int n){
    if(n < 0 || W == 0){
        return 0;
    }
    if(wt[n] > W){
        return knapsackRec(W, wt, val, n-1);
    }else{
        return max(val[n] + knapsackRec(W-wt[n], wt, val, n-1), knapsackRec(W, wt, val, n-1));
    }
}

int knapsackDP(int W, int wt[],int val[], int n){
    int table[Ncap+1][Weight+1];
    for(int i = 0; i <= n; i++){
        table[i][0] = 0;
    }
    for(int i = 0; i <= W; i++){
        table[0][i] = 0;
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= W; j++){
            if(wt[i-1] <= j){
                if(val[i-1] + table[i-1][j - wt[i-1]] > table[i - 1][j]){
                    table[i][j] = val[i-1] + table[i-1][j - wt[i-1]];
                }else{
                    table[i][j] = table[i - 1][j];
                }
            }else{
                table[i][j] = table[i - 1][j];
            }
        }
    }
    return table[n][W];
}

int main()
{
    for(int j = 0; j < 10; j++){
        int n = 1 + (rand() % Ncap);
        cout << "N=" << n ;
        cout << " W =" << Weight ;
        int* val = new int[n];
        int* wt = new int[n];
        for(int i = 0; i < n; i++){
            val[i] = 1+ (rand() % 500);
            wt[i] = 1 + (rand() % 500);
            if(n == 2){
              cout << i+1 << ": " <<  val[i] << " wt: " << wt[i] << endl;
            }
        }
        int REC = 0;
        clock_t start = clock();
        for(int i = 0; i < 1000; i++){
            REC = knapsackRec(Weight, wt, val, n-1);
        }
        clock_t end = clock();
        cout << " Rec Time = " << static_cast<double>(end - start) / CLOCKS_PER_SEC/1000
             << " ";
        start = clock();
        int DP = 0;
        for(int i = 0; i < 1000; i++){
         DP = knapsackDP(Weight, wt, val, n);
        }
        end = clock();
        cout << " DP Time = " << static_cast<double>(end - start) / CLOCKS_PER_SEC/1000
             << " ";
        cout << " Max Rec = " << REC;
        cout << " Max DP = " << DP << endl;
    }
}
