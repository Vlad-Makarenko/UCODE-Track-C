
void mx_printchar(char c);

void mx_print_alphabet(void){
    for (int i = 65; i < 91; ++i) {
        mx_printchar(i);
        i++;
        int tmp = i + 32;
        mx_printchar(tmp);
    }
    mx_printchar('\n');
}

