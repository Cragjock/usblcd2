// usb_lcd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <unistd.h> /// for sleep
#include <fcntl.h>
#include <termios.h>



using namespace std;
unsigned char sdcjp[] = { 0xbd,0xc3,0xa8,0xb0,0xcc,0xde,0xdd };
unsigned char alpha[]  = { "123456789a123456789b123456789c123456789d123456789e123456789f123456789g123456789h" };
///const char alpha1[] = { "abcdefghi0abcdefghi1abcdefghi2abcdefghi3abcdefghi4abcdefghi5abcdefghi6abcdefghi7" };
const char alpha1[] = { "0123456789abcdeX0123456789abcdeY" };
char displaybuff[20][4];
#define BAUDRATE B19200
//#define BAUDRATE B9600
int set_term();
string hello = "Hello from Linux";


int main(int argc, char* argv[])
{
	if(argc > 1)
	{
	    string my_arg = argv[1];
	    cout<< my_arg;
	    set_term();
	}



//	ofstream test_me("testme.txt", ios::out | ios::binary);
//	if (!test_me)
//	{
//		cout << "test_me failed to open" << endl;
//	}
//    test_me<< hello << flush;
//	test_me << (char)LCD_COMMAND << (char)LCD_DISPLAY_ON << flush;
//	test_me << (char)LCD_COMMAND << (char)LCD_CLEAR << flush;
//	test_me<< (char)LCD_COMMAND << (char)LCD_BLOCKCURSOR_ON << flush;
//	test_me << (char)LCD_COMMAND << (char)LCD_AUTOSCROLL_OFF << flush;
//	test_me<< (char)4 << (char)5 << flush;
//    test_me << LCD_COMMAND << LCD_DISPLAY_ON << flush;
//	test_me << LCD_COMMAND << LCD_CLEAR << flush;
//	test_me<< LCD_COMMAND << LCD_BLOCKCURSOR_ON << flush;
//	test_me << LCD_COMMAND << LCD_AUTOSCROLL_OFF << flush;
//	test_me<< 4 << 5 << flush;
//	test_me<< "fe 58: ";
//	test_me<< 0xfe << 0x58 << flush;
//	cout<<"0xfe and 0x58: " << hex <<LCD_COMMAND<<' ' << LCD_CLEAR<<endl;;




	int input;
	string s_input ="hold";
	char buffer[20];


	lcddisplay myLCD;
	myLCD.lcd_clear();
	myLCD.set_color(0,190,255);     ///http:rapidtables.com/web/color/RGB_Color.htm


	myLCD.lcd_set_cursor_address(0);

	stringstream ss;
	string converted;
	ss << sdcjp;
	ss >> converted;

	myLCD.lcd_write(converted);
	//const char *s = "Hello, World!";
	//std::string str(s);

	cout << "to pos 64" << endl;
	//myLCD.lcd_write("to pos 64");
	//cin >>input;
	myLCD.lcd_set_cursor_address(0x40);


	cout << "to pos 0" << endl;
	//cin >> input;
	myLCD.lcd_write("Hello Linda");
	sleep(1);

	myLCD.lcd_set_cursor_address(0);

	cout << "input a string: ";
	///cin.ignore();
	getline(cin, s_input);
	//cin >> s_input;
	myLCD.lcd_write(s_input);
	sleep(1);

	cout << "to pos 10" << endl;
	//cin >> buffer;
	myLCD.lcd_set_cursor_address(0x0a);
	sleep(2);

	cout << "to pos 72" << endl;
	//cin >> input;
	myLCD.lcd_set_cursor_address(0x48);
	sleep(1);

	cout << "to home" << endl;
	//cin >> input;
	myLCD.lcd_home();
	sleep(1);

	myLCD.lcd_bitmap(LeftBM);
	myLCD.lcd_bitmap(MiddleBM);
	myLCD.lcd_bitmap(RightBM);
	myLCD.lcd_bitmap(SatLeftBM);
	myLCD.lcd_bitmap(SatRightBM);
	//cin >> input;
	sleep(1);

    myLCD.lcd_clear();
	myLCD.lcd_bitmap(SatLeftBM);
	myLCD.lcd_bitmap(SatRightBM);

	myLCD.lcd_set_cursor_address(1);
	for(int i=0; i!=16; i++)        /// walk the satellite icons across the row
    {

        myLCD.lcd_set_cursor_address(i);
        myLCD.lcd_write(' ');
        myLCD.lcd_bitmap(SatLeftBM);
        myLCD.lcd_bitmap(SatRightBM);

        ///cout<<"position "<<i;
        //cin>>input;
        sleep(1);

    }


//    for (uint8_t i=0; i <ROWS; i++)
//    {
//       for (uint8_t j=0; j<COLS; j++)
//        {
//         displaybuff[j][i] = ' ';
//        }
//    }

	// sleep(2);
	myLCD.lcd_home();
	myLCD.lcd_write(alpha);
	sleep(2);


    myLCD.lcd_move_left();
    sleep(1);
    myLCD.lcd_move_left();
    sleep(1);
    myLCD.lcd_move_left();
    sleep(1);
    myLCD.lcd_move_left();
    sleep(1);

    myLCD.lcd_move_right();
    sleep(1);
    myLCD.lcd_move_right();
    sleep(1);
    myLCD.lcd_move_right();
    sleep(1);
    myLCD.lcd_move_right();
    sleep(1);
    myLCD.lcd_move_right();
    sleep(1);


    ///test_me.close();

    return 0;
}

int set_term()
{
    struct termios term;

    const char* portname = "/dev/ttyACM0";

    int usbFD = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (usbFD < 0)
    {
        cout<<"error %d opening %s: %s"<<endl;
        return 0;
    }

    term.c_cflag = BAUDRATE | CS8 | CSTOPB |CLOCAL | CREAD;
    term.c_iflag = 0;
    term.c_oflag = 0;
    term.c_lflag = 0;
    tcflush(usbFD, TCIFLUSH);
    tcsetattr(usbFD, TCSANOW, &term);
    close(usbFD);
    return 0;
}



