
void PUT8 ( unsigned int, unsigned int );
void PUT16 ( unsigned int, unsigned int );
void PUT32 ( unsigned int, unsigned int );
unsigned int GET8 ( unsigned int );
unsigned int GET16 ( unsigned int );
unsigned int GET32 ( unsigned int );
void dummy ( unsigned int );
void ASMDELAY ( unsigned int );

#define PORTC_PCR5 0x4004B014
#define GPIOC_PDOR 0x400FF080
#define GPIOC_PSOR 0x400FF084
#define GPIOC_PCOR 0x400FF088
#define GPIOC_PTOR 0x400FF08C
#define GPIOC_PDDR 0x400FF094
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

void delay ( void )
{
    //unsigned int ra;

    //for(ra=0;ra<10;ra++)
    {
        while(1) if(GET32(STK_CVR)&0x800000) break;
        while(1) if((GET32(STK_CVR)&0x800000)==0) break;
    }
}

int notmain ( void )
{
    unsigned int rx;

    //Turn off watchdog and allow update
    PUT16(WDOG_UNLOCK,0xC520);
    PUT16(WDOG_UNLOCK,0xD928);
    PUT16(WDOG_STCTRLH,0x0010);

    //Enable GPIO
    PUT32(SIM_SCGC5,GET32(SIM_SCGC5)|(1<<11));

    //configure Port C5
    PUT32(PORTC_PCR5,(1<<8));
    PUT32(GPIOC_PDDR,GET32(GPIOC_PDDR)|(1<<5));

    //16MHz FBE mode FLL Bypassed External
    PUT8(OSC0_CR,0xA);
    PUT8(MCG_C2,(2<<4)|(1<<2));
    PUT8(MCG_C1,(2<<6)|(4<<3));
    while ((GET8(MCG_S) & (1<<1)) == 0) continue;
    while ((GET8(MCG_S) & (1<<4)) != 0) continue;
    while (((GET8(MCG_S)>>2)&3) != 2) continue ;
    PUT32(SIM_CLKDIV1,0);

    PUT32(STK_CSR,0x00000004);
    PUT32(STK_RVR,0xFFFFFFFF);
    PUT32(STK_CSR,0x00000005);

    while(1)
    {
        PUT32(GPIOC_PTOR,1<<5);
        delay();
        PUT32(GPIOC_PTOR,1<<5);
        delay();
    }
}

