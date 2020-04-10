#include<graphics.h>
#include <conio.h>
#include<stdio.h>
#include <Mmsystem.h>
#pragma comment(lib,"Winmm.lib")

typedef struct position {								//����ṹ
	int x;
	int y;
}Position;

/********************************ȫ�ֱ���**********************************/

Position cursor;										//�������
Position c_chess;										//�˻�ģʽ���ӳ�ʼλ��
COLORREF bkcolor;										//���̱�����ɫ
COLORREF color[2] = { WHITE , RGB(1,1,1) };				//����������ɫ����0��1��
int turn;												//��0��1��˫��ģʽ��
int mode;												//��־ģʽ
int c_turn;												//�˻�ģʽ�غ�
int number;												//������������
char up1[100] = "δ����";								//���һ�ǳ�
char up2[100] = "δ����";								//��Ҷ��ǳ�
int score[19][19] = { 0 };								//���ڼ����˻�����÷�

/**************************��������*******************************************/

void view();											//��ʼ�˵�
void initgame();										//��ʼ����Ϸ����
void begingame();										//��ʼ��Ϸ
void playgame();										//����Ϸ��ȫ��ϸ��
void closegame(int flag,int turn,int mode);				//�ͷ���Դ
void drawcursor(COLORREF color, Position cursor);		//���ƹ��
void drawchess(int* turn, int mode);					//��������
void drawturn(int turn);								//����ִ�ӷ�
void getmax(Position* c_chess);							//��ȡ��������������
void c_downchess();										//�����˻�����
int iswinnew(int turn, int mode);						//�ж���Ӯ

/*************************************��������*************************************/

int main()
{
	initgame();
	view();
	return 0;
}

