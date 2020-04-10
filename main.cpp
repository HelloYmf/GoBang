#include<graphics.h>
#include <conio.h>
#include<stdio.h>
#include <Mmsystem.h>
#pragma comment(lib,"Winmm.lib")

typedef struct position {								//坐标结构
	int x;
	int y;
}Position;

/********************************全局变量**********************************/

Position cursor;										//光标坐标
Position c_chess;										//人机模式棋子初始位置
COLORREF bkcolor;										//棋盘背景颜色
COLORREF color[2] = { WHITE , RGB(1,1,1) };				//定义两种颜色（白0黑1）
int turn;												//黑0白1（双人模式）
int mode;												//标志模式
int c_turn;												//人机模式回合
int number;												//保存总棋子数
char up1[100] = "未设置";								//玩家一昵称
char up2[100] = "未设置";								//玩家二昵称
int score[19][19] = { 0 };								//用于计算人机坐标得分

/**************************函数声明*******************************************/

void view();											//开始菜单
void initgame();										//初始化游戏数据
void begingame();										//开始游戏
void playgame();										//玩游戏的全部细节
void closegame(int flag,int turn,int mode);				//释放资源
void drawcursor(COLORREF color, Position cursor);		//绘制光标
void drawchess(int* turn, int mode);					//绘制棋子
void drawturn(int turn);								//绘制执子方
void getmax(Position* c_chess);							//获取电脑最有利坐标
void c_downchess();										//计算人机坐标
int iswinnew(int turn, int mode);						//判断输赢

/*************************************函数定义*************************************/

int main()
{
	initgame();
	view();
	return 0;
}

