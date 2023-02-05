#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ncurses.h>
#include <time.h>

#define MAX_X 33
#define MAX_Y 129

//Phase 2---------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------

char log[1000][1000];
int log_size = 0;
int arm;

const char comms[28][18] = {"createfile -file ", "insertstr -file ", " -str", " -pos", "cat -file ", "removestr -file ", " -size",
                             "copystr -file ", "cutstr -file ", "pastestr -file ", "find -str ", " -file", " -count", " -at ", " -byword", " -all",
                             "grep", " -files", " /", "compare ", "tree ", "arm", "auto-indent ", "undo -file ", " =D ", " -str1", " -str2",
                              "replace -str1 "};

int string_checker(char a[], char b[], int max)
{
    for(int i = 0; i < max; i++){
        if(a[i] != b[i])
            return 0;
    }
    return 1;
}

char *adress_maker(char *command)
{

}

int num_maker(char *command, int start)
{
    int num = 0, i = 0, flag = 1;
    if(command[0] == '-'){
        flag = -1;
        i++;
    }
    while((command[i+start] < 58) && (command[i+start] > 47)){
        num *= 10;
        num += (command[i+start] - 48);
        i++;
    }
    return num*flag;
}

void create(char *command)
{
    char *ad_name = (char *)calloc(50, sizeof(char));
    int i = 0, start = 0;
    while(command[i] != NULL){
        if(command[i] == '/'){
            mkdir(ad_name);
        }
        ad_name[i-start] = command[i];
        if(command[i+1] == NULL){
            FILE *fptr = fopen(ad_name, "r");
            if(fptr != NULL){
                FILE *cmdptr = fopen("commandline.txt", "w");
                fprintf(cmdptr, "already exist!");
                fclose(cmdptr);
                fclose(fptr);
                FILE *t2ptr = fopen("temporary2.txt", "w");
                fclose(t2ptr);
                return;
            }
            else{
                fclose(fptr);
                fptr = fopen(ad_name, "w");
                fclose(fptr);
            }
        }
        i++;
    }
    free(ad_name);
}

void insert(char *command)
{
    char *ad_name = (char *)calloc(50, sizeof(char));
    int i = 0, start = 0, line, start_po, flag = 0;
    while(!string_checker(command+i, comms[2], strlen(comms[2]))){
        ad_name[i-start] = command[i];
        i++;
    }
    FILE *fptr = fopen(ad_name, "r");
    if(fptr == NULL){
        FILE *cmdptr = fopen("commandline.txt", "w");
        fprintf(cmdptr, "File doesn't exist");
        fclose(cmdptr);
        fclose(fptr);
        FILE *t2ptr = fopen("temporary2.txt", "w");
        fclose(t2ptr);
        return ;
    }
    fclose(fptr);
    fptr = fopen(ad_name, "w+");
    i += strlen(comms[2]) + 1;
    start = i;
    int j = strlen(command)-1, stat = i;
    while(!string_checker(command+j, comms[3], strlen(comms[3]))){
        j--;
    }
    char *string = (char *)calloc(j-i+1, sizeof(char));
    if((command[i] == '"') && (command[j-1] == '"')){
        i++;
        stat = i;
        start = i;
        flag = 1;
    }
    strcat(log[log_size], ad_name);
    strcat(log[log_size], "|||");
    strcat(log[log_size], "");
    log_size++;
    while(!string_checker(command+i, comms[3], strlen(comms[3]))){
        if((command[i] == 92) && (command[i+1] == 92) && (command[i+2] == 'n')){
            string[stat-start] = 92;
            string[stat+1-start] = 'n';
            i += 3;
            stat += 2;
        }
        else if((command[i] == 92) && (command[i+1] = 'n') && (command[i-1] != 92)){
            string[stat-start] = 10;
            i += 2;
            stat++;
        }
        else{
            string[stat-start] = command[i];
            i++;
            stat++;
        }
    }
    i += strlen(comms[3]) + 1;
    line = num_maker(command, i);
    while(command[i] != ':'){
        i++;
    }
    start_po = num_maker(command, i+1);
    for(int k = 1; k < line; k++){
        fprintf(fptr, "\n");
    }
    fseek(fptr, (long int)start_po, SEEK_CUR);
    if(flag == 1){
        string[stat-start-1] = NULL;
    }
    fputs(string, fptr);
    fclose(fptr);
    free(ad_name);
    free(string);
    return ;
}

void cat(char *command)
{
    char *ad_name = (char *)calloc(50, sizeof(char));
    int i = 0, start = 0, file_size;
    while((command[i] != NULL)*(arm == 0) || (string_checker(command+i, comms[24], strlen(comms[24])))*(arm == 1)){
        ad_name[i-start] = command[i];
        i++;
    }
    FILE *tptr = fopen("temporary.txt", "w+");
    FILE *fptr = fopen(ad_name, "r");
    if(fptr == NULL){
        FILE *cmdptr = fopen("commandline.txt", "w");
        fprintf(cmdptr, "File doesn't exist");
        fclose(fptr);
        fclose(cmdptr);
        fclose(tptr);
        free(ad_name);
        FILE *t2ptr = fopen("temporary2.txt", "w");
        fclose(t2ptr);
        return ;
    }
    else{
        fseek(fptr, 0, SEEK_END);
        file_size = ftell(fptr);
        fseek(fptr, 0, SEEK_SET);
        char *string = (char *)calloc(file_size+1, sizeof(char));
        fread(string, sizeof(char), file_size, fptr);
        fputs(string, tptr);
        free(string);
    }
    fclose(fptr);
    free(ad_name);
    if(arm == 0){
        fseek(tptr, 0, SEEK_END);
        int file_size_tptr = ftell(tptr);
        fseek(tptr, 0, SEEK_SET);
        char *string = (char *)calloc(file_size_tptr+1, sizeof(char));
        fread(string, sizeof(char), file_size_tptr, tptr);
        FILE *t2ptr = fopen("temporary2.txt", "w");
        fputs(string, t2ptr);
        free(string);
        fclose(t2ptr);
    }
    else
        arman(strstr(command, comms[24]) + strlen(comms[24]));
    fclose(tptr);
    return ;
}

void remoove(char *command)
{
    char *ad_name = (char *)calloc(50, sizeof(char));
    int i = 0, start = 0, line, start_po, file_size;
    while(!string_checker(command+i, comms[3], strlen(comms[3]))){
        ad_name[i-start] = command[i];
        i++;
    }
    FILE *fptr = fopen(ad_name, "r");
    if(fptr == NULL){
        FILE *cmdptr = fopen("commandline.txt", "w");
        fprintf(cmdptr, "File doesn't exist");
        fclose(cmdptr);
        fclose(fptr);
        FILE *t2ptr = fopen("temporary2.txt", "w");
        fclose(t2ptr);
        return ;
    }
    fclose(fptr);
    fptr = fopen(ad_name, "r");
    i += strlen(comms[3]) + 1;
    start = i;
    line = num_maker(command, start);
    while(command[i] != ':'){
        i++;
    }
    start_po = num_maker(command, i+1);
    i += strlen(comms[6]) + 3;
    start = i;
    int size = num_maker(command, start);
    fseek(fptr, 0, SEEK_END);
    file_size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    char *string = (char *)calloc(file_size+1, sizeof(char));
    fread(string, sizeof(char), file_size, fptr);
    fclose(fptr);
    strcat(log[log_size], ad_name);
    strcat(log[log_size], "|||");
    strcat(log[log_size], string);
    log_size++;
    fptr = fopen(ad_name, "w");
    int line_counter = 1, pos_counter = 0, k = 0;
    while(line_counter < line){
        if(string[k] == 10)
            line_counter++;
        k++;
    }
    while(pos_counter < start_po){
        k++;
        pos_counter++;
    }
    if(command[strlen(command)-1] == 'f'){
        for(int j = 0; j < size; j++){
            string[k+j] = NULL;
        }
    }
    else if(command[strlen(command)-1] == 'b'){
        for(int j = 0; j < size; j++){
            string[k-j] = NULL;
        }
    }
    for(int j = 0; j < file_size; j++){
        if(string[j] != NULL)
            fputc(string[j], fptr);
    }
    fclose(fptr);
    free(ad_name);
    free(string);
    fclose(x);
    return;
}

