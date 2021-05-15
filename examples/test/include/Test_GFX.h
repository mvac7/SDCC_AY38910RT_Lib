/* -----------------------------------------------------------------------------
   AY-3-8910 MSXSDCC Library
   GFXs Datas
------------------------------------------------------------------------------*/


// ----------------------------------------------------------------------------- MAPs

// map size width:3 height:8
// Size= 24
const char EnvelopeShapes[]={
0xE0,0xE1,0xE1,
0xE2,0xE1,0xE1,
0xE3,0xE4,0xE5,
0xE6,0xE7,0xE8,
0xE9,0xEA,0xEA,
0xEB,0xEC,0xED,
0xEE,0xEA,0xEA,
0xEF,0xF0,0xF1};






// map size width:32 height:24
// RLE WB compressed - Original size= 768 - Compress size= 122
const char Frame_MAP[]={
0x18,0x80,0x1D,0x17,0x19,0x16,0x80,0x1D,0x20,0x16,0x16,0x80,0x1D,0x20,0x16,0x14,
0x80,0x1D,0x17,0x13,0x16,0x80,0x1D,0x20,0x16,0x16,0x80,0x1D,0x20,0x16,0x16,0x80,
0x1D,0x20,0x16,0x16,0x80,0x1D,0x20,0x16,0x16,0x80,0x1D,0x20,0x16,0x16,0x80,0x1D,
0x20,0x16,0x16,0x80,0x1D,0x20,0x16,0x16,0x80,0x1D,0x20,0x16,0x16,0x80,0x1D,0x20,
0x16,0x16,0x80,0x1D,0x20,0x16,0x16,0x80,0x1D,0x20,0x16,0x16,0x80,0x1D,0x20,0x16,
0x16,0x80,0x1D,0x20,0x16,0x16,0x80,0x1D,0x20,0x16,0x16,0x80,0x1D,0x20,0x16,0x16,
0x80,0x1D,0x20,0x16,0x16,0x80,0x1D,0x20,0x16,0x16,0x80,0x1D,0x20,0x16,0x16,0x80,
0x1D,0x20,0x16,0x1A,0x80,0x1D,0x17,0x1B,0x80,0xFF};


// map size width:32 height:20
// RLE WB compressed - Original size= 640 - Compress size= 316
const char GUI_MAP[]={
0x14,0x80,0x1D,0x17,0x13,0x16,0x80,0x1D,0x20,0x16,0x16,0x80,0x1D,0x20,0x16,0x14,
0x80,0x08,0x17,0x12,0x80,0x08,0x17,0x12,0x80,0x09,0x17,0x13,0x16,0x43,0x68,0x61,
0x6E,0x6E,0x65,0x6C,0x20,0x41,0x16,0x43,0x68,0x61,0x6E,0x6E,0x65,0x6C,0x20,0x42,
0x16,0x43,0x68,0x61,0x6E,0x6E,0x65,0x6C,0x20,0x43,0x20,0x16,0x14,0x80,0x08,0x17,
0x15,0x80,0x08,0x17,0x15,0x80,0x09,0x17,0x13,0x16,0x54,0x6F,0x6E,0x65,0x3A,0x80,
0x03,0x20,0x16,0x54,0x6F,0x6E,0x65,0x3A,0x80,0x03,0x20,0x16,0x54,0x6F,0x6E,0x65,
0x3A,0x80,0x04,0x20,0x16,0x16,0x80,0x08,0x20,0x16,0x80,0x08,0x20,0x16,0x80,0x09,
0x20,0x16,0x14,0x80,0x08,0x17,0x15,0x80,0x08,0x17,0x15,0x80,0x09,0x17,0x13,0x16,
0x41,0x6D,0x70,0x3A,0x80,0x04,0x20,0x16,0x41,0x6D,0x70,0x3A,0x80,0x04,0x20,0x16,
0x41,0x6D,0x70,0x3A,0x80,0x05,0x20,0x16,0x14,0x80,0x08,0x17,0x15,0x80,0x08,0x17,
0x15,0x80,0x09,0x17,0x13,0x16,0x54,0x6F,0x6E,0x65,0x80,0x04,0x20,0x16,0x54,0x6F,
0x6E,0x65,0x80,0x04,0x20,0x16,0x54,0x6F,0x6E,0x65,0x80,0x05,0x20,0x16,0x16,0x4E,
0x6F,0x69,0x73,0x65,0x80,0x03,0x20,0x16,0x4E,0x6F,0x69,0x73,0x65,0x80,0x03,0x20,
0x16,0x4E,0x6F,0x69,0x73,0x65,0x80,0x04,0x20,0x16,0x14,0x80,0x08,0x17,0x11,0x80,
0x08,0x17,0x11,0x80,0x09,0x17,0x13,0x16,0x4E,0x6F,0x69,0x73,0x65,0x20,0x50,0x65,
0x72,0x69,0x6F,0x64,0x3A,0x80,0x10,0x20,0x16,0x14,0x80,0x1D,0x17,0x13,0x16,0x45,
0x6E,0x76,0x65,0x6C,0x6F,0x70,0x65,0x20,0x46,0x72,0x65,0x71,0x3A,0x80,0x0F,0x20,
0x16,0x16,0x45,0x6E,0x76,0x65,0x6C,0x6F,0x70,0x65,0x20,0x53,0x68,0x61,0x70,0x65,
0x3A,0x80,0x0E,0x20,0x16,0x14,0x80,0x1D,0x17,0x13,0x16,0x45,0x78,0x74,0x65,0x72,
0x6E,0x61,0x6C,0x20,0x41,0x59,0x80,0x12,0x20,0x16,0x80,0xFF};



