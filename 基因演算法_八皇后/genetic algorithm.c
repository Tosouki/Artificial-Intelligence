#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<limits.h>

int GroupScale; //棋子數量 
int ProblemScale; //棋盤規模 
int CrossoverNum; //交配數量 
int MutationNum;
int MaxGeneration=10000;
double CrossoverRate=0.8; //交配率 
double MutationRate=0.1; //突變率 

int**InitPopulation(){
	int i,j;
	int**a=new int*[GroupScale];
	
	for(i=0;i<GroupScale;i++){
		a[i]=new int[ProblemScale];
	}
	
	srand((unsigned)time(NULL));
	for(i=0;i<GroupScale;i++){
		for(j=0;j<ProblemScale;j++){
			a[i][j]=ProblemScale*rand()/(RAND_MAX+1);
		}
	}
	return a;
}

int main(void){
	clock_t start,finish;
	int i,j,k,n,min,temp;
	int**queen,*fitness,*selection;
	double rate,*value,total,duration;
	
	printf("請輸入種族數量和棋盤規模:\n");
	scanf("%d%d",&GroupScale,&ProblemScale);
	
	CrossoverNum=(int)(GroupScale * CrossoverRate);
	MutationNum=(int)(GroupScale * MutationRate);
	if(CrossoverNum%2==1) CrossoverNum++;
	
	fitness=new int[GroupScale];
    value=new double[GroupScale];
    selection=new int[CrossoverNum];
    
    while(true){
    	start=clock();
    	//創建初始群體
		queen = InitPopulation();		
		while(MaxGeneration--){
		//計算群體中個體適合度
		total=0;
		min=INT_MAX;
		for(k=0;k<GroupScale;k++){
			fitness[k]=0;
			for(i=0;i<ProblemScale-1;i++){
				for(j=i+1;j<ProblemScale;j++){
					if(queen[k][i]==queen[k][j]) fitness[k]++;
					if(abs(queen[k][i]-queen[k][j])==j-i) fitness[k]++;
					} 
				}
				if(fitness[k]<min){
					n=k;
    				min=fitness[k];
				} 
			}
			//評估適合度 
			if(min==0) break; 
			//根據適合度選擇個體
			for(k=0;k<GroupScale;k++){
				value[k]=1.0/fitness[k];
				total+=value[k];
			}
			for(k=0;k<GroupScale;k++){
				value[k]/=total;
				if(k!=0) value[k]+=value[k-1];
			}
			//用賭盤選擇法選擇個體
			for(i=0;i<CrossoverNum;i++){
				rate=rand()*1.0/(RAND_MAX+1);
				if(rate<value[0]) selection[i]=0;
				else{
					for(j=1;j<GroupScale;j++){
						if(rate>=value[j-1] && rate<value[j]){
							selection[i]=j;
							break;
						} 
					} 
				}
			}
			//被選擇的個體進行交叉繁殖
			for(i=0;i<CrossoverNum;i+=2){
				k=ProblemScale*rand()/(RAND_MAX+1);
				for(j=k;j<ProblemScale;j++){
					temp=queen[selection[i]][j];
					queen[selection[i]][j]=queen[selection[i+1]][j];
					queen[selection[i+1]][j]=temp;					
				}
			}
			//繁殖過程中引入變異
			for(k=0;k<MutationNum;k++){
				i=GroupScale*rand()/(RAND_MAX+1);
				j=ProblemScale*rand()/(RAND_MAX+1);
				queen[i][j]=ProblemScale*rand()/(RAND_MAX+1);				
			}  
		}
		//計算時間 
		finish=clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC; 
		//列印正確棋盤 
		if(min==0){
			printf("\n");
			for(i=0;i<ProblemScale;i++){
				for(j=0;j<ProblemScale;j++){
					if(queen[n][i]==j) printf("#|");
					else printf("_|");
				}
				printf("\n");
			}
			//printf("花費%.3lf秒.\n",duration);
			break;
		} 
	}
	return 0;
}