void copy(char *command)
{
    char *ad_name = (char *)calloc(50, sizeof(char));
    int i = 0, start = 0, line, start_po, file_size;
    while(!string_checker(command+i, comms[3], strlen(comms[3]))){
        ad_name[i-start] = command[i];
        i++;
    }
    FILE *fptr = fopen(ad_name, "r");
    if(fptr == NULL){
        FILE *cmdptr = fopen("commandline.txt", "w");
        fprintf(cmdptr, "File doesn't exist");
        fclose(fptr);
        fclose(cmdptr);
        FILE *t2ptr = fopen("temporary2.txt", "w");
        fclose(t2ptr);
        return ;
    }
    fclose(fptr);
    fptr = fopen(ad_name, "r");
    i += strlen(comms[3]) + 1;
    start = i;
    line = num_maker(command, start);
    while(command[i] != ':'){
        i++;
    }
    start_po = num_maker(command, i+1);
    i += strlen(comms[6]) + 3;
    start = i;
    int size = num_maker(command, start);
    fseek(fptr, 0, SEEK_END);
    file_size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    char *string = (char *)calloc(file_size+1, sizeof(char));
    fread(string, sizeof(char), file_size, fptr);
    fclose(fptr);
    int line_counter = 1, pos_counter = 0, k = 0;
    while(line_counter < line){
        if(string[k] == 10)
            line_counter++;
        k++;
    }
    while(pos_counter < start_po){
        k++;
        pos_counter++;
    }
    if(command[strlen(command)-1] == 'f'){
    }
    else{
        k -= size-1;
    }
    FILE *cpyptr = fopen("copy.txt", "w");
    fwrite(string+k, sizeof(char), size, cpyptr);
    fclose(cpyptr);
    free(string);
    free(ad_name);
    return ;
}

void paste(char *command)
{
    char *ad_name = (char *)calloc(50, sizeof(char));
    int i = 0, start = 0, line, start_po, file_size;
    while(!string_checker(command+i, comms[3], strlen(comms[3]))){
        ad_name[i-start] = command[i];
        i++;
    }
    FILE *fptr = fopen(ad_name, "r");
    if(fptr == NULL){
        FILE *cmdptr = fopen("commandline.txt", "w");
        fprintf(cmdptr, "File doesn't exist");
        fclose(fptr);
        fclose(cmdptr);
        FILE *t2ptr = fopen("temporary2.txt", "w");
        fclose(t2ptr);
        return ;
    }
    fclose(fptr);
    fptr = fopen(ad_name, "r");
    i += strlen(comms[3]) + 1;
    start = i;
    line = num_maker(command, start);
    while(command[i] != ':'){
        i++;
    }
    start_po = num_maker(command, i+1);
    i += strlen(comms[6]) + 3;
    start = i;
    int size = num_maker(command, start);
    fseek(fptr, 0, SEEK_END);
    file_size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    char *string = (char *)calloc(file_size+1, sizeof(char));
    fread(string, sizeof(char), file_size, fptr);
    fclose(fptr);
    strcat(log[log_size], ad_name);
    strcat(log[log_size], "|||");
    strcat(log[log_size], string);
    log_size++;
    fptr = fopen(ad_name, "w");
    int line_counter = 1, pos_counter = 0, k = 0;
    while(line_counter < line){
        if(string[k] == 10)
            line_counter++;
        k++;
    }
    while(pos_counter < start_po){
        k++;
        pos_counter++;
    }
    FILE *cpyptr = fopen("copy.txt", "r");
    fseek(cpyptr, 0, SEEK_END);
    int cpy_size = ftell(cpyptr);
    fseek(cpyptr, 0, SEEK_SET);
    char *out = (char *)calloc(cpy_size+1, sizeof(char));
    fread(out, sizeof(char), cpy_size, cpyptr);
    fwrite(string, sizeof(char), k, fptr);
    fprintf(fptr, "%s", out);
    fwrite(string + k,sizeof(char), file_size-k, fptr);
    free(out);
    free(string);
    free(ad_name);
    fclose(cpyptr);
    fclose(fptr);
}

void find(char *command)
{
    //find -str "haj" -file /root/dirdir/file.txt
    int i = 0, string_size, flag = 0, stat = 0, temp, adress_size, at, star = -1, file_size;
    while(!string_checker(command+i, comms[11], strlen(comms[11]))){
        i++;
    }
    string_size = i;
    if((command[0] == '"') && (command[i-1] == '"')){
        string_size -= 2;
        flag = 1;
    }
    temp = i;
    while(temp < (arm == 0)*strlen(command) + (arm == 1)*(strstr(command, comms[24])-command)){
        if(string_checker(command + temp, comms[12], strlen(comms[12]))){
            if(stat == 0)
                adress_size = temp-i-strlen(comms[11])-2;
            stat += 1;
        }
        else if(string_checker(command + temp, comms[15], strlen(comms[15]))){
            if(stat == 0)
                adress_size = temp-i-strlen(comms[11])-2;
            stat += 2;
        }
        else if(string_checker(command + temp, comms[13], strlen(comms[13]))){
            if(stat == 0)
                adress_size = temp-i-strlen(comms[11])-2;
            stat += 4;
            at = num_maker(command, temp + strlen(comms[13]));
        }
        else if(string_checker(command + temp, comms[14], strlen(comms[14]))){
            if(stat == 0)
                adress_size = temp-i-strlen(comms[11])-2;
            stat += 8;
        }
        temp++;
    }
    if(stat == 0)
        adress_size = temp-i-strlen(comms[11])-2;
    i += strlen(comms[11]) + 2;
    char *ad_name = (char *)calloc(adress_size+1, sizeof(char));
    int start = i;
    while(i-start < adress_size){
        ad_name[i-start] = command[i];
        i++;
    }
    FILE *fptr = fopen(ad_name, "r");
    if(fptr == NULL){
        FILE *cmdptr = fopen("commandline.txt", "w");
        fprintf(cmdptr, "File doesn't exist");
        fclose(fptr);
        free(ad_name);
        fclose(cmdptr);
        FILE *t2ptr = fopen("temporary2.txt", "w");
        fclose(t2ptr);
        return ;
    }
    fseek(fptr, 0, SEEK_END);
    file_size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    char *file_string = (char *)calloc(file_size+1, sizeof(char));
    fread(file_string, sizeof(char), file_size, fptr);
    fclose(fptr);
    printf("%s\n", file_string);
    char *string = (char *)calloc(string_size+1, sizeof(char));
    int k = flag, s = 0;
    while(s < string_size){
        if((command[k] == 92) && (command[k+1] == '*')){
            string[s] = '*';
            s += 1;
            k += 2;
            string_size--;
        }
        else if((command[k] == '*') && (command[k-1] != 92)){
            string[s] = NULL;
            star = s;
            s += 1;
            k += 1;
        }
        else{
            string[s] = command[k];
            s++;
            k++;
        }
    }
    char *string1 = (char *)calloc(100, sizeof(char));
    char *string2 = (char *)calloc(100, sizeof(char));
    if(star != -1){
        strncpy(string1, string, star);
        strncpy(string2, string+star+1, s-star-1);
    }
    k = 0;
    int count = 0, all = 0, word_counter = 1, word1, word2, mount = 0, wordstar;
    char *z;
    int done = 0;
    FILE *tptr = fopen("temporary.txt", "w+");
    //------------------------------------------------------------------------------------------------------------------------
    while(k < file_size){
        if(done == 1)
            break;
        if(((file_string[k] == ' ') || (file_string[k] == '\n')) && ((file_string[k+1] != ' ') || (file_string[k+1] != '\n')))
            word_counter++;
        if((star == -1) && ((stat == 0) || (stat == 8))){
            if(string_checker(string, file_string+k, s)){
                fprintf(tptr, "%d\n", (k+1)*(stat == 0)+(word_counter)*(stat == 8));
                done = 1;
                break;
            }
        }
        else if((star == -1) && (stat == 1)){
            if(string_checker(string, file_string+k, s))
                count++;
        }
        else if((star == -1) && ((stat == 2) || (stat == 10))){
            if(string_checker(string, file_string+k, s)){
                if(all == 0)
                    fprintf(tptr, "%d", (k+1)*(stat == 2)+(word_counter)*(stat == 10));
                else
                    fprintf(tptr, ",%d", (k+1)*(stat == 2)+(word_counter)*(stat == 10));
                all++;
            }
        }
        else if((star == -1) && ((stat == 4) || (stat == 12))){
            if(string_checker(string, file_string+k, s))
                count++;
            if(count == at){
                fprintf(tptr, "%d", (k+1)*(stat == 4)+(word_counter)*(stat == 12));
                done = 1;
                break;
            }
        }
        else if(star == -1){
            fprintf(tptr, "Not valid combination\n");
            break;
        }
        else if((star != -1) && ((stat == 0) || (stat == 8))){
            if(string_checker(string1, file_string+k, star)){
                mount = strlen(string1);
                while((file_string[k+mount] != ' ') && (file_string[k+mount] != '\n') && (file_string[k+mount] != NULL)){
                    if(string_checker(string2, file_string+k+mount, strlen(string2))){
                        fprintf(tptr, "%d\n", (k+1)*(stat == 0)+(word_counter)*(stat == 8));
                        done = 1;
                        break;
                    }
                    mount++;
                }
            }
        }
        else if((star != -1) && (stat == 1)){
            if(string_checker(string1, file_string+k, star)){
                mount = strlen(string1);
                while((file_string[k+mount] != ' ') && (file_string[k+mount] != '\n') && (file_string[k+mount] != NULL)){
                    if(string_checker(string2, file_string+k+mount, strlen(string2))){
                        count++;
                    }
                    mount++;
                }
            }
        }
        else if((star != -1) && ((stat == 2) || (stat == 10))){
            if(string_checker(string1, file_string+k, star)){
                mount = strlen(string1);
                while((file_string[k+mount] != ' ') && (file_string[k+mount] != '\n') && (file_string[k+mount] != NULL)){
                    if(string_checker(string2, file_string+k+mount, strlen(string2))){
                        if(all == 0)
                            fprintf(tptr, "%d", (k+1)*(stat == 2)+(word_counter)*(stat == 10));
                        else
                            fprintf(tptr, ",%d", (k+1)*(stat == 2)+(word_counter)*(stat == 10));
                        all++;
                    }
                    mount++;
                }
            }
        }
        else if((star != -1) && ((stat == 4) || (stat == 12))){
            if(string_checker(string1, file_string+k, star)){
                mount = strlen(string1);
                while((file_string[k+mount] != ' ') && (file_string[k+mount] != '\n') && (file_string[k+mount] != NULL)){
                    if(string_checker(string2, file_string+k+mount, strlen(string2))){
                        count++;
                        if(count == at){
                            fprintf(tptr, "%d", (k+1)*(stat == 4)+(word_counter)*(stat == 12));
                            done = 1;
                            break;
                        }
                    }
                    mount++;
                }
            }
        }
        else{
            fprintf(tptr, "Not valid combination\n");
            break;
        }
        k++;
    }
    if(((stat == 0) || (stat == 8)) && (done == 0))
        fprintf(tptr, "-1\n");
    else if(((stat == 4) || (stat == 12)) && (done == 0))
        fprintf(tptr, "-1\n");
    else if(stat == 1)
        fprintf(tptr, "%d", count);

    else if(((stat == 2) || (stat == 10)) && (all == 0)){
        fprintf(tptr, "-1\n");
    }
    free(string1);
    free(string2);
    free(string);
    free(ad_name);
    free(file_string);
    if(arm == 0){
        fseek(tptr, 0, SEEK_END);
        int file_size_tptr = ftell(tptr);
        fseek(tptr, 0, SEEK_SET);
        char *string = (char *)calloc(file_size_tptr+1, sizeof(char));
        fread(string, sizeof(char), file_size_tptr, tptr);
        FILE *t2ptr = fopen("temporary2.txt", "w");
        fprintf(t2ptr, "%s", string);
        fclose(t2ptr);
        free(string);
    }
    else
        arman(strstr(command, comms[24]) + strlen(comms[24]));
    fclose(tptr);
    return ;
}

