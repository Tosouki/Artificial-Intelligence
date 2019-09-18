#include<stdio.h>
#include<stdlib.h>
#include<time.h>
 
int queens[8][8];//實際棋盤 
int check[8][8];//虛擬棋盤 

//每列隨機產生一位皇后 
void start(){
	int i,j;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			queens[i][j]=0;	
		}
	}
	for(i=0;i<8;i++){
		int chess=rand() % 8;
		queens[i][chess]=1;		
	}
}
//列印八皇后棋盤 
void print(){
	int i,j;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(queens[i][j]==1){
				printf("#|");					
			}
			else{
				printf("_|");
			}
		}
		printf("\n");
	}	
}
//紀錄所有棋盤衝突數
int conflict(int col,int row){  
	int count = 0,p,i,j; 
	check[col][row]=1; //預設將皇后放在此位置 
	for(p=0;p<64;p++){//紀錄假如將皇后放在上述位置，所有的皇后衝突數是多少 
		if(check[p/8][p%8]==1){
			for(i=0;i<8;i++){				//同一行 
				if(i != p/8 && check[i][p%8]==1)
					count++;
			}
			for(i=0;i<8;i++){				//同一列 
				if(i != p%8 && check[p/8][i]==1)
					count++;
			}
			for(i=p/8,j=p%8;i<8&&j<8;i++,j++){//右下方 
				if(i != p/8 && check[i][j]==1)
					count++;
			}
			for(i=p/8,j=p%8;i<8&&j>=0;i++,j--){//左下方 
				if(i != p/8 && check[i][j]==1)
					count++;
			}
			for(i=p/8,j=p%8;i>=0&&j<8;i--,j++){//右上方 
				if(i != p/8 && check[i][j]==1)
					count++;
			}
			for(i=p/8,j=p%8;i>=0&&j>=0;i--,j--){//左上方 
				if(i != p/8 && check[i][j]==1)
					count++;
			}												
		}
	}
	check[col][row]=0;
	return count/2;	//會重複計算衝突 
}
int Hill(){
	int move,i,j,k;
	for(move=0;move<=50;move++){
		for(i=0;i<8;i++){
			for(j=0;j<8;j++){
				check[i][j] = queens[i][j];	//複製棋盤 
			}
		}
		int h[8][8];//記錄棋盤衝突數 
		int minc=99,x,y,now_conflict;
		for(i=0;i<8;i++){
			for(j=0;j<8;j++){
				for(k=0;k<8;k++){//先把虛擬棋盤中要更新的一列先歸零 
					check[i][k]=0;
				} 
				h[i][j]=conflict(i,j);//記錄此位置所產生的衝突數 
				if(queens[i][j]==1){ //假如此位置是原本皇后位置，則另外記錄 
					now_conflict=h[i][j];
					} 
				if(h[i][j]<minc){//假如此位置的衝突數比預設小，記錄位置與衝突數 
					minc=h[i][j];
					x=i;
					y=j;
				}
				for(k=0;k<8;k++){//恢復成與真實棋盤相同	
					check[i][k]=queens[i][k];
				}				
			}
			if(now_conflict>minc){//假如原本皇后衝突比比較後大則更改皇后位置 
				for(i=0;i<8;i++){
					queens[x][i]=0;
				} 
				queens[x][y]=1;
			}
		}
		if(checkit(h)){
			return 1;
		}			
	}
	return 0;
}
int checkit(int h[8][8]){//檢查每一列皇后的衝突數 
	int i,j;
	for(i=0;i<8;i++){
		int flag=0;
		for(j=0;j<8;j++){
			if(queens[i][j] == 1 && h[i][j]==0){
				flag=1;
				break;
			}
		}
		if(flag==0){
			return 0;
		}
	}
	return 1;
}
void Restart(){ //重新開始新棋盤 
	int find=0,restart=-1;	
	while(!find){
		start();
		find=Hill();		
		restart++;	
	}
	print();
	printf("\n重新次數:%d\n",restart);
}
int main(void){
	srand(time(NULL));
	Restart();	
	return 0;	
}