void view()
{
/*********************************初始化背景********************************************/
	initgraph(750, 570);
	setbkmode(TRANSPARENT);
A:	//用于返回主菜单
	IMAGE setting;
	loadimage(&setting, "主菜单背景.jpg", 750, 570);						//主菜单背景图片
	putimage(0, 0, &setting);

/***********************主界面选择图标***********************************************/

	settextcolor(RGB(0, 0, 195));								
	settextstyle(25, 0, _T("楷体"));									

	setlinecolor(RGB(240, 128, 128));
	rectangle(230, 250, 500, 290);
	outtextxy(320, 260, "开始游戏");

	setlinecolor(RGB(50, 205, 50));
	rectangle(230, 330, 500, 370);
	outtextxy(320, 340, "游戏规则");

	setlinecolor(RGB(244, 164, 96));
	rectangle(230, 410, 500, 450);
	outtextxy(320, 420, "作者信息");

	setlinecolor(RGB(169, 169, 169));
	rectangle(230, 490, 500, 530);
	outtextxy(320, 500, "退出游戏");
	
/*********************************初始化小手位置******************************************/

	Position hand = { 420,269 };										//初始化小手坐标
	IMAGE temp;				//保存小手重绘前的背景块
	getimage(&temp, hand.x, hand.y, hand.x + 30, hand.y + 30);
	IMAGE hand_a, hand_b;
	loadimage(&hand_a, "40hand_b.jpg");
	loadimage(&hand_b, "40hand_a.jpg");
	putimage(hand.x, hand.y, &hand_a, NOTSRCERASE);
	putimage(hand.x, hand.y, &hand_b, SRCINVERT);

/***************************死循环监听键盘消息********************************/

	while (1)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 72:
			{
				if (hand.y > 269)
				{
					putimage(hand.x, hand.y, &temp);
					getimage(&temp, hand.x, hand.y - 80, hand.x + 30, hand.y - 110);
					putimage(hand.x, hand.y - 80, &hand_a, NOTSRCERASE);
					putimage(hand.x, hand.y - 80, &hand_b, SRCINVERT);
					PlaySound(TEXT("选择.wav"), 0, SND_FILENAME | SND_ASYNC);
					hand.y -= 80;
				}
				break;
			}
			case 80:
			{
				if (hand.y < 509)
				{
					putimage(hand.x,hand.y,&temp);
					getimage(&temp, hand.x, hand.y + 80, hand.x + 30, hand.y + 110);
					putimage(hand.x, hand.y+80, &hand_a, NOTSRCERASE);
					putimage(hand.x, hand.y+80, &hand_b, SRCINVERT);
					PlaySound(TEXT("选择.wav"), 0, SND_FILENAME | SND_ASYNC);
					hand.y += 80;
				}
				break;
			}
			case 13:
			{
				switch (hand.y)
				{
				case 269:
				{
				B:
					cleardevice();
					IMAGE setting;
					loadimage(&setting, "设置背景.jpg", 750, 570);
					putimage(0, 0, &setting);
					settextcolor(RGB(255, 69, 0));
					settextstyle(40, 0, _T("黑体"));
					outtextxy(180, 40, "模式设置(Mode Setting)");
					settextstyle(30, 0, _T("楷体"));
					settextcolor(RGB(0, 0, 195));
					outtextxy(100, 160, "双人对战");
					outtextxy(100, 220, "人机对战");
					outtextxy(100, 280, "返回菜单");
					hand = { 220,175 };
					getimage(&temp, hand.x, hand.y, hand.x + 30, hand.y + 30);
					putimage(hand.x, hand.y, &hand_a, NOTSRCERASE);
					putimage(hand.x, hand.y, &hand_b, SRCINVERT);
					while (1)
					{
						if (_kbhit())
						{
							switch (_getch())
							{
							case 72:
							{
								if (hand.y > 175)
								{
									putimage(hand.x, hand.y, &temp);
									getimage(&temp, hand.x, hand.y - 60, hand.x + 30, hand.y - 90);
									putimage(hand.x, hand.y - 60, &hand_a, NOTSRCERASE);
									putimage(hand.x, hand.y - 60, &hand_b, SRCINVERT);
									PlaySound(TEXT("选择.wav"), 0, SND_FILENAME | SND_ASYNC);
									hand.y -= 60;
								}
								break;
							}
							case 80:
							{
								if (hand.y < 295)
								{
									putimage(hand.x, hand.y, &temp);
									getimage(&temp, hand.x, hand.y + 60, hand.x + 30, hand.y + 90);
									putimage(hand.x, hand.y + 60, &hand_a, NOTSRCERASE);
									putimage(hand.x, hand.y + 60, &hand_b, SRCINVERT);
									PlaySound(TEXT("选择.wav"), 0, SND_FILENAME | SND_ASYNC);
									hand.y += 60;
								}
								break;
							}
							case 13:
							{
								switch (hand.y)
								{
								case 175:
								{
								C:
									mode = 0;
									putimage(0, 0, &setting);
									settextcolor(RGB(255, 69, 0));
									settextstyle(40, 0, _T("黑体"));
									outtextxy(180, 40, "昵称设置(Name Setting)");
									settextcolor(RGB(0, 0, 205));
									settextstyle(30, 0, _T("楷体"));
									outtextxy(100, 160, "黑棋手");
									outtextxy(100, 220, "白棋手");
									outtextxy(100, 280, "完 成");
									outtextxy(100, 340, "返 回");
									hand = { 190,170 };
									getimage(&temp, hand.x, hand.y, hand.x + 30, hand.y + 30);
									putimage(hand.x, hand.y, &hand_a, NOTSRCERASE);
									putimage(hand.x, hand.y, &hand_b, SRCINVERT);
									while (1)
									{
										if (_kbhit())
										{
											switch (_getch())
											{
											case 72:
											{
												if (hand.y > 170)
												{
													putimage(hand.x, hand.y, &temp);
													getimage(&temp, hand.x, hand.y - 60, hand.x + 30, hand.y - 90);
													putimage(hand.x, hand.y - 60, &hand_a, NOTSRCERASE);
													putimage(hand.x, hand.y - 60, &hand_b, SRCINVERT);
													PlaySound(TEXT("选择.wav"), 0, SND_FILENAME | SND_ASYNC);
													hand.y -= 60;
												}
												break;
											}
											case 80:
											{
												if (hand.y < 350)
												{
													putimage(hand.x, hand.y, &temp);
													getimage(&temp, hand.x, hand.y + 60, hand.x + 30, hand.y + 90);
													putimage(hand.x, hand.y + 60, &hand_a, NOTSRCERASE);
													putimage(hand.x, hand.y + 60, &hand_b, SRCINVERT);
													PlaySound(TEXT("选择.wav"), 0, SND_FILENAME | SND_ASYNC);
													hand.y += 60;
												}
												break;
											}
											case 13:
											{
												switch (hand.y)
												{
												case 170:
												{
													InputBox(up1, 10, "请输入黑棋的昵称：");
													break;
												}
												case 230:
												{
													InputBox(up2, 10, "请输入白棋的昵称：");
													break;
												}
												case 290:
												{
													//入口
													putimage(0, 0, &setting);
													settextcolor(RGB(255, 69, 0));
													settextstyle(40, 0, _T("黑体"));
													outtextxy(180, 40, "先手设置(First Turn)");
													settextcolor(RGB(0, 0, 205));
													settextstyle(30, 0, _T("楷体"));
													outtextxy(100, 160, "黑棋");
													outtextxy(100, 220, "白棋");
													outtextxy(100, 280, "返回");
													hand = { 160,170 };
													getimage(&temp, hand.x, hand.y, hand.x + 30, hand.y + 30);
													putimage(hand.x, hand.y, &hand_a, NOTSRCERASE);
													putimage(hand.x, hand.y, &hand_b, SRCINVERT);
													while (1)
													{
														if (_kbhit())
														{
															switch (_getch())
															{
															case 72:
															{
																if (hand.y > 170)
																{
																	putimage(hand.x, hand.y, &temp);
																	getimage(&temp, hand.x, hand.y - 60, hand.x + 30, hand.y - 90);
																	putimage(hand.x, hand.y - 60, &hand_a, NOTSRCERASE);
																	putimage(hand.x, hand.y - 60, &hand_b, SRCINVERT);
																	PlaySound(TEXT("选择.wav"), 0, SND_FILENAME | SND_ASYNC);
																	hand.y -= 60;
																}
																break;
															}
															case 80:
															{
																if (hand.y < 290)
																{
																	putimage(hand.x, hand.y, &temp);
																	getimage(&temp, hand.x, hand.y + 60, hand.x + 30, hand.y + 90);
																	putimage(hand.x, hand.y + 60, &hand_a, NOTSRCERASE);
																	putimage(hand.x, hand.y + 60, &hand_b, SRCINVERT);
																	PlaySound(TEXT("选择.wav"), 0, SND_FILENAME | SND_ASYNC);
																	hand.y += 60;
																}
																break;
															}
															case 13:
															{
																switch (hand.y)
																{
																case 170:
																{
																	turn = 0;
																	begingame();
																	playgame();
																}
																case 230:
																{
																	turn = 1;
																	begingame();
																	playgame();
																}
																case 290:
																{
																	goto C;
																}
																}
															}
															}
														}
													}
													
													break;
												}
												case 350:
												{
													goto B;
												}
												}
											}
											}
										}
									}
									break;
								}
								case 235:
								{
									mode = 1;
									begingame();
									playgame();
									_getch();
									break;
								}
								case 295:
								{
									goto A;
								}
								}
							}
							}
						}
					}
				}
				case 349:
				{
					IMAGE care;
					loadimage(&care, "游戏说明new.jpg", 750, 570);
					putimage(0, 0, &care);
					settextcolor(RGB(0, 255, 255));
					settextstyle(30, 0, _T("仿宋"));
					outtextxy(20, 20, "游戏规则:");
					settextcolor(RGB(148, 0, 211));
					settextstyle(30, 0, _T("楷体"));
					outtextxy(20, 60, "1.对局双方各执一色棋子。");
					outtextxy(20, 95, "2.空棋盘开局。");
					outtextxy(20, 130, "3.交替下子，每次只能下一子。");
					outtextxy(20, 165, "4.棋子下在棋盘的空白点上，棋子下定后，不得向其它");
					outtextxy(50, 200, "点移动，不得从棋盘上拿或拿起另落别处。");
					outtextxy(20, 235, "5.黑方的第一枚棋子可下在棋盘任意交叉点上。");
					outtextxy(20, 270, "6.当有一方先在行、列、或者斜线上连续下出连续5个");
					outtextxy(50, 305, "棋子可以判定为胜局。");
					settextcolor(RGB(0, 255, 255));
					settextstyle(30, 0, _T("仿宋"));
					outtextxy(20, 360, "按键说明：");
					settextcolor(RGB(148, 0, 211));
					settextstyle(30, 0, _T("楷体"));
					outtextxy(20, 405, "UP1：上W 下S 左A 右D   落子：空格");
					outtextxy(20, 440, "UP2：小键盘方向键      落子：回车");
					outtextxy(20, 475, "ESC键返回主菜单");
					settextcolor(RGB(0, 255, 255));
					settextstyle(20, 0, _T("仿宋"));
					outtextxy(150, 520, "请按任意键返回！！！");
					_getch();
					goto A;
					break;
				}
				case 429:
				{
					mciSendString(TEXT("open 作者.mp3 alias music"), 0, 0, 0);
					mciSendString(_T("play music repeat"), NULL, 0, NULL);
					IMAGE author;
					loadimage(&author, "作者信息.jpg", 750, 570);
					putimage(0, 0, &author);
					IMAGE vx;
					loadimage(&vx, "微信二维码.jpg", 100, 100);
					putimage(220, 260, &vx);
					IMAGE qq;
					loadimage(&qq, "QQ二维码.jpg", 100, 100);
					putimage(380, 260, &qq);
					settextcolor(RGB(64, 224, 208));
					settextstyle(20, 0, _T("黑体"));
					outtextxy(220, 80, "苑明飞，沈阳工业大学大一学生");
					settextcolor(WHITE);
					settextstyle(30, 0, _T("楷体"));
					outtextxy(220, 140, "热爱大海与冷笑话");
					settextcolor(RGB(238, 130, 238));
					settextstyle(25, 0, _T("隶书"));
					outtextxy(230, 440, "胆小怕生，不易相处");
					outtextxy(230, 500, "年轻无为，卖马为生");
					settextcolor(WHITE);
					settextstyle(30, 0, _T("黑体"));
					_getch();
					mciSendString(_T("close music"), NULL, 0, NULL);
					goto A;
					break;
				}
				case 509:
				{
					closegraph();
					exit(0);
				}
				}
				break;
			}
			}
		}
	}

	_getch();
}

