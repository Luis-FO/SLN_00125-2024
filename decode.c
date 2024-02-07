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
char* base64(char* encoded_message) {
    // Caracteres Base64 padrão
    const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    int in_len = strlen(encoded_message);
    int out_len = (in_len * 3) / 4;

    // Aloca espaço para a string decodificada
    char *decoded_message = (char*)malloc(out_len + 1);

    // Índices para percorrer a string codificada e decodificada
    int i, j = 0;

    // Array para armazenar os valores decodificados de cada bloco de 4 caracteres codificados
    int b[4];

    // Loop sobre a string codificada em blocos de 4 caracteres
    for (i = 0; i < in_len; i += 4) {
        // Converte os caracteres codificados para índices na tabela Base64
        b[0] = strchr(base64_chars, encoded_message[i]) - base64_chars;
        b[1] = strchr(base64_chars, encoded_message[i + 1]) - base64_chars;
        b[2] = strchr(base64_chars, encoded_message[i + 2]) - base64_chars;
        b[3] = strchr(base64_chars, encoded_message[i + 3]) - base64_chars;

        // Combina os valores decodificados e os armazena na string decodificada
        decoded_message[j++] = (b[0] << 2) | (b[1] >> 4);
        decoded_message[j++] = (b[1] << 4) | (b[2] >> 2);
        decoded_message[j++] = (b[2] << 6) | b[3];
    }

    // Adiciona o caractere nulo no final da string decodificada
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

