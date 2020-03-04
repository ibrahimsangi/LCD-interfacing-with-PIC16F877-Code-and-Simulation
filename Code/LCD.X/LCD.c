/* 
 * File:   LCD.c
 * Author: IBRAHIM LABS
 * EMAIL:  Ibrahimlabs@gmail.com
 *
 * Website: http://www.ibrahimlabs.com/
 *
 * Created on August 10, 2014, 5:41 PM
 */

#define _XTAL_FREQ  10000000UL      //  10MHz

#include "LCD.h"
#include <xc.h>

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void Initilize_LCD(void)
{
    /*  making Pins as output   */

    ENABLE_DIRECTION    = 0;
    RS_DIRECTION        = 0;
    LCD_BUS_DIRECTION   = 0;

    /*  Writing zero to pins and port   */

    ENABLE_LCD  = 0;
    RS_LCD      = 0;
    LCD_BUS     = 0;

   __delay_ms(10);          /*  ten miliseconds delay   */

   /*   writing commonds for initialization of LCD  */

   WriteCmd_LCD(0x38);  /*  Functions Set as Given in Datasheet */
   WriteCmd_LCD(0x0F);  /*  Display ON; Cursor ON; Blink ON     */
   WriteCmd_LCD(0x06);  /*  Display Shifting OFF                */
   ClearScreen_LCD();   /*  Clear Display                       */

}   

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void ClearScreen_LCD(void)
{
    WriteCmd_LCD(0x01);         /*  Clear Screen command    */
    __delay_ms(3);              /*  Delay for cursor to return home must be
                                 *  atleast 3ms menstioned in datasheet
                                 */
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void Toggle_Enable_Pin_LCD(void)
{
    /*  toggling Enable PIN is must for data to be displayed on screen
        After every Command and data for more details see datasheet
    */
    ENABLE_LCD = 1;
    __delay_us(200);
    ENABLE_LCD = 0;
    __delay_us(200);
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void WriteCmd_LCD(unsigned char Cmd)
{
    RS_LCD  = 0;        /*  For command RS must be low (0)      */
    LCD_BUS = Cmd;      /*  write Command to data bus of LCD    */

    Toggle_Enable_Pin_LCD();
}//  © www.IbrahimLabs.com

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void WriteData_LCD(unsigned char Data)
{
    RS_LCD  = 1;        /*  For data RS must be high (1)    */
    LCD_BUS = Data;     /*  write data to data bus of LCD   */

    Toggle_Enable_Pin_LCD();
}//  © www.IbrahimLabs.com

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void WriteString_LCD(const char *String)
{
    while(*String)
    {
        WriteData_LCD(*String++);   /*  Display data untill string ends */
    }
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

unsigned char MoveCursorToPosition(unsigned char Address)
{
    /*  valid addresses are for line one 0x80 and line two are 0xC0   */
    if ((Address >= 0x80 && Address <= 0xA8) || (Address >= 0xC0 && Address <= 0xE8))
    {
        WriteCmd_LCD(Address);
        return 1;
    }
    else
        return 0;
}

