#include "tm4c123gh6pm.h"
//============================== PORTD Intialization ==============================
void PORTD_init(void){ 
	SYSCTL_RCGCGPIO_R |= 0x08; 	
  while((SYSCTL_PRGPIO_R & 0x08) == 0){}; 	// 2) allow time for clock to start
  GPIO_PORTD_CR_R = 0xF;                 // 4) allow changes to PD3-0
  GPIO_PORTD_AMSEL_R = 0x00;              // 5) disable analog on PD
  GPIO_PORTD_PCTL_R = 0x00000000;         // 6) PCTL GPIO on PD7-0 disabled i won't use Aleternate function
  GPIO_PORTD_DIR_R = 0x0F;                // 7) PD3-0 as output
  GPIO_PORTD_AFSEL_R = 0x00;              // 8) disable alt funct on PD7-0
  GPIO_PORTD_DEN_R = 0x0F;          		  // 10) enable digital I/O on PD3-0
}

//============================== UART1 Intialization ==============================
void UART1_Init(void){
uint32_t delay;
SYSCTL_RCGCUART_R |= 0x02;
SYSCTL_RCGCGPIO_R |= 0x04 ;// port c activation
delay = 1; // dummy var
UART1_CTL_R &= ~0x00000001;// disable the uart until the init.
UART1_IBRD_R = 104;
UART1_FBRD_R = 11;
UART1_LCRH_R = 0x00000070;
UART1_CTL_R |= 0x00000001; // enable UART
GPIO_PORTC_AFSEL_R |= 0x30;
GPIO_PORTC_DEN_R = 0x30;
GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R &0xFF00FFFF) + 0x00220000; // to set 2 in pctl pc4 and pc5
GPIO_PORTC_AMSEL_R &= ~0x30;// disable analog in pc4-5
}

//============================== UART2 Intialization (Temporary) ==============================
/* UART2_Init(void){
uint32_t delay;
SYSCTL_RCGCUART_R |= 0x04; 							             // activate UART2
SYSCTL_RCGCGPIO_R |= 0x08; 							             // activate port D
delay = 1; // dummy var
while((SYSCTL_PRGPIO_R & 0x08) == 0){};              // allow time for clock to start
UART2_CTL_R &= ~0x01;      							             // disable UART
UART2_CTL_R &= ~0x0000001;// disable the uart until the init.
UART2_IBRD_R = 104;                                  // IBRD = int(16,000,000 / (16 * 9,600)) = int(104.1667)
UART2_FBRD_R = 11;                                   // FBRD = int(0.1667 * 64 + 0.5) = 11                  
UART2_LCRH_R |=0x60;
UART2_CTL_R |= 0x301;       					               // enable UART
GPIO_PORTD_AFSEL_R |= 0xC0;                          // enable alt funct on PD6-PD7 
GPIO_PORTD_DEN_R |= 0xC0;                            // enable digital I/O on PD6-PD7                           
GPIO_PORTD_PCTL_R |= 0x11000000 ;			               // configure PD6-PD7 as UART
GPIO_PORTD_AMSEL_R =0x00;                            // disable analog functionality on PA
	
}*/
char UART2_read(void){
    while((UART2_FR_R&0x10) == 0x10);
    return UART2_DR_R & 0xFF;
}
void UART2_write(char c){
    while((UART2_FR_R & UART_FR_TXFF) != 0);
    UART0_DR_R = c;
}

char* UART2_ReadStr(void){
	char* str;
	int i;
	for (i=0; i<1810; i++){
		str[i] =  UART2_read();
	}
	return str;
}
