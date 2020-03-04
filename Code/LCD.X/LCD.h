/*
 * File:   LCD.h
 * Author: IBRAHIM LABS
 * EMAIL:  Ibrahimlabs@gmail.com
 *
 * Website: http://www.ibrahimlabs.com/
 *
 * Created on August 10, 2014, 5:42 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif


#define LCD_BUS     PORTB                       /*  DATA BUS FOR LCD 8bits      */
#define ENABLE_LCD  PORTCbits.RC1               /*  Enable pin of LCD           */
#define RS_LCD      PORTCbits.RC0               /*  RS pin of LCD               */

#define LCD_BUS_DIRECTION   TRISB               /*  DATA bus tristate register  */
#define ENABLE_DIRECTION    TRISCbits.TRISC1    /*  Enable pin tristate register*/
#define RS_DIRECTION        TRISCbits.TRISC0    /*  RS pin tristate register    */

#define FirstLine   0x80
#define SecondLine  0xC0

/*----------------------------------------------------------------------------*/

    /*  Functions for LCD   */

    void Initilize_LCD(void);
    void ClearScreen_LCD(void);
    void Toggle_Enable_Pin_LCD(void);
    void WriteCmd_LCD(unsigned char Cmd);
    void WriteData_LCD(unsigned char Data);
    void WriteString_LCD(const char *String);
    unsigned char MoveCursorToPosition(unsigned char Address);
//  © www.IbrahimLabs.com

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

