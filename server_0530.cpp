#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
#pragma comment(lib,"wsock32.lib")
#include <winsock.h>
#include <time.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

// 一些結構變數....
//地圖的屬性
struct map 
{
	int player=0;
	int equip1=0; //0=nothing, 1=knife, 2=machinegun, 3=sniper, 4=armor
	int equip2=0; //0=nothing, 1=health
};
map mapARRAY[24];

//玩家屬性
struct gamer 
{
	int alive = 1;
	int blood=15;
	int armor=0;
	int maxwalk=6;
	int weapon=0;
	int locat;
	int heal=0;
	int walkespace;
};
gamer gamerARRAY[4];

//一些參數....
//玩家狀態訊息
char situmessage1[10];
char situmessage2[10];
char situmessage3[10];
char situmessage4[10];

//地圖訊息
char mapmessage[200];

//暫存的空間
char strbuffer[20];

//玩家傳來的指令訊息
char instruction1[10];
char instruction2[10];
char instruction3[10];
char instruction4[10];

//指向指令訊息的指標陣列
char* inst[5];

//傳給玩家的編號
char client1[2] = { "1" };
char client2[2] = { "2" };
char client3[2] = { "3" };
char client4[2] = { "4" };

//存活名單
char alivemess[5];

//count round
int N=0;

//some function....
void int2str(int , char*);//整數轉字元
int  str2int(char);
void coding(char*, char*);//
void situcode(int);
void movefunc();
void takefunc();
void attackfunc();
void healfunc();
void randmap(int);
void spacecal();


