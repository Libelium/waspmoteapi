/* aes_enc.c */
/*
    This file is part of the AVR-Crypto-Lib.
    Copyright (C) 2008  Daniel Otte (daniel.otte@rub.de)
    Modified by Y.Carmona for Libelium in 2014

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * \file     aes_enc.c
 * \email    daniel.otte@rub.de
 * \author   Daniel Otte 
 * \date     2008-12-30
 * \license  GPLv3 or later
 * 
 */

#include <stdint.h>
#include <string.h>
#include "aes.h"
#include "aes_sbox.h"
#include "aes_enc.h"
#include <avr/pgmspace.h>
#include <pins_waspmote.h>
#include <wiring.h>
#include <util/delay.h>

void aes_shiftcol(void* data, uint8_t shift){
	uint8_t tmp[4];
	tmp[0] = ((uint8_t*)data)[ 0];
	tmp[1] = ((uint8_t*)data)[ 4];
	tmp[2] = ((uint8_t*)data)[ 8];
	tmp[3] = ((uint8_t*)data)[12];
	((uint8_t*)data)[ 0] = tmp[(shift+0)&3];
	((uint8_t*)data)[ 4] = tmp[(shift+1)&3];
	((uint8_t*)data)[ 8] = tmp[(shift+2)&3];
	((uint8_t*)data)[12] = tmp[(shift+3)&3];
}


static
void aes_enc_round(aes_cipher_state_t* state, const aes_roundkey_t* k)
{
	uint8_t tmp[16], t;
	uint8_t i;	
	
	///  *** STEP 1: subBytes  *** 
	for(i=0; i<16; ++i)
	{
		tmp[i] = pgm_read_byte((uint16_t)aes_sbox+state->s[i]);
	}
	
	#ifdef ENCRYPTION_DEBUG	
	beginSerial(115200, 0);
	digitalWrite(23,0x01);
	digitalWrite(11,0x00);
	printString("\n\n*** STEP 1: subBytes  --> ",  0);	
	_delay_ms(3);	
	for(i=0; i<16; ++i)
	{		
		puthex((char)tmp[i],0);	
		_delay_ms(3);
	}	
	#endif
	
	/// *** STEP 2: shiftRows ***
	aes_shiftcol(tmp+1, 1); // rotate over 1 bytes
	aes_shiftcol(tmp+2, 2); // rotate over 2 bytes
	aes_shiftcol(tmp+3, 3); // rotate over 3 bytes
	
	#ifdef ENCRYPTION_DEBUG	
	printString("\n*** STEP 2: shiftRows --> ",  0);
	_delay_ms(3);	
	for(i=0; i<16; ++i)
	{		
		puthex((char)tmp[i],0);	
		_delay_ms(3);
	}	
	#endif
	
	/// *** STEP 3: mixColums ***	
	gmix_column(&tmp[0]);
	gmix_column(&tmp[4]);
	gmix_column(&tmp[8]);
	gmix_column(&tmp[12]);
	
	// copy result
	for(i=0; i<16; ++i)
	{		
		state->s[i] = tmp[i];
	}
	
	#ifdef ENCRYPTION_DEBUG	
	printString("\n*** STEP 3: mixColums --> ",  0);
	_delay_ms(3);
	for(i=0; i<16; ++i)
	{		
		beginSerial(115200, 0);
		digitalWrite(23,0x01);
		digitalWrite(11,0x00);
		puthex((char)state->s[i],0);	
		_delay_ms(3);
	}		
	#endif


	/// *** STEP 4: addKey ***
	for(i=0; i<16; ++i)
	{
		state->s[i] ^= k->ks[i];
	}
		
	#ifdef ENCRYPTION_DEBUG	
	printString("\n*** STEP 4: addKey    --> ",  0);
	_delay_ms(3);
	for(i=0; i<16; ++i)
	{		
		puthex((char)state->s[i],0);	
		_delay_ms(3);
	}		
	printString("  with key:",  0);
	for(i=0; i<16; ++i)
	{		
		puthex((char)k->ks[i],0);	
		_delay_ms(3);
	}
	#endif
	
}


