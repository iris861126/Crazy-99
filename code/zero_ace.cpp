#include<iostream>
#include<stdlib.h>
#include<string>
#include<time.h>
#include<windows.h>
#define PEOPLE 4  //有幾個人
#define USERNUM 5  //每人牌數
using namespace std;
// 功能牌新增：黑桃A歸零 

string pflo[4]={"黑桃","愛心","方塊","梅花"};
string pnum[13]={"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
void cardfunc(int &, int &, int &, int &, int &, int &, int &, int &, int &, int &);
void num_5_func(int &, int &, int&);

void SetColor(int f=7,int b=0)
{
    unsigned short ForeColor=f+16*b;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,ForeColor);
}

int full_player(){
        int poker[4][13]={0};  // 0:牌堆 ; 1:手牌 ; -1:用掉的牌 
        string hand_card[PEOPLE][USERNUM];  //使用者4人 每人有5張牌
        string card[4][13];  //牌堆的牌 
        int flo,num,all;  //用來產生亂數
        int a[4][5],b[4][5];
        int card_no,flower,number;
        int count=0;
        int c=0;
        int sum=99;
        int useless_card=0;
        int loser[PEOPLE]={0};
        int loser_num=0;
        int poker_pool=0;
        int turn_around=0;
        int s=1;
        int sum_old=0;
//發牌 
        srand((unsigned)time(NULL));
        for(int i=0;i<4;i++){  //poker設初值
            for(int j=0;j<13;j++){
                poker[i][j]=0;
            }
        }
        
        for(int i=0;i<PEOPLE;i++) 
		{  
                for(int j=0;j<USERNUM;j++)    //每個人的牌數
				{  
                    do{
                        all=(int)rand()%52;
                        flo=all/13;
                        num=all%13;                               
                    	a[i][j]=flo;
                    	b[i][j]=num;
                    }while(poker[flo][num]==1 || poker[flo][num]==-1);
                    poker[flo][num]=1;
                    hand_card[i][j]=pflo[flo]+pnum[num];
                }
               
    	}
                
//出牌 
//		for(int i=0;i<PEOPLE;i++)
//		{
		for(int i=0;i<PEOPLE;i+=s)
		{
//				cout << "loser_num= " << loser_num << endl;
				do{
					if(loser[i]==1)  //跳過輸家 
					{
						i+=s;
						if(i>3 && s==1)
						{
							i=0;
						}
						if(i<0 && s==-1)
						{
							i=3;
						} 
						if(loser[i]==1)  //跳過輸家 
						{
							i+=s;
							if(i>3 && s==1)
							{
								i=0;
							}
							if(i<0 && s==-1)
							{
								i=3;
							} 
							if(loser[i]==1)  //跳過輸家 
							{
								i+=s;
								if(i>3 && s==1)
								{
									i=0;
								}
								if(i<0 && s==-1)
								{
									i=3;
								} 							
							}
						}
					}
					if(loser_num ==3)  //已經輸掉的人數 
					{ 	
						SetColor(6,0);
						cout << "  *********************" << endl;
						cout << "  *                   *" << endl;
						cout << "  *  PLAYER_" << i+1 << " WIN!!!  *" << endl;
						cout << "  *                   *" << endl;
						cout << "  *********************" << endl;
						SetColor();
						goto end;
					}
	
					useless_card=0;
					cout << "PLAYER_" << i+1 << ": ";  
					for(int j=0;j<USERNUM;j++)   
					{  	
						cout << hand_card[i][j] << "  ";  //顯示當局的手牌 
						
						if(((b[i][j]!=3) && (b[i][j]!=4) && (b[i][j]!=9) && (b[i][j]!=10) && (b[i][j]!=11) && (b[i][j]!=12))
							||(a[i][j]!=0 && b[i][j]==0))
						{
							if(b[i][j]+sum+1>99)
							{
								useless_card++;
							}
						}
					} 
					
					if(useless_card==5)  //剛輸 
					{
						SetColor(2,0);
						cout << "\nPLAYER_" << i+1<< " LOSE!" << endl;
						SetColor();
						cout << "---------------------------------------------------------------" << endl;
						loser[i] = 1;
						loser_num++;
															
						for(int y=0; y<5 ; y++)
						{
							poker[a[i][y]][b[i][y]]=-1;
						}
						i+=s;
					}
					if(i==4 && s==1)   //不確定(原為i==5) 
					{
						i=i-4;
					}
					else if(i==-1 && s==-1)
					{
						i=i+4;
					}
					
				}while(useless_card==5);
				
				//cout << "\ni= " << i << endl;
/* 
//印出棄牌 
				for (int w=0 ; w<4 ; w++)
				{
					for (int v=0 ; v<13 ; v++)
					{
						card[w][v]=pflo[w]+pnum[v];
						if (poker[w][v]==-1)
						{
							cout << card[w][v] << endl;
						}
					}
				} 	
*/				cout << endl;
//真正開始出牌				
        		do{
					count=0;
					cout << "\nNow sum is: " << sum << endl;
		            cout << "黑桃->0 ,愛心->1 ,方塊->2 ,梅花->3 " << endl; 
					cout << "which card you want to throw(ex: 0 1 -> 黑桃A):";
					cin >> flower >> number;
				
					for (int k=0; k<5 ;k++)
		            {
						if (pflo[flower]+pnum[number-1] == pflo[(a[i][k])]+pnum[(b[i][k])])
						{
							c=k;
							break;
						}
						else
						{
							count++;
						}
						if(count==5)
				    	{
				    		cout << "你的手中無此牌，請重新輸入" << endl;
						}
					}
				}while(count==5);
			    
				cout << "the card you throw:" << pflo[flower]+pnum[number-1] << endl;
				poker[flower][number-1]=-1;
				
				int tmp = i;
				sum_old = sum;
				cardfunc(number,sum,i,tmp,turn_around,loser[0],loser[1],loser[2],loser[3],flower);
				
				int circle = turn_around%2;
				
				if(circle == 0)
				{
					s=1;
				}
				else if (circle == 1)
				{
					s=-1;
				}
				
				if (sum>99)
				{
					SetColor(2,0);
					cout << "\nPLAYER_" << i+1<< " LOSE!" << endl;
					SetColor();
					cout << "---------------------------------------------------------------" << endl;
					loser[i] = 1;
					loser_num++;
					for(int y=0; y<5 ; y++)
						{
							poker[a[i][y]][b[i][y]]=-1;
						}
					sum=sum_old;
				} 
				cout << endl;
				
				
				if(loser_num ==3)  //已經輸掉的人數 
				{
					if(loser[i]==1)  //跳過輸家 
					{
						i+=s;
						if(i>3 && s==1)
						{
							i=0;
						}
						if(i<0 && s==-1)
						{
							i=3;
						} 
						if(loser[i]==1)  //跳過輸家 
						{
							i+=s;
							if(i==3 && s==1)
							{
								i=0;
							}
							if(i==0 && s==-1)
							{
								i=3;
							} 
							if(loser[i]==1)  //跳過輸家 
							{
								i+=s;
								if(i==3 && s==1)
								{
									i=0;
								}
								if(i==0 && s==-1)
								{
									i=3;
								} 							
							}
						}
					}
						SetColor(6,0);
						cout << "  *********************" << endl;
						cout << "  *                   *" << endl;
						cout << "  *  PLAYER_" << i+1 << " WIN!!!  *" << endl;
						cout << "  *                   *" << endl;
						cout << "  *********************" << endl;
						SetColor();
					goto end;
				}
				if(loser[i]!=1)
				{
//抽牌					
					do{
		            all=(int)rand()%52;
		            flo=all/13;
		            num=all%13;
		            a[i][c]=flo;
		            b[i][c]=num;
			        }while(poker[flo][num]==1 || poker[flo][num]==-1);
			                
			        poker[flo][num]=1;
			    	hand_card[i][c]=pflo[(a[i][c])]+pnum[(b[i][c])];
			    	
			    	cout << "Your handcards: ";
			    	for (int j=0; j<5 ; j++)
			        cout << hand_card[i][j] << "\t";
					cout << "\n---------------------------------------------------------------" << endl;
					
					
//判斷牌池還有沒有牌	
					poker_pool=0;				
					for(int x=0; x<4 ; x++)
					{
						
						for(int y=0; y<13 ; y++)
						{
							if(poker[x][y]==0)
							{
								poker_pool++;
							}
						}
					}
					//cout << "poker_pool= " << poker_pool << endl;
//重新洗牌					
					if(poker_pool == 0)
					{
						for(int x=0; x<4 ; x++)
						{
							for(int y=0; y<13 ; y++)
							{
								if(poker[x][y]==-1)
								{
									poker[x][y]=0;
								}
							}
						}
					} 
//一直循環下去 
					if(number==5)
					{
						num_5_func(i,tmp,s);
					}
					else
					{
						if(i==3 && s==1)
						{
							i=-1;
						}
						else if(i==0 && s==-1)
						{
							i=4;
						} 
					}	
				}
				else if(loser[i]==1)
				{
					if(i==3 && s==1)
					{
						i=-1;
					}
					if(i==0 && s==-1)
					{
						i=4;
					}
				}
/*		//印出剩餘的牌(牌堆)
		for (int w=0 ; w<4 ; w++)
		{
			for (int v=0 ; v<13 ; v++)
			{
				card[w][v]=pflo[w]+pnum[v];
				if (poker[w][v]==0)
				{
					cout << card[w][v] << endl;
				}
			}
		} 	
*/
        }
    cout << endl;
        

	end:	
    return 0;
}

