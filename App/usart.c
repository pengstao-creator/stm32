#include "usart.h"
u8 data[RECV_BYTE_SIZE];
u16 CONTROL_FLAG = 0;

void usartInit(u32 BaudRate)
{
    // 初始化GPIO空PA9-10和开启USARTI使能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
    GPIO_InitTypeDef gpioDef;
    gpioDef.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 浮空输入
    gpioDef.GPIO_Pin = GPIO_Pin_10;            // RX
    gpioDef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpioDef);
    gpioDef.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
    gpioDef.GPIO_Pin = GPIO_Pin_9;       // TX
    GPIO_Init(GPIOA, &gpioDef);

    // 绑定中断
    NVIC_InitTypeDef nvicDef;
    nvicDef.NVIC_IRQChannel = USART1_IRQn;
    nvicDef.NVIC_IRQChannelCmd = ENABLE;
    nvicDef.NVIC_IRQChannelPreemptionPriority = 2; // 优先级
    nvicDef.NVIC_IRQChannelSubPriority = 3;        // 副优先级
    NVIC_Init(&nvicDef);

    // 初始化usart1
    USART_InitTypeDef usartDef;
    usartDef.USART_BaudRate = BaudRate;                                  // 发送波特率
    usartDef.USART_WordLength = USART_WordLength_8b;                     // 一帧中的有效数据量
    usartDef.USART_StopBits = USART_StopBits_1;                          // 设置停止位个数
    usartDef.USART_Parity = USART_Parity_No;                             // 奇偶校验位
    usartDef.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 // 使能接收和发送
    usartDef.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 禁用硬件流控仅使用 TX 和 RX 两根线
    USART_Init(USART1, &usartDef);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // USART_IT_RXNE使能接受中断
    USART_Cmd(USART1, ENABLE);
    CLEAN_CONTROL_FLAG;
}

void USART1_IRQHandler()
{
    u16 tmp;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        // 表示有数据到来,进行数据解析
        tmp = USART_ReceiveData(USART1);
        if (tmp == '\r')
        {
            // 收到回车，先标记第一阶段结束
            SET_END_FLAG_R;
        }
        else if (tmp == '\n')
        {
            // 仅在先收到 '\r' 的情况下才认为接收结束
            if (GET_END_FLAG_R(CONTROL_FLAG))
            {
                SET_END_FLAG_N;
            }
            else
            {
                CLEAN_CONTROL_FLAG;
            }
        }
        else if (!GET_END_FLAG_R(CONTROL_FLAG) && !GET_END_FLAG_N(CONTROL_FLAG))
        {
            // 正常接受中
            if (GET_DATA_INDEX < RECV_BYTE_SIZE)
            {
                data[GET_DATA_INDEX] = tmp;
                SET_DATA_INDEX_ADD1;
            }
            else
            {
                // 数据超出缓冲区
                CLEAN_CONTROL_FLAG;
            }
        }
        else
        {
            // 接受失败
            CLEAN_CONTROL_FLAG;
        }
    }
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}