/************************************初始化函数********************************************************/

void initgame()
{
	//初始化执子方
	turn = 0;
	c_turn = 0;
	//初始化背景颜色
	bkcolor = RGB(218, 165, 33);
	//光标坐标
	cursor.x = 270;
	cursor.y = 270;
	//人机坐标
	c_chess.x = 30;
	c_chess.y = 30;
	//初始化总棋子数
	number = 0;
}

/******************************************做一些基础绘制*******************************************************/

void begingame()
{
	if (mode == 0)
	{
		mciSendString(TEXT("open bgm.mp3 alias music"), 0, 0, 0);
		mciSendString(_T("play music repeat"), NULL, 0, NULL);
	}
	else
	{
		mciSendString(TEXT("open 人机bgm.mp3 alias music"), 0, 0, 0);
		mciSendString(_T("play music repeat"), NULL, 0, NULL);
	}
	//绘制边框
	initgraph(750, 570);
	setbkmode(TRANSPARENT);
	setbkcolor(bkcolor);
	cleardevice();
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);
	for (int i = 30; i <= 540; i += 30)
	{
		line(30, i, 540, i);
		line(i, 30, i, 540);
	}
	IMAGE right;
	loadimage(&right, "侧图.jpg", 180, 570);
	putimage(570, 0, &right);
	//绘制当前执子方
	if (mode == 0)
	{
		drawturn(turn);
	}
	//绘制光标
	drawcursor(RED, cursor);
	//绘制昵称
	if (mode == 0)
	{
		settextcolor(BLACK);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(600, 200, "黑棋：");
		settextstyle(17, 0, _T("楷体"));
		settextcolor(RGB(148, 0, 230));
		outtextxy(600, 240, up1);
		settextcolor(BLACK);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(600, 280, "白棋：");
		settextstyle(17, 0, _T("楷体"));
		settextcolor(RGB(0, 230, 210));
		outtextxy(600, 320, up2);
	}
	//绘制模式
	settextcolor(RGB(240, 128, 128));
	settextstyle(30, 0, _T("楷体"));
	if (mode == 0)
	{
		outtextxy(600, 400, "双人模式");
	}
	else
	{
		outtextxy(600, 100, "人机模式");
		settextcolor(BLACK);
		settextstyle(20, 0, _T("楷体"));
		outtextxy(600, 200, "玩家：黑棋");
		outtextxy(600, 230, "电脑：白棋");
	}
}

