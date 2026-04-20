#include "bindKey.h"
#define OP_NULL 4
#define SET_A 0
#define SET_B 1
#define SET_R 2
#define SET_OP 0
char op[4] = {'+','-','*','/'};
u8 index_op;
u8 setop;
u8 current_ary;
u8 index_ary;
u8 aryA[8];
u8 aryB[8];
void bindKeyInit()
{
    computerInit();
    matrixInit();
    clearArryAll(aryA);
    clearArryAll(aryB);
    u8 index_op = OP_NULL;
    u8 setop = SET_OP;
    u8 current_ary = SET_A;
    u8 index_ary = 0;
}

u8 toComNum(u8 num)
{
     //添加数据
        /*
        + - * /
        1 2 3 c
        4 5 6 0
        7 8 9 =
    */
    if(num == 4)return 1;
    else if(num == 5)return 2;
    else if(num == 6)return 3;
    else if(num == 8)return 4;
    else if(num == 9)return 5;
    else if(num == 10)return 6;
    else if(num == 11)return 0;
    else if(num == 12)return 7;
    else if(num == 13)return 8;
    else if(num == 14)return 9;
    else return NOT_P;
}

void bindKey(u8 num)
{
    if(num < 4)
    {
        if(!setop && current_ary == SET_A)
        {
            setop = !setop;
            index_op = num;
            current_ary = SET_B;
            index_ary = 0;
            clearArryAll(aryB);
        }
       
    }
    else if(num == 15)
    {
        if(setop)
        {
            setop=!setop;
            current_ary = SET_R;
            index_ary = 0;
            //显示运算结果
            if(index_op >= 4)
            {
                setError();
                return;
            } 
            if(op[index_op] == '+'){add();}
            else if(op[index_op] == '-'){sub();}
            else if(op[index_op] == '*'){mul();}
            else {div();}
        }
    }
    else if(num == 7)
    {
        if(--index_ary >= 8){index_ary = 0;};
        if(current_ary == SET_R)
        {
            clearArryAll(aryA);
            clearArryAll(aryB); 
            clearAll();
            index_ary = 0;
            current_ary = SET_A;
            index_op = OP_NULL;
            setop = SET_OP;
        }
        else if(current_ary == SET_B)
        {
            //数组B
            clearArryCnt(aryB,1);
            setReArryB(aryB);
            if(!index_ary)
            {
                //切换A数组
                index_op = OP_NULL;
                current_ary = SET_A;
                index_ary = getArrySize(aryA);
            }
        }
        else
        {
            //数组A
            clearArryCnt(aryA,1);
            setReArryA(aryA);
        }
    }
    else if(num < NOT_P)
    {
        u8 a = toComNum(num);
        if(a == NOT_P)return;
        if(current_ary == SET_A)
        {
            if(index_ary < 8)
            {
                
                aryA[index_ary++] = a;
                setReArryA(aryA);
            }

        }
        else if(current_ary == SET_B)
        {
            if(index_ary < 8)
            {
                aryB[index_ary++] = a;
                setReArryB(aryB);
            }
        }
    } 
}

void show()
{
    if(current_ary == SET_A) {showArryA();}
    else if(current_ary == SET_B) {showArryB();}
    else {showResult();}
}