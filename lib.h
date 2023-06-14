/******************************************************************************
 * @file                    lib.h
 * @brief                   Header file for lib.c
 * @author                  Khoa
 ******************************************************************************/

#ifndef _LIB_H_
#define _LIB_H_

/******************************************************************************
 * DEFINITIONS
 ******************************************************************************/

#define NUMBER_OF_START_CODE       1U
#define NUMBER_OF_BYTE_COUNT       2U
#define NUMBER_OF_ADDRESS          4U
#define NUMBER_OF_RECORD_TYPE      2U
#define NUMBER_OF_CHECK_SUM        2U
#define NUMBER_OF_END_LF_CHARACTER 1U

/******************************************************************************
 * TYPEDEF
 ******************************************************************************/

typedef enum {
	NO_ERROR,
	ERROR_START_CODE,
	ERROR_BYTE_COUNT,
	ERROR_CHECKSUM,
	ERROR_HEXA,
}Error_type;

/******************************************************************************
 * PROTOTYPES
 ******************************************************************************/
 
/**
 * @brief      Check Start code
 * @param[in]  data The element of each line
 * @param[out] No
 * @return     ERROR_START_CODE
 */
Error_type check_Start_code(char data[]);

/**
 * @brief      Check Byte count
 * @param[in]  data The element of each line
 * @param[out] No
 * @return     ERROR_BYTE_COUNT
 */
Error_type check_Byte_count(char data[]);

/**
 * @brief      Check Checksum
 * @param[in]  data The element of each line
 * @param[out] No
 * @return     ERROR_CHECKSUM
 */
Error_type check_Checksum(char data[]);

/**
 * @brief      Check all character in each line is HEXA type
               Except the first character
 * @param[in]  data The element of each line
 * @param[out] No
 * @return     ERROR_HEXA
 */
Error_type check_Hexa(char data[]);

/**
 * @brief      print Address and Data of Data Record Type
 * @param[in]  data The element of each line
 * @param[out] Address and Data
 * @return     No
 */
void parse_data(char data[], int count);

#endif /* _LIB_H_ */

/******************************************************************************
 * EOF
 ******************************************************************************/
