#include<bits/stdc++.h> 
using namespace std; 
   
const int MAX = 9999; 
const int MIN = -9999; 
int del[9999]={0};
  
int minimax(int depth, int nodeIndex, bool maximizingPlayer, int values[], int alpha,int beta,int leaf) 
{ 
      
    if (depth==0)
	{ 	
        return values[nodeIndex]; 
	}
    if (maximizingPlayer) 
    { 
        int best = MIN; 
  
        for (int i = 0; i < leaf; i++) 
        { 	
        	//cout<<endl<<nodeIndex*leaf + i;
            del[nodeIndex*leaf + i] =1;
            int val = minimax(depth-1, nodeIndex * leaf + i, false, values, alpha, beta,leaf); 
			best = max(best, val); 
            alpha = max(alpha, best); 
   
            if (beta <= alpha) 
                break; 
        } 
        return best; 
    } 
    else
    { 
        int best = MAX; 
  
        for (int i = 0; i < leaf; i++) 
        { 
        	//cout<<endl<<nodeIndex*leaf + i;
        	del[nodeIndex*leaf + i] =1;
            int val = minimax(depth-1, nodeIndex * leaf + i, true, values, alpha, beta,leaf);
            best = min(best, val); 
            beta = min(beta, best); 
  
            if (beta <= alpha) 
                break; 
        } 
        return best; 
    } 
} 
 
int main() 
{ 
	int depth,leaf;
	bool maximizingPlayer;
	cout<<"輸入分支:";
	cin>>leaf;	
	cout<<endl<<"輸入層數:";
	cin>>depth;	
    int values[] = {15,4,1,17,9,-20,-19,12,23,-22,10,19,-17,0,-16,11,-8,2,-3,16,-21,-15,-6,-10,-24 };  
    int result=pow(leaf,depth);
    cout <<endl<<"root:"<< minimax(depth, 0, true, values, MIN, MAX,leaf);
    int num=0;
		for(int i=0;i<result;i++){
			if(del[i]==1)
				num++;
		}
		cout<<endl<<"共有"<<result-num<<"個葉節點沒被拜訪"; 
    return 0; 
} 
