#define button_c1 portc.rc0
#define button_c2 portc.rc1
#define button_c3 portc.rc2
#define button_c4 portc.rc3
#define buzzer portc.rc4


/*----------------- LCD -------------------*/
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
unsigned int x,y;                  // POUR STOCKER LE CONTENUE DU REGISTRE ADCON0
unsigned int t,heart;
unsigned int heartt,hearttt;
unsigned int heartttt;
unsigned int MAXI;
unsigned int MINI;
unsigned int rate;

void Move_Delay()                    // Function used for timing
{
    Delay_ms(750);
}


char flag = 0;
void interrupt ()
{
    if(INTCON.INTF == 1 )
    {
        flag = 1;              // set flag
        INTCON.INTF = 0;       // Clear Interrupt Flag
    }

    INTCON.INTE=1;
}


void main()
{

  UART1_Init(9615);

// CONFIGURER LES I/O DU PIC
    trisa=0xFF;
    porta=0x00;
    trise=0x07;
    porte=0x00;
    trisb = 0x01;
    portb=0x00;            // PORTS B EN SORTIE
    trisd=0x00;

    portd=0x00;              // PORTS D EN SORTIE
    trisc=0x8F;              // PORTS (0 à 3) EN TANT QUE DES ENTREES DES BOUTTONS
    portc=0x00;



// INITIALISATION DES VARIABLES
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
// INITIALISATION DES FONCTIONS
    ADC_Init();
    //Sound_Init(&PORTC, 4);               // L'INITIALISATION DU REGISTRE ADCON  (PINS ANALOGIQUES)
    Lcd_Init();                          // INITIALISATION DE LCD
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);


    EEPROM_Write(0x0F,0x52);               // Write some data at address 15
    EEPROM_Write(0x1F,0x3E);               // Write some data at address 31
// Validation de l'interruption
    OPTION_REG.INTEDG=1;
  INTCON.GIE=1;
  INTCON.INTE=1;
  INTCON.RBIF=1;

