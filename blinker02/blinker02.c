
void PUT16 ( unsigned int, unsigned int );
void PUT32 ( unsigned int, unsigned int );
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

    PUT32(STK_CSR,0x00000004);
    PUT32(STK_RVR,0xFFFFFFFF);
    PUT32(STK_CSR,0x00000005);

    while(1)
    {
        PUT32(GPIOC_PTOR,1<<5);
        while(1) if(GET32(STK_CVR)&0x800000) break;
        PUT32(GPIOC_PTOR,1<<5);
        while(1) if((GET32(STK_CVR)&0x800000)==0) break;
    }
}