/*************************************游戏核心部分*************************************************/

void playgame()
{
	while (1)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 72:	case 'W':	//上
			{
				if (cursor.y > 30)
				{
					drawcursor(bkcolor, cursor);
					cursor.y -= 30;
					drawcursor(RED, cursor);
				}
				setlinecolor(BLACK);
				setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 1);
				if (cursor.y != 510)
				{
					line(cursor.x, cursor.y + 44, cursor.x, cursor.y + 46);
				}
				if (cursor.x != 30)
				{
					line(cursor.x - 16, cursor.y + 30, cursor.x - 14, cursor.y + 30);
				}
				if (cursor.x != 540)
				{
					line(cursor.x + 14, cursor.y + 30, cursor.x + 16, cursor.y + 30);
				}
				
				break;
			}
			case 80:	case 'S':	//下
			{
				if (cursor.y < 540)
				{
					drawcursor(bkcolor, cursor);
					cursor.y += 30;
					drawcursor(RED, cursor);
				}
				setlinecolor(BLACK);
				setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 1);
				if (cursor.y != 60)
				{
					line(cursor.x, cursor.y - 44, cursor.x, cursor.y - 46);
				}
				if (cursor.x != 30)
				{
					line(cursor.x - 16, cursor.y - 30, cursor.x - 14, cursor.y - 30);
				}
				if (cursor.x != 540)
				{
					line(cursor.x + 14, cursor.y - 30, cursor.x + 16, cursor.y - 30);
				}
				
				break;
			}
			case 75:	case 'A':		//左
			{
				if (cursor.x > 30)
				{
					drawcursor(bkcolor, cursor);
					cursor.x -= 30;
					drawcursor(RED, cursor);
				}
				setlinecolor(BLACK);
				setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 1);
				if (cursor.x != 510)
				{
					line(cursor.x + 44, cursor.y, cursor.x + 46, cursor.y);
				}
				if (cursor.y != 30)
				{
					line(cursor.x + 30, cursor.y - 14, cursor.x + 30, cursor.y - 16);
				}
				if (cursor.y != 540)
				{
					line(cursor.x + 30, cursor.y + 14, cursor.x + 30, cursor.y + 16);
				}
				
				break;
			}
			case 77:	case 'D':	//右
			{
				if (cursor.x < 540)
				{
					drawcursor(bkcolor, cursor);
					cursor.x += 30;
					drawcursor(RED, cursor);
				}
				setlinecolor(BLACK);
				setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 1);
				if (cursor.x != 60)
				{
					line(cursor.x - 44, cursor.y, cursor.x - 46, cursor.y);
				}
				if (cursor.y != 30)
				{
					line(cursor.x - 30, cursor.y - 14, cursor.x - 30, cursor.y - 16);
				}
				if (cursor.y != 540)
				{
					line(cursor.x - 30, cursor.y + 14, cursor.x - 30, cursor.y + 16);
				}
				break;
			}
			case ' ':	case 13:		//下子
			{
				if (mode == 0)
				{
					drawchess(&turn, mode);
					PlaySound(TEXT("下子.wav"), 0, SND_FILENAME | SND_ASYNC);
					drawturn(turn);
					if (iswinnew(turn,mode))
					{
						closegame(1,turn,mode);		//胜负已定
						break;
					}
					if (number == 324)		//平局
					{
						closegame(0,turn,mode);
						break;
					}
					break;
				}
				else
				{
					mode = 1;
					drawchess(&c_turn, mode);
					PlaySound(TEXT("下子.wav"), 0, SND_FILENAME | SND_ASYNC);
					if (iswinnew(c_turn, mode))
					{
						closegame(1, c_turn, mode);		//胜负已定
						_getch();
						break;
					}
					if (number == 324)					//平局
					{
						closegame(0, c_turn, mode);
						break;
					}
					c_downchess();
					getmax(&c_chess);
					drawchess(&c_turn, mode);
					if (iswinnew(c_turn,mode))
					{
						closegame(1,c_turn,mode);		//胜负已定
						_getch();
						break;
					}
					if (number == 324)					//平局
					{
						closegame(0,c_turn,mode);
						break;
					}
					else
					{
						break;
					}
				}
			}
			case 27:
			{
				mciSendString(_T("close music"), NULL, 0, NULL);
				initgame();
				view();
				break;
			}
			}
		}
	}
}

