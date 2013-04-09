
void PUT8 ( unsigned int, unsigned int );
void PUT16 ( unsigned int, unsigned int );
void PUT32 ( unsigned int, unsigned int );
unsigned int GET8 ( unsigned int );
unsigned int GET16 ( unsigned int );
unsigned int GET32 ( unsigned int );
void dummy ( unsigned int );
void ASMDELAY ( unsigned int );

#define PORTB_PCR16 0x4004A040
#define PORTB_PCR17 0x4004A044
#define PORTC_PCR5 0x4004B014

#define GPIOC_PDOR 0x400FF080
#define GPIOC_PSOR 0x400FF084
#define GPIOC_PCOR 0x400FF088
#define GPIOC_PTOR 0x400FF08C
#define GPIOC_PDDR 0x400FF094

#define SIM_SCGC4  0x40048034
#define SIM_SCGC5  0x40048038

#define WDOG_STCTRLH 0x40052000
#define WDOG_UNLOCK  0x4005200E

#define STK_CSR 0xE000E010
#define STK_RVR 0xE000E014
#define STK_CVR 0xE000E018

#define OSC0_CR 0x40065000
#define MCG_C1  0x40064000
#define MCG_C2  0x40064001
#define MCG_C3  0x40064002
#define MCG_C4  0x40064003
#define MCG_C5  0x40064004
#define MCG_C6  0x40064005
#define MCG_S   0x40064006

#define SIM_CLKDIV1 0x40048044
#define SIM_CLKDIV2 0x40048048
#define SIM_SOPT2   0x40048004


#define UART0_BDH 0x4006A000
#define UART0_BDL 0x4006A001
#define UART0_C1  0x4006A002
#define UART0_C2  0x4006A003
#define UART0_S1  0x4006A004
#define UART0_C4  0x4006A00A
#define UART0_D   0x4006A007


//UART baud rate = UART module clock / (16 × divisor)
//divisor = UART module clock / (16 × baud)
//96000000/(16*baud) = 52.08 = 0x34
//.08 * 32 = 2.56 so we want a fraction of 3

//what if we thought in terms of 32nds of a divisor rather than the divisor
//divisor32 = (UART module clock / (16 × baud)) * 32
//divisor32 = (UART module clock * 2) / baud
//divisor32 = 96000000 * 2 / 115200 = 1666.6
//round up
//divisor32 = 1667 = 0x683
//011010000011
//0110100 00011
//divisor of 0x34 with a remainder of 3
//fraction is divisor32 & 0x1F
//lower 8 bits of divisor = (divisor32 >> 5)&0xFF
//upper 5 bits of divisor = (divisor32 >> 13)&0x1F

void delay ( void )
{
    unsigned int ra;

    for(ra=0;ra<6;ra++)
    {
        while(1) if(GET32(STK_CVR)&0x800000) break;
        while(1) if((GET32(STK_CVR)&0x800000)==0) break;
    }
}

int notmain ( void )
{

    //Turn off watchdog and allow update
    PUT16(WDOG_UNLOCK,0xC520);
    PUT16(WDOG_UNLOCK,0xD928);
    PUT16(WDOG_STCTRLH,0x0010);

    //Enable GPIOC
    PUT32(SIM_SCGC5,GET32(SIM_SCGC5)|(1<<11));

    //configure Port C5
    PUT32(PORTC_PCR5,(1<<8));
    PUT32(GPIOC_PDDR,GET32(GPIOC_PDDR)|(1<<5));

    //switch to 96Mhz
    //start in FEI mode FLL Engaged Internal
    PUT8(OSC0_CR,0xA);
    PUT8(MCG_C2,(2<<4)|(1<<2));
    PUT8(MCG_C1,(2<<6)|(4<<3));
    while ((GET8(MCG_S) & (1<<1)) == 0) continue;
    while ((GET8(MCG_S) & (1<<4)) != 0) continue;
    while (((GET8(MCG_S)>>2)&3) != 2) continue ;
    //FBE mode FLL Bypassed External
    PUT8(MCG_C5,(3<<0));
    PUT8(MCG_C6,(1<<6)|(0<<0));
    while (!(GET8(MCG_S) & (1<<5))) continue;
    while (!(GET8(MCG_S) & (1<<6))) continue;
    // PBE mode PLL Bypassed External
    PUT32(SIM_CLKDIV1,(0<<28)|(1<<24)|(3<<16));
    PUT8(MCG_C1,(0<<6)|(4<<3));
    while (((GET8(MCG_S)>>2)&3)!=3) continue;
    // PEE mode PLL Engaged External
    PUT32(SIM_CLKDIV2,(1<<1));
    PUT32(SIM_SOPT2,(1<<18)|(1<<16)|(1<<12)|(6<<5));

    PUT32(SIM_SCGC4,GET32(SIM_SCGC4)|(1<<10));
    PUT32(SIM_SCGC5,GET32(SIM_SCGC5)|(1<<10));
    PUT32(PORTB_PCR17,(3<<8)|(1<<6));
    PUT8(UART0_BDH,(1667>>13)&0x1F);
    PUT8(UART0_BDL,(1667>> 5)&0xFF);
    PUT8(UART0_C4, (1667>> 0)&0x1F);
    //PUT8(UART0_C1,(1<<2)); //??
    PUT8(UART0_C2,(1<<3));

    PUT32(STK_CSR,0x00000004);
    PUT32(STK_RVR,0xFFFFFFFF);
    PUT32(STK_CSR,0x00000005);

    while(1)
    {
        PUT32(GPIOC_PTOR,1<<5);
        PUT8(UART0_D,0x55);
        delay();
        PUT32(GPIOC_PTOR,1<<5);
        PUT8(UART0_D,0x56);
        delay();
    }
}

