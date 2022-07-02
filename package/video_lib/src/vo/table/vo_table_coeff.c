/* Copyright (c) 2022, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/******************************************************************************
  File Name     : vo_coeff.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
/*
*
*/
int V_Coef[128]= {
        0x400000,
        0x0,
        0x3ffff8,
        0xfff008,
        0x3fdff0,
        0xfff011,
        0x3fafea,
        0xffe01c,
        0x3f6fe3,
        0xffe027,
        0x3f1fde,
        0xffd033,
        0x3eafd8,
        0xffb040,
        0x3e3fd3,
        0xffa04e,
        0x3dbfcf,
        0xff905d,
        0x3d1fca,
        0xff706c,
        0x3c7fc7,
        0xff507c,
        0x3bcfc3,
        0xff308c,
        0x3b0fc0,
        0xff109d,
        0x3a3fbd,
        0xfef0af,
        0x395fbb,
        0xfec0c1,
        0x387fb9,
        0xfea0d4,
        0x378fb8,
        0xfe80e8,
        0x368fb6,
        0xfe50fb,
        0x357fb5,
        0xfe210f,
        0x346fb4,
        0xfe0124,
        0x334fb4,
        0xfdd139,
        0x322fb4,
        0xfda14e,
        0x30ffb4,
        0xfd8163,
        0x2fcfb4,
        0xfd5179,
        0x2e9fb5,
        0xfd318f,
        0x2d4fb5,
        0xfd01a4,
        0x2c0fb6,
        0xfcd1bb,
        0x2abfb7,
        0xfcb1d1,
        0x296fb9,
        0xfc81e7,
        0x281fba,
        0xfc61fd,
        0x26bfbc,
        0xfc4213,
        0x255fbe,
        0xfc2229,
        0x240fc0,
        0xfc0240,
        0x229fc2,
        0xfbe255,
        0x213fc4,
        0xfbc26b,
        0x1fdfc6,
        0xfba281,
        0x1e7fc8,
        0xfb9296,
        0x1d1fcb,
        0xfb72ab,
        0x1bbfcd,
        0xfb62c0,
        0x1a4fd0,
        0xfb52d4,
        0x18ffd3,
        0xfb52e9,
        0x179fd5,
        0xfb42fc,
        0x163fd8,
        0xfb430f,
        0x14efda,
        0xfb4322,
        0x139fdd,
        0xfb4334,
        0x124fe0,
        0xfb4346,
        0x10ffe2,
        0xfb5357,
        0xfbfe5,
        0xfb6368,
        0xe8fe8,
        0xfb8378,
        0xd4fea,
        0xfb9387,
        0xc1fec,
        0xfbb395,
        0xaffef,
        0xfbd3a3,
        0x9dff1,
        0xfc03b0,
        0x8cff3,
        0xfc33bc,
        0x7cff5,
        0xfc73c7,
        0x6cff7,
        0xfca3d1,
        0x5dff9,
        0xfcf3db,
        0x4effa,
        0xfd33e3,
        0x40ffb,
        0xfd83ea,
        0x33ffd,
        0xfde3f1,
        0x27ffe,
        0xfe33f6,
        0x1cffe,
        0xfea3fa,
        0x11fff,
        0xff03fd,
        0x8fff,
        0xff83ff
};
/*
*
*/
int H_Coef[192] ={
        0x0,
        0x4000,
        0x0,
        0xf8000000,
        0xf0083fff,
        0xff,
        0xf0000000,
        0xf0113fdf,
        0xff,
        0xea000000,
        0xe01c3faf,
        0xff,
        0xe3000000,
        0xe0273f6f,
        0xff,
        0xde000000,
        0xd0333f1f,
        0xff,
        0xd8000000,
        0xb0403eaf,
        0xff,
        0xd3000000,
        0xa04e3e3f,
        0xff,
        0xcf000000,
        0x905d3dbf,
        0xff,
        0xca000000,
        0x706c3d1f,
        0xff,
        0xc7000000,
        0x507c3c7f,
        0xff,
        0xc3000000,
        0x308c3bcf,
        0xff,
        0xc0000000,
        0x109d3b0f,
        0xff,
        0xbd000000,
        0xf0af3a3f,
        0xfe,
        0xbb000000,
        0xc0c1395f,
        0xfe,
        0xb9000000,
        0xa0d4387f,
        0xfe,
        0xb8000000,
        0x80e8378f,
        0xfe,
        0xb6000000,
        0x50fb368f,
        0xfe,
        0xb5000000,
        0x210f357f,
        0xfe,
        0xb4000000,
        0x124346f,
        0xfe,
        0xb4000000,
        0xd139334f,
        0xfd,
        0xb4000000,
        0xa14e322f,
        0xfd,
        0xb4000000,
        0x816330ff,
        0xfd,
        0xb4000000,
        0x51792fcf,
        0xfd,
        0xb5000000,
        0x318f2e9f,
        0xfd,
        0xb5000000,
        0x1a42d4f,
        0xfd,
        0xb6000000,
        0xd1bb2c0f,
        0xfc,
        0xb7000000,
        0xb1d12abf,
        0xfc,
        0xb9000000,
        0x81e7296f,
        0xfc,
        0xba000000,
        0x61fd281f,
        0xfc,
        0xbc000000,
        0x421326bf,
        0xfc,
        0xbe000000,
        0x2229255f,
        0xfc,
        0xc0000000,
        0x240240f,
        0xfc,
        0xc2000000,
        0xe255229f,
        0xfb,
        0xc4000000,
        0xc26b213f,
        0xfb,
        0xc6000000,
        0xa2811fdf,
        0xfb,
        0xc8000000,
        0x92961e7f,
        0xfb,
        0xcb000000,
        0x72ab1d1f,
        0xfb,
        0xcd000000,
        0x62c01bbf,
        0xfb,
        0xd0000000,
        0x52d41a4f,
        0xfb,
        0xd3000000,
        0x52e918ff,
        0xfb,
        0xd5000000,
        0x42fc179f,
        0xfb,
        0xd8000000,
        0x430f163f,
        0xfb,
        0xda000000,
        0x432214ef,
        0xfb,
        0xdd000000,
        0x4334139f,
        0xfb,
        0xe0000000,
        0x4346124f,
        0xfb,
        0xe2000000,
        0x535710ff,
        0xfb,
        0xe5000000,
        0x63680fbf,
        0xfb,
        0xe8000000,
        0x83780e8f,
        0xfb,
        0xea000000,
        0x93870d4f,
        0xfb,
        0xec000000,
        0xb3950c1f,
        0xfb,
        0xef000000,
        0xd3a30aff,
        0xfb,
        0xf1000000,
        0x3b009df,
        0xfc,
        0xf3000000,
        0x33bc08cf,
        0xfc,
        0xf5000000,
        0x73c707cf,
        0xfc,
        0xf7000000,
        0xa3d106cf,
        0xfc,
        0xf9000000,
        0xf3db05df,
        0xfc,
        0xfa000000,
        0x33e304ef,
        0xfd,
        0xfb000000,
        0x83ea040f,
        0xfd,
        0xfd000000,
        0xe3f1033f,
        0xfd,
        0xfe000000,
        0x33f6027f,
        0xfe,
        0xfe000000,
        0xa3fa01cf,
        0xfe,
        0xff000000,
        0x3fd011f,
        0xff,
        0xff000000,
        0x83ff008f,
        0xff
};
/*
*
*/
int  GammaCoef[256] ={
        0b00000000,
        0b00000001,
        0b00000010,
        0b00000011,
        0b00000100,
        0b00000101,
        0b00000110,
        0b00000111,
        0b00001000,
        0b00001001,
        0b00001010,
        0b00001011,
        0b00001100,
        0b00001101,
        0b00001110,
        0b00001111,
        0b00010000,
        0b00010001,
        0b00010010,
        0b00010011,
        0b00010100,
        0b00010101,
        0b00010110,
        0b00010111,
        0b00011000,
        0b00011001,
        0b00011010,
        0b00011011,
        0b00011100,
        0b00011101,
        0b00011110,
        0b00011111,
        0b00100000,
        0b00100001,
        0b00100010,
        0b00100011,
        0b00100100,
        0b00100101,
        0b00100110,
        0b00100111,
        0b00101000,
        0b00101001,
        0b00101010,
        0b00101011,
        0b00101100,
        0b00101101,
        0b00101110,
        0b00101111,
        0b00110000,
        0b00110001,
        0b00110010,
        0b00110011,
        0b00110100,
        0b00110101,
        0b00110110,
        0b00110111,
        0b00111000,
        0b00111001,
        0b00111010,
        0b00111011,
        0b00111100,
        0b00111101,
        0b00111110,
        0b00111111,
        0b01000000,
        0b01000001,
        0b01000010,
        0b01000011,
        0b01000100,
        0b01000101,
        0b01000110,
        0b01000111,
        0b01001000,
        0b01001001,
        0b01001010,
        0b01001011,
        0b01001100,
        0b01001101,
        0b01001110,
        0b01001111,
        0b01010000,
        0b01010001,
        0b01010010,
        0b01010011,
        0b01010100,
        0b01010101,
        0b01010110,
        0b01010111,
        0b01011000,
        0b01011001,
        0b01011010,
        0b01011011,
        0b01011100,
        0b01011101,
        0b01011110,
        0b01011111,
        0b01100000,
        0b01100001,
        0b01100010,
        0b01100011,
        0b01100100,
        0b01100101,
        0b01100110,
        0b01100111,
        0b01101000,
        0b01101001,
        0b01101010,
        0b01101011,
        0b01101100,
        0b01101101,
        0b01101110,
        0b01101111,
        0b01110000,
        0b01110001,
        0b01110010,
        0b01110011,
        0b01110100,
        0b01110101,
        0b01110110,
        0b01110111,
        0b01111000,
        0b01111001,
        0b01111010,
        0b01111011,
        0b01111100,
        0b01111101,
        0b01111110,
        0b01111111,
        0b10000000,
        0b10000001,
        0b10000010,
        0b10000011,
        0b10000100,
        0b10000101,
        0b10000110,
        0b10000111,
        0b10001000,
        0b10001001,
        0b10001010,
        0b10001011,
        0b10001100,
        0b10001101,
        0b10001110,
        0b10001111,
        0b10010000,
        0b10010001,
        0b10010010,
        0b10010011,
        0b10010100,
        0b10010101,
        0b10010110,
        0b10010111,
        0b10011000,
        0b10011001,
        0b10011010,
        0b10011011,
        0b10011100,
        0b10011101,
        0b10011110,
        0b10011111,
        0b10100000,
        0b10100001,
        0b10100010,
        0b10100011,
        0b10100100,
        0b10100101,
        0b10100110,
        0b10100111,
        0b10101000,
        0b10101001,
        0b10101010,
        0b10101011,
        0b10101100,
        0b10101101,
        0b10101110,
        0b10101111,
        0b10110000,
        0b10110001,
        0b10110010,
        0b10110011,
        0b10110100,
        0b10110101,
        0b10110110,
        0b10110111,
        0b10111000,
        0b10111001,
        0b10111010,
        0b10111011,
        0b10111100,
        0b10111101,
        0b10111110,
        0b10111111,
        0b11000000,
        0b11000001,
        0b11000010,
        0b11000011,
        0b11000100,
        0b11000101,
        0b11000110,
        0b11000111,
        0b11001000,
        0b11001001,
        0b11001010,
        0b11001011,
        0b11001100,
        0b11001101,
        0b11001110,
        0b11001111,
        0b11010000,
        0b11010001,
        0b11010010,
        0b11010011,
        0b11010100,
        0b11010101,
        0b11010110,
        0b11010111,
        0b11011000,
        0b11011001,
        0b11011010,
        0b11011011,
        0b11011100,
        0b11011101,
        0b11011110,
        0b11011111,
        0b11100000,
        0b11100001,
        0b11100010,
        0b11100011,
        0b11100100,
        0b11100101,
        0b11100110,
        0b11100111,
        0b11101000,
        0b11101001,
        0b11101010,
        0b11101011,
        0b11101100,
        0b11101101,
        0b11101110,
        0b11101111,
        0b11110000,
        0b11110001,
        0b11110010,
        0b11110011,
        0b11110100,
        0b11110101,
        0b11110110,
        0b11110111,
        0b11111000,
        0b11111001,
        0b11111010,
        0b11111011,
        0b11111100,
        0b11111101,
        0b11111110,
        0b11111111
};