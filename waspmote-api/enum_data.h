// EnumApp_enum_data.h 
// Enumeration tables & HID keyboard data
//
#ifndef _enum_data_h_
#define _enum_data_h_

const unsigned char DD[] = 	// DEVICE Descriptor
       {0x12,	       		// bLength = 18d
        0x01,			// bDescriptorType = Device (1) Keyboard
        0x00,0x01,		// bcdUSB(L/H) USB spec rev (BCD)
	0x00,0x00,0x00, 	// bDeviceClass, bDeviceSubClass, bDeviceProtocol
	0x40,			// bMaxPacketSize0 EP0 is 64 bytes
	0x6A,0x0B,		// idVendor(L/H)--Maxim is 0B6A
	0x46,0x53,		// idProduct(L/H)--5346
	0x34,0x12,		// bcdDevice--1234
	1,2,3,			// iManufacturer, iProduct, iSerialNumber
	1};			// bNumConfigurations

const unsigned char CD[]=	// CONFIGURATION Descriptor
	{0x09,			// bLength
	0x02,			// bDescriptorType = Config
	0x22,0x00,		// wTotalLength(L/H) = 34 bytes
	0x01,			// bNumInterfaces
	0x01,			// bConfigValue
	0x00,			// iConfiguration
	//0xE0,			// bmAttributes. b7=1 b6=self-powered b5=RWU supported
	0x40,			// bmAttributes b6=self-powered
	0x01,			// MaxPower is 2 ma
// INTERFACE Descriptor
	0x09,			// length = 9
	0x04,			// type = IF
	0x00,			// IF #0
	0x00,			// bAlternate Setting
	0x01,			// bNum Endpoints
	0x03,			// bInterfaceClass = HID
	0x01,0x02,		// bInterfaceSubClass, bInterfaceProtocol
	0x00,			// iInterface
// HID Descriptor--It's at CD[18]
	0x09,			// bLength
	0x21,			// bDescriptorType = HID
	0x10,0x01,		// bcdHID(L/H) Rev 1.1
	0x00,			// bCountryCode (none)
	0x01,			// bNumDescriptors (one report descriptor)
	0x22,			// bDescriptorType	(report)
	43,0,                   // CD[25]: wDescriptorLength(L/H) (report descriptor size is 43 bytes)
// Endpoint Descriptor
	0x07,			// bLength
	0x05,			// bDescriptorType (Endpoint)
	0x83,			// bEndpointAddress (EP3-IN)		
	0x03,			// bmAttributes	(interrupt)
	64,0,                   // wMaxPacketSize (64)
	10};			// bInterval (poll every 10 msec)


const unsigned char RepD[]=   // Report descriptor 
	{
	0x05,0x01,		// Usage Page (generic desktop)
	0x09,0x06,		// Usage (keyboard)
	0xA1,0x01,		// Collection
	0x05,0x07,		//   Usage Page 7 (keyboard/keypad)
	0x19,0xE0,		//   Usage Minimum = 224
	0x29,0xE7,		//   Usage Maximum = 231
	0x15,0x00,		//   Logical Minimum = 0
	0x25,0x01,		//   Logical Maximum = 1
	0x75,0x01,		//   Report Size = 1
	0x95,0x08,		//   Report Count = 8
	0x81,0x02,		//  Input(Data,Variable,Absolute)
	0x95,0x01,		//   Report Count = 1
	0x75,0x08,		//   Report Size = 8
	0x81,0x01,		//  Input(Constant)
	0x19,0x00,		//   Usage Minimum = 0
	0x29,0x65,		//   Usage Maximum = 101
	0x15,0x00,		//   Logical Minimum = 0,
	0x25,0x65,		//   Logical Maximum = 101
	0x75,0x08,		//   Report Size = 8
	0x95,0x01,		//   Report Count = 1
	0x81,0x00,		//  Input(Data,Variable,Array)
	0xC0};			// End Collection 

// STRING descriptors. An array of string arrays

const unsigned char strDesc[][64]= {
// STRING descriptor 0--Language string
{
        0x04,			// bLength
	0x03,			// bDescriptorType = string
	0x09,0x04		// wLANGID(L/H) = English-United Sates
},
// STRING descriptor 1--Manufacturer ID
{
        12,			// bLength
	0x03,			// bDescriptorType = string
	'M',0,'a',0,'x',0,'i',0,'m',0 // text in Unicode
}, 
// STRING descriptor 2 - Product ID
{	24,			// bLength
	0x03,			// bDescriptorType = string
	'M',0,'A',0,'X',0,'3',0,'4',0,'2',0,'0',0,'E',0,' ',0,
        'E',0,'n',0,'u',0,'m',0,' ',0,'C',0,'o',0,'d',0,'e',0
},

// STRING descriptor 3 - Serial Number ID
{       20,			// bLength
	0x03,			// bDescriptorType = string
	'S',0,				
	'/',0,
	'N',0,
	' ',0,
	'3',0,
	'4',0,
	'2',0,
	'0',0,
        'E',0,
}};

const unsigned char Message[]={ // each letter is 3 bytes--shiftcode, 00, HID keycode
	0x00,0x00,0x28,         // (cr)
        0x02,0x00,0x17,		// T (02 is shift)
	0x00,0x00,0x0B,		// h
	0x00,0x00,0x08,		// e
	0x00,0x00,0x2C,		// (sp)
	0x02,0x00,0x10,		// M
	0x02,0x00,0x04,		// A
	0x02,0x00,0x1B,		// X
	0x00,0x00,0x20,		// 3
	0x00,0x00,0x21,		// 4
	0x00,0x00,0x1F,		// 2
	0x00,0x00,0x27,		// 0
	0x02,0x00,0x08,		// E
	0x00,0x00,0x2C,		// (sp)
	0x00,0x00,0x07,		// d
	0x00,0x00,0x12,		// o
	0x00,0x00,0x08,		// e
	0x00,0x00,0x16,		// s
	0x00,0x00,0x2C,		// (sp)
	0x02,0x00,0x18,		// U
	0x02,0x00,0x16,		// S
	0x02,0x00,0x05,		// B
	0x02,0x00,0x1E,		// !
	0x00,0x00,0x28};	// (cr)

#endif //enum_data.h