// ----------------------------------------------------------------------------- Tileset

// Project: Test AY-3-8910
// tileset pattern
// Tiles range: 0 to 255
// RLE WB compressed - Original size= 2048 - Compress size= 1256
const char GUI_G1_TSET[]={
0x80,0x08,0x00,0x70,0x7E,0x80,0x02,0x42,0x7E,0x00,0x78,0x4C,0x4E,0x80,0x02,0x42,
0x7E,0x00,0x80,0x02,0x7F,0x41,0x80,0x02,0x7F,0x00,0x7F,0x77,0x77,0x41,0x77,0x77,
0x7F,0x00,0x80,0x02,0x7F,0x41,0x63,0x77,0x7F,0x7F,0x5C,0x62,0x70,0x5E,0x42,0x42,
0x7E,0x00,0xFC,0xBA,0xBA,0x80,0x02,0x82,0xFE,0x80,0x02,0x00,0x18,0x3C,0x7E,0x80,
0x05,0x00,0x7E,0x3C,0x18,0x80,0x02,0x00,0x08,0x18,0x38,0x38,0x18,0x08,0x00,0x00,
0x10,0x18,0x1C,0x1C,0x18,0x10,0x80,0x20,0x00,0x80,0x02,0x18,0x7E,0x80,0x06,0x18,
0xFF,0xFF,0x80,0x05,0x00,0xFF,0xFF,0x80,0x05,0x18,0xF8,0xF8,0x80,0x05,0x18,0x1F,
0x1F,0x80,0x05,0x18,0xFF,0xFF,0x80,0x0A,0x18,0x80,0x02,0x00,0xFF,0xFF,0x80,0x05,
0x00,0x0F,0x1F,0x1C,0x18,0x18,0x80,0x02,0x00,0xF0,0xF8,0x38,0x80,0x03,0x18,0x1C,
0x1F,0x0F,0x80,0x02,0x00,0x18,0x18,0x38,0xF8,0xF0,0x80,0x02,0x00,0xFF,0xDD,0xEB,
0xF7,0xEB,0xDD,0xFF,0xFF,0x80,0x10,0x00,0x10,0x10,0xFF,0xFF,0x10,0x10,0x80,0x08,
0x00,0x80,0x03,0x30,0x00,0x30,0x30,0x00,0x28,0x28,0x80,0x07,0x00,0x28,0x7C,0x28,
0x7C,0x28,0x00,0x00,0x10,0x7C,0xD0,0x7C,0x16,0x7C,0x10,0x00,0x00,0x66,0x6C,0x18,
0x36,0x66,0x00,0x00,0x70,0xD8,0x7A,0xCC,0xCC,0x7A,0x00,0x00,0x18,0x30,0x80,0x04,
0x00,0x18,0x30,0x80,0x02,0x60,0x30,0x18,0x00,0x60,0x30,0x80,0x02,0x18,0x30,0x60,
0x80,0x02,0x00,0x5A,0x3C,0x7E,0x3C,0x5A,0x80,0x02,0x00,0x18,0x18,0x7E,0x18,0x18,
0x80,0x05,0x00,0x30,0x30,0x20,0x80,0x03,0x00,0x7C,0x80,0x07,0x00,0x30,0x30,0x00,
0x00,0x06,0x0C,0x18,0x30,0x60,0xC0,0x00,0x7C,0xC6,0xCE,0xD6,0xE6,0xC6,0x7C,0x00,
0x30,0x70,0x80,0x03,0x30,0x78,0x00,0xFC,0x06,0x06,0x7C,0xC0,0xC0,0xFE,0x00,0xFC,
0x06,0x06,0x7C,0x06,0x06,0xFC,0x00,0x80,0x02,0xC6,0xFE,0x80,0x02,0x06,0x00,0xFE,
0xC0,0xC0,0xFC,0x06,0x06,0xFC,0x00,0x7C,0xC0,0xC0,0xFC,0xC6,0xC6,0x7C,0x00,0xFE,
0x06,0x0C,0x18,0x80,0x02,0x30,0x00,0x7C,0xC6,0xC6,0x7C,0xC6,0xC6,0x7C,0x00,0x7C,
0xC6,0xC6,0x7E,0x06,0x06,0x7C,0x00,0x00,0x30,0x30,0x00,0x30,0x30,0x80,0x02,0x00,
0x30,0x30,0x00,0x30,0x30,0x20,0x00,0x00,0x18,0x30,0x60,0x30,0x18,0x80,0x03,0x00,
0x78,0x00,0x78,0x80,0x03,0x00,0x60,0x30,0x18,0x30,0x60,0x00,0x00,0x3C,0x66,0x06,
0x0C,0x18,0x00,0x18,0x00,0x7C,0x82,0xBA,0xAA,0xBE,0x80,0x00,0x7C,0x00,0x7C,0x80,
0x02,0xC6,0xFE,0xC6,0xC6,0x00,0xFC,0xC6,0xC6,0xFC,0xC6,0xC6,0xFC,0x00,0x7E,0x80,
0x04,0xC0,0x7E,0x00,0xFC,0x80,0x04,0xC6,0xFC,0x00,0xFE,0xC0,0xC0,0xF8,0xC0,0xC0,
0xFE,0x00,0xFE,0xC0,0xC0,0xFC,0x80,0x02,0xC0,0x00,0x7E,0xC0,0xC0,0xCE,0xC6,0xC6,
0x7E,0x00,0x80,0x02,0xC6,0xFE,0x80,0x02,0xC6,0x00,0x78,0x80,0x04,0x30,0x78,0x00,
0x3C,0x80,0x03,0x18,0xD8,0x70,0x00,0xC6,0xC6,0xCC,0xF8,0xCC,0xC6,0xC6,0x00,0x80,
0x05,0xC0,0xFE,0x00,0xC6,0xEE,0xFE,0xD6,0x80,0x02,0xC6,0x00,0xC6,0xE6,0xF6,0xDE,
0xCE,0xC6,0xC6,0x00,0x7C,0x80,0x04,0xC6,0x7C,0x00,0xFC,0x80,0x02,0xC6,0xFC,0xC0,
0xC0,0x00,0x7C,0x80,0x02,0xC6,0xD6,0xCC,0x7A,0x00,0xFC,0xC6,0xC6,0xFC,0x80,0x02,
0xC6,0x00,0x7E,0xC0,0xC0,0x7C,0x06,0x06,0xFC,0x00,0xFC,0x80,0x05,0x30,0x00,0x80,
0x05,0xC6,0x7C,0x00,0x80,0x04,0xC6,0x6C,0x38,0x00,0x80,0x02,0xC6,0xD6,0xFE,0xEE,
0xC6,0x00,0xC6,0xC6,0x6C,0x38,0x6C,0xC6,0xC6,0x00,0x80,0x02,0xCC,0x78,0x80,0x02,
0x30,0x00,0xFE,0x06,0x0C,0x18,0x30,0x60,0xFE,0x00,0x1C,0x80,0x04,0x18,0x1C,0x00,
0x00,0xC0,0x60,0x30,0x18,0x0C,0x06,0x00,0x38,0x80,0x04,0x18,0x38,0x80,0x0E,0x00,
0x7E,0x80,0x0A,0x00,0xFC,0x06,0x7E,0xC6,0xFE,0x00,0xC0,0xC0,0xFC,0x80,0x02,0xC6,
0xFC,0x80,0x02,0x00,0x7E,0x80,0x02,0xC0,0x7E,0x00,0x06,0x06,0x7E,0x80,0x02,0xC6,
0x7E,0x80,0x02,0x00,0x7C,0xC6,0xFE,0xC0,0x7C,0x00,0x3C,0x60,0x60,0xF8,0x80,0x02,
0x60,0x80,0x02,0x00,0x7E,0xC6,0xC6,0x7E,0x06,0x7C,0xC0,0xC0,0xFC,0x80,0x03,0xC6,
0x00,0x30,0x00,0x70,0x80,0x02,0x30,0x78,0x00,0x18,0x00,0x80,0x04,0x18,0x70,0xC0,
0xC0,0xC6,0xCC,0xF8,0xCC,0xC6,0x00,0x70,0x80,0x04,0x30,0x78,0x80,0x02,0x00,0xFC,
0x80,0x03,0xD6,0x80,0x02,0x00,0xDC,0xE6,0x80,0x02,0xC6,0x80,0x02,0x00,0x7C,0x80,
0x02,0xC6,0x7C,0x80,0x02,0x00,0xFC,0x80,0x02,0xC6,0xFC,0xC0,0x00,0x00,0x7E,0x80,
0x02,0xC6,0x7E,0x06,0x00,0x00,0xDC,0xE6,0x80,0x02,0xC0,0x80,0x02,0x00,0x7E,0xC0,
0x7C,0x06,0xFC,0x00,0x30,0x30,0x7C,0x80,0x02,0x30,0x1C,0x80,0x02,0x00,0x80,0x03,
0xC6,0x7C,0x80,0x02,0x00,0x80,0x02,0xC6,0x6C,0x38,0x80,0x02,0x00,0xC6,0xD6,0xFE,
0xEE,0xC6,0x80,0x02,0x00,0xC6,0x6C,0x38,0x6C,0xC6,0x80,0x02,0x00,0x80,0x02,0xC6,
0x7E,0x06,0x7C,0x00,0x00,0xFC,0x18,0x30,0x60,0xFC,0x80,0x29,0x00,0x7C,0x80,0x02,
0xC0,0x7C,0x10,0x30,0x00,0x28,0x00,0x80,0x02,0xC6,0x7C,0x00,0x00,0x06,0x7C,0xC6,
0xFE,0xC0,0x7E,0x80,0x11,0x00,0xC0,0x7C,0x06,0x7E,0xC6,0xFE,0x80,0x0A,0x00,0x7C,
0xC0,0xC0,0x7C,0x10,0x30,0x80,0x10,0x00,0xC0,0x7C,0xC6,0xFE,0xC0,0x7E,0x80,0x11,
0x00,0x30,0x18,0x00,0x38,0x18,0x3C,0x80,0x39,0x00,0xC0,0x60,0x7C,0xC6,0xC6,0x7C,
0x80,0x48,0x00,0x0C,0x1E,0x3E,0x5C,0x68,0x70,0x80,0x02,0x00,0x06,0x7C,0x06,0x7E,
0xC6,0xFE,0x00,0x00,0x0C,0x18,0x00,0x38,0x18,0x3C,0x00,0x00,0x06,0x0C,0x7C,0xC6,
0xC6,0x7C,0x00,0x00,0x06,0x0C,0x80,0x02,0xC6,0x7C,0x00,0x00,0xFC,0x00,0xFC,0x80,
0x02,0xC6,0x00,0xFE,0x00,0xE6,0xF6,0xDE,0xCE,0xC6,0x00,0x00,0x38,0x18,0x38,0x00,
0x38,0x80,0x02,0x00,0x38,0x28,0x38,0x00,0x38,0x80,0x03,0x00,0x30,0x00,0x30,0x60,
0xCC,0x78,0x80,0x9F,0x00,0x7F,0xF8,0x80,0x02,0xF7,0xF8,0x7F,0x00,0xFF,0xDD,0x4D,
0x55,0x59,0xDD,0xFF,0x00,0xE0,0x80,0x04,0xF0,0xE0,0x00,0x7C,0xC6,0xCE,0xD6,0xE6,
0xC6,0x7C,0x00,0x30,0x70,0x80,0x03,0x30,0x78,0x00,0xFC,0x06,0x06,0x7C,0xC0,0xC0,
0xFE,0x00,0xFC,0x06,0x06,0x7C,0x06,0x06,0xFC,0x00,0x80,0x02,0xC6,0xFE,0x80,0x02,
0x06,0x00,0xFE,0xC0,0xC0,0xFC,0x06,0x06,0xFC,0x00,0x7C,0xC0,0xC0,0xFC,0xC6,0xC6,
0x7C,0x00,0xFE,0x06,0x0C,0x18,0x80,0x02,0x30,0x00,0x7C,0xC6,0xC6,0x7C,0xC6,0xC6,
0x7C,0x00,0x7C,0xC6,0xC6,0x7E,0x06,0x06,0x7C,0x80,0x98,0x00,0x7F,0xE3,0x80,0x02,
0xDD,0xE3,0x7F,0x00,0xFF,0x08,0x7B,0x18,0x7B,0x7B,0xFF,0x00,0xE0,0x70,0x80,0x03,
0xF0,0xE0,0x00,0x00,0x80,0x00,0x40,0x20,0x10,0x08,0x07,0x80,0x06,0x00,0xFF,0x00,
0x00,0x04,0x0C,0x14,0x24,0x44,0x87,0x00,0x00,0x84,0x46,0x25,0x14,0x0C,0x04,0x00,
0x00,0x21,0x31,0x29,0xA5,0x63,0x21,0x00,0x00,0x08,0x8C,0x4A,0x29,0x18,0x08,0x00,
0x00,0x80,0x00,0x40,0x20,0x11,0x0A,0x04,0x00,0x00,0x20,0x50,0x88,0x04,0x02,0x01,
0x00,0x00,0x08,0x14,0x22,0x41,0x80,0x00,0x80,0x02,0x00,0x87,0x44,0x24,0x14,0x0C,
0x04,0x00,0x00,0xFF,0x80,0x06,0x00,0x04,0x0C,0x14,0x25,0x46,0x84,0x00,0x00,0x21,
0x63,0xA5,0x29,0x31,0x21,0x00,0x00,0x08,0x18,0x29,0x4A,0x8C,0x08,0x00,0x00,0x07,
0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x04,0x0A,0x11,0x20,0x40,0x80,0x00,0x00,
0x00,0x01,0x02,0x04,0x88,0x50,0x20,0x80,0x02,0x00,0x80,0x00,0x41,0x22,0x14,0x08,
0x80,0x68,0x00,0x80,0x07,0xFF,0x80,0xFF};





// Project: Test AY-3-8910
// tileset color - type:G1
// RLE WB compressed - Original size= 32 - Compress size= 22
const char GUI_G1_TSET_COLOR[]={
0x74,0x24,0x54,0x54,0x80,0x0E,0xF4,0xE4,0x80,0x02,0xF4,0x34,0x74,0x74,0x04,0x94,
0x80,0x02,0xD4,0xE4,0x80,0xFF};





