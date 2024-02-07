#include "decode.h"
int main() {

    // Lê arquivo message.txt
    char* encoded_message = readFile("message.txt");

    // Decodifica a mensagem
    char* decoded_message_base64 = base64(encoded_message);

    // Inverte a mensagem
    char* final_message = reverse(decoded_message_base64);

    // Imprimi a mensagem decodificada e invertida
    printf("Mensagem decodificada e invertida: %s\n", final_message);

    // Liberar memória alocada dinamicamente
    free(encoded_message);
    free(decoded_message_base64);
    free(final_message);
    getchar();
    return 0;
}



