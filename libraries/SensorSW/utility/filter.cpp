/*
 *  Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
   
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version:		3.0
 *  Design:			Ahmad Saad
 * */

//!*************************************************************************************
//! Includes
//!*************************************************************************************

#include "filter.h"

#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif


//!*************************************************************************************
//! Filter Object
//!*************************************************************************************
filterClass myFilter;


//!*************************************************************************************
//!	Name:	filterClass()										
//!	Description: Class contructor		
//!	Param : void														
//!	Returns: void							
//!*************************************************************************************
filterClass::filterClass(){}


//!*************************************************************************************
//!	Name:	median()										
//!	Description: Class contructor		
//!	Param : float* array: values to filter
//!			 uint8_t length: length of the vector
//!	Returns: void							
//!*************************************************************************************
float filterClass::median(float* array, uint8_t length)
{
	int k,l,m,n;
	float aux[length];

	// Initialization of the auxiliar array
	for(k=0;k<length;k++) aux[k]=-100000;
	aux[0] = array[0];

	// Ordering of the sensor from lower to higher value
	for (l=1;l<length;l++)
	{
		for(m=0;m<l+1;m++)
		{
			if(array[l]>aux[m])
			{
				for(n=length-1;n>m;n--) aux[n]=aux[n-1];
				aux[m]=array[l];
				m=l+1;
				continue;
			}
		}
	}
	
	// The value in the central position of the array is returned
	return aux[int(length/2)];
}

