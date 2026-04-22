#include "bindKey.h"
#define OP_NULL 4

#define IS_A 0x08 
#define IS_B 0x10
#define IS_R 0x18
#define IS_OP 0x20 //标志运算符有效
#define OP_ADD 0x00
#define OP_SUB 0x40
#define OP_MUL 0x80
#define OP_DIV 0xC0
//修改为8bit位进行表示
//00设置的运算符 0是否设置运算符 00当前数组 000 数组下标0-7
#define GET_ARY_INDEX(X) ((X)&(0x07)) //获取当前数组下标
#define GET_ARY(X) ((X)&(IS_R)) //获取当前数组
#define GET_OP_STATE(X) ((X)&(IS_OP)) //获取当前运算符状态
#define GET_OP(X) ((X)&(OP_DIV)) //获取运算符
#define CLEAN_ARY(X) ((X)&(~IS_R))
#define CLEAN_ARY_INDEX(X) ((X)&(~0x07))
#define SET_ARY_INDEX(X,IDX) ((X) = (((X)&(~0x07)) | ((IDX)&0x07)))
#define SET_A(X) ((X) = (CLEAN_ARY(X) | (IS_A)))
#define SET_B(X) ((X) = (CLEAN_ARY(X) | (IS_B)))
#define SET_R(X) ((X) = (CLEAN_ARY(X) | (IS_R)))
#define CLEAN_OP_STATE(X) ((X) = ((X)&(~IS_OP)))
#define SET_OP_STATE(X) ((X) = ((X)|(IS_OP)))
#define SET_OP(X,Y) ((X) = ((X)&(~OP_DIV) | ((Y)&OP_DIV)))

u8 aryA[8];
u8 aryB[8];
u8 state = 0;


void bindKeyInit()
{
    computerInit();
    matrixInit();
    clearArryAll(aryA);
    clearArryAll(aryB);
    state = 0;
    SET_A(state);
    SET_ARY_INDEX(state,0);
    CLEAN_OP_STATE(state);
    SET_OP(state,OP_ADD);
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
    u8 idx = GET_ARY_INDEX(state);
    u8 ary = GET_ARY(state);

    if(num < 4)
    {
        if(!GET_OP_STATE(state) && ary == IS_A)
        {
            //设置符号位启用
            SET_OP_STATE(state);
            SET_OP(state,num << 6);
            SET_B(state);
            SET_ARY_INDEX(state,0);
            clearArryAll(aryB);
        }
       
    }
    else if(num == 15)
    {
        if(GET_OP_STATE(state))
        {
            SET_R(state);
            SET_ARY_INDEX(state,0);
            CLEAN_OP_STATE(state);
            //计算运算结果
            if(GET_OP(state) == OP_ADD){add();}
            else if(GET_OP(state) == OP_SUB){sub();}
            else if(GET_OP(state) == OP_MUL){mul();}
            else if(GET_OP(state) == OP_DIV){div();}
            else {setError();}
        }
    }
    else if(num == 7)
    {
        if(ary == IS_R)
        {
            clearArryAll(aryA);
            clearArryAll(aryB); 
            clearAll();
            SET_A(state);
            SET_ARY_INDEX(state,0);
            CLEAN_OP_STATE(state);
            SET_OP(state,OP_ADD);
        }
        else if(ary == IS_B)
        {
            //数组B
            if(idx > 0)
            {
                idx--;
                SET_ARY_INDEX(state,idx);
                clearArryCnt(aryB,1);
                setReArryB(aryB);
            }
            if(GET_ARY_INDEX(state) == 0)
            {
                SET_A(state);
                SET_ARY_INDEX(state,getArrySize(aryA));
                CLEAN_OP_STATE(state);
            }
        }
        else
        {
            //数组A
            if(idx > 0)
            {
                idx--;
                SET_ARY_INDEX(state,idx);
                clearArryCnt(aryA,1);
                setReArryA(aryA);
            }
        }
    }
    else if(num < NOT_P)
    {
        u8 a = toComNum(num);
        if(a == NOT_P)return;
        idx = GET_ARY_INDEX(state);
        ary = GET_ARY(state);
        if(ary == IS_A)
        {
            if(idx < 8)
            {
                aryA[idx++] = a;
                SET_ARY_INDEX(state,idx);
                setReArryA(aryA);
            }

        }
        else if(ary == IS_B)
        {
            if(idx < 8)
            {
                aryB[idx++] = a;
                SET_ARY_INDEX(state,idx);
                setReArryB(aryB);
            }
        }
    } 
}

void show()
{
    u8 ary = GET_ARY(state);
    if(ary == IS_A) {showArryA();}
    else if(ary == IS_B) {showArryB();}
    else {showResult();}
}