/*********************************************关闭游戏*********************************************************/

void closegame(int flag,int turn,int mode)
{
	mciSendString(_T("close music"), NULL, 0, NULL);
	PlaySound(TEXT("绝杀.wav"), 0, SND_FILENAME | SND_ASYNC);
	if (flag)
	{
		if (turn)
		{
			IMAGE win;
			loadimage(&win, "黑棋获胜new.jpg", 750, 570);
			putimage(0, 0, &win);

			Position hand = { 360,400 };
			IMAGE temp;				//保存小手重绘前的背景块
			getimage(&temp, hand.x, hand.y, hand.x + 30, hand.y + 30);
			IMAGE hand_a, hand_b;
			loadimage(&hand_a, "40hand_b.jpg");
			loadimage(&hand_b, "40hand_a.jpg");
			putimage(hand.x, hand.y, &hand_a, NOTSRCERASE);
			putimage(hand.x, hand.y, &hand_b, SRCINVERT);
			while (1)
			{
				if (_kbhit())
				{
					switch (_getch())
					{
					case 72:
					{
						if (hand.y > 400)
						{
							putimage(hand.x, hand.y, &temp);
							getimage(&temp, hand.x, hand.y - 100, hand.x + 30, hand.y - 130);
							putimage(hand.x, hand.y - 100, &hand_a, NOTSRCERASE);
							putimage(hand.x, hand.y - 100, &hand_b, SRCINVERT);
							PlaySound(TEXT("选择.wav"), 0, SND_FILENAME | SND_ASYNC);
							hand.y -= 100;
						}
						break;
					}
					case 80:
					{
						if (hand.y < 460)
						{
							putimage(hand.x, hand.y, &temp);
							getimage(&temp, hand.x, hand.y + 100, hand.x + 30, hand.y + 130);
							putimage(hand.x, hand.y + 100, &hand_a, NOTSRCERASE);
							putimage(hand.x, hand.y + 100, &hand_b, SRCINVERT);
							PlaySound(TEXT("选择.wav"), 0, SND_FILENAME | SND_ASYNC);
							hand.y += 100;
						}
						break;
					}
					case 13:
					{
						if (hand.y == 400)
						{
							initgame();
							begingame();
							playgame();
						}
						if (hand.y == 500)
						{
							initgame();
							view();
						}
						break;
					}
					}
				}
			}

		}
		else
		{
			IMAGE win;
			loadimage(&win, "白棋获胜new.jpg", 750, 570);
			putimage(0, 0, &win);
			Position hand = { 360,400 };
			IMAGE temp;				//保存小手重绘前的背景块
			getimage(&temp, hand.x, hand.y, hand.x + 30, hand.y + 30);
			IMAGE hand_a, hand_b;
			loadimage(&hand_a, "40hand_b.jpg");
			loadimage(&hand_b, "40hand_a.jpg");
			putimage(hand.x, hand.y, &hand_a, NOTSRCERASE);
			putimage(hand.x, hand.y, &hand_b, SRCINVERT);
			while (1)
			{
				if (_kbhit())
				{
					switch (_getch())
					{
					case 72:
					{
						if (hand.y > 400)
						{
							putimage(hand.x, hand.y, &temp);
							getimage(&temp, hand.x, hand.y - 100, hand.x + 30, hand.y - 130);
							putimage(hand.x, hand.y - 100, &hand_a, NOTSRCERASE);
							putimage(hand.x, hand.y - 100, &hand_b, SRCINVERT);
							PlaySound(TEXT("选择.wav"), 0, SND_FILENAME | SND_ASYNC);
							hand.y -= 100;
						}
						break;
					}
					case 80:
					{
						if (hand.y < 460)
						{
							putimage(hand.x, hand.y, &temp);
							getimage(&temp, hand.x, hand.y + 100, hand.x + 30, hand.y + 130);
							putimage(hand.x, hand.y + 100, &hand_a, NOTSRCERASE);
							putimage(hand.x, hand.y + 100, &hand_b, SRCINVERT);
							PlaySound(TEXT("选择.wav"), 0, SND_FILENAME | SND_ASYNC);
							hand.y += 100;
						}
						break;
					}
					case 13:
					{
						if (hand.y == 400)
						{
							initgame();
							begingame();
							playgame();
						}
						if (hand.y == 500)
						{
							initgame();
							view();
						}
						break;
					}
					}
				}
			}
		}
	}
	else
	{
		IMAGE tie;
		loadimage(&tie, "平局.jpg", 750, 570);
		putimage(0, 0, &tie);
		Position hand = { 360,400 };
		IMAGE temp;				//保存小手重绘前的背景块
		getimage(&temp, hand.x, hand.y, hand.x + 30, hand.y + 30);
		IMAGE hand_a, hand_b;
		loadimage(&hand_a, "40hand_b.jpg");
		loadimage(&hand_b, "40hand_a.jpg");
		putimage(hand.x, hand.y, &hand_a, NOTSRCERASE);
		putimage(hand.x, hand.y, &hand_b, SRCINVERT);
		while (1)
		{
			if (_kbhit())
			{
				switch (_getch())
				{
				case 72:
				{
					if (hand.y > 400)
					{
						putimage(hand.x, hand.y, &temp);
						getimage(&temp, hand.x, hand.y - 100, hand.x + 30, hand.y - 130);
						putimage(hand.x, hand.y - 100, &hand_a, NOTSRCERASE);
						putimage(hand.x, hand.y - 100, &hand_b, SRCINVERT);
						PlaySound(TEXT("选择.wav"), 0, SND_FILENAME | SND_ASYNC);
						hand.y -= 100;
				}
				break;
			}
			case 80:
			{
				if (hand.y < 460)
				{
					putimage(hand.x, hand.y, &temp);
					getimage(&temp, hand.x, hand.y + 100, hand.x + 30, hand.y + 130);
					putimage(hand.x, hand.y + 100, &hand_a, NOTSRCERASE);
					putimage(hand.x, hand.y + 100, &hand_b, SRCINVERT);
					PlaySound(TEXT("选择.wav"), 0, SND_FILENAME | SND_ASYNC);
					hand.y += 100;
				}
				break;
			}
			case 13:
			{
				if (hand.y == 400)
				{
					initgame();
					begingame();
					playgame();
				}
				if (hand.y == 500)
				{
					initgame();
					view();
				}
				break;
			}
			}
		}
	}
	}
	_getch();
	closegraph();
	exit(0);
}

