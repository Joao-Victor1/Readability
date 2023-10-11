#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void set_string(char text[], int max_length){

    printf("Insira um texto para ser avaliado: ");
    scanf("%999[^\n]", text);
}

void get_string(char text[]){
    printf("\nO texto inserido foi:\n %s\n\n", text);
}

int character_count(const char text[]){
    int counter = 0;
    int i = 0;

    for(i = 0; text[i] != '\0'; i++){
        if (isalpha(text[i]) || (text[i] >= -96 && text[i] <= -65)) {
            counter++;
        }
    }

    return counter;
}

int word_count(const char text[]){
    int counter = 0;
    int inside_word = 0;
    int i = 0;
    
    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] == ' ' || text[i] == '.' || text[i] == '!' || text[i] == '?' || text[i] == ',') {
            inside_word = 0;

        } else if (!inside_word) {
            inside_word = 1;
            counter++;
        }
    }

    return counter;
}

int average_words_per_phrase(const char text[]){
    int total_words = 0;
    int total_phrases = 0;
    int inside_word = 0;
    int i = 0;

    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] == ' ' || text[i] == '.') {
            inside_word = 0;

        } else if (!inside_word) {
            inside_word = 1;
            total_words++;

        } else if (text[i] == '?' || text[i] == '!') {
            total_phrases++;
        }
    }

    if (total_words > 0) {
        total_phrases++;
    }

    if (total_phrases > 0) {
        return total_words / total_phrases;
    } else {
        return 0;
    }
}

int is_vowel(char caracter){
    char vowels[] = "AEIOUaeiou";
    int i = 0;

     for (i = 0; vowels[i] != '\0'; i++) {
        if (caracter == vowels[i]) {
            return 1;
        }
    }
    return 0;
}

int count_syllables(const char word[]) {
    int counter = 0;
    int inside_vowels = 0;
    int i = 0;

    for (i = 0; word[i] != '\0'; i++) {
        if (is_vowel(word[i])) {
            if (!inside_vowels) {
                counter++;
                inside_vowels = 1;
            }
        } else {
            inside_vowels = 0;
        }
    }

    // Verifica as letras "ia" no final da palavra
    int length = strlen(word);
    if (length >= 2 && word[length - 2] == 'i' && word[length - 1] == 'a') {
        counter--;
    }

    return counter;
}

int average_syllable(char text[]) {
    int total_syllables = 0;
    int total_words = 0;
    char *token = strtok(text, " ");

    while (token != NULL) {
        int syllables = count_syllables(token);
        total_syllables += syllables;
        total_words++;
        token = strtok(NULL, " ");
    }

    if (total_words > 0) {
        double average_syllables = (double)total_syllables / total_words;
        return round(average_syllables);
    } else {
        return 0;
    }
}

int calculate_readbility(int average_words, int average_syllables){

    int readbility_index = ((0.39 * average_words) + (11.8 * average_syllables)) - 15.59;

    return readbility_index;
}

void grade_verification(int readbility_index){

    if(readbility_index >= 90 && readbility_index <= 100){
        printf("O nível de escolaridade para o texto é: Pós-Graduação.\n\n");

    }else if(readbility_index >= 80 && readbility_index <= 89){
        printf("O nível de escolaridade para o texto é: Ensino Superior\n\n");

    }else if(readbility_index >= 70 && readbility_index <= 79){
        printf("O nível de escolaridade para o texto é:  Ensino médio (1° ao 3°).\n\n");

    }else if(readbility_index >= 60 && readbility_index <= 69){
        printf("O nível de escolaridade para o texto é: 8° e 9° ano\n\n");

    }else if(readbility_index >= 50 && readbility_index <= 59){
        printf("O nível de escolaridade para o texto é: 7° ano\n\n");

    }
    else if(readbility_index >= 50 && readbility_index <= 59){
        printf("O nível de escolaridade para o texto é: 6° ano\n\n");

    }
    else if(readbility_index >= 30 && readbility_index <= 49){
        printf("O nível de escolaridade para o texto é: 5° ano\n\n");

    }
    else if(readbility_index < 30){
        printf("O nível de escolaridade para o texto é: Abaixo do 5° ano.\n\n");

    }

}


int main()
{
    char text[1000];

    set_string(text, sizeof(text));
    get_string(text);
    int total_character = character_count(text);
    int total_words = word_count(text);
    int average_words = average_words_per_phrase(text);
    int average_syllables_per_words = average_syllable(text);
    int readbility_index = calculate_readbility(average_words, average_syllables_per_words);

    printf("\nO total de caracteres é: %d\n", total_character);
    printf("O total de palavras é: %d\n", total_words);
    printf("O texto inserido tem uma média de: %d palavra(s) por frase\n", average_words);
    printf("O texto inserido tem uma média de: %d sílaba(s) por palavras\n", average_syllables_per_words);
    printf("O texto inserido tem um índice de: %d de legibilidade\n", readbility_index);
    grade_verification(readbility_index);

    return 0;
}

