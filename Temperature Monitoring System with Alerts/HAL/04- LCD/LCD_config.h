/**********************************************************************************************/
/*                                                                                            */
/*  Author       : Mansour                                                                    */
/*  Last Updated : 29/11/2024, 07:22 AM                                                       */
/*  Version      : 1.0                                                                        */
/*  Description  : LCD                                                                        */
/*                                                                                            */
/*  Changelog    :                                                                            */
/*     - v1.0 (21/10/2024): Initial version created.                                          */
/*                                                                                            */
/*  License      : <Specify license type here if applicable>                                  */
/*                                                                                            */
/**********************************************************************************************/

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/*

Option:
1- four_bit_mode
2- eight_bit_mode

*/
#define eight_bit_mode
#define EN 0
#define RW 1
#define RS 2
#define LCD_PORT 'A'
#define EN_PORT 'B'
#define RS_PORT 'B'
#define RW_PORT 'B'
#endif /* LCD_CONFIG_H_ */