void view()
{
/*********************************��ʼ������********************************************/
	initgraph(750, 570);
	setbkmode(TRANSPARENT);
A:	//���ڷ������˵�
	IMAGE setting;
	loadimage(&setting, "���˵�����.jpg", 750, 570);						//���˵�����ͼƬ
	putimage(0, 0, &setting);

/***********************������ѡ��ͼ��***********************************************/

	settextcolor(RGB(0, 0, 195));								
	settextstyle(25, 0, _T("����"));									

	setlinecolor(RGB(240, 128, 128));
	rectangle(230, 250, 500, 290);
	outtextxy(320, 260, "��ʼ��Ϸ");

	setlinecolor(RGB(50, 205, 50));
	rectangle(230, 330, 500, 370);
	outtextxy(320, 340, "��Ϸ����");

	setlinecolor(RGB(244, 164, 96));
	rectangle(230, 410, 500, 450);
	outtextxy(320, 420, "������Ϣ");

	setlinecolor(RGB(169, 169, 169));
	rectangle(230, 490, 500, 530);
	outtextxy(320, 500, "�˳���Ϸ");
	
/*********************************��ʼ��С��λ��******************************************/

	Position hand = { 420,269 };										//��ʼ��С������
	IMAGE temp;				//����С���ػ�ǰ�ı�����
	getimage(&temp, hand.x, hand.y, hand.x + 30, hand.y + 30);
	IMAGE hand_a, hand_b;
	loadimage(&hand_a, "40hand_b.jpg");
	loadimage(&hand_b, "40hand_a.jpg");
	putimage(hand.x, hand.y, &hand_a, NOTSRCERASE);
	putimage(hand.x, hand.y, &hand_b, SRCINVERT);

/***************************��ѭ������������Ϣ********************************/

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
					PlaySound(TEXT("ѡ��.wav"), 0, SND_FILENAME | SND_ASYNC);
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
					PlaySound(TEXT("ѡ��.wav"), 0, SND_FILENAME | SND_ASYNC);
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
					loadimage(&setting, "���ñ���.jpg", 750, 570);
					putimage(0, 0, &setting);
					settextcolor(RGB(255, 69, 0));
					settextstyle(40, 0, _T("����"));
					outtextxy(180, 40, "ģʽ����(Mode Setting)");
					settextstyle(30, 0, _T("����"));
					settextcolor(RGB(0, 0, 195));
					outtextxy(100, 160, "˫�˶�ս");
					outtextxy(100, 220, "�˻���ս");
					outtextxy(100, 280, "���ز˵�");
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
									PlaySound(TEXT("ѡ��.wav"), 0, SND_FILENAME | SND_ASYNC);
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
									PlaySound(TEXT("ѡ��.wav"), 0, SND_FILENAME | SND_ASYNC);
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
									settextstyle(40, 0, _T("����"));
									outtextxy(180, 40, "�ǳ�����(Name Setting)");
									settextcolor(RGB(0, 0, 205));
									settextstyle(30, 0, _T("����"));
									outtextxy(100, 160, "������");
									outtextxy(100, 220, "������");
									outtextxy(100, 280, "�� ��");
									outtextxy(100, 340, "�� ��");
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
													PlaySound(TEXT("ѡ��.wav"), 0, SND_FILENAME | SND_ASYNC);
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
													PlaySound(TEXT("ѡ��.wav"), 0, SND_FILENAME | SND_ASYNC);
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
													InputBox(up1, 10, "�����������ǳƣ�");
													break;
												}
												case 230:
												{
													InputBox(up2, 10, "�����������ǳƣ�");
													break;
												}
												case 290:
												{
													//���
													putimage(0, 0, &setting);
													settextcolor(RGB(255, 69, 0));
													settextstyle(40, 0, _T("����"));
													outtextxy(180, 40, "��������(First Turn)");
													settextcolor(RGB(0, 0, 205));
													settextstyle(30, 0, _T("����"));
													outtextxy(100, 160, "����");
													outtextxy(100, 220, "����");
													outtextxy(100, 280, "����");
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
																	PlaySound(TEXT("ѡ��.wav"), 0, SND_FILENAME | SND_ASYNC);
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
																	PlaySound(TEXT("ѡ��.wav"), 0, SND_FILENAME | SND_ASYNC);
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
					loadimage(&care, "��Ϸ˵��new.jpg", 750, 570);
					putimage(0, 0, &care);
					settextcolor(RGB(0, 255, 255));
					settextstyle(30, 0, _T("����"));
					outtextxy(20, 20, "��Ϸ����:");
					settextcolor(RGB(148, 0, 211));
					settextstyle(30, 0, _T("����"));
					outtextxy(20, 60, "1.�Ծ�˫����ִһɫ���ӡ�");
					outtextxy(20, 95, "2.�����̿��֡�");
					outtextxy(20, 130, "3.�������ӣ�ÿ��ֻ����һ�ӡ�");
					outtextxy(20, 165, "4.�����������̵Ŀհ׵��ϣ������¶��󣬲���������");
					outtextxy(50, 200, "���ƶ������ô��������û���������𴦡�");
					outtextxy(20, 235, "5.�ڷ��ĵ�һö���ӿ������������⽻����ϡ�");
					outtextxy(20, 270, "6.����һ�������С��С�����б���������³�����5��");
					outtextxy(50, 305, "���ӿ����ж�Ϊʤ�֡�");
					settextcolor(RGB(0, 255, 255));
					settextstyle(30, 0, _T("����"));
					outtextxy(20, 360, "����˵����");
					settextcolor(RGB(148, 0, 211));
					settextstyle(30, 0, _T("����"));
					outtextxy(20, 405, "UP1����W ��S ��A ��D   ���ӣ��ո�");
					outtextxy(20, 440, "UP2��С���̷����      ���ӣ��س�");
					outtextxy(20, 475, "ESC���������˵�");
					settextcolor(RGB(0, 255, 255));
					settextstyle(20, 0, _T("����"));
					outtextxy(150, 520, "�밴��������أ�����");
					_getch();
					goto A;
					break;
				}
				case 429:
				{
					mciSendString(TEXT("open ����.mp3 alias music"), 0, 0, 0);
					mciSendString(_T("play music repeat"), NULL, 0, NULL);
					IMAGE author;
					loadimage(&author, "������Ϣ.jpg", 750, 570);
					putimage(0, 0, &author);
					IMAGE vx;
					loadimage(&vx, "΢�Ŷ�ά��.jpg", 100, 100);
					putimage(220, 260, &vx);
					IMAGE qq;
					loadimage(&qq, "QQ��ά��.jpg", 100, 100);
					putimage(380, 260, &qq);
					settextcolor(RGB(64, 224, 208));
					settextstyle(20, 0, _T("����"));
					outtextxy(220, 80, "Է���ɣ�������ҵ��ѧ��һѧ��");
					settextcolor(WHITE);
					settextstyle(30, 0, _T("����"));
					outtextxy(220, 140, "�Ȱ�������Ц��");
					settextcolor(RGB(238, 130, 238));
					settextstyle(25, 0, _T("����"));
					outtextxy(230, 440, "��С�����������ദ");
					outtextxy(230, 500, "������Ϊ������Ϊ��");
					settextcolor(WHITE);
					settextstyle(30, 0, _T("����"));
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

/************************************��ʼ������********************************************************/

void initgame()
{
	//��ʼ��ִ�ӷ�
	turn = 0;
	c_turn = 0;
	//��ʼ��������ɫ
	bkcolor = RGB(218, 165, 33);
	//�������
	cursor.x = 270;
	cursor.y = 270;
	//�˻�����
	c_chess.x = 30;
	c_chess.y = 30;
	//��ʼ����������
	number = 0;
}

/******************************************��һЩ��������*******************************************************/

void begingame()
{
	if (mode == 0)
	{
		mciSendString(TEXT("open bgm.mp3 alias music"), 0, 0, 0);
		mciSendString(_T("play music repeat"), NULL, 0, NULL);
	}
	else
	{
		mciSendString(TEXT("open �˻�bgm.mp3 alias music"), 0, 0, 0);
		mciSendString(_T("play music repeat"), NULL, 0, NULL);
	}
	//���Ʊ߿�
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
	loadimage(&right, "��ͼ.jpg", 180, 570);
	putimage(570, 0, &right);
	//���Ƶ�ǰִ�ӷ�
	if (mode == 0)
	{
		drawturn(turn);
	}
	//���ƹ��
	drawcursor(RED, cursor);
	//�����ǳ�
	if (mode == 0)
	{
		settextcolor(BLACK);
		settextstyle(20, 0, _T("����"));
		outtextxy(600, 200, "���壺");
		settextstyle(17, 0, _T("����"));
		settextcolor(RGB(148, 0, 230));
		outtextxy(600, 240, up1);
		settextcolor(BLACK);
		settextstyle(20, 0, _T("����"));
		outtextxy(600, 280, "���壺");
		settextstyle(17, 0, _T("����"));
		settextcolor(RGB(0, 230, 210));
		outtextxy(600, 320, up2);
	}
	//����ģʽ
	settextcolor(RGB(240, 128, 128));
	settextstyle(30, 0, _T("����"));
	if (mode == 0)
	{
		outtextxy(600, 400, "˫��ģʽ");
	}
	else
	{
		outtextxy(600, 100, "�˻�ģʽ");
		settextcolor(BLACK);
		settextstyle(20, 0, _T("����"));
		outtextxy(600, 200, "��ң�����");
		outtextxy(600, 230, "���ԣ�����");
	}
}

/*************************************��Ϸ���Ĳ���*************************************************/

void playgame()
{
	while (1)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 72:	case 'W':	//��
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
			case 80:	case 'S':	//��
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
			case 75:	case 'A':		//��
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
			case 77:	case 'D':	//��
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
			case ' ':	case 13:		//����
			{
				if (mode == 0)
				{
					drawchess(&turn, mode);
					PlaySound(TEXT("����.wav"), 0, SND_FILENAME | SND_ASYNC);
					drawturn(turn);
					if (iswinnew(turn,mode))
					{
						closegame(1,turn,mode);		//ʤ���Ѷ�
						break;
					}
					if (number == 324)		//ƽ��
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
					PlaySound(TEXT("����.wav"), 0, SND_FILENAME | SND_ASYNC);
					if (iswinnew(c_turn, mode))
					{
						closegame(1, c_turn, mode);		//ʤ���Ѷ�
						_getch();
						break;
					}
					if (number == 324)					//ƽ��
					{
						closegame(0, c_turn, mode);
						break;
					}
					c_downchess();
					getmax(&c_chess);
					drawchess(&c_turn, mode);
					if (iswinnew(c_turn,mode))
					{
						closegame(1,c_turn,mode);		//ʤ���Ѷ�
						_getch();
						break;
					}
					if (number == 324)					//ƽ��
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

/*********************************************�ر���Ϸ*********************************************************/

void closegame(int flag,int turn,int mode)
{
	mciSendString(_T("close music"), NULL, 0, NULL);
	PlaySound(TEXT("��ɱ.wav"), 0, SND_FILENAME | SND_ASYNC);
	if (flag)
	{
		if (turn)
		{
			IMAGE win;
			loadimage(&win, "�����ʤnew.jpg", 750, 570);
			putimage(0, 0, &win);

			Position hand = { 360,400 };
			IMAGE temp;				//����С���ػ�ǰ�ı�����
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
							PlaySound(TEXT("ѡ��.wav"), 0, SND_FILENAME | SND_ASYNC);
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
							PlaySound(TEXT("ѡ��.wav"), 0, SND_FILENAME | SND_ASYNC);
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
			loadimage(&win, "�����ʤnew.jpg", 750, 570);
			putimage(0, 0, &win);
			Position hand = { 360,400 };
			IMAGE temp;				//����С���ػ�ǰ�ı�����
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
							PlaySound(TEXT("ѡ��.wav"), 0, SND_FILENAME | SND_ASYNC);
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
							PlaySound(TEXT("ѡ��.wav"), 0, SND_FILENAME | SND_ASYNC);
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
		loadimage(&tie, "ƽ��.jpg", 750, 570);
		putimage(0, 0, &tie);
		Position hand = { 360,400 };
		IMAGE temp;				//����С���ػ�ǰ�ı�����
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
						PlaySound(TEXT("ѡ��.wav"), 0, SND_FILENAME | SND_ASYNC);
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
					PlaySound(TEXT("ѡ��.wav"), 0, SND_FILENAME | SND_ASYNC);
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

/***************************************�ػ��꺯��***************************************************/

void drawcursor(COLORREF color, Position cursor)
{
	setlinecolor(color);
	setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 2);
	circle(cursor.x, cursor.y, 15);
}

/******************************************������������************************************************/

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

/*********************************�ж��Ƿ������Ӯ*********************************************/

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




/**********************************�ػ�ִ�ӷ�����*******************************************************/

void drawturn(int turn)
{
	settextcolor(BLACK);
	settextstyle(20, 0, _T("����"));
	outtextxy(600, 80, "ִ�ӷ���");
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

/************************************�����˻���������λ��***************************************************/

void c_downchess()
{
	memset(score, 0, sizeof(score));
	for (int x = 0; x <= 18; x++)		//���ڱ���������
	{
		for (int y = 0; y <= 18; y++)			//���ڱ���������
		{
			if (getpixel(x * 30, y * 30) == BLACK && (x * 30) >= 30 && (x * 30) <= 540 && (y * 30) >= 30 && (y * 30) <= 540)	//����ҵ���λ
			{
				for (int i = -1; i <= 1; i++)			//���ڿ��Ʒ���
				{
					for (int j = -1; j <= 1; j++)			//���ڿ��Ʒ���
					{
						if (i != 0 || j != 0)
						{
							int number_p = 0;
							int number_c = 0;
							int empty = 0;
							for (int k = 1; k <= 5; k++)	//�谭���
							{
								if (x * 30 + i * k * 30 >= 30 && x * 30 + i * k * 30 <= 540 && y * 30 + j * k * 30 >= 30 && y * 30 + j * k * 30 <=540 && getpixel(x * 30 + i * k * 30, y * 30 + j * k * 30) == RGB(1, 1, 1))
								{
									number_p++;		//��¼������������ı�����1
								}
								else if (x * 30 + i * k * 30 >= 30 && x * 30 + i * k * 30 <= 540 && y * 30 + j * k * 30 >= 30 && y * 30 + j * k * 30 <=540 && getpixel(x * 30 + i * k * 30, y * 30 + j * k * 30) == BLACK)
								{
									empty++;		//��¼����������1
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
									number_p++;			//ͬ��ֻ�Ƿ����෴
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
							if (number_p == 1)		//�谭������ɻ��������
							{
								score[y][x]+=1;
							}
							else if (number_p == 2)
							{
								if (empty == 1)			//�谭�����������
								{
									score[y][x] += 5;
								}
								else if (empty == 2)		//�谭������ɻ���
								{
									score[y][x] += 10;
								}
							}
							else if (number_p == 3)
							{
								if (empty == 1)			//�谭�����������
								{
									score[y][x] += 20;
								}
								else if (empty == 2)		//�谭������ɻ���
								{
									score[y][x] += 100;
								}
							}
							else if (number_p == 4)
							{
								score[y][x] += 1000;		//�谭�����������
							}
							empty = 0;
							for (int k = 1; k <= 5; k++)		//�����Լ�����
							{
								if (x * 30 + i * k * 30 >= 30 && x * 30 + i * k * 30 <= 540 && y * 30 + j * k * 30 >= 30 && y * 30 + j * k * 30 <=540 && getpixel(x * 30 + i * k * 30, y * 30 + j * k * 30) == WHITE)
								{
									number_c++;			//ͬ���¼����������
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
								score[y][x]++;		//��������һ��
							}
							else if (number_c == 1)
							{
								score[y][x]+=2;		//������������
							}
							else if (number_c == 2)
							{
								if (empty == 1)			//������������
								{
									score[y][x] += 8;
								}
								else if (empty == 2)		//�������ɻ���
								{
									score[y][x] += 30;
								}
							}
							else if (number_c == 3)
							{
								if (empty == 1)
								{
									score[y][x] += 50;		//������������
								}
								else if (empty == 2)		
								{
									score[y][x] += 200;		//�������ɻ���
								}
							}
							else if (number_c == 4)
							{
								score[y][x] += 10000;		//������������
							}
						}
					}
				}
			}
		}
	}

}

/************************************ѡ����������****************************************************/

void getmax(Position* c_chess)
{
	int max = 0;
	for (int i = 0; i <= 18; i++)		//����
	{
		for (int j = 0; j <= 18; j++)		//����
		{
			if (score[i][j] > max)
			{
				max = score[i][j];			//��¼�������λ��
				c_chess->x = j * 30;		//��ֵ��������
				c_chess->y = i * 30;		//��ֵ��������
			}
		}
	}
}