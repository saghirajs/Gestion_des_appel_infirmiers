#line 1 "C:/Users/saghir/Desktop/(2P1) 2018-2019/Microcontrolleur et projet/projet gestion des appels infirmiers/projet_gestion_appels_infirmiers.c"



sbit LCD_RS at RC5_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D4 at RB2_bit;
sbit LCD_D5 at RB3_bit;
sbit LCD_D6 at RB4_bit;
sbit LCD_D7 at RB5_bit;

sbit LCD_RS_Direction at TRISC5_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D7_Direction at TRISB5_bit;


unsigned int a,b;
unsigned int x,y;
unsigned int t,heart;
unsigned int heartt,hearttt;
unsigned int heartttt;
unsigned int MAXI;
unsigned int MINI;
unsigned int rate;



void Move_Delay() {
 Delay_ms(1000);
}


char flag = 0;
void interrupt ()
{
 if(INTCON.INTF == 1 )
 {
 flag = 1;
 INTCON.INTF = 0;
 }

 INTCON.INTE=1;
}
void main() { UART1_Init(9615);


 trisa=0xFF;
 porta=0x00;
 trise=0x07;
 porte=0x00;
 trisb = 0x01;
 portb=0x00;
 trisd=0x00;

 portd=0x00;
 trisc=0x8F;
 portc=0x00;




 a=0x00;
 b=0x00;
 x=0x00;
 y=0x00;
 t=0x00;
 heart=0x00;
 heartt=0x00;
 hearttt=0x00;
 heartttt=0x00;
 rate=0x00;

 ADC_Init();

 Lcd_Init();
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);


 EEPROM_Write(0x0F,0x52);
 EEPROM_Write(0x1F,0x3E);

 OPTION_REG.INTEDG=1;
 INTCON.GIE=1;
 INTCON.INTE=1;
 INTCON.RBIF=1;


 INTCON.INTF=0;


 for(;;)
 {
 MAXI=EEPROM_Read(0x0F);
 MINI=EEPROM_Read(0x1F);

 a=ADC_Read(0);
 b=ADC_Read(1);
 x=ADC_Read(2);
 y=ADC_Read(3);
 heart=ADC_Read(4);
 heartt=ADC_Read(5);
 hearttt=ADC_Read(6);
 heartttt=ADC_Read(7);
 rate=0b100110011;

 if(INTCON.T0IF == 1)
 {

 INTCON.T0IF = 0;
 }




 if(porta.ra5==0 && portc.rc0 == 0 && portc.rc1 == 0 && portc.rc2 == 0 && portc.rc3 == 0 && a<MAXI && a>MINI && b<MAXI && b>MINI && x<MAXI && x>MINI && y<MAXI && y>MINI && heart>rate && heartt>rate && hearttt>rate && heartttt>rate)
 {

 Lcd_Out(1, 3, "ETAT NORMALE");
#line 128 "C:/Users/saghir/Desktop/(2P1) 2018-2019/Microcontrolleur et projet/projet gestion des appels infirmiers/projet_gestion_appels_infirmiers.c"
 }





 else if(portc.rc0 == 1 && portc.rc1 == 0 && portc.rc2 == 0 && portc.rc3 == 0)
 {
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Out(1, 4, "APPEL DE LA ");
 Lcd_Out(2, 5, "CHAMBRE 1");
  portc.rc4 =1;
 portd=0xFF;
 Move_Delay() ;
 portd=0x00;
  portc.rc4 =0;
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);

 }




 else if(portc.rc1 == 1 && portc.rc0 == 0 && portc.rc2 == 0 && portc.rc3 == 0)
 {
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Out(1, 4, "APPEL DE LA ");
 Lcd_Out(2, 5, "CHAMBRE 2");
  portc.rc4  = 1;
 portd=0x3F;
 Move_Delay() ;
 portd=0x00;
  portc.rc4  = 0;
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);

 }




 else if(portc.rc2 == 1 && portc.rc1 == 0 && portc.rc0 == 0 && portc.rc3 == 0)
 {
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Out(1, 4, "APPEL DE LA ");
 Lcd_Out(2, 5, "CHAMBRE 3");
  portc.rc4  = 1;
 portd=0x3F;
 Move_Delay() ;
 portd=0x00;
  portc.rc4  = 0;
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);

 }




 else if(portc.rc3 == 1 && portc.rc1 == 0 && portc.rc2 == 0 && portc.rc0 == 0)
 {
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Out(1, 4, "APPEL DE LA");
 Lcd_Out(2, 5, "CHAMBRE 4");
  portc.rc4  = 1;
 portd=0x3F;
 Move_Delay() ;
 portd=0x00;
  portc.rc4  = 0;
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);

 }



 else if(a >= 0x52 || a<=0x3E || b >= 0x52 || b <=0x3E || x >= 0x52 || x <=0x3E || y >= 0x52 || y <=0x3E || heart<=rate || heartt<=rate || hearttt<=rate || heartttt<=rate)
 {
 portb.rb6=1;
  portc.rc4  =1;
 Move_Delay() ;
 portb.rb6=0;
 }




 if (flag == 1)
 {
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 while(flag==1)
 {
 Lcd_Out(1, 4, "URGENCE!!!!");
 UART1_Write(13);
 UART1_Write_Text("Urgence");
 UART1_Write(13);
 Move_Delay();
 if(portb.rb0==0){
 flag=0;
  portc.rc4 =0;
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 }

 }

 }


 }}
