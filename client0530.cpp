#include <cstdlib>
#include <iostream>
#pragma comment(lib,"wsock32.lib")
#include <winsock.h>
#include <conio.h>

using namespace std;

//map information
char health[7] = { " √ƒ•] " };
char knife[7] = { " §p§M " };
char submachine[7] = { "ΩƒæW∫j" };
char sniper[7] = { "™Æ¿ª∫j" };
char armor[7] = { "®æºu¶Á" };
char nothing[7] = { "      " };
char gamer1[7] = { "gamer1" };
char gamer2[7] = { "gamer2" };
char gamer3[7] = { "gamer3" };
char gamer4[7] = { "gamer4" };

//user api
char attack[9] = { "  ß¿ª" };
char dotattack[9] = { "°¥ß¿ª" };
char relive[9] = { "  ¶^¶Â" };
char dotrelive[9] = { "°¥¶^¶Â" };
char take[9] = { "  ¨B®˙" };
char dottake[9] = { "°¥¨B®˙" };
char movestr[9] = { "  ≤æ∞ " };
char dotmove[9] = { "°¥≤æ∞ " };

//take
char take_eq1[] = { "°¥æﬂ∏À≥∆    æﬂ√ƒ•]" };
char take_eq2[] = { "  æﬂ∏À≥∆  °¥æﬂ√ƒ•]" };

//move
char move_0[] = { "°¥0   1   2   3   4   5   6" };
char move_1[] = { "  0 °¥1   2   3   4   5   6" };
char move_2[] = { "  0   1 °¥2   3   4   5   6" };
char move_3[] = { "  0   1   2 °¥3   4   5   6" };
char move_4[] = { "  0   1   2   3 °¥4   5   6" };
char move_5[] = { "  0   1   2   3   4 °¥5   6" };
char move_6[] = { "  0   1   2   3   4   5 °¥6" };
char* moveARRAY[7];

char number[2];

struct map
{
	char *player = nothing;
	char *equip1 = nothing;
	char *equip2 = nothing;
};
map mapARRAY[24];

char* list[4];

struct situation
{
	char* name;
	int blood;
	int heal;
	int maxmove;
	int armor;
	char *weapon;
	int range = 0;
	int alive = 1;
};
situation situ;

int N = 4;

void int2str(int, char*);
int str2int(char);
void resetmap();
void storemap(char mapmess[], char alivemess[]);
void updatesitu(char*);
void printmap();
void printapi(int);
void printwaiting();
void deathapi();
char takeapi();
char moveapi();
void printwin();
void printloss();

