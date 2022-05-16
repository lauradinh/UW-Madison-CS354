/******************************************************************************
 * @file: functions.c
 *
 * WISC NETID       lmdinh
 * CANVAS USERNAME  Laura Dinh  
 * WISC ID NUMBER   9080660948   
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: YOUR PREFERED NAME (YOUR WISC EMAIL)
 * @modified: SUBMISSION DATE
 *****************************************************************************/
#include <stdio.h>
#include "functions.h"

// Some macros that may be useful to you 
#define MAX_USERNAME_LEN    32
#define MAX_EMAIL_LEN       32
#define MAX_DOMAIN_LEN      64
#define MIN_PASSWORD_LEN    8
#define MAX_PASSWORD_LEN    16
#define NEW_LINE_CHAR       10

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0 
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 
// Examples: IsLetter, IsDigit, Length, Find...

int Length(char arr[], size_t len){
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] == '\0') {
            break;    
        }
        else {
            count++;
        }
    }
    return count;
}

int IsLetter(char input) {
    if (input >= 'A' && input <= 'Z') {
        return 1;
    } else if (input >= 'a' && input <= 'z') {
        return 1;    
    } else {
        return 0;
    }
}

int IsDigit(char input) {
    if (input >= '0' && input <= '9') {
        return 1;
    }
    return 0;
}

int IsUpper(char input) {
    if (input >= 'A' && input <= 'Z') {
        return 1;
    }
    return 0;
}

int IsLower(char input) {
    if (input >= 'a' && input <= 'z') {
        return 1;
    }
    return 0;
}

int IsTopDomain(char arr[], int start_index) {
    if (arr[start_index] == '.' && arr[start_index+1] == 'e' && arr[start_index+2] == 'd' && arr[start_index+3] == 'u') {
        return 1;
    } else if (arr[start_index] == '.' && arr[start_index+1] == 'c' && arr[start_index+2] == 'o' && arr[start_index+3] == 'm') {
        return 1;
    } else if (arr[start_index] == '.' && arr[start_index+1] == 'n' && arr[start_index+2] == 'e' && arr[start_index+3] == 't') {
        return 1;
    } 
    return 0;
    
}

/******************************************************************************
 * Verification functions
 *****************************************************************************/

/*
 * A username must begin with a letter [A-Z, a-z], contain 32 characters
 * or less, and  may only consist of letters, underscores, or 
 * digits [A-Z, a-z, _, 0-9]. An error message is displayed if any of 
 * these conditions are not met. Only print the first applicable error 
 * message. 
 *
 * @param user : The username string
 * @param len : Size of the username input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Username(char user[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
    dbgprintf("This line only prints if DEBUG is set to 1\n"); 
    if (!IsLetter(user[0])) {
        printf(ERROR_01_USER_START_INVALID);
        return 0;
    }
    int size = Length(user, len);
    if (size > MAX_USERNAME_LEN) { 
        printf(ERROR_02_USER_LEN_INVALID);
        return 0;
    }
    for (int i = 0; i < size; i++) {
        if (!IsDigit(user[i]) && !IsLetter(user[i]) && user[i] != '_') {
            printf(ERROR_03_USER_CHARS_INVALID);
            return 0;        
        }
    }
    /* END MODIFYING CODE HERE */

    printf(SUCCESS_1_USER);
    return 1;
}

