void write_character(unsigned char c, unsigned char forecolour, unsigned char backcolour, int x, int y);
struct TextColors {
    unsigned char black;          // 0
    unsigned char blue;           // 1
    unsigned char green;          // 2
    unsigned char cyan;           // 3
    unsigned char red;            // 4
    unsigned char magenta;        // 5
    unsigned char brown;          // 6
    unsigned char lightGrey;      // 7
    unsigned char darkGrey;       // 8
    unsigned char lightBlue;      // 9
    unsigned char lightGreen;     // 10
    unsigned char lightCyan;      // 11
    unsigned char lightRed;       // 12
    unsigned char lightMagenta;   // 13
    unsigned char lightBrown;     // 14
    unsigned char white;          // 15
};

void init_colors(struct TextColors *colors);