int main(int argc, char *argv[])
{
	system("color 0f");
	moveARRAY[0] = move_0; moveARRAY[1] = move_1; moveARRAY[2] = move_2;
	moveARRAY[3] = move_3; moveARRAY[4] = move_4; moveARRAY[5] = move_5; moveARRAY[6] = move_6;
	/**********************************************************/
	int port;
	char ip[20];

	printf("°@°@°@°@°@°@°@¿t°@°@°@°@°@°@°@°@°@°@°@°@°@°@°@¿t°@°@¿t                    ###############\n");
	printf("°@°@°@°@°@°@°@¿t°@°@°@°@°@°@°@°@°@¿t°@°@°@°@°@¿t°@°@¿t                 ######################\n");
	printf("°@°@°@°@°@°@°@¿t°@°@°@°@°@°@°@°@°@°@¿t°@¿t°@°@¿t°@°@¿t°@°@¿t         ##########################\n");
	printf("°@°@°@°@°@°@°@¿t°@°@°@°@°@°@°@°@°@°@¿t°@°@¿t°@¿t°@°@¿t°@¿t¿t        #############################\n");
	printf("°@°@°@°@°@°@°@¿t°@°@°@°@°@  °@°@°@°@°@°@°@¿t°@¿t°@°@¿t¿t          #################################\n");
	printf("¿t¿t¿t¿t¿t¿t¿t¿t¿t¿t¿t¿t¿t¿t¿t°@°@°@°@°@°@°@°@¿t°@°@¿t           #####    ################    #####\n");
	printf("°@°@°@°@°@°@°@¿t°@°@°@°@°@°@°@°@¿t¿t¿t°@°@°@¿t¿t°@°@¿t¿t        ####       ##############       ####\n");
	printf("°@°@°@°@°@°@¿t°@¿t°@°@°@°@°@°@°@°@°@¿t°@°@¿t°@¿t°@°@¿t°@¿t     ####        ##############        ####\n");
	printf("°@°@°@°@°@°@¿t°@¿t°@°@°@°@°@°@°@°@°@¿t°@¿t°@°@¿t°@°@¿t°@¿t       ##       ################       ##\n");
	printf("°@°@°@°@°@°@¿t°@°@¿t°@°@°@°@°@°@°@°@¿t°@°@°@°@¿t°@°@¿t           ###     ###### ##### #####     ###\n");
	printf("°@°@°@°@°@¿t°@°@°@¿t°@°@°@°@°@°@°@°@¿t°@°@°@¿t°@°@°@¿t°@°@¿t      ############  #####  ###########\n");
	printf("°@°@°@°@°@¿t°@°@°@°@¿t°@°@°@°@°@°@°@¿t°@°@¿t°@°@°@°@¿t°@°@¿t        ############################\n");
	printf("°@°@°@°@¿t°@°@°@°@°@°@¿t°@°@°@°@°@°@¿t°@¿t°@°@°@°@°@¿t°@°@¿t         ##########################\n");
	printf("°@°@°@¿t°@°@°@°@°@°@°@°@¿t¿t¿t°@°@¿t°@¿t°@°@°@°@°@°@°@¿t¿t            ###   ####    ####   ###\n");
	printf("°@¿t¿t°@°@°@°@°@°@°@°@°@°@¿t°@°@¿t°@°@°@¿t                            ###   ####    ####   ###\n");
	printf("°@°@°@°@°@°@°@°@°@°@°@°@°@°@°@°@°@°@°@°@°@¿t¿t¿t¿t¿t¿t¿t¿t¿t¿t        ###   ####    ####   ###\n");
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
	printf("  enter ip :");
	scanf_s("%s", ip, 20);
	printf("  enter port :");
	scanf_s("%d", &port);
	
	//init
	WSADATA wsaData = { 0 };
	WORD wVer = MAKEWORD(2, 2);
	WSAStartup(wVer, &wsaData);

	//socket
	SOCKET hServer;
	hServer = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

	//connect
	sockaddr_in saServer;
	saServer.sin_family = AF_INET;
	saServer.sin_port = htons(port);
	saServer.sin_addr.s_addr = inet_addr(ip);
	connect(hServer, (sockaddr*)&saServer, sizeof(sockaddr));
	/**********************************************************/
	
	//send,recv
	char mapmessage[200];
	char instruction[10];
	char stiumessage[10];//blood2 max1 weapon1 armor1 heal2
	char buffer[2];
	char alivemess[5];
	list[0] = gamer1;
	list[1] = gamer2;
	list[2] = gamer3;
	list[3] = gamer4;

	int i,n;
	int k = 1;
	int victory = 0;
	recv(hServer, number, sizeof(number), 0);
	n = str2int(number[0]);
	switch (n)
	{
	case 1:
		situ.name = gamer1;
		break;
	case 2:
		situ.name = gamer2;
		break;
	case 3:
		situ.name = gamer3;
		break;
	case 4:
		situ.name = gamer4;
		break;
	default:
		break;
	}
	while (1)//gaming
	{
		N -= 1;
		if (N == 0) N = 3;
		recv(hServer, mapmessage, sizeof(mapmessage), 0);//recv mapmessage from server
		recv(hServer, stiumessage, sizeof(stiumessage), 0);
		recv(hServer, alivemess, sizeof(alivemess), 0);
		if (stiumessage[0] == 'v')
		{
			victory = 1;
			break;
		}
		else if (stiumessage[0] == 'l')
			break;

		//print map & user api
		resetmap();
		updatesitu(stiumessage);
		storemap(mapmessage, alivemess);
		system("CLS");
		printmap();
		if (situ.alive == 1)
		{
			printapi(k);
			while (1)//userapi catch 'up'  'down'  'left'  'right' 'enter' key
			{
				i = _getch();
				if (i == 224)//user press direction key
				{
					i = _getch();
					switch (i) {
					case 72://up key
					case 80://down key
						if (k == 1)
							k = 3;
						else if (k == 2)
							k = 4;
						else if (k == 3)
							k = 1;
						else if (k == 4)
							k = 2;
						break;
					case 75://left key
					case 77://right key
						if (k == 1)
							k = 2;
						else if (k == 2)
							k = 1;
						else if (k == 3)
							k = 4;
						else if (k == 4)
							k = 3;
						break;
					default:break;
					}//switch end
					system("CLS");
					printmap();
					printapi(k);
				}
				else if (i == 13)//user press 'enter'
					break;
			}//catch key end

			//code instruction to server
			char c;
			instruction[0] = number[0];
			switch (k)
			{
			case 1://attack
				instruction[1] = '1';
				instruction[2] = '/';
				break;
			case 2://heal
				instruction[1] = '2';
				instruction[2] = '/';
				break;
			case 3://take
				instruction[1] = '3';
				c = takeapi();
				instruction[2] = c;
				instruction[3] = '/';
				break;
			case 4://move
				instruction[1] = '4';
				c = moveapi();
				instruction[2] = c;
				instruction[3] = '/';
				break;
			default:
				break;
			}//coding end

			system("CLS");
			printmap();
			printwaiting();

			send(hServer, instruction, sizeof(instruction), 0);//send instruction to server
		}
		else if (situ.alive == 0)
		{
			deathapi();
			instruction[1] = '/';
			send(hServer, instruction, sizeof(instruction), 0);
		}
	}

	if (victory == 1)
		printwin();
	else if (victory == 0)
		printloss();

	//close
	closesocket(hServer);
	WSACleanup();

	_getch();
	return EXIT_SUCCESS;
}//end main

