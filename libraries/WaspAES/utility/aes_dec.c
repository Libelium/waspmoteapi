/* aes.c */
/*
    This file is part of the AVR-Crypto-Lib.
    Copyright (C) 2008, 2009  Daniel Otte (daniel.otte@rub.de)
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

#include <stdint.h>
#include <string.h>
#include "aes.h"
#include "aes_invsbox.h"
#include "aes_dec.h"
#include <avr/pgmspace.h>
#include <util/delay.h>

void aes_invshiftrow(void* data, uint8_t shift){
	uint8_t tmp[4];
	tmp[0] = ((uint8_t*)data)[(4+0-shift)&3];
	tmp[1] = ((uint8_t*)data)[(4+1-shift)&3];
	tmp[2] = ((uint8_t*)data)[(4+2-shift)&3];
	tmp[3] = ((uint8_t*)data)[(4+3-shift)&3];
	memcpy(data, tmp, 4);
}

void aes_invshiftcol(void* data, uint8_t shift){
	uint8_t tmp[4];
	tmp[0] = ((uint8_t*)data)[ 0];
	tmp[1] = ((uint8_t*)data)[ 4];
	tmp[2] = ((uint8_t*)data)[ 8];
	tmp[3] = ((uint8_t*)data)[12];
	((uint8_t*)data)[ 0] = tmp[(4-shift+0)&3];
	((uint8_t*)data)[ 4] = tmp[(4-shift+1)&3];
	((uint8_t*)data)[ 8] = tmp[(4-shift+2)&3];
	((uint8_t*)data)[12] = tmp[(4-shift+3)&3];
}


static
void aes_dec_round(aes_cipher_state_t* state, const aes_roundkey_t* k)
{
	uint8_t tmp[16];
	uint8_t i;
	uint8_t t,u,v,w;
	
	
	/// *** STEP 1: keyAdd ***
	for(i=0; i<16; ++i)
	{
		tmp[i] = state->s[i] ^ k->ks[i];
	}
		
	#ifdef ENCRYPTION_DEBUG
	beginSerial(115200, 0);
	digitalWrite(23,0x01);
	digitalWrite(11,0x00);
	printString("\n\n*** STEP 1: keyAdd    --> ",  0);	
	for(i=0; i<16; ++i)
	{
		puthex((char)tmp[i],0);	
		_delay_ms(3);
	}
	#endif
	
	
	/// *** STEP 2: mixColums ***
	inv_mix_column(&tmp[0]);
	inv_mix_column(&tmp[4]);
	inv_mix_column(&tmp[8]);
	inv_mix_column(&tmp[12]);
	
	// copy result 
	for(i=0; i<16; ++i)
	{	
		state->s[i] = tmp[i];
	}	
	
	#ifdef ENCRYPTION_DEBUG
	printString("\n*** STEP 2: mixColums --> ",  0);
	_delay_ms(3);	
	for(i=0; i<16; ++i)
	{		
		puthex((char)state->s[i],0);	
		_delay_ms(3);
	}		
	#endif
	
	
	/// *** STEP 3: shiftRows ***
	aes_invshiftcol(state->s+1, 1);
	aes_invshiftcol(state->s+2, 2);
	aes_invshiftcol(state->s+3, 3);		
	
	#ifdef ENCRYPTION_DEBUG
	printString("\n*** STEP 3: shiftRows --> ",  0);
	_delay_ms(3);	
	for(i=0; i<16; ++i)
	{		
		puthex((char)state->s[i],0);	
		_delay_ms(3);
	}
	#endif
	
	
	/// *** STEP 4: subBytes ***
	for(i=0; i<16; ++i)
	{
		state->s[i] = pgm_read_byte(aes_invsbox+state->s[i]);
	}	
	
	#ifdef ENCRYPTION_DEBUG
	printString("\n*** STEP 4: subBytes  --> ",  0);
	_delay_ms(3);	
	for(i=0; i<16; ++i)
	{		
		puthex((char)state->s[i],0);	
		_delay_ms(3);
	}
	printString("\n",  0);
	#endif
}


static
void aes_dec_firstround(aes_cipher_state_t* state, const aes_roundkey_t* k)
{
	uint8_t i;
	
	/// *** STEP 1: keyAdd ***
	for(i=0; i<16; ++i)
	{
		state->s[i] ^= k->ks[i];
	}
	
	#ifdef ENCRYPTION_DEBUG
	beginSerial(115200, 0);
	digitalWrite(23,0x01);
	digitalWrite(11,0x00);	
	printString("\n\n*** STEP 1: keyAdd    --> ",  0);	
	_delay_ms(3);	
	for(i=0; i<16; ++i)
	{
		puthex((char)state->s[i],0);	
		_delay_ms(3);
	}
	#endif
	
	
	/// *** STEP 2: invert shiftRows ***
	aes_invshiftcol(state->s+1, 1);
	aes_invshiftcol(state->s+2, 2);
	aes_invshiftcol(state->s+3, 3);	
		
	#ifdef ENCRYPTION_DEBUG
	printString("\n*** STEP 2: shiftRows --> ",  0);
	_delay_ms(3);	
	for(i=0; i<16; ++i)
	{		
		puthex((char)state->s[i],0);	
		_delay_ms(3);
	}		
	#endif
	
	
	/// *** STEP 3: subBytes ***
	for(i=0; i<16; ++i)
	{
		state->s[i] = pgm_read_byte(aes_invsbox+state->s[i]);
	}
	
	#ifdef ENCRYPTION_DEBUG
	printString("\n*** STEP 3: subBytes  --> ",  0);
	_delay_ms(3);	
	for(i=0; i<16; ++i)
	{		
		puthex((char)state->s[i],0);	
		_delay_ms(3);
	}
	#endif
}

/*
 * aes_decrypt_core
 * 
 * This function performs the steps to undo the encryption 
 * 
 */
