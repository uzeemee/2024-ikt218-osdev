extern "C" void kernel_main() {
    const char *welcome_message = "Hello World!";
    volatile char *video_memory = (volatile char*)0xb8000;
    unsigned int i = 0, j = 0;

    // Renser skjermen
    while(i < 80 * 25 * 2) {
        video_memory[i] = ' '; // Bruker mellomrom for å rense skjermen
        video_memory[i+1] = 0x07; // Standard grå tekst på svart bakgrunn
        i += 2;
    }

    i = 0;

    // Skriver ut velkomstmeldingen til skjermen
    while(welcome_message[j] != '\0') {
        video_memory[i] = welcome_message[j];
        video_memory[i+1] = 0x0A; // Grønn tekst
        j++;
        i += 2;
    }
}