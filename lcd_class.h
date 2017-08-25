
#ifndef MY_USB_LCD_CLASS_H
#define MY_USB_LCD_CLASS_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
#include <bitset>

/******** text commands */
#define LCD_AUTOSCROLL_ON           0x51
#define LCD_AUTOSCROLL_OFF          0x52
#define LCD_CLEAR                   0x58
#define LCD_CHANGESPLASH            0x40           /// COL * ROW chars!
#define LCD_AUTOWRAPLINE_ON         0x43
#define LCD_AUTOWRAPLINE_OFF        0x44
#define LCD_SETCURSOR_POSITION      0x47     /// 2 args: col, row
#define LCD_HOME                    0x48
#define LCD_MOVECURSOR_BACK         0x4C
#define LCD_MOVECURSOR_FORWARD      0x4D
#define LCD_UNDERLINECURSOR_ON      0x4A
#define LCD_UNDERLINECURSOR_OFF     0x4B
#define LCD_SETCUSTOMBMP            0x4E
#define LCD_BLOCKCURSOR_ON          0x53
#define LCD_BLOCKCURSOR_OFF         0x54
#define LCD_DISPLAY_SHIFT_R      0x5A
#define LCD_DISPLAY_SHIFT_L      0x5B

/****** special chars */
#define LCD_CUSTOM_CHARACTER 0x4E       /// 9 args: char #, 8 bytes data
#define LCD_SAVECUSTOMCHARBANK 0xC1     /// 9 args: char #, 8 bytes data
#define LCD_LOADCUSTOMCHARBANK 0xC0     /// 9 args: char #, 8 bytes data

/***** Numbers & Bargraphs */
// not supported until we know what these look like
//#define LCD_PLACEMEDIUMDIGIT 0x6F

/***** display func */
#define LCD_DISPLAY_ON              0x42            /// backlight. 1 argument afterwards, in minutes
#define LCD_DISPLAY_OFF             0x46
#define LCD_SET_BRIGHTNESS          0x99         /// 1 arg: scale
#define LCD_SETSAVE_BRIGHTNESS      0x98     /// 1 arg: scale
#define LCD_SET_CONTRAST            0x50           /// 1 arg
#define LCD_SETSAVE_CONTRAST        0x91       /// 1 arg

/***** GPO commands */
#define LCD_GPO_OFF                 0x56
#define LCD_GPO_ON                  0x57
#define LCD_GPO_START_ONOFF         0xC3

/***** Extra Adafruit commands */
#define LCD_RGBBACKLIGHT            0xD0      /// 3 args - R G B
#define LCD_SETSIZE                 0xD1           /// 2 args - Cols & Rows
#define LCD_TESTBAUD                0xD2          /// zero args, prints baud rate to uart


#define LCD_COMMAND                 0xFE
//#define LCD_END_COMMAND 0x9A

// storage of the current backlight state
#define COLS_ADDR 0
#define ROWS_ADDR 1
#define SPLASH_ADDR 2
#define BACKLIGHT_R_ADDR 100
#define BACKLIGHT_G_ADDR 101
#define BACKLIGHT_B_ADDR 102
#define BACKLIGHT_STATE_ADDR 103
#define BACKLIGHT_BRIGHTNESS_ADDR 104
#define AUTOSCROLL_ADDR 105
#define BAUDRATE_ADDR 106  // and 107, 108
#define CONTRAST_ADDR 109
#define CUSTOMCHARBANKS_ADDR 110
// 110 thru 430 !
#define GPO_1_START_ONOFF_ADDR 431
#define GPO_2_START_ONOFF_ADDR 432
#define GPO_3_START_ONOFF_ADDR 434
#define GPO_4_START_ONOFF_ADDR 435
#define LAST_ADDR 436
#define EEPROM_END 511

#define ROWS 2
#define COLS 16

//uint8_t COLS = EEPROM.read(COLS_ADDR);
//uint8_t ROWS = EEPROM.read(ROWS_ADDR);



template <typename T> struct my_vector
{
	T x, y, z;
};



#define XXXBM 0x08
#define LeftBM 0x01
#define MiddleBM 0x02
#define RightBM 0x03
#define SatLeftBM 0x04
#define SatRightBM 0x05
#define HandBM 0x06
#define CheckBM 0x07

#define full 0x01
#define half_fill_upper 0x02
#define half_fill_lower 0x03
#define full_L_upper 0x04
//#define full_L_lower 0x04
#define half_L_lower 0x05
#define half_L_upper 0x06
//#define full_R_upper
#define half_R_lower 0x07
#define half_R_upper 0x08


// #include <stdint.h>

/** from stdint.h what about <cstdint> **/
/* Signed.  */

typedef signed char     int8_t;
typedef short int       int16_t;
typedef int             int32_t;



/* Unsigned.  */
typedef unsigned char	        uint8_t;
typedef unsigned short int	uint16_t;
//#ifndef __uint32_t_defined
#ifndef __uint32_t_defined
typedef unsigned int		uint32_t;
//# define __uint32_t_defined
#define __uint32_t_defined
#endif // __uint32_t_defined

enum myColor { RED = 2, GREEN, BLUE };

    class lcddisplay
    {
    public:
        lcddisplay();           /**< default constructor */
        ~lcddisplay();          /**< default destructor */
        //int lcd_open(void);     /**< lcd_init call within this */
        void lcd_clear(void);
        void lcd_home(void);
        int lcd_write(const std::string);
		void lcd_bitmap(int);
        void lcd_set_cursor_address(uint8_t address);
		void set_color(int, int, int);
		void lcd_usb_splash(std::string mystring);
        void lcd_move_left(void);
        void lcd_move_right(void);

        template<typename T>
		int lcd_write(T message);



    private:
        uint8_t height, width, cursor_col, cursor_row;
        uint8_t cursor_address;
		int R;
		int G;
		int B;
		std::ofstream in;
		char* command_param;
		//bool write_command(char command, int, const char*);
		//bool write_command(char command, int size=0, const char* buffer=0);
		bool write_command(char command);
		bool write_command(char command, int bsize, const std::vector<int> buffer);


       // void lcd_close(void);
        // int lcd_init(void);
        uint8_t lcd_get_cursor_address(void);
        void lcd_display_on(void);
        void lcd_display_off(void);
        //void lcd_blink_on(void);
        //void lcd_blink_off(void);
        //void lcd_cursor_on(void);
        //void lcd_cursor_off(void);
        void lcd_backlight_on(void);
        void lcd_backlight_off(void);

        //void lcd_left_to_right(void);
        //void lcd_right_to_left(void);
        //void lcd_autoscroll_on(void);
        //void lcd_autoscroll_off(void);
        void set_bmp(void);
        void lcd_write_custom_bitmap(uint8_t location);
        void lcd_store_custom_bitmap(uint8_t location, uint8_t bitmap[]);
        void lcd_set_backlight(uint8_t state);



        uint8_t colrow2address(uint8_t col, uint8_t row);
        uint8_t address2col(uint8_t address);
        uint8_t address2row(uint8_t address);

        void lcd_send_command(uint8_t command);
        void lcd_send_data(uint8_t data);
    };

    template<typename T>
	int lcddisplay::lcd_write(T message)
	{

		this->in << message << std::flush;
		return 0;

	}

#endif // MY_USB_LCD_CLASS_H
