#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<math.h>
#include<time.h>
#include "box.h"
int notfilled();
int *add(int item[]);
int ifmove(int item[]);
int if2n(int x);
int ifup();
int ifdown();
int ifleft();
int ifright();
int boxmax();
int keyboardcontrol(int key);
int gamewin();
int gamefail();
#pragma warning(disable:4996)
int BOX[4][4] = {
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0
};
int score = 0;
int step = 0;
int *add(int item[])
{
	int i, j = 0;
	int tep[4] = { 0,0,0,0 };
	int tmp[4] = { 0,0,0,0 };
	for (i = 0; i < 4; i++)
	{
		if (item[i] != 0)
		{
			tep[j++] = item[i];
		}
	}
	for (i = 0; i < 3; i++)
	{
		if (tep[i] == tep[i + 1])
		{
			tep[i] *= 2;
			tep[i + 1] = 0;
			score += tep[i];
		}
	}
	j = 0;
	for (i = 0; i < 4; i++)
	{
		if (tep[i] != 0)
		{
			tmp[j++] = tep[i];
		}
	}
	return (int *)(&tmp);
}

//判断能否移动
int ifmove(int item[])
{
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		if (item[i] != 0 && item[i] == item[i + 1])return 1;
		if (item[i] == 0 && item[i + 1] != 0)return 1;
	}
	return 0;
}
//是否是2的n次方
int if2n(int x)
{
	int flag = 0;
	int n;
	for (n = 1; n <= 11; n++)
	{
		if (x == pow(2, n))flag = 1;
	}
	return flag;
}
//能否上下左右移
int ifup()
{
	int i, j, addup;
	int flag = 0;
	for (j = 0; j < 4; j++)
	{
		for (i = 0; i < 3; i++)
		{
			
			if (BOX[i][j] == BOX[i + 1][j] || BOX[i + 1][j]==0)
				flag = 1;
		}
	}
	return flag;
}
int ifdown()
{
	int i, j, addup;
	int flag = 0;
	for (j = 0; j < 4; j++)
	{
		for (i = 3; i > 0; i--)
		{
			if (BOX[i][j] == BOX[i - 1][j] || BOX[i - 1][j]==0)
				flag = 1;
		}
	}
	return flag;
}
int ifleft()
{
	int i, j, addup;
	int flag = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (BOX[i][j] == BOX[i][j+1] || BOX[i][j+1]==0)
				flag = 1;
		}
	}
	return flag;
}
int ifright()
{
	int i, j, addup;
	int flag = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 3; j > 0; j--)
		{
			if (BOX[i][j] == BOX[i][j-1] || BOX[i][j-1]==0)
				flag = 1;
		}
	}
	return flag;
}

//返回最大值
int boxmax()
{
	int max = BOX[0][0];
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (BOX[i][j] > max)
				max = BOX[i][j];
		}
	}
	return max;
}
int keyboardcontrol(int key)
{
	int i, j = 0;
	int *p;
	int tp[4] = { 0,0,0,0 };
	switch (key)
	{
	case 38:
		for (int i = 0; i < 4; i++)
		{
			tp[0] = BOX[0][i];
			tp[1] = BOX[1][i];
			tp[2] = BOX[2][i];
			tp[3] = BOX[3][i];
			p = add(tp);
			if (!ifmove(tp))j++;
			BOX[0][i] = p[0];
			BOX[1][i] = p[1];
			BOX[2][i] = p[2];
			BOX[3][i] = p[3];
		}
		return j;
	case 40:
		j = 0;
		for (i = 0; i < 4; i++)
		{
			tp[0] = BOX[3][i];
			tp[1] = BOX[2][i];
			tp[2] = BOX[1][i];
			tp[3] = BOX[0][i];
			p = add(tp);
			if (!ifmove(tp))j++;
			BOX[3][i] = p[0];
			BOX[2][i] = p[1];
			BOX[1][i] = p[2];
			BOX[0][i] = p[3];
		}
		return j;
	case 37:
		j = 0;
		for (i = 0; i < 4; i++)
		{
			tp[0] = BOX[i][0];
			tp[1] = BOX[i][1];
			tp[2] = BOX[i][2];
			tp[3] = BOX[i][3];
			p = add(tp);
			if (!ifmove(tp))j++;
			BOX[i][0] = p[0];
			BOX[i][1] = p[1];
			BOX[i][2] = p[2];
			BOX[i][3] = p[3];
		}
		return j;
	case 39:
		j = 0;
		for (i = 0; i < 4; i++)
		{
			tp[0] = BOX[i][3];
			tp[1] = BOX[i][2];
			tp[2] = BOX[i][1];
			tp[3] = BOX[i][0];
			p = add(tp);
			if (!ifmove(tp))j++;
			BOX[i][0] = p[3];
			BOX[i][1] = p[2];
			BOX[i][2] = p[1];
			BOX[i][3] = p[0];
		}
		return j;

	}
}
int gamewin()
{
	int flag = 0;
	if (boxmax() == 2048)
	{
		flag = 1;
	}
	return flag;
}
//游戏失败
int gamefail()
{
	int flag = 0;
	int i, j = 0;
	if (ifup() + ifdown() + ifleft() + ifright() == 0||!notfilled)
	{
		flag = 1;
	}
	
	return flag;
}
int notfilled()
{
	int i, j = 0;
	int flag = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (BOX[i][j] == 0)
			{
				flag = 1;
				return flag;
			}

		}
	}
	return flag;
}