void replace(char *command)
{
    //replace -str1 "haj" -str2 "Gol" -file /root/dirdir/file.txt -all
    int i = 0, string_size1, string_size2, flag1 = 0, flag2 = 0, stat = 0, temp, adress_size, at = 1, star = -1, file_size;
    while(!string_checker(command+i, comms[26], strlen(comms[26]))){
        i++;
    }
    printf("0\n");
    string_size1 = i;
    if((command[0] == '"') && (command[i-1] == '"')){
        string_size1 -= 2;
        flag1 = 1;
    }
    while(!string_checker(command+i, comms[11], strlen(comms[11]))){
        i++;
    }
    printf("1\n");
    string_size2 = i-(string_size1 + 2*flag1)-strlen(comms[26])-1;
    if((command[string_size1 + 2*flag1 + strlen(comms[26]) + 1] == '"') && (command[i-1] == '"')){
        string_size2 -= 2;
        flag2 = 1;
    }
    temp = i;
    while(temp < strlen(command)){
        if(string_checker(command + temp, comms[15], strlen(comms[15]))){
            if(stat == 0)
                adress_size = temp-i-strlen(comms[11])-2;
            stat += 2;
        }
        else if(string_checker(command + temp, comms[13], strlen(comms[13]))){
            if(stat == 0)
                adress_size = temp-i-strlen(comms[11])-2;
            stat += 4;
            at = num_maker(command, temp + strlen(comms[13]));
        }
        temp++;
    }
    printf("2 %d\n", adress_size);
    if(stat == 0)
        adress_size = temp-i-strlen(comms[11])-2;
    i += strlen(comms[11]) + 2;
    char *ad_name = (char *)calloc(adress_size+1, sizeof(char));
    int start = i;
    while(i-start < adress_size){
        ad_name[i-start] = command[i];
        i++;
    }
    printf("3\n");
    FILE *fptr = fopen(ad_name, "r");
    if(fptr == NULL){
        FILE *cmdptr = fopen("commandline.txt", "w");
        fprintf(cmdptr, "File doesn't exist");
        fclose(fptr);
        fclose(cmdptr);
        free(ad_name);
        FILE *t2ptr = fopen("temporary2.txt", "w");
        fclose(t2ptr);
        return ;
    }
    fseek(fptr, 0, SEEK_END);
    file_size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    char *file_string = (char *)calloc(file_size+1, sizeof(char));
    fread(file_string, sizeof(char), file_size, fptr);
    fclose(fptr);
    strcat(log[log_size], ad_name);
    strcat(log[log_size], "|||");
    strcat(log[log_size], file_string);
    log_size++;
    char *message1 = (char *)calloc(string_size1+1, sizeof(char));
    int k = flag1, s = 0;
    printf("4\n");
    while(s < string_size1){
        if((command[k] == 92) && (command[k+1] == '*')){
            message1[s] = '*';
            s += 1;
            k += 2;
            string_size1--;
        }
        else if((command[k] == '*') && (command[k-1] != 92)){
            message1[s] = NULL;
            star = s;
            s += 1;
            k += 1;
        }
        else{
            message1[s] = command[k];
            s++;
            k++;
        }
    }
    printf("6\n");
    char *message2 = (char *)calloc(string_size2+1, sizeof(char));
    k = flag2 + string_size1 + 2*flag1 +strlen(comms[26]) + 1;
    s = 0;
    while(s < string_size2){
        message2[s] = command[k];
        s++;
        k++;
    }
    printf("7\n");
    char *string1 = (char *)calloc(100, sizeof(char));
    char *string2 = (char *)calloc(100, sizeof(char));
    if(star != -1){
        strncpy(string1, message1, star);
        strncpy(string2, message1+star+1, s-star-1);
    }
    k = 0;
    int count = 0, all = 0, word_counter = 1, word1, word2, mount = 0, wordstar, l = 0;
    char *z;
    int done = 0;
    char *ans = (char *)calloc(2*file_size + 1, sizeof(char));
    FILE *tptr = fopen("temporary.txt", "w+");
    fptr = fopen(ad_name, "w");
    printf("%s\n%s %s\n", file_string, message1, message2);
    //------------------------------------------------------------------------------------------------------------------------
    while(k < file_size){
        if(((file_string[k] == ' ') || (file_string[k] == '\n')) && ((file_string[k+1] != ' ') || (file_string[k+1] != '\n')))
            word_counter++;
        if((star == -1) && (stat == 2)){
            if(string_checker(message1, file_string+k, s)){
                strncat(ans, file_string+l, k-l);
                strcat(ans, message2);
                l = k + strlen(message1);
                all++;
            }
        }
        else if((star == -1) && ((stat == 4) || (stat == 0))){
            if(string_checker(message1, file_string+k, s))
                count++;
            if(count == at){
                strncat(ans, file_string+l, k-l);
                strcat(ans, message2);
                l = k + strlen(message1);
                fputs(ans, fptr);
                fprintf(tptr, "Success\n");
                done = 1;
                break;
            }
        }
        else if((star != -1) && (stat == 2)){
            if(string_checker(string1, file_string+k, star)){
                mount = strlen(string1);
                while((file_string[k+mount] != ' ') && (file_string[k+mount] != '\n') && (file_string[k+mount] != NULL)){
                    if(string_checker(string2, file_string+k+mount, strlen(string2))){
                        strncat(ans, file_string+l, k-l);
                        strcat(ans, message2);
                        l = k + mount + strlen(string2);
                        all++;
                    }
                    mount++;
                }
            }
        }
        else if((star != -1) && ((stat == 4) || (stat == 0))){
            if(string_checker(string1, file_string+k, star)){
                mount = strlen(string1);
                while((file_string[k+mount] != ' ') && (file_string[k+mount] != '\n') && (file_string[k+mount] != NULL)){
                    if(string_checker(string2, file_string+k+mount, strlen(string2))){
                        count++;
                        if(count == at){
                            strncat(ans, file_string+l, k-l);
                            strcat(ans, message2);
                            l = k + mount + strlen(string2);
                            fputs(ans, fptr);
                            fprintf(tptr, "Success\n");
                            done = 1;
                            break;
                        }
                    }
                    mount++;
                }
            }
        }
        else{
            fprintf(tptr, "Not valid combination\n");
            fputs(file_string, fptr);
            break;
        }
        k++;
    }
    strncat(ans, file_string+l, file_size-l);
    if(((stat == 0) || (stat == 4)) && (done == 0)){
        fputs(file_string, fptr);
        fprintf(tptr, "-1\n");
    }
    else if((stat == 2) && (all == 0)){
        fputs(file_string, fptr);
        fprintf(tptr, "-1\n");
    }
    else if((stat == 2) && (all != 0)){
        fputs(ans, fptr);
        fprintf(tptr, "Success\n");
    }
    free(ans);
    fclose(fptr);
    free(string1);
    free(string2);
    free(message1);
    free(message2);
    free(ad_name);
    free(file_string);
    if(arm == 0){
        fseek(tptr, 0, SEEK_END);
        int file_size_tptr = ftell(tptr);
        fseek(tptr, 0, SEEK_SET);
        char *string = (char *)calloc(file_size_tptr+1, sizeof(char));
        fread(string, sizeof(char), file_size_tptr, tptr);
        printf("%s", string);
        free(string);
    }
    else
        arman(strstr(command, comms[24]) + strlen(comms[24]));
    fclose(tptr);
    return ;
}

