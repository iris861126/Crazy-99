#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

int player[8][13];
int card[52];
int card_index;
int player_card_index[8];

//���J�P�C������l�Ƴ]�w
//�������ͤ@�Ʒs�P�B�M�ũҦ����a���P���ʧ@
void initial()
{
     int i,j;
     for(i=0;i<=3;i++)
     {
        for(j=0;j<=12;j++)
        {
           player[i][j]=-1;
        } 
     }
     
     for(i=0;i<=51;i++)
     {
        card[i]=i;
     }
     
     for(i=0;i<=3;i++)
     {
        player_card_index[i]=0;
     }
       
     card_index = 0;
     srand( time(NULL) );
}

//�N��i���J�P�洫 
void swap2card(int a, int b)
{
   int temp;
   temp = card[a];
   card[a] = card[b];
   card[b] = temp;
}

//�~�P(�H�C���洫��i�P���覡�i�楴�õP���ʧ@)
void shuffle(int n)
{
   int i;
   int sa, sb;
   for(i=1;i<=n;i++)
   {
      sa = rand() % 52;
      sb = rand() % 52;
      swap2card(sa, sb);   
   }
}

//���o���J�P��⪺�r���X
char getsuit(int card_no)
{
   char sign[4]={6,3,4,5};
   char suit;
   
   suit = sign[ card_no/13 ];
   
   return suit;     
}

//���o���J�P���I�ƕ� 
int getpoint(int card_no)
{
   int point;
   
   point = card_no%13 + 1;   
   return point;     
}

//�L�X��Ƽ��J�P�A�̧ǥѲ�0�i�ܲ�51�i�@52�i���J�P�����P�I��
void display_allcard()
{
   int i;
   char suit;
   int point;
   
   for(i=0;i<=51;i++)
   {
     suit = getsuit( card[i] );
     point = getpoint( card[i] );
     cout << "(" << setw(2) << i << ")card no. " << setw(2) << card[i] << " " << suit << setw(2) << point << endl; 
   }
   cout << "------------------------------------------------" << endl << endl;
}

//�Y�@�쪱�a����@�i�P
int draw(int player_no)
{
   int card_no;
   int index;
   
   card_no = card[card_index];
   card_index = card_index + 1;
   
   index = player_card_index[player_no];
   player[player_no][index] = card_no;
   player_card_index[player_no] = player_card_index[player_no] + 1;
   
   return card_no;
}

//��ܬY�@�쪱�a�⤤���Ҧ��P
void display_player_card(int player_no)
{
   int i;
   int index;
   char suit;
   int point;
   
   cout << "player " << player_no << endl;
   index = player_card_index[player_no];
   for(i=0;i<index;i++)
   {
     suit = getsuit( player[player_no][i] );
     point = getpoint( player[player_no][i] );
     cout << suit << setw(2) << point << "  " ;  
   }
   cout << endl;
}