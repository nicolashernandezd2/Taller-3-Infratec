

#include <stdio.h>
#include <stdlib.h>

// Nombre: Nicolás Hernández Derch
// Código: 202322148
// Correo: n.hernandezd2@uniandes.edu.co

void insertarBits(char *mensajeOut, unsigned char bits_a_insertar, int k, int numero_componente_de_insercion) {
    int pos_insercion_bits = numero_componente_de_insercion * k;           // esta es la posición global (en bits) donde se insertan estos k bits
    int indice_byte = pos_insercion_bits / 8;              // este es el indice del byte en mensajeOut donde inicia la inserción
    int bits_insertados = pos_insercion_bits % 8;              // este es el numero de bits ya insertados en ese byte
    int disponible = 8 - bits_insertados;                   // y este es, el espacio disponible en el byte actual  (en bits tambien)

    if (k <= disponible) {
        mensajeOut[indice_byte] |= (bits_a_insertar & ((1 << k) - 1)) << (disponible - k);
    } 
    else {
        int bits_en_actual = disponible;             // estos son los bits que caben en el byte actual
        int bits_en_siguiente = k - disponible;              // y estos son los Bits que deben ir en el siguiente byte
        
        unsigned char parte1 = (bits_a_insertar & ((1 << k) - 1)) >> bits_en_siguiente;  // sacamos los bits que van en el byte actual
        mensajeOut[indice_byte] |= parte1;   
        
        unsigned char parte2 = bits_a_insertar & ((1 << bits_en_siguiente) - 1);  // sacamos los bits que van en el siguiente byte
        mensajeOut[indice_byte + 1] |= parte2 << (8 - bits_en_siguiente);
    }
}


void procesarImagen(unsigned char *imagenIn, char *mensajeOut, int numero_pixeles, int k) {
    int totalComponentes = numero_pixeles * 3;  
    for (int i = 0; i < totalComponentes; i++) {
        
        unsigned char bits = imagenIn[i] & ((1 << k) - 1);
        
        insertarBits(mensajeOut, bits, k, i);
    }
}

int main() {
    int numero_pixeles, k;
    
    printf("Ingrese el número de pixeles de la imagen: ");
    scanf("%d", &numero_pixeles);
    printf("Ingrese el número de bits escondidos por componente: ");
    scanf("%d", &k);
    
    int totalComponentes = numero_pixeles * 3;
    int tamanio_mensaje = (totalComponentes * k) / 8;
    
    unsigned char *imagenIn = (unsigned char *) calloc(totalComponentes, sizeof(unsigned char));
    char *mensajeOut = (char *) calloc(tamanio_mensaje, sizeof(char));
    
    printf("Ingrese los valores en hexa de cada componente:\n");
    for (int i = 0; i < totalComponentes; i++) {
        scanf("%X", &imagenIn[i]);
    }
    
    procesarImagen(imagenIn, mensajeOut, numero_pixeles, k);
    
    printf("el mensaje oculto es: ");
    
    for (int i = 0; i < tamanio_mensaje; i++) {
        printf("%c", mensajeOut[i]);
    }
    printf("\n");
    
    free(imagenIn);
    free(mensajeOut);
    
    return 0;
}