void grep(char *command)
{
    // grep -str "qam" -files /root/dirdir/file.txt /root/dirdir/file1.txt /root/dirdir/file2.txt
    int i = 0, start = 0;
    while(!string_checker(command+i, comms[2], strlen(comms[2]))){
        i++;
    }
    i += strlen(comms[2]) + 1;
    start = i;
    int j = i, stat = i, flag = 0;
    while(!string_checker(command+j, comms[17], strlen(comms[17]))){
        j++;
    }
    char *string = (char *)calloc(j-i+1, sizeof(char));
    if((command[i] == '"') && (command[j-1] == '"')){
        i++;
        stat = i;
        start = i;
        flag = 1;
    }
    while(!string_checker(command+i, comms[17], strlen(comms[17]))){
        if((command[i] == 92) && (command[i+1] == 92) && (command[i+2] == 'n')){
            string[stat-start] = 92;
            string[stat+1-start] = 'n';
            i += 3;
            stat += 2;
        }
        else if((command[i] == 92) && (command[i+1] = 'n') && (command[i-1] != 92)){
            string[stat-start] = 10;
            i += 2;
            stat++;
        }
        else{
            string[stat-start] = command[i];
            i++;
            stat++;
        }
    }
    if(flag == 1){
        string[stat-start-1] = NULL;
    }
    i += strlen(comms[17]) + 2;
    int count = 0, first = start;
    start = i;
    char *ad_name = (char *)calloc(50, sizeof(char));
    FILE *tptr = fopen("temporary.txt", "w+");
    do{
        if(string_checker(command+i, comms[18], strlen(comms[18])) || (string_checker(command+i, comms[24], strlen(comms[24])))*(arm == 1) || (i == strlen(command))*(arm == 0)){
            i += 2;
            start = i;
            //---------------------------------------------------------------
            FILE *fptr = fopen(ad_name, "r");
            if((fptr == NULL) && (!string_checker(command+i-2-strlen(comms[24]), comms[24], strlen(comms[24])))){
                fprintf(tptr, "file %s not found\n", ad_name);
                fclose(fptr);
            }
            else{
                char *file_string = (char *)calloc(100, sizeof(char));
                int l = 0;
                while(!feof(fptr)){
                    fgets(file_string, 100, fptr);
                    l = 0;
                    while((l < 100) || (file_string[l] != NULL)){
                        if(string_checker(string, file_string + l, stat-first-flag)){
                            if(command[2] == 's'){
                                fprintf(tptr, "%s : %s\n", ad_name, file_string);
                            }
                            else if(command[2] == 'c'){
                                count++;
                            }
                            else if(command[2] == 'l'){
                                fprintf(tptr, "%s\n", ad_name);
                            }
                            l++;
                            break;
                        }
                        l++;
                    }
                }
            free(file_string);
            fclose(fptr);
            }
            //---------------------------------------------------------------
            free(ad_name);
            char *ad_name = (char *)calloc(50, sizeof(char));
        }
        ad_name[i-start] = command[i];
        i++;
    }while((!string_checker(command+i, comms[24], strlen(comms[24])))*(arm == 1) || (i < strlen(command)+1)*(arm == 0));
    if(command[2] == 'c')
        fprintf(tptr, "%d", count);
    free(string);
    free(ad_name);
    if(arm == 0){
        fseek(tptr, 0, SEEK_END);
        int file_size_tptr = ftell(tptr);
        fseek(tptr, 0, SEEK_SET);
        char *string = (char *)calloc(file_size_tptr+1, sizeof(char));
        fread(string, sizeof(char), file_size_tptr, tptr);
        FILE *t2ptr = fopen("temporary2.txt", "w");
        fprintf(t2ptr, "%s", string);
        fclose(t2ptr);
        free(string);
    }
    else
        arman(strstr(command, comms[24]) + strlen(comms[24]));
    fclose(tptr);
    return ;
}

void undo(char *command)
{
    FILE *fptr;
    for(int i = log_size; i > -1; i--){
        if(string_checker(command, log[i], strlen(command))){
            fptr = fopen(command, "r");
            if(fptr == NULL){
                FILE *cmdptr = fopen("commandline.txt", "w");
                fprintf(cmdptr, "File doesn't exist");
                fclose(fptr);
                fclose(cmdptr);
                FILE *t2ptr = fopen("temporary2.txt", "w");
                fclose(t2ptr);
                return ;
            }
            fclose(fptr);
            fptr = fopen(command, "w");
            fputs(log[i]+strlen(command)+3, fptr);
            fclose(fptr);
            return ;
        }
    }
    FILE *cmdptr = fopen("commandline.txt", "w");
    fprintf(cmdptr, "NO history!");
    fclose(cmdptr);
    FILE *t2ptr = fopen("temporary2.txt", "w");
    fclose(t2ptr);
    return ;
}

int find_most(char *string, int loc, char side)
{
    int k , mount = 0, ans = -1;
    if(side == 'l'){
        while((string[loc+mount] != '\n') && (string[loc+mount] != NULL) && (loc+mount >= 0) && (string[loc+mount] != '{') && (string[loc+mount] != '}')){
            if(string[loc+mount] != ' ')
                ans = loc+mount;
            mount--;
        }
        return ans;
    }
    else{
        while((string[loc+mount] != '\n') && (string[loc+mount] != NULL) && (loc+mount >= 0) && (string[loc+mount] != '{') && (string[loc+mount] != '}')){
            if(string[loc+mount] != ' ')
                return loc+mount;
            mount--;
        }
        return -1;
    }
}