/***************************************重绘光标函数***************************************************/

void drawcursor(COLORREF color, Position cursor)
{
	setlinecolor(color);
	setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 2);
	circle(cursor.x, cursor.y, 15);
}

/******************************************绘制下落棋子************************************************/

void drawchess(int* turn,int mode)
{
	if (mode == 0)
	{
		if (getpixel(cursor.x, cursor.y) != color[0] && getpixel(cursor.x, cursor.y) != color[1])
		{
			if (*turn)
			{
				setlinecolor(WHITE);
				setlinestyle(PS_SOLID, 1);
				setfillcolor(WHITE);
				fillcircle(cursor.x, cursor.y, 12);
				*turn = 0;
			}
			else
			{
				setlinecolor(RGB(1, 1, 1));
				setlinestyle(PS_SOLID, 1);
				setfillcolor(RGB(1, 1, 1));
				fillcircle(cursor.x, cursor.y, 12);
				*turn = 1;
			}
			number++;
		}
	}
	else
	{
		if (*turn)
		{
			if (getpixel(c_chess.x, c_chess.y) != color[0] && getpixel(c_chess.x, c_chess.y) != color[1])
			{
				setlinecolor(WHITE);
				setlinestyle(PS_SOLID, 1);
				setfillcolor(WHITE);
				fillcircle(c_chess.x, c_chess.y, 12);
				*turn = 0;
				number++;
			}
		}
		else
		{
			if (getpixel(cursor.x, cursor.y) != color[0] && getpixel(cursor.x, cursor.y) != color[1])
			{
				setlinecolor(RGB(1, 1, 1));
				setlinestyle(PS_SOLID, 1);
				setfillcolor(RGB(1, 1, 1));
				fillcircle(cursor.x, cursor.y, 12);
				*turn = 1;
				number++;
			}
		}
		
	}
}

