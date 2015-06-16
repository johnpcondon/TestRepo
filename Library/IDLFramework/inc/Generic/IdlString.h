#ifndef IDLSTRING_H_
#define IDLSTRING_H_

static int concat(char *s1,char *s2)
{
	int idx = 0;
	while(*s1!='\0')  
	{			 
		s1++; idx++;
	}
	while(*s2!='\0')                                
	{
		*s1=*s2;                                 
		s1++; idx++;                                         
		s2++;                                         
	}
	*s1='\0';
	return idx;
}

/* A utility function to reverse a string  */
//static void reverse(char str[], int length)
//{
//	int start = 0;
//	int end = length -1;
//	while (start < end)
//	{
//			swap(*(str+start), *(str+end));
//			start++;
//			end--;
//	}
//}

// Implementation of itoa()
static char* itoaHex(int num, char* str)
{
		int base = 16;
    int i = 0;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[0] = '0';
        str[0] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        num = -num;
    }
 
    // Process individual digits
		i = 1;
    while (num != 0)
    {
        int rem = num % base;
        str[i--] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // Reverse the string
    //reverse(str, i);
 
    return str;
}

#endif