void num_5_func(int &i, int &j, int &s)
{
	if(s==1)
	{
		i = j-2;
	}
	else if(s==-1)
	{
		i = j;
	}
}

void cardfunc(int &i, int &j, int &k, int &l, int &turn_around, int &a, int &b, int &c, int &d, int &f) 
{   
	int choose=0;
	int func_or_num=0;
	int new_loser[4]={0};
	int illegal=0;
	
	new_loser[0]=a;
	new_loser[1]=b;
	new_loser[2]=c;
	new_loser[3]=d;
	/*
	for(int m=0 ; m<4 ; m++)
	{
		cout << "new_loser[" << m << "]= " << new_loser[m] << endl;
	}
    */
	switch(i)
	{
	case 1:
		if(f==0)
		{
			j=0;
		}
		else
		{
			j=i+j;
		}
	break;	
		
	case 2:
	case 3:
	case 6:
	case 7:
	case 8:
	case 9:
		j=i+j;
	break;
	
	case 4:
		do{
			cout << "use function card →1 / use number card →-1" << endl;
			cin >> func_or_num;
			if (func_or_num == 1) 
			{
				turn_around++;
			}
			else if(func_or_num == -1) 
			{
				j=j+4;
			}
			else
			{
				cout << "輸入無效，請重新輸入： " << endl;
			}
		}while((func_or_num!=1) && (func_or_num!=-1) );
	break;
	
	case 5:
		do{
			cout << "use function card →1 / use number card →-1" << endl;
			cin >> func_or_num;
			if (func_or_num == 1) 
			{
				cout << "Who you want to choose: " << endl;
				do{
					//cout << "illegal_0=" << illegal << endl;
					l=0;
					illegal=0;
					
					for (int n=0; n<4 ; n++)
					{
						
						cin >> l;
						n=l-1;
						illegal=0;
						
						if(new_loser[n]==1)
						{
							if(l==n+1)
							{
								//cout << "illegal_1="<<illegal<<endl;
								cout << "輸入無效，請重新輸入： " << endl;
							 	illegal = 1;
							 	//cout << "illegal_2="<<illegal<<endl;
								break;
							}
						}
						else
						{
							if(l==k+1)
							{
								cout << "輸入無效，請重新輸入： " << endl;
								break;
							}
							else if(l<5 && l>0)	
							{
								//cout << "illegal_3="<<illegal<<endl;
								break;
							}
								
							else
								cout << "輸入無效，請重新輸入： " << endl;	
								break;
						}
					}
					
				}while(l>4 || l<1 || l==k+1 || illegal==1);
			}
			else if(func_or_num == -1) 
			{
				j=j+5;
			}
			else
			{
				cout << "輸入無效，請重新輸入： " << endl;
			}
		}while((func_or_num!=1) && (func_or_num!=-1) );
	break;	
	
	case 10:
	    
		do{
			cout << "use function card →1 / use number card →-1" << endl;
			cin >> func_or_num;
			if (func_or_num == 1) 
			{
				do{
				cout << "You want to +10 or -10(1 →+10 / -1 →-10): ";
				cin >> choose;
				if (choose==1)
					j=i+j;
				else if((choose==-1)&&(j-i>0))
					j=j-i;
				else
					cout << "輸入無效，請重新輸入： " << endl;
				}while( ((choose!=1) && (choose!=-1)) || ((choose==-1) && (j-i<0)) );
			}
			else if(func_or_num == -1) 
			{
				j=j+10;
			}
			else
			{
				cout << "輸入無效，請重新輸入： " << endl;
			}
		}while((func_or_num!=1) && (func_or_num!=-1) );
	break;
	
	case 11:
		do{
			cout << "use function card →1 / use number card →-1" << endl;
			cin >> func_or_num;
			if (func_or_num == 1) 
			{
				j=j;
			} 
			else if(func_or_num == -1) 
			{
				j=j+11;
			}
			else
			{
				cout << "輸入無效，請重新輸入： " << endl;
			}
		}while((func_or_num!=1) && (func_or_num!=-1) );
	break;
	
	case 12:	
		do{
			cout << "use function card →1 / use number card →-1" << endl;
			cin >> func_or_num;
			if (func_or_num == 1) 
			{
				do{
				cout << "You want to +20 or -20(1 →+20 / -1 →-20): ";
				cin >> choose;
				if (choose==1)
					j=20+j;
				else if((choose==-1)&&(j-i>0))
					j=j-20;
				else
					cout << "輸入無效，請重新輸入： " << endl;
				}while( ((choose!=1) && (choose!=-1)) || ((choose==-1) && (j-i<0)) );
			}
			else if(func_or_num == -1) 
			{
				j=j+12;
			}
			else
			{
				cout << "輸入無效，請重新輸入： " << endl;
			}
		}while((func_or_num!=1) && (func_or_num!=-1) );
	break;
	
	case 13:
		do{
			cout << "use function card →1 / use number card →-1" << endl;
			cin >> func_or_num;
			if (func_or_num == 1) 
			{
				j=99;
			}
			else if(func_or_num == -1) 
			{
				j=j+13;
			}
			else
			{
				cout << "輸入無效，請重新輸入： " << endl;
			}
		}while((func_or_num!=1) && (func_or_num!=-1) );
	break;
	}
}




