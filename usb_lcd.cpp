// usb_lcd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;
unsigned char sdcjp[] = { 0xbd,0xc3,0xa8,0xb0,0xcc,0xde,0xdd };
char displaybuff[20][4];


int main()
{
	int input;
	string s_input ="hold";
	char buffer[20];


	lcddisplay myLCD;
	myLCD.lcd_clear();
	myLCD.set_color(100,100,100);


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
	cin >>input;
	myLCD.lcd_set_cursor_address(0x40);

	cout << "to pos 0" << endl;
	cin >> input;
	myLCD.lcd_set_cursor_address(0);

	cout << "input a string: ";
	cin.ignore();
	getline(cin, s_input);
	//cin >> s_input;
	myLCD.lcd_write(s_input);

	cout << "to pos 10" << endl;
	cin >> buffer;
	myLCD.lcd_set_cursor_address(0x0a);

	cout << "to pos 72" << endl;
	cin >> input;
	myLCD.lcd_set_cursor_address(0x48);

	cout << "to home" << endl;
	cin >> input;
	myLCD.lcd_home();

	myLCD.lcd_bitmap(LeftBM);
	myLCD.lcd_bitmap(MiddleBM);
	myLCD.lcd_bitmap(RightBM);
	myLCD.lcd_bitmap(SatLeftBM);
	myLCD.lcd_bitmap(SatRightBM);
	cin >> input;


	myLCD.lcd_set_cursor_address(1);
	for(int i=0; i!=16; i++)
    {

        myLCD.lcd_set_cursor_address(i);
        cout<<"position "<<i;
        //cin>>input;

    }


    for (uint8_t i=0; i <ROWS; i++)
    {
       for (uint8_t j=0; j<COLS; j++)
        {
         displaybuff[j][i] = ' ';
        }
    }






    return 0;
}

