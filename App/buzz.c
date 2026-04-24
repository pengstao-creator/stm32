#include "buzz.h"
#include "stm32f10x_gpio.h"

void buzzInit()
{
    timeInit(72);
    //设置时钟使能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef initDef;
    initDef.GPIO_Mode = GPIO_Mode_Out_PP;
    initDef.GPIO_Pin = BUZZ_PIN;
    initDef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&initDef);
}

void vibFreqCtrl(u16 t,u16 us)
{
    while(t--)
    {
        BUZZ=!BUZZ;
        delay_us(us);
    }
}

static u16 getHalfPeriodUs(u8 scale)
{
    switch(scale)
    {
    case 1: return 1910; // do  (C4, 262Hz)
    case 2: return 1703; // re  (D4, 294Hz)
    case 3: return 1517; // mi  (E4, 330Hz)
    case 4: return 1432; // fa  (F4, 349Hz)
    case 5: return 1276; // sol (G4, 392Hz)
    case 6: return 1136; // la  (A4, 440Hz)
    case 7: return 1012; // si  (B4, 494Hz)
    default: return 0;
    }
}

void musicPlay(u8 scale)
{
    u16 halfPeriodUs = getHalfPeriodUs(scale);
    if(halfPeriodUs == 0) return;

    vibFreqCtrl(120, halfPeriodUs);
    delay_ms(80);
}

static void playScaleWithBeats(u8 scale, u8 beats, u16 beatMs, u16 gapMs)
{
    u16 halfPeriodUs = getHalfPeriodUs(scale);
    u16 toggles;
    u16 durationMs;

    if(halfPeriodUs == 0 || beats == 0) return;

    durationMs = (u16)(beatMs * beats);
    toggles = (u16)((durationMs * 1000UL) / halfPeriodUs);
    if(toggles == 0) toggles = 1;

    vibFreqCtrl(toggles, halfPeriodUs);
    delay_ms(gapMs);
}

static void playPhrase(const u8* notes, const u8* beats, u8 len, u16 beatMs, u16 gapMs)
{
    u8 i;
    for(i = 0; i < len; i++)
    {
        playScaleWithBeats(notes[i], beats[i], beatMs, gapMs);
    }
}

void playTestMelody(void)
{
    static const u8 s1_notes[] = {
        5,5,3,2,3,
        5,5,3,2,1,
        6,
        1,2,3,5,3,
        2
    };

    static const u8 s1_beats[] = {
        1,1,1,1,1,
        1,1,1,1,1,
        4,
        1,1,1,1,1,
        4
    };

    static const u8 s2_notes[] = {
        6,1,2,3,
        5,5,3,2,3,
        5,5,3,2,1,
        6
    };

    static const u8 s2_beats[] = {
        1,1,1,1,
        1,1,1,1,1,
        1,1,1,1,1,
        4
    };

    static const u8 s3_notes[] = {
        1,2,3,5,
        3,2,1,6,
        1,2,3,5,
        3,2,1,6
    };

    static const u8 s3_beats[] = {
        1,1,1,1,
        1,1,1,1,
        1,1,1,1,
        1,1,1,1
    };

    static const u8 s5_notes[] = {
        1,2,
        3,5,
        3,5,6,
        5,3,
        2,1,
        6,5,
        3,5,
        6,5,
        3,2,
        1
    };

    static const u8 s5_beats[] = {
        2,2,
        2,2,
        1,1,2,
        2,2,
        2,2,
        2,2,
        2,2,
        2,2,
        2,2,
        4
    };

    // 第一段
    playPhrase(s1_notes, s1_beats, (u8)(sizeof(s1_notes) / sizeof(s1_notes[0])), 220, 45);
    delay_ms(120);

    // 第二段
    playPhrase(s2_notes, s2_beats, (u8)(sizeof(s2_notes) / sizeof(s2_notes[0])), 220, 45);
    delay_ms(120);

    // 第三段（高潮）：提高速度，并重复两次
    playPhrase(s3_notes, s3_beats, (u8)(sizeof(s3_notes) / sizeof(s3_notes[0])), 165, 35);
    playPhrase(s3_notes, s3_beats, (u8)(sizeof(s3_notes) / sizeof(s3_notes[0])), 165, 35);
    delay_ms(120);

    // 第四段（回落）
    playPhrase(s1_notes, s1_beats, (u8)(sizeof(s1_notes) / sizeof(s1_notes[0])), 220, 45);
    delay_ms(120);

    // 第五段（尾声）：时值更长
    playPhrase(s5_notes, s5_beats, (u8)(sizeof(s5_notes) / sizeof(s5_notes[0])), 280, 50);
    delay_ms(300);
}
