#include <stdlib.h>
#include <stdio.h>

//need function for opening files in a wanted manner

//function for opening the input file
FILE* input_file_open(const char* filepath){
    FILE* file = fopen(filepath, "r");
    
    if(file == NULL){
        printf("Error: Unabel to open the file %s\n", filepath);
        exit(1);
    }

    return file;
}

//function to open the output file
FILE* output_file_open(const char* filepath){
    FILE* file = fopen(filepath, "w");

    if(file == NULL){
        printf("Error: Unable to open the file %s\n", filepath);
        exit(1);
    }

    return file;
}

//function to compute the statistics
void compute_statistics(const char* filepath_in, const char* filepath_out, char ch){
    FILE* file_in = input_file_open(filepath_in);
    FILE* file_out = output_file_open(filepath_out);

    int count_lowercase = 0, count_uppercase = 0, count_digits = 0, count_ch = 0;
    char c;

    while((c = fgetc(file_in)) != EOF){
        if(c >= 'a' && c <= 'z'){
            count_lowercase++;
        }else if(c >= 'A' && c <= 'Z'){
            count_uppercase++;
        }else if(c >= '0' && c <= '9'){
            count_digits++;
        }

        if(c == ch){
            count_ch++;
        }
    }

    fprintf(file_out, "Lowercase: %d\n", count_lowercase);
    fprintf(file_out, "Uppercase: %d\n", count_uppercase);
    fprintf(file_out, "Digits: %d\n", count_digits);
    fprintf(file_out, "Character %c: %d\n", ch, count_ch);
    
}

int main(int argc, char* argv[]){

    if(argc != 4){
        printf("Usage: %s  <input_filepath> <statistical_output_filepath> <ch> \n", argv[0]);
        exit(1);
    }

    const char* filepath_in = argv[1];
    const char* filepath_out = argv[2];
    char ch = argv[3][0];

    compute_statistics(filepath_in, filepath_out, ch);


}