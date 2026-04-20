#include "computer.h"


u8 arryA[8];
u8 arryB[8];
u8 result[8];

int pow(u8 num,u8 cnt)
{
    int ret = 1;
    for(int i = 0;i < cnt;i++)
    {
        ret *= num ;
    }
    return ret;
}

void computerInit()
{
    smgInit();
    timeInit(72);
    clearAll();
}
int toInt(u8 * arry)
{
    int num = 0;
    for(int i = 0;i < 8;i++)
    {
        if(arry[i] != NUM_NULL)
        {
            num += arry[i] * pow(10,i);
        }
    }
    return num;
}
void add()
{
    int num = toInt(arryA) + toInt(arryB);
    if(num > MAX_NUM){setError();}
    else{setArry(result,num);}
}
void sub()
{
    int num = toInt(arryA) - toInt(arryB);
    if(num < 0 || num > MAX_NUM){setError();}
    else{setArry(result,num);}
}
void mul()
{
    int num = toInt(arryA) * toInt(arryB);
    if(num > MAX_NUM){setError();}
    else{setArry(result,num);}
}
void div()
{
    int a = toInt(arryA);
    int b = toInt(arryB);
    if(b == 0){setError();return;}
    int num = a / b;
    if(num > MAX_NUM){setError();}
    else{setArry(result,num);}
}

void showArry(u8 *arry)
{
    for (int i = 7; i >= 0; i--)
    {
        setPos(i + 1);
        if (arry[i] != NUM_NULL) {
            showNum(gsmg_code[arry[i]]);
        } else {
            showNum(gsmg_code[CODE_SIZE - 1]); // 空白
        }
        delay_ms(1);
    }
}

void showError()
{
    setError();
    showArry(result);
}

void showResult()
{
    showArry(result);
}
void showArryA()
{
    showArry(arryA);
}
void showArryB()
{
    showArry(arryB);
}


void setReArry(u8 * ary,u8 * arry)
{
    clearArryAll(arry);
    int j  = 0;
    for(int i = 7;i >= 0;i--)
    {
        if(ary[i] != NUM_NULL)
        {
            arry[j++] = ary[i];
        }
    }
}

void setReArryA(u8 * ary)
{
    setReArry(ary,arryA);
}
void setReArryB(u8 * ary)
{
    setReArry(ary,arryB);
}

void setArry(u8 * arry,u32 num)
{
    u8 end = 1;
    for(int i = 0;i < 8;i++)
    {
        if(num || end)
        {
            arry[i] = num % 10;
            num /= 10;
            if(num == 0)end = 0;
        }
        else
        {
            arry[i] = NUM_NULL;
        }
    }
}
void setArryA(u32 num)
{
   setArry(arryA,num);
}
void setArryB(u32 num)
{
   setArry(arryB,num);
}
void setError()
{
    clearArryAll(result);
    result[0] = 15;
    result[1] = 0;
    result[2] = 14;
}

void clearArryAll(u8 * arry)
{
    for(int i = 0;i < 8;i++){arry[i] = NUM_NULL;}
}
void clearAll()
{
    clearArryAll(arryA);
    clearArryAll(arryB);
    clearArryAll(result);
}

void clearArryCnt(u8 * arry,u8 count)
{
    if(count >= 8)
    {
        clearArryAll(arry);
    }
    else
    {
        u8 j = count;
        for(int i = 0;i < 8;i++)
        {
            if(j < 8) {arry[i] = arry[j++];}
            else {arry[i] = NUM_NULL;}
        }
    }
}

u8 getArrySize(u8 * arry)
{
    u8 arrysize = 0;
    for(int i = 0;i < 8;i++)
    {
        if(arry[i] != NUM_NULL){arrysize++;}
    }
    return arrysize;
}
