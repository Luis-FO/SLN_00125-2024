#ifndef DECODE_H
#define DECODE_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

char* readFile(const char* filename);
char* base64_decode(const char* encoded_message);
char* reverse(char* decoded_message);

#endif