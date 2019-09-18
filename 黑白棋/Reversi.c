#include<stdio.h>

//列印黑白旗棋盤 
void print(char chessboard[][8]){
	int row,col;
	//輸出頂部字母 
	printf("\n ");
	for(col=0;col<8;col++){
		printf("   %c",'A'+col);
	} 
	printf("\n");
	//輸出頂部 
	printf("  ┌");
	for(col=0;col<7;col++){
		printf("  ─┬"); 
	}
	printf("  ─┐\n");
	//輸出中間棋盤 
	for(row=0;row<8;row++){
		printf("%2d｜",row+1);
		for(col=0;col<8;col++){
			if(chessboard[row][col]==1){//白棋 
				printf("●｜"); 
			}
			else if(chessboard[row][col]==-1){
				printf("○｜");
			}
			else{
				printf("  ｜"); 
			} 
		}
		printf("\n");
		if(row<7){
			printf("  ├");
			for(col=0;col<7;col++){
				printf("  ─┼"); 
			}
			printf("  ─┤\n"); 
		} 
	}
	//輸出底部 
	printf("  └");
	for(col=0;col<7;col++){
		printf("  ─┴"); 
	}
	printf("  ─┘\n"); 	 
}
//檢查是否可下子
int check(char chessboard[][8],int hasDown[][8],char player){
	int rowdelta,coldelta,row,col,x,y=0;
	int istep = 0;
	char opponent = (player ==1) ? -1 : 1 ;//對方棋子
	char myplayer = -1 * opponent;//我方棋子
	//將hasDown清除
	for(row=0;row<8;row++){
		for(col=0;col<8;col++){
			hasDown[row][col]=0; 
		} 
	}
	//判斷棋盤中哪裡可下子
	for(row=0;row<8;row++){
		for(col=0;col<8;col++){
			if(chessboard[row][col]!=0){
				continue; 
			}
			//檢查上下行 
			for(rowdelta=-1;rowdelta<=1;rowdelta++){
				for(coldelta=-1;coldelta<=1;coldelta++){
					if(row+rowdelta<0||row+rowdelta>=8
					||col+coldelta<0||col+coldelta>=8
					||(rowdelta==0&&coldelta==0)){
						continue; 
					}
					//假如[row+rowdelta,col+coldelta]有對手的棋子 
					if(chessboard[row+rowdelta][col+coldelta]==opponent){
						//以對手的棋子位置為座標 
						x=row+rowdelta;
						y=col+coldelta;
						//以對手棋子為起始點，向四周查找己方的棋子，以攻擊對方棋子 
						while(1){
							//對手棋子四周座標
							x+=rowdelta;
							y+=coldelta;
							//超過棋盤範圍
							if(x<0||x>=8||y<0||y>=8){
								break;//退出循環 
							}
							//若對應位置為空
							if(chessboard[x][y]==0){
								break; 
							}
							//若對應位置的子是目前下棋方的
							if(chessboard[x][y]==myplayer){
								//設hasDown為1，指該位置可下子 
								hasDown[row][col]=1;
								istep++;//累加可下子數量 
								break ; 
							} 
						} 
					} 
				} 
			} 
		} 
	}
	return istep; 
}