int main(int argc, char *argv[])
{	
	/******************************************/
	//init
	PlaySound(TEXT("gamemusic.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	int port;
	char ip[20];

	printf("　　　　　　　龜　　　　　　　　　　　　　　　龜　　龜                    ###############\n");
	printf("　　　　　　　龜　　　　　　　　　龜　　　　　龜　　龜                 ######################\n");
	printf("　　　　　　　龜　　　　　　　　　　龜　龜　　龜　　龜　　龜         ##########################\n");
	printf("　　　　　　　龜　　　　　　　　　　龜　　龜　龜　　龜　龜龜        #############################\n");
	printf("　　　　　　　龜　　　　　  　　　　　　　龜　龜　　龜龜          #################################\n");
	printf("龜龜龜龜龜龜龜龜龜龜龜龜龜龜龜　　　　　　　　龜　　龜           #####    ################    #####\n");
	printf("　　　　　　　龜　　　　　　　　龜龜龜　　　龜龜　　龜龜        ####       ##############       ####\n");
	printf("　　　　　　龜　龜　　　　　　　　　龜　　龜　龜　　龜　龜     ####        ##############        ####\n");
	printf("　　　　　　龜　龜　　　　　　　　　龜　龜　　龜　　龜　龜       ##       ################       ##\n");
	printf("　　　　　　龜　　龜　　　　　　　　龜　　　　龜　　龜           ###     ###### ##### #####     ###\n");
	printf("　　　　　龜　　　龜　　　　　　　　龜　　　龜　　　龜　　龜      ############  #####  ###########\n");
	printf("　　　　　龜　　　　龜　　　　　　　龜　　龜　　　　龜　　龜        ############################\n");
	printf("　　　　龜　　　　　　龜　　　　　　龜　龜　　　　　龜　　龜         ##########################\n");
	printf("　　　龜　　　　　　　　龜龜龜　　龜　龜　　　　　　　龜龜            ###   ####    ####   ###\n");
	printf("　龜龜　　　　　　　　　　龜　　龜　　　龜                            ###   ####    ####   ###\n");
	printf("　　　　　　　　　　　　　　　　　　　　　龜龜龜龜龜龜龜龜龜龜        ###   ####    ####   ###\n");
	printf("\n");
	printf("         $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$                     @@@@@@\n");
	printf("         $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$                     @@@@@@@@@\n");
	printf("         $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$                     @@@@@@@@@\n");
	printf("        $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$                     @@@@@@\n");
	printf("       $$$$$$$$$$$$$$$$$$         $$\n");
	printf("     $$$$$$$$$$$$$$$$$$$        $$ \n");
	printf("    $$$$$$$$$$$$$$$$$$$$ $$$$$$$\n");
	printf("   $$$$$$$$$$$$$$$$$$$$\n");
	printf("  $$$$$$$$$$$$$$$$$$$$$\n\n");
	printf("  enter port :");
	scanf_s("%d", &port);
	WSADATA wsaData = {0};
	WORD wVer = MAKEWORD(2,2);
	WSAStartup( wVer, &wsaData );
	
	//socket
	SOCKET hSock;
	hSock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

	//bind
	sockaddr_in saListen = {0};
	saListen.sin_family = AF_INET;
	saListen.sin_port = htons( port );
	saListen.sin_addr.s_addr = htonl( INADDR_ANY );
	bind( hSock, (sockaddr*)&saListen, sizeof(sockaddr) );
	
	//listen
	listen( hSock, 5 );
	printf("waiting for connection ... \n");

	//accept
	sockaddr_in saClient;
	int nSALen = sizeof( sockaddr );
	SOCKET hClient1 = accept( hSock, (sockaddr*)&saClient, &nSALen );
	SOCKET hClient2 = accept( hSock, (sockaddr*)&saClient, &nSALen );
	SOCKET hClient3 = accept( hSock, (sockaddr*)&saClient, &nSALen );
	SOCKET hClient4 = accept( hSock, (sockaddr*)&saClient, &nSALen );
	/*********************************************************/

	//進入遊戲

	//將指令指標指向指令陣列
	inst[1] = instruction1;
	inst[2] = instruction2;
	inst[3] = instruction3;
	inst[4] = instruction4;

	//傳送編號給玩家
	send(hClient1, client1, sizeof(client1), 0);
	send(hClient2, client2, sizeof(client2), 0);
	send(hClient3, client3, sizeof(client3), 0);
	send(hClient4, client4, sizeof(client4), 0);
	
	int n,count;
	int victory;//獲勝者
	
	randmap(0);

	while (1)//gaming
	{
		for (count = 0, n = 0; n < 4; n++)//檢查生還者
		{
			if (gamerARRAY[n].alive == 1)
			{
				alivemess[n] = '1';
				count += 1;
				victory = n + 1;
			}
			else if(gamerARRAY[n].alive == 0)
				alivemess[n] = '0';
		}

		//code map message
		coding(mapmessage, strbuffer);

		// code gamer situation message
		if (count != 1)
		{
			for (n = 0; n < 4; n++)
				situcode(n);
		}

		else if (count == 1)//勝利者誕生
		{
			switch (victory)
			{
			case 1:
				situmessage1[0] = 'v';
				situmessage2[0] = 'l';
				situmessage3[0] = 'l';
				situmessage4[0] = 'l';
				break;
			case 2:
				situmessage1[0] = 'l';
				situmessage2[0] = 'v';
				situmessage3[0] = 'l';
				situmessage4[0] = 'l';
				break;
			case 3:
				situmessage1[0] = 'l';
				situmessage2[0] = 'l';
				situmessage3[0] = 'v';
				situmessage4[0] = 'l';
				break;
			case 4:
				situmessage1[0] = 'l';
				situmessage2[0] = 'l';
				situmessage3[0] = 'l';
				situmessage4[0] = 'v';
				break;
			default:
				break;
			}
		}

		//send messages to players
		send(hClient1, mapmessage,  sizeof(mapmessage) , 0);//send client1
		send(hClient1, situmessage1, sizeof(situmessage1), 0);
		send(hClient1, alivemess, sizeof(alivemess), 0);

		send(hClient2, mapmessage, sizeof(mapmessage), 0);//send client2
		send(hClient2, situmessage2, sizeof(situmessage2), 0);
		send(hClient2, alivemess, sizeof(alivemess), 0);

		send(hClient3, mapmessage, sizeof(mapmessage), 0);//send client3
		send(hClient3, situmessage3, sizeof(situmessage3), 0);
		send(hClient3, alivemess, sizeof(alivemess), 0);

		send(hClient4, mapmessage, sizeof(mapmessage), 0);//send client4
		send(hClient4, situmessage4, sizeof(situmessage4), 0);
		send(hClient4, alivemess, sizeof(alivemess), 0);

		if (count == 1)//Game over
			break;

		//recive instrustaion from players
		recv(hClient1, instruction1, sizeof(instruction1), 0);//recive
		recv(hClient2, instruction2, sizeof(instruction2), 0);//recive
		recv(hClient3, instruction3, sizeof(instruction3), 0);//recive
		recv(hClient4, instruction4, sizeof(instruction4), 0);//recive

		//calculate
		movefunc();
		takefunc();
		attackfunc();
		healfunc();
		N += 1;
		if(N%3==0)
			randmap(1);
	}//end gaming


	//*****close*****
	closesocket( hSock );
	WSACleanup();	
	
	system("PAUSE");
	return EXIT_SUCCESS;
}//main end


void coding(char* mapmessage, char* strbuffer)
{
	int n, m;
	for (n = 0, m = 0; n < 24; n++)//check map & coding
	{
		if (mapARRAY[n].equip1 == 0 && mapARRAY[n].equip2 == 0 && mapARRAY[n].player == 0)
			continue;
		else//make code
		{
			//set first & second bit
			int2str(n, strbuffer);
			if (n < 10)
			{
				mapmessage[m] = '0';
				mapmessage[m + 1] = strbuffer[0];
			}
			else
			{
				mapmessage[m] = strbuffer[0];
				mapmessage[m + 1] = strbuffer[1];
			}

			//set third bit
			switch (mapARRAY[n].equip1)
			{
			case 0:
				mapmessage[m + 2] = 'x';
				break;
			case 1:
				mapmessage[m + 2] = 'k';
				break;
			case 2:
				mapmessage[m + 2] = 'm';
				break;
			case 3:
				mapmessage[m + 2] = 's';
				break;
			case 4:
				mapmessage[m + 2] = 'a';
				break;
			default:
				break;
			}

			//set 4th bit
			if (mapARRAY[n].equip2 == 0)
				mapmessage[m + 3] = 'x';
			else if (mapARRAY[n].equip2 == 1)
				mapmessage[m + 3] = 'h';

			//set 5th bit
			if (mapARRAY[n].player == 0)
				mapmessage[m + 4] = 'x';
			else
			{
				int2str(mapARRAY[n].player, strbuffer);
				mapmessage[m + 4] = strbuffer[0];
			}

			//shift m
			m = m + 5;
		}//coding end		
	}//for loop end
	mapmessage[m] = '/';
}

void int2str(int i, char* strbuffer)
{
	sprintf_s(strbuffer, sizeof(strbuffer), "%d", i);
}

int str2int(char c)
{
	switch (c)
	{
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	default:
		break;
	}
}


void movefunc()
{
	int moveARRAY[4],n,num1,num2,i,j,loc,max;
	int walknum,maxwalk;
	char* ptr;

	for (n = 0; n < 4; n++)
		moveARRAY[n] = n;

	for (max = 0; max < 4; max++)
	{
		for (n = max; n < 3; n++)//排序，第一個[0]的移動空間最大
		{
			for (i = max; i < 3; i++)
			{
				num1 = moveARRAY[i];
				num2 = moveARRAY[i + 1];
				if (gamerARRAY[num1].walkespace < gamerARRAY[num2].walkespace)
				{
					moveARRAY[i + 1] = num1;
					moveARRAY[i] = num2;
				}
			}
		}

		i = moveARRAY[max];//i 是玩家陣列的陣列位置
		ptr = inst[i + 1];//陣列位置加一即是對應指令
		if (ptr[1] != '4') continue;

		loc = gamerARRAY[i].locat;
		walknum = str2int(ptr[2]);
		maxwalk = 6 - gamerARRAY[i].armor - gamerARRAY[i].weapon;

		if (walknum <= maxwalk)
		{
			for (j = 1; j <= walknum; j++)
			{
				if (mapARRAY[(loc + j)%24].player)
				{
					walknum = j - 1;
					break;
				}
			}
			mapARRAY[loc].player = 0;//remove gamer from the block right now
			gamerARRAY[i].locat = (loc + walknum) % 24;//update the gamer location by new location
			mapARRAY[gamerARRAY[i].locat].player = i + 1;//update map
		}
		spacecal();
	}

}

void takefunc()
{
	char* ptr;
	int n;
	for (n = 1; n < 5; n++)
	{
		ptr=inst[n];
		if (ptr[1] != '3') continue;
		int num = str2int(ptr[0]) - 1; //gamer's number "in array"
		int loc = gamerARRAY[num].locat;//gamer's location
		int stuff = str2int(ptr[2]);//what gamer want to take
		int temp;

		if (stuff == 1)//take eq1
		{
			if (mapARRAY[loc].equip1 == 4)//take armor
			{
				gamerARRAY[num].armor += 1;//gamer get a armor
				mapARRAY[loc].equip1 = 0;//remove armor from map
			}
			else //weapon
			{	//switch gamer's weapon & map's weapon
				temp = gamerARRAY[num].weapon;
				gamerARRAY[num].weapon = mapARRAY[loc].equip1;
				mapARRAY[loc].equip1 = temp;
			}
		}
		else if (stuff == 2 && mapARRAY[loc].equip2)//take eq2
		{
			gamerARRAY[num].heal += 1;//gamer get a heal
			mapARRAY[loc].equip2 = 0;//remove eq2 from map
		}
		gamerARRAY[num].maxwalk = 6 - gamerARRAY[num].armor - gamerARRAY[num].weapon;
	}
	
}

void attackfunc()
{
	char* ptr;
	int n;
	for (n = 1; n < 5; n++)
	{
		ptr = inst[n];
		if (ptr[1] != '1') continue;
		int num = str2int(ptr[0]) - 1; //gamer's number "in array"
		int loc = gamerARRAY[num].locat;//gamer's location
		int weapon = gamerARRAY[num].weapon;
		if (weapon == 0) continue;//if no weapon don't continu

		int range = weapon * 2 - 1;

		int n, i, aim;
		for (n = 1; n <= range; n++)
		{
			aim = (loc + n) % 24;
			if ((aim == 0 || aim == 6 || aim == 12 || aim == 18) && !(mapARRAY[aim].player))
				break; //if range touch the corner
			if (mapARRAY[aim].player  &&  mapARRAY[aim].player != str2int(ptr[0]))
			{	//find the enemy in the range except player
				i = mapARRAY[aim].player - 1;

				if (gamerARRAY[i].armor)//if enemy has armor
					gamerARRAY[i].armor -= 1;
				else
				{
					gamerARRAY[i].blood -= 5;
					if (gamerARRAY[i].blood == 0)
					{
						gamerARRAY[i].alive = 0;
						loc = gamerARRAY[i].locat;
						mapARRAY[loc].player = 0;
					}
				}
				break;
			}
		}
	}
}

void healfunc()
{
	char* ptr;
	int n;
	for (n = 1; n < 5; n++)
	{
		ptr = inst[n];
		if (ptr[1] != '2') continue;
		int num = str2int(ptr[0]) - 1; //gamer's number "in array"
		if (gamerARRAY[num].heal && gamerARRAY[num].blood < 15)
		{	//if gamer has heal && blood is not full
			gamerARRAY[num].heal -= 1;
			gamerARRAY[num].blood += 5;
		}
		else
			continue;
	}
}

void situcode(int n)
{
	char *situ = situmessage1;
	switch (n)
	{
	case 0:
		situ = situmessage1;
		break;
	case 1:
		situ = situmessage2;
		break;
	case 2:
		situ = situmessage3;
		break;
	case 3:
		situ = situmessage4;
		break;
	}

	if (gamerARRAY[n].alive == 0)
	{
		situ[0] = '/';
		return;
	}

	char buffer[10];
	int blood = gamerARRAY[n].blood;
	int heal = gamerARRAY[n].heal;
	int t;
	int o;
	int max, weapon, armor;
		
	//blood : first bit & second bit
	t = blood - (blood % 10);
	o = blood % 10;
	int2str(t, buffer);
	situ[0] = buffer[0];
	int2str(o, buffer);
	situ[1] = buffer[0];

	//movemax : third bit
	gamerARRAY[n].maxwalk = 6 - gamerARRAY[n].armor - gamerARRAY[n].weapon;
	max = gamerARRAY[n].maxwalk;
	int2str(max, buffer);
	situ[2] = buffer[0];

	//weapon : 4th bit
	weapon = gamerARRAY[n].weapon;
	int2str(weapon, buffer);
	situ[3] = buffer[0];

	//armor : 5th bit
	armor = gamerARRAY[n].armor;
	int2str(armor, buffer);
	situ[4] = buffer[0];

	//heal : 6th & 7th bit
	t = heal - (heal % 10);
	o = heal % 10;
	int2str(t, buffer);
	situ[5] = buffer[0];
	int2str(o, buffer);
	situ[6] = buffer[0];
}

void spacecal()
{
	int i,n,loc,aimloc;
	for (i = 0; i < 4; i++)
	{
		loc = gamerARRAY[i].locat;//玩家i所在的位置

		for (n = 1; n < 7; n++)
		{
			aimloc = (loc + n)%24;//目標位置
			if (mapARRAY[aimloc].player || n == 6)
			{//若目標位置有人或達到最大步數
				gamerARRAY[i].walkespace = n - 1;//紀錄玩家i的可走空間
				break;
			}
		}
	}
}

void randmap(int n)
{
	int i, poker[24], temp, pos;
	srand((unsigned)time(NULL));

	for (i = 0; i < 24; ++i)//build
		poker[i] = i;

	for (i = 0; i < 24; ++i) {//random
		pos = 24 * rand() / RAND_MAX;
		temp = poker[i];
		poker[i] = poker[pos];
		poker[pos] = temp;
	}

	for (i = 0; i < 24; i++)//reset 地圖上的裝備
	{
		mapARRAY[i].equip1 = 0;
		mapARRAY[i].equip2 = 0;
	}

	
	for (i = 0; i <= 3; i++)
	{
		if (n == 0)
		{
			mapARRAY[poker[i]].player = i + 1;//put gamer
			gamerARRAY[i].locat = poker[i];
		}
		mapARRAY[poker[i]].equip1 = rand() % 5;
		mapARRAY[poker[i]].equip2 = rand() % 2;
	}
	

	for (i = 4; i < 7; i++)
	{
		mapARRAY[poker[i]].equip1 = (rand() % 4) + 1;
		mapARRAY[poker[i]].equip2 = rand() % 2;
	}
	spacecal();
}