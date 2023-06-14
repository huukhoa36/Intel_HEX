/******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
 
#include "lib.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************
 * PROTOTYPES
 ******************************************************************************/
 
/**
 * @brief      Convert 2 character from ASCII into DEC
 * @param[in]  Character with ASCII type
 * @param[in]  Character with ASCII type
 * @param[out] No
 * @return     The variable with decimal type
 */
static char Convert_ASCII_to_DEC(char char_1, char char_2);

/******************************************************************************
 * FUNTIONS
 ******************************************************************************/
 
static char Convert_ASCII_to_DEC(char char_1, char char_2)
{
	char retVal = 0;
	
	if((char_1 >= '0') && (char_1 <= '9'))
		char_1 = char_1 - '0';
		
	if((char_1 >= 'A') && (char_1 <= 'F'))
		char_1 = char_1 - 'A' + 10;
	
	if((char_2 >= '0') && (char_2 <= '9'))
		char_2 = char_2 - '0';
		
	if((char_2 >= 'A') && (char_2 <= 'F'))
		char_2 = char_2 - 'A' + 10;
		
	retVal = ((char_1 & 0x0F) << 4) | (char_2 & 0x0F);
	
	return retVal;
}

Error_type check_Start_code(char data[])
{
	Error_type retVal = NO_ERROR;
	
	if(data[0] == ':')
		retVal = NO_ERROR;		
 	else 
		retVal = ERROR_START_CODE;

	return retVal;
}

Error_type check_Byte_count(char data[])
{
	unsigned char byte_count_value = 0;
	unsigned char number_of_data = 0;
	Error_type retVal = NO_ERROR;
	
	byte_count_value = Convert_ASCII_to_DEC(data[1], data[2]);
	
	number_of_data = strlen(data) - NUMBER_OF_START_CODE \
									- NUMBER_OF_BYTE_COUNT \
									- NUMBER_OF_ADDRESS \
									- NUMBER_OF_RECORD_TYPE \
									- NUMBER_OF_CHECK_SUM \
									- NUMBER_OF_END_LF_CHARACTER;
	
	if((byte_count_value * 2) == number_of_data)
		retVal = NO_ERROR;
	else
		retVal = ERROR_BYTE_COUNT;
	
	return retVal;
}

Error_type check_Checksum(char data[])
{
	unsigned char check_sum = 0;
	unsigned char check_sum_value = 0;
	unsigned char index = 0;
	Error_type retVal = NO_ERROR;
	
	for(index = 1; index <= (strlen(data) - NUMBER_OF_START_CODE \
		- NUMBER_OF_CHECK_SUM - NUMBER_OF_END_LF_CHARACTER); index = index + 2)
	{
		check_sum += Convert_ASCII_to_DEC(data[index], data[index + 1]);
	}
	
	/* two's complement */
	check_sum = ~check_sum + 1;
	
	check_sum_value = Convert_ASCII_to_DEC(data[strlen(data) - 3], data[strlen(data) - 2]);
	
	if(check_sum_value == check_sum)
		retVal = NO_ERROR;
	else
		retVal = ERROR_CHECKSUM;
		
	return retVal;
}

Error_type check_Hexa(char data[])
{
	unsigned char index = 0;
	Error_type retVal = NO_ERROR;
	
	for(index = 1; index <= (strlen(data) - NUMBER_OF_START_CODE \
		- NUMBER_OF_END_LF_CHARACTER); index++)
	{
		if(((data[index] >= '0') && (data[index] <= '9')) || ((data[index] >= 'A') && (data[index] <= 'F')))
		{
			retVal = NO_ERROR;
		} else {
			retVal = ERROR_HEXA;
		}
	}
	
	return retVal;
}

void parse_data(char data[], int count)
{
	unsigned char record_type_value = 0;
	unsigned char index = 0;
	
	record_type_value = Convert_ASCII_to_DEC(data[7], data[8]);
	
	//printf("Line\t Address\t Data\n", record_type_value);
	
	if(record_type_value == 0)
	{
		printf("\nLine %d: ", count);
		
		//print address
		for(index = 3; index < 7; index++)
		{
			printf("%c", data[index]);
		}
		
		printf("   -   ");
		
		//print data
		for(index = 9; index <= (strlen(data) - ERROR_CHECKSUM \
		- NUMBER_OF_END_LF_CHARACTER); index++)
		{
			printf("%c", data[index]);
		}
	}	
}

/******************************************************************************
 * EOF
 ******************************************************************************/