/*********************************判断是否产生输赢*********************************************/

int iswinnew(int turn, int mode)
{
	Position temp;
	if (mode == 0)
	{
		temp = cursor;
	}
	else if(turn==1&&mode==1)
	{
		temp = cursor;
	}
	else if (turn == 0 && mode == 1)
	{
		temp = c_chess;
	}
	int number1 = 0;
	int number2 = 0;
	int number3 = 0;
	int number4 = 0;
	for (int i = -1; i <= 1; i+=2)
	{
		for (int j = 1; j <= 4; j++)
		{
			if (temp.x + i * j * 30 >= 30 && temp.x + i * j * 30 <= 540 && temp.y + i * j * 30 >= 30 && temp.y + i * j * 30 <= 540 && getpixel(temp.x + i * j * 30, temp.y + i * j * 30) == color[turn])
			{
				number1++;
			}
			else
			{
				break;
			}
		}
	}
	for (int i = -1; i <= 1; i += 2)
	{
		for (int j = 1; j <= 4; j++)
		{
			if (temp.x + i * j * 30 >= 30 && temp.x + i * j * 30 <= 540 && temp.y - i * j * 30 >= 30 && temp.y - i * j * 30 <= 540 && getpixel(temp.x + i * j * 30, temp.y - i * j * 30) == color[turn])
			{
				number2++;
			}
			else
			{
				break;
			}
		}
	}
	for (int i = -1; i <= 1; i += 2)
	{
		for (int j = 1; j <= 4; j++)
		{
			if (temp.y + i * j * 30 >= 30 && temp.y + i * j * 30 <= 540 && getpixel(temp.x , temp.y + i * j * 30) == color[turn])
			{
				number3++;
			}
			else
			{
				break;
			}
		}
	}
	for (int i = -1; i <= 1; i += 2)
	{
		for (int j = 1; j <= 4; j++)
		{
			if (temp.x + i * j * 30 >= 30 && temp.x + i * j * 30 <= 540  && getpixel(temp.x + i * j * 30, temp.y ) == color[turn])
			{
				number4++;
			}
			else
			{
				break;
			}
		}
	}
	if (number1 >= 4 || number2 >= 4 || number3 >= 4 || number4 >= 4)
	{
		return 1;
	}
	return 0;
}




/**********************************重绘执子方函数*******************************************************/

void drawturn(int turn)
{
	settextcolor(BLACK);
	settextstyle(20, 0, _T("楷体"));
	outtextxy(600, 80, "执子方：");
	if (turn)
	{
		setlinecolor(WHITE);
		setfillcolor(WHITE);
		fillcircle(690, 88, 10);
	}
	else
	{
		setlinecolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(690, 88, 10);
	}
}

/************************************计算人机棋子最优位置***************************************************/