void aes_decrypt_core(	aes_cipher_state_t* state, 
						const aes_genctx_t* ks, 
						uint8_t rounds)
{
	uint8_t i;
	
	// Firstly, undo the final encryption step 
	// using the round keys from backwards
	aes_dec_firstround(state, &(ks->key[i=rounds]));
	
	// Secondly, undo all the remaining rounds
	// using the round keys from backwards
	for(;rounds>1;--rounds)
	{
		--i;
		aes_dec_round(state, &(ks->key[i]));
	}
	
	// Finally add the key to get the original message decrypted from the input
	for(i=0; i<16; ++i)
	{
		state->s[i] ^= ks->key[0].ks[i];
	}		
}





/*
 * gmul
 * 
 * Multiplication in Rijndael's galois field is a little more complicated. The 
 * procedure is as follows:
 * 
 * 	- 	Take two eight-bit numbers, a and b, and an eight-bit product p
 * 	- 	Set the product to zero.
 * 	- 	Make a copy of a and b, which we will simply call a and b in the rest of 
 * 		this algorithm
 * 	-	Run the following loop eight times:
 * 			1. If the low bit of b is set, exclusive or the product p by the 
 * 			value of a
 * 			2. Keep track of whether the high (eighth from left) bit of a is set 
 * 			to one
 * 			3. Rotate a one bit to the left, discarding the high bit, and making 
 * 			the low bit have a value of zero
 * 			4. If a's hi bit had a value of one prior to this rotation, 
 * 			exclusive or a with the hexadecimal number 0x1b
 * 			5. Rotate b one bit to the right, discarding the low bit, and making
 * 			the high (eighth from left) bit have a value of zero. 
 *	-	The product p now has the product of a and b 
 * 
 * Reference: http://www.samiam.org/galois.html
 */
unsigned char gmul(unsigned char a, unsigned char b) 
{
	unsigned char p = 0;
	unsigned char counter;
	unsigned char hi_bit_set;
	for(counter = 0; counter < 8; counter++) {
		if((b & 1) == 1) 
			p ^= a;
		hi_bit_set = (a & 0x80);
		a <<= 1;
		if(hi_bit_set == 0x80) 
			a ^= 0x1b;		
		b >>= 1;
	}
	return p;
}

/*
 * inv_mix_column
 * 
 * The MixColumns operation has the following inverse (numbers are decimal):
 * 	|r0| = | 14  11  13   9 | |a0|
 * 	|r1| = |  9  14  11  13 | |a1|
 * 	|r2| = | 13   9  14  11 | |a2|
 * 	|r3| = | 11  13   9  14 | |a3|
 * 
 * This can also be seen as the following:
 * 	r_0 = 14a_0 + 11a_1 + 13a_2 + 9a_3
 * 	r_1 = 9a_0 + 14a_1 + 11a_2 + 13a_3
 * 	r_2 = 13a_0 + 9a_1 + 14a_2 + 11a_3
 * 	r_3 = 11a_0 + 13a_1 + 9a_2 + 14a_3 
 * 
 * Refernece: http://en.wikipedia.org/wiki/Rijndael_mix_columns
 *  
 */
void inv_mix_column(unsigned char *r) 
{
	unsigned char a[4];
	unsigned char c;
	for(c=0;c<4;c++) 
	{
		a[c] = r[c];
	}
	
	r[0] = gmul(a[0],14) ^ gmul(a[3],9) ^ gmul(a[2],13) ^ gmul(a[1],11);
	r[1] = gmul(a[1],14) ^ gmul(a[0],9) ^ gmul(a[3],13) ^ gmul(a[2],11);
	r[2] = gmul(a[2],14) ^ gmul(a[1],9) ^ gmul(a[0],13) ^ gmul(a[3],11);
	r[3] = gmul(a[3],14) ^ gmul(a[2],9) ^ gmul(a[1],13) ^ gmul(a[0],11);
}