void indent(char *command)
{
    char *ad_name = (char *)calloc(50, sizeof(char));
    int i = 0, start = 0, file_size;
    while(i < strlen(command)){
        ad_name[i-start] = command[i];
        i++;
    }
    FILE *fptr = fopen(ad_name, "r");
    if(fptr == NULL){
        FILE *cmdptr = fopen("commandline.txt", "w");
        fprintf(cmdptr, "File doesn't exist");
        fclose(fptr);
        free(ad_name);
        fclose(cmdptr);
        FILE *t2ptr = fopen("temporary2.txt", "w");
        fclose(t2ptr);
        return ;
    }
     //auto-indent /root/dirdir/file.txt   for(int j = 0; j < count; j++){fprintf(fptr, "\t");}
    fseek(fptr, 0, SEEK_END);
    file_size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    char *string = (char *)calloc(file_size+1, sizeof(char));
    fread(string, sizeof(char), file_size, fptr);
    fclose(fptr);
    strcat(log[log_size], ad_name);
    strcat(log[log_size], "|||");
    strcat(log[log_size], string);
    log_size++;
    fptr = fopen(ad_name, "w");
    int l = 0, r = 0, mount, count = 0, k = 0;
    while(k < file_size){
        if((string[k] == '{') && (((string[k+1] != '\'') || (string[k-1] != '\'')) && ((string[k+1] != '\"') || (string[k-1] != '\"')))){
            l = find_most(string, k-1, 'l');
            r = find_most(string, k-1, 'r');
            for(int j = 0; j < count; j++){
                fprintf(fptr, "\t");
            }
            if(l != -1){
                fwrite(string+l, sizeof(char), r-l+1, fptr);
                fprintf(fptr, " ");
            }
            fprintf(fptr, "{\n");
            count++;
        }
        else if((string[k] == '}') && (((string[k+1] != '\'') || (string[k-1] != '\'')) && ((string[k+1] != '\"') || (string[k-1] != '\"')))){
            l = find_most(string, k-1, 'l');
            r = find_most(string, k-1, 'r');
            for(int j = 0; j < count; j++){
                fprintf(fptr, "\t");
            }
            count--;
            if(l != -1){
                fwrite(string+l, sizeof(char), r-l+1, fptr);
            }
            if(string[k-1] != '}')
                fprintf(fptr, "\n");
            for(int j = 0; j < count; j++){
                fprintf(fptr, "\t");
            }
            fprintf(fptr, "}\n");
        }
        k++;
    }
    fclose(fptr);
    free(ad_name);
    free(string);
    return ;
}

int line_counter(char *string, int size)
{
    int line = 1;
    for(int i = 0; i < size; i++){
        if(string[i] == '\n')
            line++;
    }
    return line;
}