/*
code:
	ÆÊº∆ ∏À≥∆1 ∏À≥∆2 ™±Æa
	k = §p§M, m = ΩƒæW∫j, s = ™Æ¿ª∫j, a = ®æºu¶Á
*/

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

void updatesitu(char* mess)//blood,01 max,2 weapon,3 armor,4 heal,56
{
	if (mess[0] == '/')
	{
		situ.alive = 0;
		return;
	}
	int t, o;
	t = str2int(mess[0]);
	o = str2int(mess[1]);
	situ.blood = 10 * t + o;
	situ.maxmove = str2int(mess[2]);
	switch (mess[3])
	{
	case '0':
		situ.weapon = nothing;
		situ.range = 0;
		break;
	case '1':
		situ.weapon = knife;
		situ.range = 1;
		break;
	case '2':
		situ.weapon = submachine;
		situ.range = 2;
		break;
	case '3':
		situ.weapon = sniper;
		situ.range = 3;
		break;
	default:
		break;
	}
	situ.armor = str2int(mess[4]);
	t = str2int(mess[5]);
	o = str2int(mess[6]);
	situ.heal = 10 * t + o;
}

void resetmap()
{
	int n;
	for (n = 0; n < 24; n++)
	{
		mapARRAY[n].equip1 = nothing;
		mapARRAY[n].equip2 = nothing;
		mapARRAY[n].player = nothing;
	}
	return;
}