void playstep(char chessboard[][8],int row,int col,char player){
	int rowdelta,coldelta,x,y=0;
	char opponent = (player ==1) ? -1 : 1 ;//對方棋子
	char myplayer = -1 * opponent;//我方棋子
	chessboard[row][col]=myplayer;//保存下的棋子
	//檢查下子四周的棋子
	for(rowdelta=-1;rowdelta<=1;rowdelta++){
		for(coldelta=-1;coldelta<=1;coldelta++){
			//若座標超過棋盤界限
			if(row+rowdelta<0||row+rowdelta>=8||col+coldelta<0
			||col+coldelta>=8||(rowdelta==0&&coldelta==0)){
				continue; 
			}
			//若該位置是對手的棋子
			if(chessboard[row+rowdelta][col+coldelta]==opponent){
				//對手棋子四周座標
				x=row+rowdelta;
				y=col+coldelta;
				//在對手棋子四周尋找我方棋子
				while(1){
					x+=rowdelta;
					y+=coldelta;
					//若座標超過棋盤
					if(x<0||x>=8||y<0||y>=8){
						break; 
					}
					//若對應位置為空
					if(chessboard[x][y]==0){
						break; 
					}
					//若對應位置為我方棋子
					if(chessboard[x][y]==myplayer){
						while(chessboard[x-=rowdelta][y-=coldelta]==opponent){
							//將中間的棋子變成我方棋子
							chessboard[x][y]=myplayer; 
						} 
						break; 
					} 
				} 
			} 
		} 
	}		
}
int getmaxscore(char chessboard[][8],char player){
	int score,row,col;
	char opponent=(player==1)?-1:1;
	char myplayer=-1*opponent;
	for(row=0;row<8;row++){
		for(col=0;col<8;col++){
			score-=chessboard[row][col]==opponent;
			score+=chessboard[row][col]==myplayer; 
		} 
	}
	return score; 
} 
//獲取最佳下子位置
int bestplay(char chessboard[][8],int hasDown[][8],char player){
	int row,col,i,j;
	char chessboard1[8][8]={0};
	int MaxScore=0;
	int Score=0;
	char opponent=(player==1)?-1:1;//對手的棋子
	for(row=0;row<8;row++){
		for(col=0;col<8;col++){
			//若該位置不可下子 
			if(!hasDown[row][col]){
				continue; 
			}
			//複製棋盤 
			for(i=0;i<8;i++){
				for(j=0;j<8;j++){
					chessboard1[i][j]=chessboard[i][j]; 
				} 
			}
			//在複製的棋盤中下子 
			playstep(chessboard1,row,col,player);
			//獲取下子後可得分數 
			Score=getmaxscore(chessboard1,player);
			if(MaxScore<Score){
				MaxScore=Score; 
			} 
		} 
	}
	return MaxScore;//返回得到的最高分 
}
//AI自動下子
void autoplaystep(char chessboard[][8],int hasDown[][8],char player){
	int row,col,row1,col1,i,j;
	//對方可下子得到的分數和最小分數 
	int Score=0,MinScore=100;
	//臨時數據，保存棋盤下子位置 
	char chessboard1[8][8];
	//臨時數據，保存可下子位置
	int hasDown1[8][8];
	char opponent=(player==1)?-1:1;//對手下的棋子 
	for(row=0;row<8;row++){
		for(col=0;col<8;col++){
			//若不可下子 
			if(hasDown[row][col]==0){
				continue; 
			}
			for(i=0;i<8;i++){
				for(j=0;j<8;j++){
					chessboard1[i][j]=chessboard[i][j]; 
				} 
			}
			//試著在臨時棋盤中下子 
			playstep(chessboard1,row,col,player);
			//檢查對手是否有地方可下子 
			check(chessboard1,hasDown1,opponent);
			//獲得臨時棋盤中對方下子的得分情況 
			Score=bestplay(chessboard1,hasDown1,opponent);
			//保存對方得分最低的下法 
			if(Score<MinScore){
				MinScore=Score;
				row1=row;
				col1=col; 
			} 
		} 
	}
	printf("AI下子位置為%c%d",'A'+col1,row1+1);		
	playstep(chessboard,row1,col1,player); 
} 
int main(void){
	//保存棋盤中下子的狀態 
	char chessboard[8][8];
	//保存棋盤中各位置，可下子為1,其餘為0
	int hasDown[8][8]={0};
	int AI,play,row,col,x;
	char y;
	//已下棋子數量 
	int iCount=0;
	//下棋方 
	int player=0;
	//跳過下子的次數，若為2，表示雙方都不能下子
	int skipplay=0;
	int Score[2];
	char select;
	do{
		int black=2,white=1;
		//計算下棋方
		printf("是否為先手(y/n)?");
		scanf("%c",&select);
		if(select=='Y'||select=='y'){
			player=1;
			play=2;
			AI=1;	
		}
		else{
			player=0;
			play=1;
			AI=2;			
		}
		iCount=4;//累積下子數 
		//清空棋盤 
		for(row=0;row<8;row++){
			for(col=0;col<8;col++){
				chessboard[row][col]=0; 
			} 
		}
		//放置白棋
		chessboard[3][3]=chessboard[4][4]=1; 
		//放置黑棋 
		chessboard[3][4]=chessboard[4][3]=-1;
		printf("初始棋盤:\n");
		print(chessboard);
		do{
			//下黑子 
			if(player==1){
				player=0;
				//判斷是否可下黑子 
				skipplay=0;
				if(check(chessboard,hasDown,play)){
					//陷入循環，直到玩家輸入正確座標
					while(1){
						fflush(stdin);//清除輸入緩衝區 
						printf("輸入下子的位置:");
						scanf("%c%d",&y,&x);
						x--;//計算行座標
						if(y>='a'){
							y=y-'a'; 
						}
						else{
							y=y-'A'; 
						}
						if(x>=0&&y>=0&&x<8&&y<8&&hasDown[x][y]){
							playstep(chessboard,x,y,play);
							iCount++;
							break; 
						}
						else{
							printf("輸入錯誤，請重新輸入\n"); 
						} 
					}
					printf("\n下子後的狀態:\n");
					print(chessboard); 
				}
				else if(++skipplay<2){
					fflush(stdin);
					printf("你沒位置可下，按Enter鍵繼續");
					scanf("%c",&select); 
				}
				else{
					printf("雙方都沒地方下子，遊戲結束!"); 
				} 
			}
			else{
				player=1;
				if(check(chessboard,hasDown,AI)){
					skipplay=0;
					autoplaystep(chessboard,hasDown,AI);
					iCount++;
					printf("\nAI下子後的狀態:\n");
					print(chessboard); 
				}
				else if(++skipplay<2){
					printf("我沒位置可下，請繼續\n");
				}
				else{
					printf("雙方都沒地方下子，遊戲結束!"); 
				} 
			} 
		}while(iCount<64&&skipplay<2);
		print(chessboard);
		Score[0]=Score[1]=0;
		for(row=0;row<8;row++){
			for(col=0;col<8;col++){
				Score[0]+=chessboard[row][col]==-1;
				Score[1]+=chessboard[row][col]==1; 
		} 
		} 
		printf("最終成績:\n");
		printf("AI:%d\n玩家:%d\n",Score[1],Score[0]);
		fflush(stdin);
		printf("繼續下一局(y/n)?");
		scanf("%c",&select);
	}while(select=='Y'||select=='y');
	printf("Game Over!\n");
	return 0 ; 
}