void compare(char *command)
{
    // compare /root/dirdir/file1.txt /root/dirdir/file2.txt
    char *ad_name1 = (char *)calloc(50, sizeof(char));
    char *ad_name2 = (char *)calloc(50, sizeof(char));
    int i = 0, start = 0;
    while(!string_checker(command+i, comms[18], strlen(comms[18]))){
        ad_name1[i-start] = command[i];
        i++;
    }
    i += 2;
    start = i;
    while(i < (arm == 0)*strlen(command) + (arm == 1)*(strstr(command, comms[24])-command)){
        ad_name2[i-start] = command[i];
        i++;
    }
    int line1, line2;
    FILE *fptr1 = fopen(ad_name1, "r");
    FILE *fptr2 = fopen(ad_name2, "r");
    if(fptr1 == NULL){
        FILE *cmdptr = fopen("commandline.txt", "w");
        fprintf(cmdptr, "File %s doesn't exist", ad_name1);
        fclose(fptr1);
        fclose(cmdptr);
        FILE *t2ptr = fopen("temporary2.txt", "w");
        fclose(t2ptr);
        return ;
    }
    if(fptr2 == NULL){
        FILE *cmdptr = fopen("commandline.txt", "w");
        fprintf(cmdptr, "File %s doesn't exist\n", ad_name2);
        fclose(fptr2);
        fclose(cmdptr);
        FILE *t2ptr = fopen("temporary2.txt", "w");
        fclose(t2ptr);
        return ;
    }
    fseek(fptr1, 0, SEEK_END);
    int file_size1 = ftell(fptr1);
    fseek(fptr1, 0, SEEK_SET);
    char *string = (char *)calloc(file_size1+1, sizeof(char));
    fread(string, sizeof(char), file_size1, fptr1);
    line1 = line_counter(string, file_size1);
    free(string);
    fseek(fptr2, 0, SEEK_END);
    int file_size2 = ftell(fptr2);
    fseek(fptr2, 0, SEEK_SET);
    string = (char *)calloc(file_size2+1, sizeof(char));
    fread(string, sizeof(char), file_size2, fptr2);
    line2 = line_counter(string, file_size2);
    free(string);
    fclose(fptr1);
    fclose(fptr2);
    fptr1 = fopen(ad_name1, "r");
    fptr2 = fopen(ad_name2, "r");
    int l1, r1 = -2, l2, r2 = -2, length, word_Counter1 = 0, word_Counter2 = 0, fail = 0, max_l, line = 1, left1, right1, left2, right2;
    FILE *tptr = fopen("temporary.txt", "w+");
    while((!feof(fptr1)) && (!feof(fptr2))){
        r1 = -2;
        r2 = -2;
        char *string1 = (char *)calloc(100, sizeof(char));
        char *string2 = (char *)calloc(100, sizeof(char));
        fgets(string1, 100, fptr1);
        fgets(string2, 100, fptr2);
        length = strlen(string1) * (strlen(string1) >= strlen(string2)) + strlen(string2) * (strlen(string1) < strlen(string2));
        fail = 0;
        if(!string_checker(string1, string2, length)){
            string1[strlen(string1)-1] = (string1[strlen(string1)-1])*(string1[strlen(string1)-1] != '\n');
            string2[strlen(string2)-1] = (string2[strlen(string2)-1])*(string2[strlen(string2)-1] != '\n');
            fail = 0;
            for(int k = 0; k < length+1; k++){
                if((string1[k] == ' ') || ((string1[k] == NULL) && (string1[k-1] != NULL))){
                    word_Counter1++;
                    l1 = r1 + 2;
                    r1 = k-1;
                    if(word_Counter1 == word_Counter2){
                        if((r1-l1 != r2-l2) || ((r1-l1 == r2-l2) && (!string_checker(string1+l1, string2+l2, r1-l1+1)))){
                            fail++;
                            if(fail == 1){
                                left1 = l1;
                                right1 = r1;
                                left2 = l2;
                                right2 = r2;
                            }
                            else if(fail > 1){
                                fprintf(tptr, "============ #%d ============\n%s\n%s\n", line, string1, string2);
                                break;
                            }
                        }
                    }
                }
                if((string2[k] == ' ') || ((string2[k] == NULL) && (string2[k-1] != NULL))){
                    word_Counter2++;
                    l2 = r2 + 2;
                    r2 = k-1;
                    if(word_Counter1 == word_Counter2){
                        if((r1-l1 != r2-l2) || ((r1-l1 == r2-l2) && (!string_checker(string1+l1, string2+l2, r1-l1+1)))){
                            fail++;
                            if(fail == 1){
                                left1 = l1;
                                right1 = r1;
                                left2 = l2;
                                right2 = r2;
                            }
                            else if(fail > 1){
                                fprintf(tptr, "============ #%d ============\n%s\n%s\n", line, string1, string2);
                                break;
                            }
                        }
                    }
                }
            }
        }
        if(fail == 1){
            char *uns1 = (char *)calloc(100, sizeof(char));
            char *uns2 = (char *)calloc(100, sizeof(char));
            strncat(uns1, string1, left1);
            strcat(uns1, ">>");
            strncat(uns1, string1+left1, right1-left1+1);
            strcat(uns1, "<<");
            strcat(uns1, string1+right1+1);
            strncat(uns2, string2, left2);
            strcat(uns2, ">>");
            strncat(uns2, string2+left2, right2-left2+1);
            strcat(uns2, "<<");
            strcat(uns2, string2+right2+1);
            fprintf(tptr, "============ #%d ============\n%s\n%s\n", line, uns1, uns2);
            free(uns1);
            free(uns2);
        }
        line++;
        free(string1);
        free(string2);
    }
    if(feof(fptr1) && !feof(fptr2)){
        fprintf(tptr, ">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n", line, line1+1);
        while(!feof(fptr2)){
            char *string2 = (char *)calloc(100, sizeof(char));
            fgets(string2, 100, fptr2);
            fprintf(tptr, "%s\n", string2);
            free(string2);
        }
    }
    else if(!feof(fptr1) && feof(fptr2)){
        fprintf(tptr, "<<<<<<<<<<<< #%d - #%d <<<<<<<<<<<<\n", line, line2+1);
        while(!feof(fptr1)){
            char *string1 = (char *)calloc(100, sizeof(char));
            fgets(string1, 100, fptr1);
            fprintf(tptr, "%s\n", string1);
            free(string1);
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    free(ad_name1);
    free(ad_name2);
    if(arm == 0){
        fseek(tptr, 0, SEEK_END);
        int file_size_tptr = ftell(tptr);
        fseek(tptr, 0, SEEK_SET);
        char *string = (char *)calloc(file_size_tptr+1, sizeof(char));
        fread(string, sizeof(char), file_size_tptr, tptr);
        FILE *t2ptr = fopen("temporary2.txt", "w");
        fprintf(t2ptr, "%s", string);
        fclose(t2ptr);
        free(string);
    }
    else
        arman(strstr(command, comms[24]) + strlen(comms[24]));
    return ;
}

void listdirectory(char *dirname, int depth, int curdepth, int next_situation, FILE *tptr)
{
    if((curdepth > depth) && (depth != -1))
        return ;
    DIR *dir = opendir(dirname);
    if(dir == NULL)
        return ;
    struct dirent *subdir;
    subdir = readdir(dir);
    FILE *fptr;
    // printf("root\n")
    while(subdir != NULL){
        char *name = (char *)calloc(100, sizeof(char));
        strcat(name, subdir->d_name);
        subdir = readdir(dir);
        if(!string_checker(name, ".", 1) && !string_checker(name, "..", 1)){
            for(int i = 0; i < curdepth-2; i++){
                // _setmode(_fileno(stdout), _O_U16TEXT);
                // wprintf(L"    \x2502");
                // _setmode(_fileno(stdout), _O_U8TEXT);
                if(next_situation == 1)
                    fprintf(tptr, "|    ");
                else
                    fprintf(tptr, "     ");
            }
            if(curdepth != 1){
                fprintf(tptr, "|--->");
                // _setmode(_fileno(stdout), _O_U16TEXT);
                // wprintf(L"    \x251c\x2500\x2500\x2500");
                // _setmode(_fileno(stdout), _O_U8TEXT);
            }
            fprintf(tptr, "%s\n", name);
        }
        char *dir_name = (char *)calloc(100, sizeof(char));
        strcat(dir_name, dirname);
        strcat(dir_name, "/");
        strcat(dir_name, name);
        fptr = fopen(dir_name, "r");
        if((fptr == NULL) && !string_checker(name, ".", 1) && !string_checker(name, "..", 1)){
            listdirectory(dir_name, depth, curdepth+1, (subdir != NULL), tptr);
            // fprintf(tptr, "\n");
        }
        free(dir_name);
        free(name);
        fclose(fptr);
    }
    closedir(dir);
    return ;
}

void tree(char *command)
{
    int depth = num_maker(command, 0);
    if(depth < -1){
        FILE *cmdptr = fopen("commandline.txt", "w");
        printf("invalid depth\n");
        fclose(cmdptr);
        FILE *t2ptr = fopen("temporary2.txt", "w");
        fclose(t2ptr);
        return ;
    }
    FILE *tptr = fopen("temporary.txt", "w");
    listdirectory("root", depth, 1, 0, tptr);
    fclose(tptr);
    if(arm == 0){
        tptr = fopen("temporary.txt", "r");
        fseek(tptr, 0, SEEK_END);
        int file_size = ftell(tptr);
        fseek(tptr, 0, SEEK_SET);
        char *string = (char *)calloc(file_size+1, sizeof(char));
        fread(string, sizeof(char), file_size, tptr);
        FILE *t2ptr = fopen("temporary2.txt", "w");
        fprintf(t2ptr, "%s", string);
        fclose(t2ptr);
        free(string);
        fclose(tptr);
    }
    else{
        arman(strstr(command, comms[24]) + strlen(comms[24]));
    }
    return ;
}

void arman(char *command)
{
    arm = 0;
    FILE *tptr = fopen("temporary.txt", "r");
    fseek(tptr, 0, SEEK_END);
    int file_size = ftell(tptr);
    fseek(tptr, 0, SEEK_SET);
    char *string = (char *)calloc(file_size+1, sizeof(char));
    fread(string, sizeof(char), file_size, tptr);
    char *temp = (char *)calloc(strlen(command) + strlen(comms[2]) + file_size + 4, sizeof(char));
    if(string_checker(command, comms[1], strlen(comms[1]))){
        strncat(temp, command, (size_t)(strstr(command, comms[3])-command));
        strcat(temp, comms[2]);
        strcat(temp, " \"");
        strcat(temp, string);
        strcat(temp, "\"");
        strcat(temp, strstr(command, comms[3]));
        insert(temp + strlen(comms[1]) + 1);
    }
    else if(string_checker(command, "find", 4)){
        strcat(temp, "find");
        strcat(temp, comms[2]);
        strcat(temp, " \"");
        strcat(temp, string);
        strcat(temp, "\"");
        strcat(temp, command+4);
        find(command + strlen(comms[10]));
    }
    else if(string_checker(command, "replace", 7)){
        strcat(temp, "replace");
        strcat(temp, " -str1");
        strcat(temp, " \"");
        strcat(temp, string);
        strcat(temp, "\"");
        strcat(temp, command+7);
        replace(command + strlen(comms[27]));
    }
    else if(string_checker(command, "grep", 4)){
        strcat(temp, "grep");
        strcat(temp, comms[2]);
        strcat(temp, " \"");
        strcat(temp, string);
        strcat(temp, "\"");
        strcat(temp, command+4);
        grep(command + strlen(comms[16]));
    }
    free(temp);
    free(string);
    fclose(tptr);
}

//Phase 2---------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------
int line = 1;
int endposition[200] = {-1};
int endpositionl[200] = {-1};
int x = -1, y = -1;
int x_past, y_past;
int r = 0, d = 0;
int mode = 0, s = 0;
int select_pos[2][2];
int name = 0;
int locsaved;
int smap[MAX_X][MAX_Y] = {0};
int size = 0, pos1, pos2;

void print_default()
{
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	attron(COLOR_PAIR(4));
	for(int i = 0; i < MAX_X; i++){
		printw("~");
		for(int j = 0; j < MAX_Y; j++){
			printw(" ");
		}
		printw("\n");
	}
	attroff(COLOR_PAIR(4));
}

int digit_counter(int num)
{
	int i = 0;
	while(num != 0){
		num = num/10;
		i++;
	}
	return i;
}

void print_maintext()
{
    FILE *tptr = fopen("temporary2.txt", "r");
    fseek(tptr, 0, SEEK_END);
    int file_size = ftell(tptr);
    fseek(tptr, 0, SEEK_SET);
    char *string = (char *)calloc(file_size+1, sizeof(char));
    fread(string, sizeof(char), file_size, tptr);
	int i = 0, count = 1, k = 0;
	move(0,0);
	init_pair(6, COLOR_GREEN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_WHITE);
	attron(COLOR_PAIR(3));
    printw("1 ");
    attroff(COLOR_PAIR(3));
    int x_first = -1, y_first = -1, x_last, y_last, tempend = -1, flag = 0;
    for(int kx = 0; kx < MAX_X; kx++){
        for(int ky = 0; ky < MAX_Y; ky++){
            if(smap[kx][ky] == 1){
                if(x_first == -1){
                    x_first = kx;
                    y_first = ky;
                }
                x_last = kx;
                y_last = ky;
            }
        }
    }
    while((i < file_size) && (count < MAX_X)){
        if((i - endposition[count-1] > r) && (i - endposition[count-1] < MAX_Y) && (count > d)){
            if(string[i] == '\n'){
                endposition[count] = i;
                endpositionl[count] = endposition[count] - endposition[count-1] + digit_counter(count);
                attron(COLOR_PAIR(7));
                move(count-1, MAX_Y-1);
                printw("\n");
                i++;
                attroff(COLOR_PAIR(7));
                    count++;
                attron(COLOR_PAIR(3));
                printw("%d ", count);
                attroff(COLOR_PAIR(3));
            }
	    if((i-endposition[count-1]+digit_counter(count) == y_first) && (count-1 == x_first))
		    flag = 1;
	    if(flag == 1){
		    attron(COLOR_PAIR(8));
		    printw("%c", string[i]);
		    attroff(COLOR_PAIR(8));
	    }
	    else{
            	attron(COLOR_PAIR(7));
            	printw("%c", string[i]);
            	attroff(COLOR_PAIR(7));
	    }
	    if((i-endposition[count-1]+digit_counter(count) == y_last) && (count-1 == x_last))
		    flag = 0;
        }
        i++;
    }
    fclose(tptr);
    free(string);
	line = count;
	y = (i-endposition[count-1])*(y == -1) + y*(y != -1);
	x = (count-1)*(x == -1) + x*(x != -1);
	if(y < 1+digit_counter(x+1))
		y = 1+digit_counter(x+1);
    return ;
}

void print_modebar(char *file_name, int saved)
{
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    init_color(COLOR_MAGENTA, 300, 300, 300);
    init_pair(2, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(8, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(1));
    move(MAX_X, 0);
    if(mode%10 == 0)
       	printw(" NORMAL ");
    else if(mode == 1)
        printw(" INSERT ");
    else
        printw(" VISUAL ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    printw(" %s %c", file_name, ('+')*(saved == 1)+('-')*(saved == 0));
    for(int i = 0; i < MAX_Y-strlen(file_name)-8; i++){
	    if((i == MAX_Y-7-strlen(file_name)-8) && (s == 1))
		    printw("S");
	    else
	    	printw(" ");
    }
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(8));
    FILE *cmdptr = fopen("commandline.txt", "r");
    fseek(cmdptr, 0, SEEK_END);
    int cmd_size = ftell(cmdptr);
    fseek(cmdptr, 0, SEEK_SET);
    char *cmdstring = (char *)calloc(cmd_size+1, sizeof(char));
    fread(cmdstring, sizeof(char), cmd_size, cmdptr);
    printw("%s", cmdstring);
    locsaved = strlen(file_name) + 10;
    for(int i = cmd_size; i < MAX_Y+4; i++){
	    printw(" ");
    }
    attroff(COLOR_PAIR(8));
    free(cmdstring);
    fclose(cmdptr);
    return ;
}

void copyf(char *filename1, char *filename2)
{
    FILE *fptr2 = fopen(filename2, "r");
    FILE *fptr1 = fopen(filename1, "w");
    fseek(fptr2, 0, SEEK_END);
    int file_size = ftell(fptr2);
    fseek(fptr2, 0, SEEK_SET);
    char *string = (char *)calloc(file_size+1, sizeof(char));
    fread(string, sizeof(char), file_size, fptr2);
    fwrite(string, sizeof(char), file_size, fptr1);
    free(string);
    fclose(fptr1);
    fclose(fptr2);
    return ;
}

void command_controller()
{
    FILE *tptr = fopen("temporary2.txt", "r");
    fseek(tptr, 0, SEEK_END);
    int temp_size = ftell(tptr);
    fseek(tptr, 0, SEEK_SET);
    char *temp_string = (char *)calloc(temp_size+1, sizeof(char));
    fread(temp_string, sizeof(char), temp_size, tptr);
    fclose(tptr);
    FILE *cmdptr = fopen("commandline.txt", "r");
    fseek(cmdptr, 0, SEEK_END);
    int cmd_size = ftell(cmdptr);
    fseek(cmdptr, 0, SEEK_SET);
    char *cmd_string = (char *)calloc(cmd_size+1, sizeof(char));
    fread(cmd_string, sizeof(char), cmd_size, cmdptr);
    fclose(cmdptr);
    char *command = cmd_string+1;
    if(strncmp(cmd_string, ":open ", strlen(":open "))){
        command_controller(":save");
        FILE *fptr = fopen(cmd_string+strlen(":open ")+1, "r");
        if(fptr != NULL){
            copyf("temporary.txt", cmd_string+strlen(":open ")+1);
        }
        else{
            FILE *tptr = fopen("temporary2.txt", "w");
            fclose(tptr);
        }
        FILE *cmdptr = fopen("commandline.txt", "w");
        fclose(cmdptr);
        print_modebar(cmd_string+strlen(":open ")+1, (fptr != NULL));
        mode = 0;
        fclose(fptr);
    }
    else if(strcmp(cmd_string, ":save")){
        char *filename = (char *)calloc(100, sizeof(char));
        for(int i = 9; i < locsaved-1; i++){
            filename[i-9] = (char)mvinch(MAX_X-2, i);
        }
        if(strstr(filename, "root/") == NULL){
            FILE *cmdptr = fopen("commandline.txt", "w");
            fputs("adress : ", cmdptr);
            fclose(cmdptr);
        }
        else{
            create(filename);
            copyf(filename, "temporary2.txt");
            FILE *cmdptr = fopen("commandline.txt", "w");
            fclose(cmdptr);
            mode = 0;
            print_modebar(filename, 1);
        }
        free(filename);
    }
    else if(strncmp(cmd_string, "adress : ", strlen("adress : "))){
        create(cmd_string+strlen("adress : "));
        copyf(cmd_string+strlen("adress : "), "temporary2.txt");
        FILE *cmdptr = fopen("commandline.txt", "w");
        fclose(cmdptr);
        mode = 0;
        print_modebar(cmd_string+strlen("adress : "), 1);
    }
    else if(strncmp(cmd_string, ":saveas /", strlen(":saveas /"))){
        create(cmd_string+strlen(":saveas "));
        copyf(cmd_string+strlen(":saveas "), "temporary2.txt");
        FILE *cmdptr = fopen("commandline.txt", "w");
        fclose(cmdptr);
        mode = 0;
        print_modebar(cmd_string+strlen(":saveas "), 1);
    }
    else if(strcmp(cmd_string, ":undo")){
        char *filename = (char *)calloc(100, sizeof(char));
        for(int i = 9; i < locsaved-1; i++){
            filename[i-9] = (char)mvinch(MAX_X-2, i);
        }
        undo(filename);
        FILE *cmdptr = fopen("commandline.txt", "w");
        fclose(cmdptr);
        mode = 0;
        print_modebar(filename, 1);
        free(filename);
    }
    else if(cmd_string[0] == '\\'){
        char *filename = (char *)calloc(100, sizeof(char));
        for(int i = 9; i < locsaved-1; i++){
            filename[i-9] = (char)mvinch(MAX_X-2, i);
        }
        char *string = (char *)calloc(200, sizeof(char));
        strcat(string, cmd_string+1);
        strcat(string, " -file /");
        strcat(string, "temporary2.txt");
        strcat(string, " -all");
        find(string);
        print_modebar(filename, mvinch(MAX_X-2, locsaved) == (int)'+');
    }
    else if(strncmp(cmd_string, ":replace -str1 ", strlen(":replace -str1 "))){
        if(strstr(cmd_string, "-file ") == NULL){
            char *filename = (char *)calloc(100, sizeof(char));
            char *string = (char *)calloc(200, sizeof(char));
            for(int i = 9; i < locsaved-1; i++){
                filename[i-9] = (char)mvinch(MAX_X-2, i);
            }
            int k = 0;
            while((cmd_string[k] != NULL) || (strcmp(cmd_string+k, " -all")) || strcmp(cmd_string+k, " -at")){
                k++;
            }
            strncat(string, cmd_string+strlen(":replace -str1 "), k-strlen(":replace -str1 "));
            strcat(string, "-file /temporary.txt");
            strcat(string, cmd_string+k);
            replace(string);
        }
        else{
            replace(cmd_string+strlen(":replace -str1 "));
        }
    }
    else if(cmd_string[0] = '='){
        char *filename = (char *)calloc(100, sizeof(char));
        for(int i = 9; i < locsaved-1; i++){
            filename[i-9] = (char)mvinch(MAX_X-2, i);
        }
        indent(filename);
    }
//---------------------------------------------------------------------------------------------------
    arm = strstr(command, comms[24]) != NULL;
    if(string_checker(command, comms[0], strlen(comms[0])))
        create(command + strlen(comms[0]) + 1);
    else if(string_checker(command, comms[1], strlen(comms[1])))
        insert(command + strlen(comms[1]) + 1);
    else if(string_checker(command, comms[4], strlen(comms[4])))
        cat(command + strlen(comms[4]) + 1);
    else if(string_checker(command, comms[5], strlen(comms[5])))
        remoove(command + strlen(comms[5]) + 1);
    else if(string_checker(command, comms[7], strlen(comms[7])))
        copy(command + strlen(comms[7]) + 1);
    else if(string_checker(command, comms[8], strlen(comms[8]))){
        copy(command + strlen(comms[8]) + 1);
        remoove(command + strlen(comms[8]) + 1);
    }
    else if(string_checker(command, comms[9], strlen(comms[9])))
        paste(command + strlen(comms[9]) + 1);
    else if(string_checker(command, comms[10], strlen(comms[10])))
        find(command + strlen(comms[10]));
    else if(string_checker(command, comms[27], strlen(comms[27])))
        replace(command + strlen(comms[27]));
    else if(string_checker(command, comms[16], strlen(comms[16])))
        grep(command + strlen(comms[16]));
    else if(string_checker(command, comms[23], strlen(comms[23])))
        undo(command + strlen(comms[23]) + 1);
    else if(string_checker(command, comms[22], strlen(comms[22])))
        indent(command + strlen(comms[22]) + 1);
    else if(string_checker(command, comms[19], strlen(comms[19])))
        compare(command + strlen(comms[19]) + 1);
    else if(string_checker(command, comms[20], strlen(comms[20])))
        tree(command + strlen(comms[20]));
    else
        printf("invalid command:(\n");
    return ;
}

void empty_smap()
{
	for(int i = 0; i < MAX_X; i++){
		for(int j = 0; j < MAX_Y; j++){
			smap[i][j] = 0;
		}
	}
}

int input_manager(int input)
{
    init_pair(8, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_MAGENTA);
    int temp, pos1, pos2, size = 0;
    if((mode == 2) || (mode == 0)){
        if(input == (int)'e'){
            return 1;
        }
        else if(input == (int)'i')
            mode = 1;
        else if((mode == 2) && (input == (int)'n'))
            mode = 0;
        else if(input == (int)'k'){
            if((x == 4) && (d != 0))
                d--;
            if((d == 0)*(x > 0) + (d != 0)*(x > 4)){
                if(s == 1)
                    smap[x][y] = smap[x][y] == 0;
                y = (endpositionl[x] <= y)*endpositionl[x] + (endpositionl[x] > y)*y;
                x -= 1;
                if(s == 1)
                    smap[x][y] = 1;
            }
            input = 0;
        }
        else if(input == (int)'j'){
		    if((x == MAX_X-5) && (x+d < line))
			    d++;
            if((d == 0)*(x < line-1) + (d != 0)*(x < MAX_X-5)){
		        if(s == 1)
			        smap[x][y] = smap[x][y] == 0;
                y = (endpositionl[x+2] <= y)*endpositionl[x+2] + (endpositionl[x+2] > y)*y;
                x += 1;
                if(s == 1)
                    smap[x][y] = 1;
            }
            input = 0;
        }
        else if(input == (int)'h'){
		    if((y == 4) && (r != 0))
			    r--;
            if((r == 0)*(y > 1+digit_counter(x+1)) + (r != 0)*(y > 4)){
		        if(s == 1)
			        smap[x][y] = smap[x][y] == 0;
		        y -= 1;
                if(s == 1)
                    smap[x][y] = 1;
	        }
            input = 0;
        }
        else if(input == (int)'l'){
		    if((y == MAX_Y-5) && (y+r < endpositionl[x+1]))
			    r++;
            if((r == 0)*(y < endpositionl[x+1]) + (r != 0)*(y < MAX_Y-5)){
		        if(s == 1)
			        smap[x][y] = smap[x][y] == 0;
		        y += 1;
                if(s == 1)
                    smap[x][y] = 1;
	        }
            input = 0;
	    }
	    else if(input == (int)'s'){
            s = (s == 0);
            if(s == 1)
                mode = 2;
            else if(s == 0)
                empty_smap();
            input = 0;
	    }
        else if(((input == (int)'y') || (input == (int)'d')) && (mode == 2)){
            if(s != 0){
                select_pos[1][0] = x;
                select_pos[1][1] = y;
                int max = (select_pos[0][0] < select_pos[1][0]);
                int min = (select_pos[0][0] > select_pos[1][0]);
                pos1 = select_pos[min][0] + 1;
                pos2 = select_pos[min][1];
                size = endposition[select_pos[max][0]+1]-endposition[select_pos[min][0]+1]+endpositionl[select_pos[min][0]+1]-select_pos[min][1]+1;
                FILE *cmptr = fopen("commandgen.txt", "w+");
                if(input == 'y')
                    fprintf(cmptr, "copystr -file temporary2.txt -pos %d:%d -size %d -f", pos1, pos2, size);
                else if(input == 'd')
                    fprintf(cmptr, "cutstr -file temporary2.txt -pos %d:%d -size %d -f", pos1, pos2, size);
                fseek(cmptr, 0, SEEK_END);
                int file_size = ftell(cmptr);
                fseek(cmptr, 0, SEEK_SET);
                char *string = (char *)calloc(file_size+1, sizeof(char));
                fread(string, sizeof(char), file_size, cmptr);
                //command_controller(string);
                free(string);
                fclose(cmptr);
            }
        }
        else if((input == (int)'p') && (mode == 2)){
            FILE *cmptr = fopen("commandgen.txt", "w+");
            fprintf(cmptr, "pastestr -file temporary2.txt -pos %d:%d", x+1, y);
            fseek(cmptr, 0, SEEK_END);
            int file_size = ftell(cmptr);
            fseek(cmptr, 0, SEEK_SET);
            char *string = (char *)calloc(file_size+1, sizeof(char));
            fread(string, sizeof(char), file_size, cmptr);
            //command_controller(string);
            free(string);
            fclose(cmptr);
        }
        else if(((input == (int)'/') || (input == (int)':')) && (mode == 0)){
            mode = 10;
	    x_past = x;
	    y_past = y;
	    FILE *cmdptr = fopen("commandline.txt", "r");
	    fseek(cmdptr, 0, SEEK_END);
	    int cmd_size = ftell(cmdptr);
	    fseek(cmdptr, 0, SEEK_SET);
	    char *cmd_string = (char *)calloc(cmd_size+1, sizeof(char));
	    fread(cmd_string, sizeof(char), cmd_size, cmdptr);
	    x = MAX_X+1;
	    y = cmd_size;
	    free(cmd_string);
	    fclose(cmdptr);
        }
    }
    else if(mode == 1){
	    if(input == (int)'|')
		    mode = 0;
	    else{
            int loc = y-digit_counter(x+1)+endposition[x];
            char in = input;
            FILE *tptr = fopen("temporary2.txt", "r");
            fseek(tptr, 0, SEEK_END);
            int temp_size = ftell(tptr);
            fseek(tptr, 0, SEEK_SET);
            char *temp_string = (char *)calloc(temp_size+2, sizeof(char));
            fread(temp_string, sizeof(char), loc, tptr);
	    temp_string[loc] = in;
            fread(temp_string+loc+1, sizeof(char), temp_size-loc, tptr);
            fclose(tptr);
            tptr = fopen("temporary2.txt", "w");
            fputs(temp_string, tptr);
            fclose(tptr);
            free(temp_string);
	    if(in == 10){
		    x += 1;
		    y = digit_counter(x+1)+1;
	    }
	    else
            	y++;
	    }
    }
    else if(mode == 10){
        if((input == (int)'~') || (input == KEY_ENTER)){
            y = -1;
            x = -1;
            command_controller();
            mode = 0;
        }
	else if(input == (int)'+'){
		FILE *genptr = fopen("commandgen.txt", "w+");
		fprintf(genptr, "commandline.txt -pos %d:%d -size %d -b", 1, y-1, 1);
		char *tomp = (char *)calloc(100, sizeof(char));
		fread(tomp, sizeof(char), 100, genptr);
//		printw("%s", tomp);
		remoove(tomp);
		fclose(genptr);
		free(tomp);
		y--;
	}
        else if(input == (int)'|'){
            mode = 0;
	    x = x_past;
	    y = y_past;
	}
        else{
            y++;
	    FILE *cmdptr = fopen("commandline.txt", "r");
	    fseek(cmdptr, 0, SEEK_END);
	    int cmd_size = ftell(cmdptr);
	    fseek(cmdptr, 0, SEEK_SET);
	    char *cmd_string = (char *)calloc(cmd_size+1, sizeof(char));
	    fread(cmd_string, sizeof(char), cmd_size, cmdptr);
	    fclose(cmdptr);
	    cmdptr = fopen("commandline.txt", "w");
            fprintf(cmdptr, "%s%c", cmd_string, (char)input);
	    free(cmd_string);
            fclose(cmdptr);
        }
    }
    return 0;
}

int main()
{
	initscr();
	refresh();
	srand(time(NULL));
	start_color();
//	nodelay(stdscr, 1);
	noecho();
	int input;
	while(1){
        clear();
        print_default();
        print_modebar("untitled", 0);
        print_maintext();
        move(x, y);
        input = getch();
        if (input_manager(input))
            break;
        refresh();
    }
    endwin();
    return 0;
}