void storemap(char mapmess[], char alivemess[]) //store map from 'mapmessage'
{
	int n, m;
	int tendigit, onedigit, block;

	for (n = 0; mapmess[n] != '/'; n = n + 5)//beging to decode
	{
		switch (mapmess[n])//first bit
		{
		case '0':
			tendigit = 0;
			break;
		case '1':
			tendigit = 1;
			break;
		case '2':
			tendigit = 2;
			break;
		case '3':
			tendigit = 3;
			break;
		case '4':
			tendigit = 4;
			break;
		case '5':
			tendigit = 5;
			break;
		case '6':
			tendigit = 6;
			break;
		case '7':
			tendigit = 7;
			break;
		case '8':
			tendigit = 8;
			break;
		case '9':
			tendigit = 9;
			break;
		}//end

		switch (mapmess[n + 1])//second bit
		{
		case '0':
			onedigit = 0;
			break;
		case '1':
			onedigit = 1;
			break;
		case '2':
			onedigit = 2;
			break;
		case '3':
			onedigit = 3;
			break;
		case '4':
			onedigit = 4;
			break;
		case '5':
			onedigit = 5;
			break;
		case '6':
			onedigit = 6;
			break;
		case '7':
			onedigit = 7;
			break;
		case '8':
			onedigit = 8;
			break;
		case '9':
			onedigit = 9;
			break;
		}//end

		block = tendigit * 10 + onedigit; //determine which block on map should be updated

		switch (mapmess[n + 2])//third bit
		{
		case 'x': //"µL"
			mapARRAY[block].equip1 = nothing;
			break;
		case 'k': // "§p§M "
			mapARRAY[block].equip1 = knife;
			break;
		case 'm': // "ΩƒæW∫j "
			mapARRAY[block].equip1 = submachine;
			break;
		case 's': // "™Æ¿ª∫j "
			mapARRAY[block].equip1 = sniper;
			break;
		case 'a': //"®æºu¶Á"
			mapARRAY[block].equip1 = armor;
			break;

		}//end

		switch (mapmess[n + 3])//4th bit
		{
		case 'x': //"µL"
			mapARRAY[block].equip2 = nothing;
			break;
		case 'h': // "§p§M "
			mapARRAY[block].equip2 = health;
			break;
		}//end

		switch (mapmess[n + 4])//5th bit
		{
		case 'x':
			mapARRAY[block].player = nothing;
			break;
		case '1': // "gamer1 "
			mapARRAY[block].player = gamer1;
			break;
		case '2': // "gamer2 "
			mapARRAY[block].player = gamer2;
			break;
		case '3': // "gamer3 "
			mapARRAY[block].player = gamer3;
			break;
		case '4': //"gamer4"
			mapARRAY[block].player = gamer4;
			break;

		}//end

	}
	for (n = 0; n < 5; n++)
	{
		if (alivemess[n] == '0')
			list[n] = nothing;
	}
}

