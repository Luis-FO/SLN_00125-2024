// #include "decode.h"

// int main(int argc, char* argv[]) {

//     const char* filename;

//     // Verifica se um argumento foi fornecido
//     if (argc == 2) {
//         filename = argv[1];
//     } else {
//         printf("Arquivo não especificado!\n");
//         return -1;
//     }

//     // Lê arquivo message.txt
//     char* encoded_message = readFile(filename);

//     // Decodifica a mensagem
//     char* decoded_message_base64 = base64(encoded_message);

//     // Inverte a mensagem
//     char* final_message = reverse(decoded_message_base64);

//     // Imprimi a mensagem decodificada e invertida
//     printf("Mensagem decodificada e invertida: %s\n", final_message);

//     // Liberar memória alocada dinamicamente
//     free(encoded_message);
//     free(decoded_message_base64);
//     free(final_message);
//     getchar();
//     return 0;
// }