/*
 * An email address has four parts:
 *      name
 *          exists
 *          must start with letter
 *          max 32 characters
 *          may contain only letters and digits
 *      @ symbol
 *          exists
 *      domain name
 *          exists
 *          max of 64 characters
 *          composed of one or more subdomains separated by .
 *          subdomain must begin with a letter
 *          subdomains may contain only letters and digits
 *      top-level domain 
 *          must be [.edu, .com, .net]
 *
 * If the email address contains one or more errors print only the first
 * applicable error from the list.
 *
 * Note this task is based on a real world problem and may not be the best 
 * order to approach writing the code.
 *
 * @param email : The email string
 * @param len : Size of the email input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Email(char email[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
    int size = Length(email, len); // size of email
    
    int name_length = 0; // counter for size of name
    int email_at_index = -1; // index of @ symbol (-1 if there is no @ symbol)
    for (int i = 0; i < size; i++) { // counts the size of name
        if (email[i] == '@') { // has @ symbol
            email_at_index = i;
            break; 
        } 
        if (email[i] == '\0') { // does not have @ or domain
            break;
        }    
        name_length++;
    }
    
    if (IsTopDomain(email, size-4) && email_at_index == -1) { // has domain but not @
        name_length = 0;
        for (int i = 0; i < size-4; i++) {
            if (email[i] == '.') {
                break;   
            } 
            name_length++;
        }
    }
    
    // checks if name exists
    if (email[0] == '@') {
        printf(ERROR_04_EMAIL_MISSING_NAME);  // example @domain.com
        return 0;    
    }

    // checks for valid start of name
    if(!IsLetter(email[0])) {
        printf(ERROR_05_EMAIL_START_INVALID);
        return 0;
    }
       
    // checks for length of email name is valid
    if (name_length > MAX_EMAIL_LEN) {
        printf(ERROR_06_EMAIL_NAME_LEN_INVALID);
        return 0;    
    }
    
    // checks for chars in email name is valid
    for (int i = 0; i < name_length; i++) {
        if(!IsLetter(email[i]) && !IsDigit(email[i])) {
            printf(ERROR_07_EMAIL_NAME_CHARS_INVALID);
            return 0;
        }
    }   
    
    // checks if at symbol is missing
    if (email_at_index == -1) {
        printf(ERROR_08_EMAIL_MISSING_SYMBOL); // example mike.wisc.edu
        return 0;
    }

    // checks for domain name
    int domain_start = email_at_index + 1;
    for (int i = domain_start; i < size; i++) {
        if (email[i] == '.') {
            if(!IsDigit(email[i-1]) && !IsLetter(email[i-1])) {
                printf(ERROR_09_EMAIL_MISSING_DOMAIN); // example mike@.edu
                return 0;
            }
        }
      
    }
    
    // checks for email domain length     
    if (size - domain_start > MAX_DOMAIN_LEN) {
        printf(ERROR_10_EMAIL_DOMAIN_LEN_INVALID);
        return 0;
    }

    // checks for domain begins with letter
    for (int i = email_at_index; i < size; i++) {
        if(email[i] == '@') {
            if(!IsLetter(email[i+1])) {
                printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
                return 0; 
            }
        } 
        if (email[i] == '.') {
            if(!IsLetter(email[i+1])) {
                printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
                return 0;
            }
        }
    }
//    printf(ERROR_12_EMAIL_DOMAIN_CHARS_INVALID);
//    printf(ERROR_13_TOP_LEVEL_DOMAIN_INVALID);
    /* END MODIFYING CODE HERE */
    
    printf(SUCCESS_2_EMAIL);
    return 1;
}

/*
 * The following password requirements must be verified:
 *  - May use any character except spaces (i.e., "my password" is invalid)
 *  - Must contain at least 8 characters (i.e., "Password" has 8 characters 
 *    and is valid)
 *  - May have at most 16 characters (i.e., "1234567890Abcdef" has 16 
 *    characters and is valid)
 *  - Must contain at least one upper case character [A-Z]
 *  - Must contain at least one lower case character [a-z]
 *
 * @param pwd : The original password string
 * @param len : Size of the original password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Password(char pwd[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
    int size = Length(pwd, len);
    for (int i = 0; i < size; i++) {
        if (pwd[i] == ' ') {    
            printf(ERROR_14_PWD_SPACES_INVALID);
            return 0;
        }
    }
    if (size < MIN_PASSWORD_LEN) {
        printf(ERROR_15_PWD_MIN_LEN_INVALID);
        return 0;
    }
    if (size > MAX_PASSWORD_LEN) {
        printf(ERROR_16_PWD_MAX_LEN_INVALID);
        return 0;
    }
    int upper_count = 0;
    int lower_count = 0; 
    for (int i = 0; i < size; i++) {
        if (IsUpper(pwd[i])) {
            upper_count++;
        } else if (IsLower(pwd[i])) {
            lower_count++;
        }
    }
    if (upper_count == 0) {
        printf(ERROR_17_PWD_MIN_UPPER_INVALID);
        return 0;
    }
    if (lower_count == 0) { 
        printf(ERROR_18_PWD_MIN_LOWER_INVALID);
        return 0;
    }
    /* END MODIFYING CODE HERE */

    return 1;
}
/*
 * Original Password and the Reentered Password must match
 *
 * @param pwd1 : The original password string
 * @param len1 : Size of the original password input buffer
 * @param pwd2 : The reentered password string
 * @param len2 : Size of the renetered password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Passwords_Match(char pwd1[], size_t len1, char pwd2[], size_t len2) {

    /* BEGIN MODIFYING CODE HERE */
    int size1 = Length(pwd1, len1);
    int size2 = Length(pwd2, len2);
    if (size1 != size2) {
        printf(ERROR_19_PWD_MATCH_INVALID);
        return 0;
    }
    for (int i = 0; i < size1; i++) {
        if (pwd1[i] != pwd2[i]) {
            printf(ERROR_19_PWD_MATCH_INVALID);
            return 0; 
        }
    }
    /* END MODIFYING CODE HERE */

    printf(SUCCESS_3_PASSWORDS);
    return 1;
}

/******************************************************************************
 * I/O functions
 *****************************************************************************/

/*
 * Prompts user with an input and reads response from stdin
 *
 * @param message : Prompt displayed to the user
 * @param data : char array to hold user repsonse