void printmap()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printf(" +--------+  +--------+  +--------+  +--------+  +--------+  +--------+  +--------+ ""\n");
	printf(" | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s| \n"
		, mapARRAY[0].equip1, mapARRAY[1].equip1, mapARRAY[2].equip1, mapARRAY[3].equip1, mapARRAY[4].equip1, mapARRAY[5].equip1, mapARRAY[6].equip1);
	printf(" | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s| \n"
		, mapARRAY[0].equip2, mapARRAY[1].equip2, mapARRAY[2].equip2, mapARRAY[3].equip2, mapARRAY[4].equip2, mapARRAY[5].equip2, mapARRAY[6].equip2);
	printf(" | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s| \n"
		, mapARRAY[0].player, mapARRAY[1].player, mapARRAY[2].player, mapARRAY[3].player, mapARRAY[4].player, mapARRAY[5].player, mapARRAY[6].player);
	printf(" +--------+  +--------+  +--------+  +--------+  +--------+  +--------+  +--------+ ""\n");
	printf("\n");

	printf(" +--------+                                                              +--------+ ""\n");
	printf(" | %-7s| °∂                    ¶aπœ≠´∏m≠Àº∆ : %d                    °ø | %-7s| \n", mapARRAY[23].equip1, N, mapARRAY[7].equip1);
	printf(" | %-7s| °∂                                                        °ø | %-7s| \n", mapARRAY[23].equip2, mapARRAY[7].equip2);
	printf(" | %-7s| °∂                        ¶s¨°¶W≥Ê                        °ø | %-7s| \n", mapARRAY[23].player, mapARRAY[7].player);
	printf(" +--------+                                                              +--------+ ""\n");
	printf("\n");

	printf(" +--------+                                                              +--------+ ""\n");
	printf(" | %-7s| °∂                         %-7s                        °ø | %-7s| \n", mapARRAY[22].equip1, list[0], mapARRAY[8].equip1);
	printf(" | %-7s| °∂                                                        °ø | %-7s| \n", mapARRAY[22].equip2, mapARRAY[8].equip2);
	printf(" | %-7s| °∂                                                        °ø | %-7s| \n", mapARRAY[22].player, mapARRAY[8].player);
	printf(" +--------+                                                              +--------+ ""\n");
	printf("\n");

	printf(" +--------+                                                              +--------+ ""\n");
	printf(" | %-7s| °∂                         %-7s                        °ø | %-7s| \n", mapARRAY[21].equip1, list[1], mapARRAY[9].equip1);
	printf(" | %-7s| °∂                                                        °ø | %-7s| \n", mapARRAY[21].equip2, mapARRAY[9].equip2);
	printf(" | %-7s| °∂                                                        °ø | %-7s| \n", mapARRAY[21].player, mapARRAY[9].player);
	printf(" +--------+                                                              +--------+ ""\n");
	printf("\n");

	printf(" +--------+                                                              +--------+ ""\n");
	printf(" | %-7s| °∂                         %-7s                        °ø | %-7s| \n", mapARRAY[20].equip1, list[2], mapARRAY[10].equip1);
	printf(" | %-7s| °∂                                                        °ø | %-7s| \n", mapARRAY[20].equip2, mapARRAY[10].equip2);
	printf(" | %-7s| °∂                                                        °ø | %-7s| \n", mapARRAY[20].player, mapARRAY[10].player);
	printf(" +--------+                                                              +--------+ ""\n");
	printf("\n");

	printf(" +--------+                                                              +--------+ ""\n");
	printf(" | %-7s| °∂                         %-7s                        °ø | %-7s| \n", mapARRAY[19].equip1, list[3], mapARRAY[11].equip1);
	printf(" | %-7s| °∂                                                        °ø | %-7s| \n", mapARRAY[19].equip2, mapARRAY[11].equip2);
	printf(" | %-7s| °∂                                                        °ø | %-7s| \n", mapARRAY[19].player, mapARRAY[11].player);
	printf(" +--------+                                                              +--------+ ""\n");
	printf("\n");

	printf(" +--------+  +--------+  +--------+  +--------+  +--------+  +--------+  +--------+ ""\n");
	printf(" | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s| \n"
		, mapARRAY[18].equip1, mapARRAY[17].equip1, mapARRAY[16].equip1, mapARRAY[15].equip1, mapARRAY[14].equip1, mapARRAY[13].equip1, mapARRAY[12].equip1);
	printf(" | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s| \n"
		, mapARRAY[18].equip2, mapARRAY[17].equip2, mapARRAY[16].equip2, mapARRAY[15].equip2, mapARRAY[14].equip2, mapARRAY[13].equip2, mapARRAY[12].equip2);
	printf(" | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s|  | %-7s| \n"
		, mapARRAY[18].player, mapARRAY[17].player, mapARRAY[16].player, mapARRAY[15].player, mapARRAY[14].player, mapARRAY[13].player, mapARRAY[12].player);
	printf(" +--------+  +--------+  +--------+  +--------+  +--------+  +--------+  +--------+ ""\n");
	printf("\n");
	SetConsoleTextAttribute(h, wOldColorAttrs);
}

