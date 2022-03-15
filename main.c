#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

size_t f_size;

void decrypt(char *str, int key){
    int i;
    for(i = 0; i < strlen(str); i++){
        if(!strchr("abcdefghijklmnopqrstuvwxyz", str[i])) continue;
        str[i] -= key;
        if(str[i] < 'a') str[i] = 'z' - ('a' - str[i]) + 1;
    }
}

int find_key(char *str){
    char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    float values[26] = { 0.098f, 0.01f, 0.05f, 0.035f, 0.12f, 0.01f, 0.008f, 0.005f, 0.1f,  0.002f, 0.001f, 0.043f, 0.038f, 0.07f, 0.041f, 0.038f, 0.0f, 0.072f, 0.043f, 0.058f, 0.059f, 0.01f, 0.0f, 0.001f, 0.001f, 0.008f};
    int i, j, k;
    int flag = 0;
    char *input = (char*) malloc(f_size);
    float scores[26] = { 0 }, max;
    for(i = 1; i < 26; i++){
        strcpy(input, str);
        for(j = 0; j < strlen(input); j++){
            if(!strchr("abcdefghijklmnopqrstuvwxyz", input[j])) continue;
            input[j] -= i;
            if(input[j] < 'a') input[j] = 'z' - ('a' - input[j]) + 1;
            for(k = 0; k < 26; k ++) if(input[j] == letters[k]) scores[i] += values[k];
        }
    }
    free(input);
    max = scores[1];
    for(i = 1; i < 26; i++){
        if(scores[i] > max){
            max = scores[i];
            flag = i;
        }
    }
    return flag;
}

size_t get_fsize(FILE *file){
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Example: %s [file path]", argv[0]);
        exit(EINVAL);
    }
    FILE *file;
    char *text = NULL;
    file = fopen(argv[1], "r");
    if (!file) {
        printf("Error: cannot open file.");
        exit(ENOENT);
    }
    f_size = get_fsize(file) * sizeof(char) + 1;
    text = (char *) malloc(f_size);
    fscanf(file, "%[^\n]", text);
    fclose(file);
    text = strlwr(text);
    decrypt(text, find_key(text));
    printf("%s\n", text);
    return 0;
}