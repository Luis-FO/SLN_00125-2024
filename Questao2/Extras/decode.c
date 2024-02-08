#include "decode.h"

// Implementação da função readFile
char* readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)malloc(file_size + 1);
    if (content == NULL) {
        perror("Erro de alocação de memória");
        exit(EXIT_FAILURE);
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0';

    fclose(file);

    return content;
}


/***
 * @brief Função para decodificar uma string usando Base64
 * Ref: https://stackoverflow.com/questions/342409/how-do-i-base64-encode-decode-in-c
*/
char* base64_decode(const char* encoded_message) {
    const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    int in_len = strlen(encoded_message);
    int out_len = (in_len * 3) / 4;

    // Verifica e ajusta o comprimento de saída se houver caracteres de preenchimento
    if (encoded_message[in_len - 1] == '=') {
        out_len--;
        if (encoded_message[in_len - 2] == '=') {
            out_len--;
        }
    }

    char *decoded_message = (char*)malloc(out_len + 1);
    int i, j = 0;
    int b[4];

    for (i = 0; i < in_len; i += 4) {
        for (int k = 0; k < 4; k++) {
            // Ignora caracteres de preenchimento
            if (encoded_message[i + k] != '=') {
                b[k] = strchr(base64_chars, encoded_message[i + k]) - base64_chars;
            } else {
                b[k] = 0; // Preenchimento é tratado como zero
            }
        }

        decoded_message[j++] = (b[0] << 2) | (b[1] >> 4);
        decoded_message[j++] = (b[1] << 4) | (b[2] >> 2);
        decoded_message[j++] = (b[2] << 6) | b[3];
    }

    decoded_message[j] = '\0';

    return decoded_message;
}



/***
 * @brief Função para inverter uma string
*/
char* reverse(char* decoded_message) {
    // Obtém o comprimento da string
    int length = strlen(decoded_message);

    // Aloca espaço para a string invertida, incluindo o caractere nulo
    char* reversed_message = (char*)malloc(length + 1);

    if (reversed_message == NULL) {
        perror("Erro de alocação de memória");
        exit(EXIT_FAILURE);
    }

    // Inverte a string
    for (int i = 0, j = length - 1; i < length; i++, j--) {
        reversed_message[i] = decoded_message[j];
    }

    reversed_message[length] = '\0';

    // Retorna a string invertida
    return reversed_message;
}