void printapi(int k)
{
	char* a = attack;
	char* r = relive;
	char* m = movestr;
	char* t = take;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	switch (k)
	{
	case 1:
		a = dotattack;
		break;
	case 2:
		r = dotrelive;
		break;
	case 3:
		t = dottake;
		break;
	case 4:
		m = dotmove;
		break;
	default:
		break;
	}
	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("+---------------------------------++--------------------------------+\n");
	printf("| ¶Ê∞  :			  || ™¨∫A :	%-7s	            |\n",situ.name);
	printf("|	%-9s      %-9s  ||	¶Â∂q:%-2d		√ƒ•]:%-2d     |\n", a, r, situ.blood, situ.heal);
	printf("|				  ||	≥Ã§j®Bº∆:%-2d	®æºu¶Á:%-2d   |\n", situ.maxmove, situ.armor);
	printf("|	%-9s      %-9s  ||	™Zæπ:%-7s(%d)             |\n", t, m, situ.weapon, situ.range);
	printf("+---------------------------------++--------------------------------+\n");
	SetConsoleTextAttribute(h, wOldColorAttrs);
	return;
}

void printwaiting()
{

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("+---------------------------------++--------------------------------+\n");
	printf("|                                 || ™¨∫A :	%-7s             |\n",situ.name);
	printf("|	  Waiating.....           ||	¶Â∂q:%-2d		√ƒ•]:%-2d     |\n", situ.blood, situ.heal);
	printf("|	                          ||	≥Ã§j®Bº∆:%-2d	®æºu¶Á:%-2d   |\n", situ.maxmove, situ.armor);
	printf("|	                          ||	™Zæπ:%-7s(%d)             |\n", situ.weapon, situ.range);
	printf("+---------------------------------++--------------------------------+\n");
	SetConsoleTextAttribute(h, wOldColorAttrs);
}

char takeapi()
{
	char* str = take_eq1;
	int i;
	int k = 1;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	system("CLS");
	printmap();
	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("+---------------------------------++--------------------------------+\n");
	printf("| ¨B®˙ :	 		  || ™¨∫A :	%-7s             |\n",situ.name);
	printf("|	%s        ||	¶Â∂q:%-2d		√ƒ•]:%-2d     |\n", str, situ.blood, situ.heal);
	printf("|				  ||	≥Ã§j®Bº∆:%-2d	®æºu¶Á:%-2d   |\n", situ.maxmove, situ.armor);
	printf("|				  ||	™Zæπ:%-7s(%d)             |\n", situ.weapon, situ.range);
	printf("+---------------------------------++--------------------------------+\n");
	SetConsoleTextAttribute(h, wOldColorAttrs);
	while (1)
	{
		i = _getch();
		if (i == 224)//user press direction key
		{
			i = _getch();
			switch (i) {
			case 75://left key
			case 77://right key
				if (k == 1)
				{
					k = 2;
					str = take_eq2;
				}
				else if (k == 2)
				{
					k = 1;
					str = take_eq1;
				}
				break;
			default:break;
			}//switch end
			system("CLS");
			printmap();
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			printf("+---------------------------------++--------------------------------+\n");
			printf("| ¨B®˙ :	 		  || ™¨∫A :	%-7s             |\n",situ.name);
			printf("|	%s        ||	¶Â∂q:%-2d		√ƒ•]:%-2d     |\n", str, situ.blood, situ.heal);
			printf("|				  ||	≥Ã§j®Bº∆:%-2d	®æºu¶Á:%-2d   |\n", situ.maxmove, situ.armor);
			printf("|				  ||	™Zæπ:%-7s(%d)             |\n", situ.weapon, situ.range);
			printf("+---------------------------------++--------------------------------+\n");
			SetConsoleTextAttribute(h, wOldColorAttrs);
		}
		else if (i == 13)
			break;
	}
	if (k == 1)
		return '1';
	else if (k == 2)
		return '2';
}

