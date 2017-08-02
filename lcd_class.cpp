
#include "stdafx.h"


using namespace std;
vector<int> cin_c_position{ 0xfe, 0x47 };
string forSplash ="Good bye cruel world, see you ";


lcddisplay::lcddisplay()

{
	cout << "In constructor" << endl;

//	string hello = "Hello from Windows";
//	in.open("COM4", ios::out | ios::binary);
//	if (!in)
//	{
//		cout << "LCDstream failed to open" << endl;
//	}


	#ifdef __linux__
	string hello = "Hello from Linux";
	in.open("/dev/ttyACM0", ios::out | ios::binary);
	if (!in)
	{
		cout << "LCDstream failed to open" << endl;
	}

#elif _WIN32
	string hello = "Hello from Windows";
	in.open("COM4", ios::out | ios::binary);
	if (!in)
	{
		cout << "LCDstream failed to open" << endl;
	}
#else
#endif

	this->in << hello << flush;
	this->in << (char)LCD_COMMAND << (char)LCD_CLEAR << flush;
	this->in << (char)LCD_COMMAND << (char)LCD_BLOCKCURSOR_ON << flush;
	this->in << hello << flush;
	set_bmp();
	this->in << (char)4 << (char)5 << flush;


}


lcddisplay::~lcddisplay()
{
	this->in << (char)LCD_COMMAND << (char)LCD_CLEAR << flush;
	lcd_usb_splash(forSplash);
	this->in.close();
}


void lcddisplay:: set_color(int red, int green, int blue)
{
	string reply;
	this->R = red;
	this->G = green;
	this->B = blue;
	vector<int>c_color{ 0xfe, 0xd0, red, green, blue };
	copy(c_color.cbegin(), c_color.cend(), ostream_iterator<char>(in));
	in << flush;

//	do
//	{
//		cout << "Enter R,G,B (0-255)";
//		cin >> red >> green >> blue;
//		vector<int>c_color{ 0xfe, 0xd0, red, green, blue };
//		copy(c_color.cbegin(), c_color.cend(), ostream_iterator<char>(in));
//		in << flush;
//		cout << "color ok? " << endl;
//		cin >> reply;
//	} while (reply != "X");
}

void lcddisplay:: set_bmp()
{
	vector<int>custom_one{ 0xfe, 0x4e, 0x00, 0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4, 0x0 };
	vector<int>bmLeft = { 0xfe, 0x4e, 0x01, 8, 12, 10, 9, 10, 12, 8, 0 };
	vector<int>bmMiddle = { 0xfe, 0x4e, 0x02, 0, 0, 31, 14, 4, 14, 31, 0 };
	vector<int>bmRight = { 0xfe, 0x4e, 0x03, 2, 6, 10, 18, 10, 6, 2, 0 };
	vector<int>bmSatLeft = { 0xfe, 0x4e, SatLeftBM, 0, 20, 21, 21, 31, 21, 20, 20 };
	vector<int>bmSatright = { 0xfe, 0x4e, 0x05, 0, 5, 21, 21, 31, 21, 5, 5 };

	copy(custom_one.cbegin(), custom_one.cend(), ostream_iterator<char>(in));
	copy(bmLeft.cbegin(), bmLeft.cend(), ostream_iterator<char>(in));
	copy(bmMiddle.cbegin(), bmMiddle.cend(), ostream_iterator<char>(in));
	copy(bmRight.cbegin(), bmRight.cend(), ostream_iterator<char>(in));
	copy(bmSatLeft.cbegin(), bmSatLeft.cend(), ostream_iterator<char>(in));
	copy(bmSatright.cbegin(), bmSatright.cend(), ostream_iterator<char>(in));

	//in << custom_one << bmLeft << bmMiddle << bmRight << bmSatLeft<< bmSatright<< flush;
	lcd_set_cursor_address(0);
	in << flush;
	lcd_set_cursor_address(0);
	in << (char)2 << (char)3 << (char)4<< flush;
	lcd_set_cursor_address(0x40);
	in << (char)4 << (char)5 << flush;
	lcd_set_cursor_address(0x49);
	in << (char)0  << flush;

}

void lcddisplay::lcd_set_cursor_address(uint8_t address)
{
	if (address > 16)
		cursor_row = 2;
	else
		cursor_row = 1;

	cursor_col = (address & 0x0f) + 1;

	vector<int>gotoPosition = cin_c_position;

	gotoPosition.push_back(cursor_col);
	gotoPosition.push_back(cursor_row);
	copy(gotoPosition.cbegin(), gotoPosition.cend(), ostream_iterator<char>(this->in));
	this->in<< flush;

}


void lcddisplay::lcd_clear(void)
{
	this->in << (char)LCD_COMMAND << (char)LCD_CLEAR << flush;
}


void lcddisplay::lcd_home(void)
{
	this->in << (char)LCD_COMMAND << (char)LCD_CLEAR << flush;
	lcd_set_cursor_address(0);
}

int lcddisplay::lcd_write(const string message)
{
	int size = message.size();
	this->in << message << flush;
	return size;
}




void lcddisplay::lcd_bitmap(int bmp_id)
{
	this->in << (char)bmp_id << flush;
}


void lcddisplay::lcd_usb_splash(string mystring)
{

	vector<int>cmd_splash{ 0xfe, 0x40 };

	copy(cmd_splash.cbegin(), cmd_splash.cend(), ostream_iterator<char>(this->in));
	this->in << mystring << flush;
}