int main()
{
	
	char answer;
	SetColor(3,0);
	cout << "===    ===    ===  =========  ==         =========  =========  ====       ====" << endl ;
	cout << " ==   == ==   ==   ==         ==         ==         ==     ==  == ==     == ==" << endl ;
	cout << "  == ==   == ==    =========  ==         ==         ==     ==  ==  ==   ==  ==" << endl ;
	cout << "   ===     ===     ==         ==         ==         ==     ==  ==   == ==   ==" << endl ;
	cout << "    =       =      =========  =========  =========  =========  ==    ===    ==" << endl ;
	cout << endl ;
	
	cout << "                              =========  =========                            " << endl ;
	cout << "                                  ==     ==     ==                            " << endl ;
	cout << "                                  ==     ==     ==                            " << endl ;
	cout << "                                  ==     ==     ==                            " << endl ;
	cout << "                                  ==     =========                            " << endl ;
	cout << endl ;
	SetColor(6,0);
	cout << "           =========  ========       ==      =========  ==      ==            " << endl ;
	cout << "           ==         ==     ==     =  =          ===    ==    ==             " << endl ;
	cout << "           ==         ========     ======       ===       ==  ==              " << endl ;
	cout << "           ==         ==  ===     ==    ==    ===           ==                " << endl ;
	cout << "           =========  ==    ===  ===    ===  =========      ==                " << endl ;
	cout << endl ;
	SetColor(6,0);
	cout << "                                                        ==========  ==========" << endl ;
	cout << "                                                        ==      ==  ==      ==" << endl ;
	cout << "                                                        ==========  ==========" << endl ;
	cout << "                                                                ==          ==" << endl ;
	cout << "                                                        ==========  ==========" << endl ;
	cout << endl ;
	SetColor();
	cout << "L0ADING..." << endl ;
	cout << "\nDo you want to watch the instruction? (y/n)" ;
	cin >> answer;
	if (answer=='y')
	{
		cout << "\nFirst you can see your handcards on the screen" << endl;
	    //cout << "/nDecide how many card you want throw(1or2)" << endl;
	    cout << "\nPlease enter the color first" << endl;
	    cout << "\nSuch as 黑桃→0 /紅心→1/方塊→2/梅花→3" << endl;
	    cout << "\nSecond enter the number of card(1~13)" << endl;
	    cout << "\nfunction card: 4→迴轉; 5→指定; 10→加減十; 11→Pass; 12→加減二十; 13→99" << endl;
	    //cout << "/nIf you want to throw two cards just do it twice" << endl;
	    cout << "\nFinal Good Luck and Have Fun!!!" << endl;
		cout << endl;
	    cout << "---------------------------------------------------------------" << endl;
 	    
	}
    
	full_player();
    
    system("Pause");
	return 0;
}