char moveapi()
{
	char* str = move_0;
	char buffer[10];
	int i;
	int k = 0;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	system("CLS");
	printmap();
	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("+---------------------------------++--------------------------------+\n");
	printf("| ≤æ∞  :			  || ™¨∫A :	%-7s             |\n",situ.name);
	printf("|   %s   ||	¶Â∂q:%-2d		√ƒ•]:%-2d     |\n", str, situ.blood, situ.heal);
	printf("|				  ||	≥Ã§j®Bº∆:%-2d	®æºu¶Á:%-2d   |\n", situ.maxmove, situ.armor);
	printf("|				  ||	™Zæπ:%-7s(%d)             |\n", situ.weapon, situ.range);
	printf("+---------------------------------++--------------------------------+\n");
	SetConsoleTextAttribute(h, wOldColorAttrs);
	while (1)
	{
		i = _getch();
		if (i == 224)//user press direction key
		{
			i = _getch();
			switch (i) {
			case 75://left key
				if (k == 0)
				{
					k = 6;
					str = moveARRAY[6];
				}
				else
				{
					k -= 1;
					str = moveARRAY[k];
				}
				break;
			case 77://right key
				if (k == 6)
				{
					k = 0;
					str = moveARRAY[k];
				}
				else
				{
					k += 1;
					str = moveARRAY[k];
				}
				break;
			default:break;
			}//switch end
			system("CLS");
			printmap();
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			printf("+---------------------------------++--------------------------------+\n");
			printf("| ≤æ∞  :			  || ™¨∫A :	%-7s             |\n",situ.name);
			printf("|   %s   ||	¶Â∂q:%-2d		√ƒ•]:%-2d     |\n", str, situ.blood, situ.heal);
			printf("|				  ||	≥Ã§j®Bº∆:%-2d	®æºu¶Á:%-2d   |\n", situ.maxmove, situ.armor);
			printf("|				  ||	™Zæπ:%-7s(%d)             |\n", situ.weapon, situ.range);
			printf("+---------------------------------++--------------------------------+\n");
			SetConsoleTextAttribute(h, wOldColorAttrs);
		}
		else if (i == 13)
			break;
	}
	int2str(k, buffer);
	return buffer[0];
}

void deathapi()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("+---------------------------------++\n");
	printf("|	         Death            ||\n");
	printf("+---------------------------------++\n");
	SetConsoleTextAttribute(h, wOldColorAttrs);
}

void printwin()
{
	system("CLS");
	printf("\n");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("     #######              #######             ##########      #####        ####	\n");
	printf("      ######             # ######            #   #####       #### #       ####	\n");
	printf("       ######           #   ######          #    #####      ####  #      ####	\n");
	printf("        ######         #     ######        #     #####     ####   #     ####		\n");
	printf("         ######       #       ######      #      #####    ####    #    ####		\n");
	printf("          ######     #         ######    #       #####   ####     #   ####		\n");
	printf("           ######   #           ######  #        #####  ####      #  ####		\n");
	printf("            ###### #             #######         ##### ####       # ####			\n");
	printf("            ########              #####     ##############        #####			\n");
	printf("\n");
	SetConsoleTextAttribute(h, wOldColorAttrs);
}

void printloss()
{
	system("CLS");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("\n");
	printf("       ###############################  		\n");
	printf("           #####          ####                  \n");
	printf("          #####           ####                  \n");
	printf("         ################ ####                  \n");
	printf("       #####         ###  ############          \n");
	printf("      ##  ##        ###   ####                  \n");
	printf("     #     ##     ###     ####                  \n");
	printf("             ##  ###      ####   #              \n");
	printf("              ###         ####    ##            \n");
	printf("            ###           ####     ####         \n");
	printf("           ##             ##############        \n");
	printf("         #                ###############       \n");
	printf("       #									    \n");
	printf("\n");
	SetConsoleTextAttribute(h, wOldColorAttrs);
}