// Effacer l'indicateur de l'interruption RB0
    INTCON.INTF=0;


    for(;;)
    {
         MAXI=EEPROM_Read(0x0F);
         MINI=EEPROM_Read(0x1F);

        a=ADC_Read(0);               //STOCKER LE SIGNAL ANALOGIQUE RECU LORS DE RA0 SOUS FORME NUMERIQUE DANS a
        b=ADC_Read(1);               //STOCKER LE SIGNAL ANALOGIQUE RECU LORS DE RA1 SOUS FORME NUMERIQUE DANS b
        x=ADC_Read(2);               //STOCKER LE SIGNAL ANALOGIQUE RECU LORS DE RA2 SOUS FORME NUMERIQUE DANS c
        y=ADC_Read(3);               //STOCKER LE SIGNAL ANALOGIQUE RECU LORS DE RA3 SOUS FORME NUMERIQUE DANS d
        heart=ADC_Read(4);           //STOCKER LE SIGNAL ANALOGIQUE RECU LORS DE RA5 SOUS FORME NUMERIQUE DANS heart
        heartt=ADC_Read(5);          //STOCKER LE SIGNAL ANALOGIQUE RECU LORS DE RE0 SOUS FORME NUMERIQUE DANS heartt
        hearttt=ADC_Read(6);         //STOCKER LE SIGNAL ANALOGIQUE RECU LORS DE RE1 SOUS FORME NUMERIQUE DANS hearttt
        heartttt=ADC_Read(7);        //STOCKER LE SIGNAL ANALOGIQUE RECU LORS DE RE2 SOUS FORME NUMERIQUE DANS heartttt
        rate=0b100110011;

        if(INTCON.T0IF == 1)
        {

            INTCON.T0IF = 0;
        }

        /*-------------------------------- AFFICHAGE DE L'ETAT NORMALE ---------------------------------------*/


        if(porta.ra5==0 && portc.rc0 == 0 && portc.rc1 == 0 && portc.rc2 == 0 && portc.rc3 == 0 && a<MAXI && a>MINI && b<MAXI && b>MINI && x<MAXI && x>MINI && y<MAXI && y>MINI && heart>rate && heartt>rate && hearttt>rate && heartttt>rate)
        {

            Lcd_Out(1, 3, "ETAT NORMALE");
            /*UART1_Write(13);
            UART1_Write_Text("ETAT NORMALE");
            UART1_Write(13);
            Move_Delay() ;*/


        }


        /*-------------------------------- APPEL DE LA CHAMBRE 1 ---------------------------------------*/


        else if(portc.rc0 == 1 && portc.rc1 == 0 && portc.rc2 == 0 && portc.rc3 == 0)
        {
            Lcd_Cmd(_LCD_CLEAR);
            Lcd_Cmd(_LCD_CURSOR_OFF);
            Lcd_Out(1, 4, "APPEL DE LA ");
            Lcd_Out(2, 5, "CHAMBRE 1");
            buzzer=1;
            portd=0xFF;
            Move_Delay() ;
            portd=0x00;
            buzzer=0;
            Lcd_Cmd(_LCD_CLEAR);
            Lcd_Cmd(_LCD_CURSOR_OFF);

        }

        /*-------------------------------- APPEL DE LA CHAMBRE 2 ---------------------------------------*/


        else if(portc.rc1 == 1 && portc.rc0 == 0 && portc.rc2 == 0 && portc.rc3 == 0)
        {
            Lcd_Cmd(_LCD_CLEAR);
            Lcd_Cmd(_LCD_CURSOR_OFF);
            Lcd_Out(1, 4, "APPEL DE LA ");
            Lcd_Out(2, 5, "CHAMBRE 2");
            buzzer = 1;
            portd=0x3F;
            Move_Delay() ;
            portd=0x00;
            buzzer = 0;
            Lcd_Cmd(_LCD_CLEAR);
            Lcd_Cmd(_LCD_CURSOR_OFF);

        }

        /*-------------------------------- APPEL DE LA CHAMBRE 3 ---------------------------------------*/


        else if(portc.rc2 == 1 && portc.rc1 == 0 && portc.rc0 == 0 && portc.rc3 == 0)
        {
            Lcd_Cmd(_LCD_CLEAR);
            Lcd_Cmd(_LCD_CURSOR_OFF);
            Lcd_Out(1, 4, "APPEL DE LA ");
            Lcd_Out(2, 5, "CHAMBRE 3");
            buzzer = 1;
            portd=0x3F;
            Move_Delay() ;
            portd=0x00;
            buzzer = 0;
            Lcd_Cmd(_LCD_CLEAR);
            Lcd_Cmd(_LCD_CURSOR_OFF);

        }

        /*-------------------------------- APPEL DE LA CHAMBRE 4 ---------------------------------------*/


        else if(portc.rc3 == 1 && portc.rc1 == 0 && portc.rc2 == 0 && portc.rc0 == 0)
        {
            Lcd_Cmd(_LCD_CLEAR);
            Lcd_Cmd(_LCD_CURSOR_OFF);
            Lcd_Out(1, 4, "APPEL DE LA");
            Lcd_Out(2, 5, "CHAMBRE 4");
            buzzer = 1;
            portd=0x3F;
            Move_Delay() ;
            portd=0x00;
            buzzer = 0;
            Lcd_Cmd(_LCD_CLEAR);
            Lcd_Cmd(_LCD_CURSOR_OFF);

        }

        /*-------------------------------- CAS D'URGENCE ---------------------------------------*/

        else if(a >= 0x52 || a<=0x3E || b >= 0x52 || b <=0x3E || x >= 0x52 || x <=0x3E || y >= 0x52 || y <=0x3E || heart<=rate || heartt<=rate || hearttt<=rate || heartttt<=rate)
        {
            portb.rb6=1;
            buzzer =1;
            Move_Delay() ;
            portb.rb6=0;
        }



        /*-------------------------------- SI L'INTERRUPTION DECLANCHE ---------------------------------------*/
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
                                                   buzzer=0;
                                                   Lcd_Cmd(_LCD_CLEAR);
                                                   Lcd_Cmd(_LCD_CURSOR_OFF);
                                                    }

           }

            }


    }
}