void c_downchess()
{
	memset(score, 0, sizeof(score));
	for (int x = 0; x <= 18; x++)		//用于遍历横坐标
	{
		for (int y = 0; y <= 18; y++)			//用于遍历纵坐标
		{
			if (getpixel(x * 30, y * 30) == BLACK && (x * 30) >= 30 && (x * 30) <= 540 && (y * 30) >= 30 && (y * 30) <= 540)	//如果找到空位
			{
				for (int i = -1; i <= 1; i++)			//用于控制方向
				{
					for (int j = -1; j <= 1; j++)			//用于控制方向
					{
						if (i != 0 || j != 0)
						{
							int number_p = 0;
							int number_c = 0;
							int empty = 0;
							for (int k = 1; k <= 5; k++)	//阻碍玩家
							{
								if (x * 30 + i * k * 30 >= 30 && x * 30 + i * k * 30 <= 540 && y * 30 + j * k * 30 >= 30 && y * 30 + j * k * 30 <=540 && getpixel(x * 30 + i * k * 30, y * 30 + j * k * 30) == RGB(1, 1, 1))
								{
									number_p++;		//记录玩家棋子数量的变量加1
								}
								else if (x * 30 + i * k * 30 >= 30 && x * 30 + i * k * 30 <= 540 && y * 30 + j * k * 30 >= 30 && y * 30 + j * k * 30 <=540 && getpixel(x * 30 + i * k * 30, y * 30 + j * k * 30) == BLACK)
								{
									empty++;		//记录空子数量加1
									break;
								}
								else
								{
									break;
								}
							}
							for (int k = -1; k >= -5; k--)
							{
								if (x * 30 + i * k * 30 >= 30 && x * 30 + i * k * 30 <= 540 && y * 30 + j * k * 30 >= 30 && y * 30 + j * k * 30 <=540 && getpixel(x * 30 + i * k * 30, y * 30 + j * k * 30) == RGB(1, 1, 1))
								{
									number_p++;			//同理，只是方向相反
								}
								else if (x * 30 + i * k * 30 >= 30 && x * 30 + i * k * 30 <= 540 && y * 30 + j * k * 30 >= 30 && y * 30 + j * k * 30 <=540 && getpixel(x * 30 + i * k * 30, y * 30 + j * k * 30) == BLACK)
								{
									empty++;
									break;
								}
								else
								{
									break;
								}
							}
							if (number_p == 1)		//阻碍玩家连成活二或死二
							{
								score[y][x]+=1;
							}
							else if (number_p == 2)
							{
								if (empty == 1)			//阻碍玩家连成死三
								{
									score[y][x] += 5;
								}
								else if (empty == 2)		//阻碍玩家连成活三
								{
									score[y][x] += 10;
								}
							}
							else if (number_p == 3)
							{
								if (empty == 1)			//阻碍玩家连成死四
								{
									score[y][x] += 20;
								}
								else if (empty == 2)		//阻碍玩家连成活四
								{
									score[y][x] += 100;
								}
							}
							else if (number_p == 4)
							{
								score[y][x] += 1000;		//阻碍玩家连成五子
							}
							empty = 0;
							for (int k = 1; k <= 5; k++)		//电脑自己落子
							{
								if (x * 30 + i * k * 30 >= 30 && x * 30 + i * k * 30 <= 540 && y * 30 + j * k * 30 >= 30 && y * 30 + j * k * 30 <=540 && getpixel(x * 30 + i * k * 30, y * 30 + j * k * 30) == WHITE)
								{
									number_c++;			//同理记录电脑棋子数
								}
								else if (x * 30 + i * k * 30 >= 30 && x * 30 + i * k * 30 <= 540 && y * 30 + j * k * 30 >= 30 && y * 30 + j * k * 30 <=540 && getpixel(x * 30 + i * k * 30, y * 30 + j * k * 30) == BLACK)
								{
									empty++;
									break;
								}
								else
								{
									break;
								}
							}
							for (int k = -1; k >= -5; k--)
							{
								if (x * 30 + i * k * 30 >= 30 && x * 30 + i * k * 30 <= 540 && y * 30 + j * k * 30 >= 30 && y * 30 + j * k * 30 <=540 && getpixel(x * 30 + i * k * 30, y * 30 + j * k * 30) == WHITE)
								{
									number_c++;
								}
								else if (x * 30 + i * k * 30 >= 30 && x * 30 + i * k * 30 <= 540 && y * 30 + j * k * 30 >= 30 && y * 30 + j * k * 30 <=540 && getpixel(x * 30 + i * k * 30, y * 30 + j * k * 30) == BLACK)
								{
									empty++;
									break;
								}
								else
								{
									break;
								}
							}
							if (number_c == 0)
							{
								score[y][x]++;		//电脑连成一子
							}
							else if (number_c == 1)
							{
								score[y][x]+=2;		//电脑连成两子
							}
							else if (number_c == 2)
							{
								if (empty == 1)			//电脑连成死三
								{
									score[y][x] += 8;
								}
								else if (empty == 2)		//电脑连成活三
								{
									score[y][x] += 30;
								}
							}
							else if (number_c == 3)
							{
								if (empty == 1)
								{
									score[y][x] += 50;		//电脑连成死四
								}
								else if (empty == 2)		
								{
									score[y][x] += 200;		//电脑连成活四
								}
							}
							else if (number_c == 4)
							{
								score[y][x] += 10000;		//电脑连成五子
							}
						}
					}
				}
			}
		}
	}

}

/************************************选出最优坐标****************************************************/

void getmax(Position* c_chess)
{
	int max = 0;
	for (int i = 0; i <= 18; i++)		//遍历
	{
		for (int j = 0; j <= 18; j++)		//遍历
		{
			if (score[i][j] > max)
			{
				max = score[i][j];			//记录分数最高位置
				c_chess->x = j * 30;		//赋值给横坐标
				c_chess->y = i * 30;		//赋值给纵坐标
			}
		}
	}
}