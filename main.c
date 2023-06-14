/******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lib.h"

/******************************************************************************
 * MAIN FUNCTION
 ******************************************************************************/
 
int main()
{
	FILE* fptr;
	char read_data[50];
	int count = 0;
	Error_type status = NO_ERROR;
	bool status_error = false;
	
	// opening the file in read mode
    fptr = fopen("Blinkled.hex", "r");
  
    // checking if the file is opened successfully
    if (fptr == NULL) {
        printf("The file is not opened. The program will now exit.");
        exit(0);
    } else {
    	printf("The file is now opened \n");
    	
    	// Read data from the file
        while (fgets(read_data, 50, fptr) != NULL) 
		{
			count++;
			
			status = check_Start_code(read_data);
			if(status == ERROR_START_CODE)
			{
				printf("Line %d: error start code\n", count);
				status_error = true;
			}
			
			status = check_Byte_count(read_data);
			if(status == ERROR_BYTE_COUNT)
			{
				printf("Line %d: error byte count\n", count);
				status_error = true;
			}	
				
			status = check_Checksum(read_data);
			if(status == ERROR_CHECKSUM)
			{
				printf("Line %d: error checksum\n", count);
				status_error = true;
			}
				
			status = check_Hexa(read_data);
			if(status == ERROR_HEXA)
			{
				printf("Line %d: error hexa\n", count);
				status_error = true;
			}
				
			// if have no error, print data
			if(status_error == false)
			{
				parse_data(read_data, count);
			}
        }
	}
	
	return 0;
}

/******************************************************************************
 * EOF
 ******************************************************************************/
