/*
    Tuan Nguyen (http://www.iotsharing.com) or (nha.tuan84@gmail.com)
*/

#ifndef EspLed7SegNDigit_H
#define EspLed7SegNDigit_H

//byte Tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff}; //0,1,2,3,4,5,6,7,8,9, ALL OFF
//byte Taf[]={0xA0,0x83,0xa7,0xa1,0x86,0x8e,0xc2,0x8b,0xe6,0xe1,0x89,0xc7,0xaa,0xc8,0xa3,0x8c,0x98,0xce,0x9b,0x87,0xc1,0xe3,0xd5,0xb6,0x91,0xb8};//a,b,c,d,e,f,g,h,i,j,k,l,o,m,n,o,p,q,r,s,t,u,v,w,x,y,z
//byte Tap[]={0xff,0x7f}; //"space", "." 

typedef void (*updateDisplay)(void);
class EspLed7SegNDigit
{
    private:
        //each value is according to decimal number 0,1,2,3,4,5,6,7,8,9, 0., 1., 2., 3., 4., 5., 6., 7., 8., 9., -, a,b,c,d,e,f,
        const unsigned char seg7[50] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10, 0xbf, 0xA0,0x83,0xa7,0xa1,0x86,0x8e,0xc2,0x8b,0xe6,0xe1,0x89,0xc7,0xaa,0xc8,0xa3,0x8c,0x98,0xce,0x9b,0x87,0xc1,0xe3,0xd5,0xb6,0x91,0xb8, 0xff};
        //choose the LED7 segs that we want to display number 
        const unsigned char led[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
        const int numOfDigits;
        int SCLK = -1; //pulse
        int RCLK = -1; //latch
        int DIO = -1;  //data
        long lastTick = 0;
        int **data;
        int reFreshInMs;
        updateDisplay updateCb;
        //trigger to transfer data to IC74HC595 
        void pulse(void);
        //latch data  
        void latch(void);
        //send data to DIO pin  
        void high(void); 
        void low(void);
        void scan_led(void);
        int mapToSeg(unsigned char chr);
        
    public: 
        EspLed7SegNDigit(int SCLK, int RCLK, int DIO, int numOfDigits = 8);
        ~EspLed7SegNDigit();
        int setCharAt(int pos, unsigned char chr);
        int setRefreshTime(int ms);
        void displayNum(float number, int nrBehindDot);
        void setUpdateCb(updateDisplay cb);
        void clearDisplay(void);
        void loop(void);
};

#endif
