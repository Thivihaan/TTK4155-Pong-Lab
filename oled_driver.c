#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>


#include "fonts.h"
#include "oled_driver.h"
#include "spi_driver.h"

void oled_write_command(uint8_t command){

    PORTB &= ~(1 << OLED_DC_PIN);

    spi_write_byte(command, SPI_SLAVE_OLED);
}

void oled_write_data(uint8_t data){

    PORTB |= (1 << OLED_DC_PIN);

    spi_write_byte(data, SPI_SLAVE_OLED);
}

void oled_init(void){

    DDRB |= (1 << OLED_DC_PIN);

    // 1. Éteindre l'écran pendant la configuration
    oled_write_command(0xAE); // Display OFF (Sleep Mode)[cite: 27, 39]

    // 2. Configurer l'horloge et le diviseur d'affichage
    oled_write_command(0xD5); // Command: Set Display Clock Divide Ratio / Osc. Freq.[cite: 34, 42]
    oled_write_command(0xA0); // Diviseur = 1, Fréquence oscillateur[cite: 34]

    // 3. Définir le ratio de multiplexage (64 MUX pour 128x64)
    oled_write_command(0xA8); // Command: Set Multiplex Ratio[cite: 33]
    oled_write_command(0x3F); // 64 MUX (63d)[cite: 33]

    // 4. Définir le décalage d'affichage (Display Offset)
    oled_write_command(0xD3); // Command: Set Display Offset[cite: 33, 39]
    oled_write_command(0x00); // Pas de décalage[cite: 33]

    // 5. Définir la ligne de départ de l'affichage
    oled_write_command(0x40); // Ligne 0[cite: 33]

    // 6. Mode d'adressage mémoire (Page Addressing Mode)
    oled_write_command(0x20); // Command: Set Memory Addressing Mode[cite: 32]
    oled_write_command(0x02); // 0x02 = Page Addressing Mode[cite: 32]

    // 7. Orientation de l'écran (Vos 2 commandes d'orientation)
    oled_write_command(0xA1); // Segment Re-map (Miroir horizontal)[cite: 33, 38]
    oled_write_command(0xC8); // COM Scan Direction (Miroir vertical / 180°)[cite: 33, 39]

    // 8. Configuration matérielle des broches COM
    oled_write_command(0xDA); // Command: Set COM Pins Hardware Configuration
    oled_write_command(0x12); // Configuration alternative[cite: 33, 43]

    // 9. Régler le contraste (Luminosité)
    oled_write_command(0x81); // Command: Set Contrast Control
    oled_write_command(0xFF); // Luminosité maximale (0x00 à 0xFF)[cite: 27, 38]

    // 10. Temps de précharge (Pre-charge period)
    oled_write_command(0xD9); // Command: Set Pre-charge Period[cite: 34, 42]
    oled_write_command(0xF1); // Phase 1 & Phase 2 timing[cite: 34]

    // 11. Niveau VCOMH Deselect
    oled_write_command(0xDB); // Command: Set VCOMH Deselect Level[cite: 34, 45]
    oled_write_command(0x34); // ~0.78 x VCC[cite: 34]

    // 12. Mode d'affichage normal
    oled_write_command(0xA4); // Suivre le contenu de la GDDRAM (Resume to RAM content)[cite: 27, 38]
    oled_write_command(0xA6); // Affichage normal (1 = pixel allumé)[cite: 27, 39]

    oled_clear_display();

    oled_write_command(0xAF);

}

void oled_go_to_line(uint8_t line){ 
    if(line > 7){
        line = 7;
    } 
    oled_write_command(0xB0 | line); // 
}

void oled_go_to_column(uint8_t column){
    if (column > 127){
        column = 127;
    }
    // Lower nibble
    oled_write_command(0x00 | (column & 0x0F));

    // Higher nibble
    oled_write_command(0x10 | ((column >> 4) & 0x0F));

}

void oled_write_char(char c) {
    if (c < 32 || c > 127){
        c = '?';
    }

    uint8_t index = c - 32;

    // Parcourir les 8 colonnes du caractère
    for (uint8_t i = 0; i < 8; i++) {
        // Lecture de l'octet dans la mémoire PROGMEM
        uint8_t byte = pgm_read_byte(&(font8[index][i]));
        
        // Envoi à l'écran OLED
        oled_write_data(byte);
    }
}


// AI written 
void oled_clear_display(void) {
    for (uint8_t page = 0; page < 8; page++) {
        // 1. Envoyer manuellement les commandes pour se placer au début de la page
        oled_write_command(0xB0 + page); // Définit la page de 0 à 7[cite: 32]
        oled_write_command(0x00);        // Colonne 0 (4 bits de poids faible)[cite: 32]
        oled_write_command(0x10);        // Colonne 0 (4 bits de poids fort)[cite: 32]
        
        // 2. Écrire 128 fois 0x00 pour vider toute la largeur de cette page
        for (uint8_t col = 0; col < 128; col++) {
            oled_write_data(0x00);
        }
    }
}

void oled_printf(const char* str) {
    // Boucle tant qu'on n'a pas atteint la fin de la chaîne (caractère nul '\0')
    while (*str != '\0') {
        oled_write_char(*str); // Affiche le caractère pointé
        str++;                 // Avance le pointeur vers le caractère suivant
    }
}

