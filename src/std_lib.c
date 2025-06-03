#include "std_lib.h"

int div(int a, int b)
{
  int dividend = a;
  int divisor = b;
  int result = 0;
  int polarity = 1;

  if (divisor == 0) {
    return 0;
  }

  if (dividend < 0) {
    polarity = -polarity;
    dividend = -dividend;
  }
  if (divisor < 0) {
    polarity = -polarity;
    divisor = -divisor;
  }

  while (dividend >= divisor) {
    dividend -= divisor;
    result++;
  }

  return result * polarity;
}

int mod(int a, int b)
{
  int dividend = a;
  int divisor = b;

  if (divisor == 0) {
    return 0;
  }
  
  if (divisor < 0) {
    divisor = -divisor;
  }
  if (dividend < 0) {
    while (dividend <= -divisor) {
      dividend += divisor;
    }
  } else {
    while (dividend >= divisor) {
      dividend -= divisor;
    }
  }
  
  return dividend;
}

bool strcmp(char *str1, char *str2)
{
  char *s1 = str1;
  char *s2 = str2;
  
  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  
  return (*s1 == *s2);
}

void strcpy(char *dst, char *src)
{
  char* destination = dst;
  char* source = src;
  int i = 0;

  for (i = 0; source[i] != '\0'; i++) {
    destination[i] = source[i];
  }
  destination[i] = '\0';
}

void clear(byte *buf, unsigned int size)
{
  byte *buffer = buf;
  byte *end_ptr = buffer + size;
  
  while (buffer < end_ptr) {
    *buffer = 0;
    buffer++;
  }
}

void atoi(char *str, int *num)
{
  char* current_char = str;
  int value = 0;
  int polarity = 1;

  while (*current_char == ' ') {
    current_char++;
  }

  if (*current_char == '-') {
    polarity = -1;
    current_char++;
  } else if (*current_char == '+') {
    current_char++;
  }

  while (*current_char >= '0' && *current_char <= '9') {
    value = (value * 10) + (*current_char - '0');
    current_char++;
  }

  *num = value * polarity;
}

void itoa(int num, char *str)
{
  int number = num;
  char* buffer = str;
  int i = 0;
  int j = 0;
  bool is_negative = false;

  if (number == 0) {
    buffer[i++] = '0';
    buffer[i] = '\0';
    return;
  }

  if (number < 0) {
    is_negative = true;
    number = -number;
  }

  while (number > 0) {
    buffer[i++] = mod(number, 10) + '0';
    number = div(number, 10);
  }

  if (is_negative) {
    buffer[i++] = '-';
  }
  
  buffer[i] = '\0';

  i--;
  while (j < i) {
    char temp = buffer[j];
    buffer[j] = buffer[i];
    buffer[i] = temp;
    j++;
    i--;
  }
}