static
void aes_enc_lastround(aes_cipher_state_t* state,const aes_roundkey_t* k)
{
	uint8_t i;
	
	/// *** STEP 1: subBytes ***
	for(i=0; i<16; ++i)
	{
		state->s[i] = pgm_read_byte((uint16_t)aes_sbox+state->s[i]);	
	}
	
	#ifdef ENCRYPTION_DEBUG	
	printString("\n\n*** STEP 1: subBytes  --> ",  0);	
	_delay_ms(3);	
	for(i=0; i<16; ++i)
	{		
		puthex((char)state->s[i],0);	
		_delay_ms(3);
	}
	#endif
	
	
	/// *** STEP 2: shiftRows ***
	aes_shiftcol(state->s+1, 1); // rotate over 1 bytes
	aes_shiftcol(state->s+2, 2); // rotate over 2 bytes
	aes_shiftcol(state->s+3, 3); // rotate over 3 bytes	
	
	#ifdef ENCRYPTION_DEBUG
	printString("\n*** STEP 2: shiftRows --> ",  0);
	_delay_ms(3);	
	for(i=0; i<16; ++i)
	{		
		puthex((char)state->s[i],0);	
		_delay_ms(3);
	}
	#endif
	
	
	/// *** STEP 3: keyAdd ***
	for(i=0; i<16; ++i)
	{
		state->s[i] ^= k->ks[i];
	}
	
	#ifdef ENCRYPTION_DEBUG
	printString("\n*** STEP 4: addKey    --> ",  0);
	_delay_ms(3);
	for(i=0; i<16; ++i)
	{		
		puthex((char)state->s[i],0);	
		_delay_ms(3);
	}			
	printString("  with key:",  0);
	for(i=0; i<16; ++i)
	{			
		puthex((char)k->ks[i],0);	
		_delay_ms(3);
	}	
	printString("\n",  0);
	#endif
}

void aes_encrypt_core(	aes_cipher_state_t* state, 
						const aes_genctx_t* ks, 
						uint8_t rounds)
{
	#ifdef ENCRYPTION_DEBUG
	beginSerial(115200, 0);
	digitalWrite(23,0x01);
	digitalWrite(11,0x00);
	printString("\ninside aes_encrypt_core...\nActual state:",  0);	
	_delay_ms(3);	
	#endif
	
	uint8_t i;
	uint8_t k;
	for(i=0; i<16; ++i)
	{
		state->s[i] ^= ks->key[0].ks[i];
		
		#ifdef ENCRYPTION_DEBUG
		beginSerial(115200, 0);
		digitalWrite(23,0x01);
		digitalWrite(11,0x00);
		puthex((char)state->s[i],0);	
		_delay_ms(3);	
		#endif
	}	
	
	// perform the total number of selected rounds indicating 
	// the proper key in each round
	i=1;
	for(;rounds>1;--rounds)
	{
		aes_enc_round(state, &(ks->key[i]));
		++i;
	}
	
	aes_enc_lastround(state, &(ks->key[i]));
	
}


/*
 * gmix_column
 * 
 * The MixColumns step can be performed by multiplying a coordinate vector of 
 * four numbers in Rijndael's Galois field by the following circulant MDS 
 * matrix:
 * 	|b0| = | 2 3 1 1 | |a0|
 * 	|b1| = | 1 2 3 1 | |a1|
 * 	|b2| = | 1 1 2 3 | |a2|
 * 	|b3| = | 3 1 1 2 | |a3|
 * 
 * This can also be seen as the following:
 * 	b_0 = 2a_0 + 3a_1 + 1a_2 + 1a_3
 * 	b_1 = 1a_0 + 2a_1 + 3a_2 + 1a_3
 * 	b_2 = 1a_0 + 1a_1 + 2a_2 + 3a_3
 * 	b_3 = 3a_0 + 1a_1 + 1a_2 + 2a_3 
 * 
 * Refernece: http://en.wikipedia.org/wiki/Rijndael_mix_columns
 *  
 */
void gmix_column(uint8_t *r) 
{
        uint8_t a[4];
        uint8_t b[4];
        uint8_t c;
        uint8_t h;
        /* The array 'a' is simply a copy of the input array 'r'
         * The array 'b' is each element of the array 'a' multiplied by 2
         * in Rijndael's Galois field
         * a[n] ^ b[n] is element n multiplied by 3 in Rijndael's Galois field */ 
        for(c=0;c<4;c++) 
        {
                a[c] = r[c];
                /* h is 0xff if the high bit of r[c] is set, 0 otherwise */
                h = (uint8_t)((int8_t)r[c] >> 7); /* arithmetic right shift, thus shifting in either zeros or ones */
                b[c] = r[c] << 1; /* implicitly removes high bit because b[c] is an 8-bit char, so we xor by 0x1b and not 0x11b in the next line */
                b[c] ^= 0x1B & h; /* Rijndael's Galois field */
        }
        r[0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1]; /* 2 * a0 + a3 + a2 + 3 * a1 */
        r[1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2]; /* 2 * a1 + a0 + a3 + 3 * a2 */
        r[2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3]; /* 2 * a2 + a1 + a0 + 3 * a3 */
        r[3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0]; /* 2 * a3 + a2 + a1 + 3 * a0 */
}
