#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <windows.h>

char log[100][2][1000];
int log_size = 0;
int arm;

const char comms[28][18] = {"createfile -file ", "insertstr -file ", " -str", " -pos", "cat -file ", "removestr -file ", " -size",
                             "copystr -file ", "cutstr -file ", "pastestr -file ", "find -str ", " -file", " -count", " -at ", " -byword", " -all",
                             "grep -", " -files", " /root", "compare ", "tree ", "arm", "auto-indent ", "undo -file ", " =D "و " -str1", " -str2",
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
    int num = 0, i = 0;
    while((command[i+start] < 58) && (command[i+start] > 47)){
        num *= 10;
        num += (command[i+start] - 48);
        i++;
    }
    return num;
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
                printf("already exist!\n");
                fclose(fptr);
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
        printf("File doesn't exist\n");
        fclose(fptr);
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
    strcpy(log[log_size-1][0], ad_name);
    strcpy(log[log_size-1][1], "");
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
    FILE *tptr = fopen("temporary.txt", "w");
    fclose(tptr);
    tptr = fopen("temporary.txt", "a+");
    FILE *fptr = fopen(ad_name, "r");
    if(fptr == NULL){
        fprintf(tptr, "File doesn't exist\n");
        fclose(fptr);
        free(ad_name);
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
        printf("%s", string);
        free(string);
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
        printf("File doesn't exist\n");
        fclose(fptr);
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
    strcpy(log[log_size-1][0], ad_name);
    strcpy(log[log_size-1][1], string);
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
    else{
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
        printf("File doesn't exist\n");
        fclose(fptr);
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
    OpenClipboard(0);
    EmptyClipboard();
    HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, size+1);
    memcpy(GlobalLock(h), string+k, size+1);
    GlobalUnlock(h);
    SetClipboardData(CF_TEXT, h);
    CloseClipboard();
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
        printf("File doesn't exist\n");
        fclose(fptr);
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
    strcpy(log[log_size-1][0], ad_name);
    strcpy(log[log_size-1][1], string);
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
    OpenClipboard(0);
    HANDLE out = GetClipboardData(CF_TEXT);
    fwrite(string, sizeof(char), k, fptr);
    fprintf(fptr, "%s", (char *) out);
    fwrite(string + k,sizeof(char), file_size-k, fptr);
    CloseClipboard();
    free(string);
    free(ad_name);
    fclose(fptr);
}

void find(char *command)
{
    int i = 0, string_size, flag = 0, stat = 0, temp, adress_size, at, star = -1, file_size;
    while(!string_checker(command+i, comms[11], strlen(comms[11]))){
        i++;
    }
    string_size = i;
    if((command[0] == 92) && (command[i-1] == 92)){
        string_size -= 2;
        flag = 1;
    }
    temp = i;
    while(temp < strlen(command)){
        if(string_checker(command + temp, comms[12], strlen(comms[11]))){
            if(stat == 0)
                adress_size = temp-i-strlen(comms[11])-2;
            stat += 1;
        }
        else if(string_checker(command + temp, comms[15], strlen(comms[14]))){
            if(stat == 0)
                adress_size = temp-i-strlen(comms[11])-2;
            stat += 2;
        }
        else if(string_checker(command + temp, comms[13], strlen(comms[12]))){
            if(stat == 0)
                adress_size = temp-i-strlen(comms[11])-2;
            stat += 4;
            at = num_maker(command + temp + strlen(comms[12]));
        }
        else if(string_checker(command + temp, comms[14], strlen(comms[13]))){
            if(stat == 0)
                adress_size = temp-i-strlen(comms[11])-2;
            stat += 8;
        }
        temp++;
    }
    if(stat == 0)
        adress_size = temp-i-strlen(comms[10])-2;
    i += strlen(11) + 2;
    char *ad_name = (char *)calloc(adress_size+1, sizeof(char));
    int start = i;
    while(i-start < adress_size){
        ad_name[i-start] = command[i];
        i++;
    }
    FILE *fptr = fopen(ad_name, "r");
    if(fptr == NULL){
        printf("File doesn't exist\n");
        fclose(fptr);
        free(ad_name);
        return ;
    }
    fseek(fptr, 0, SEEK_END);
    file_size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    char *file_string = (char *)calloc(file_size+1, sizeof(char));
    fread(file_string, sizeof(char), file_size, fptr);
    fclose(fptr);
    char *string = (char *)calloc(string_size+1, sizeof(char));
    int k = flag, s = 0;
    while(k < string_size){
        if((command[k] == 92) && (command[k+1] == '*')){
            string[s] = '*';
            s += 1;
            k += 2;
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
    FILE *tptr = fopen("temporary.txt", "w");
    fclose(tptr);
    tptr = fopen("temporary.txt", "a+");
    //------------------------------------------------------------------------------------------------------------------------
    while(k < file_size){
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
                    fprintf(tptr, "%d", (k+1)*(stat == 0)+(word_counter)*(stat == 8));
                else
                    fprintf(tptr, ",%d", (k+1)*(stat == 0)+(word_counter)*(stat == 8));
                all++;
            }
        }
        else if((star == -1) && ((stat == 4) || (stat == 12))){
            if(string_checker(string, file_string+k, s))
                count++;
            if(count == at){
                fprintf(tptr, "%d", (k+1)*(stat == 0)+(word_counter)*(stat == 8));
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
                            fprintf(tptr, "%d", (k+1)*(stat == 2)+(word_counter)*(stat == 10));
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
        printf("%s", string);
        free(string);
    }
    else
        arman(strstr(command, comms[24]) + strlen(comms[24]));
    fclose(tptr);
    return ;
}

void replace(char *command)
{
    int i = 0, string_size1, string_size2, flag1 = 0, flag2 = 0, stat = 0, temp, adress_size, at = 1, star = -1, file_size;
    while(!string_checker(command+i, comms[26], strlen(comms[26]))){
        i++;
    }
    string_size1 = i;
    if((command[0] == 92) && (command[i-1] == 92)){
        string_size1 -= 2;
        flag1 = 1;
    }
    while(!string_checker(command+i, comms[11], strlen(comms[11]))){
        i++;
    }
    string_size2 = i-(string_size1 + 2*flag1)-strlen(comms[26])-1;
    if((command[string_size1 + 2*flag1 + strlen(comms[26]) + 1] == 92) && (command[i-1] == 92)){
        string_size2 -= 2;
        flag2 = 1;
    }
    temp = i;
    while(temp < strlen(command)){
        if(string_checker(command + temp, comms[15], strlen(comms[14]))){
            if(stat == 0)
                adress_size = temp-i-strlen(comms[11])-2;
            stat += 2;
        }
        else if(string_checker(command + temp, comms[13], strlen(comms[12]))){
            if(stat == 0)
                adress_size = temp-i-strlen(comms[11])-2;
            stat += 4;
            at = num_maker(command + temp + strlen(comms[12]));
        }
        temp++;
    }
    if(stat == 0)
        adress_size = temp-i-strlen(comms[11])-2;
    i += strlen(11) + 2;
    char *ad_name = (char *)calloc(adress_size+1, sizeof(char));
    int start = i;
    while(i-start < adress_size){
        ad_name[i-start] = command[i];
        i++;
    }
    FILE *fptr = fopen(ad_name, "r");
    if(fptr == NULL){
        printf("File doesn't exist\n");
        fclose(fptr);
        free(ad_name);
        return ;
    }
    fseek(fptr, 0, SEEK_END);
    file_size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    char *file_string = (char *)calloc(file_size+1, sizeof(char));
    fread(file_string, sizeof(char), file_size, fptr);
    fclose(fptr);
    strcpy(log[log_size-1][0], ad_name);
    strcpy(log[log_size-1][1], file_string);
    log_size++;
    char *message1 = (char *)calloc(string_size1+1, sizeof(char));
    int k = flag1, s = 0;
    while(s < string_size1){
        if((command[k] == 92) && (command[k+1] == '*')){
            message1[s] = '*';
            s += 1;
            k += 2;
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
    char *message2 = (char *)calloc(string_size2+1, sizeof(char));
    k = flag2 + string_size1 + 2*flag1 +strlen(comms[26]) + 1;
    s = 0;
    while(s < string_size2){
        message1[s] = command[k];
        s++;
        k++;
    }
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
    FILE *tptr = fopen("temporary.txt", "w");
    fclose(tptr);
    FILE *fptr = fopen(ad_name, "w");
    tptr = fopen("temporary.txt", "a+");
    //------------------------------------------------------------------------------------------------------------------------
    while(k < file_size){
        if(((file_string[k] == ' ') || (file_string[k] == '\n')) && ((file_string[k+1] != ' ') || (file_string[k+1] != '\n')))
            word_counter++;
        if((star == -1) && (stat == 2)){
            if(string_checker(message1, file_string+k, s)){
                strncpy(ans, file_string+l, k-l);
                strcpy(ans, message2);
                l = k + strlen(message1);
            }
        }
        else if((star == -1) && ((stat == 4) || (stat == 0))){
            if(string_checker(message1, file_string+k, s))
                count++;
            if(count == at){
                strncpy(ans, file_string+l, k-l);
                strcpy(ans, message2);
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
                        strncpy(ans, file_string+l, k-l);
                        strcpy(ans, message2);
                        l = k + mount + strlen(string2);
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
                            strncpy(ans, file_string+l, k-l);
                            strcpy(ans, message2);
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
    int i = 0, start = 0;
    while(string_checker(command+i, comms[2], strlen(comms[2]))){
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
    int count = 0;
    FILE *tptr = fopen("temporary.txt", "w");
    fclose(tptr);
    tptr = fopen("temporary.txt", "a+");
    while((!string_checker(command+i, comms[24], strlen(comms[24])))*(arm == 1) || (i < strlen(command))*(arm == 0)){
        if(string_checker(command+i, comms[18], strlen(comms[18]))){
            i += 2;
            //---------------------------------------------------------------
            FILE *fptr = fopen(ad_name, "r");
            if(fptr == NULL){
                fprintf(tptr, "file %s not found\n", ad_name);
                fclose(fptr);
            }
            else{
                char *file_string = (char *)calloc(100, sizeof(char));
                int l = 0;
                while(!feof(fptr)){
                    fgets(file_string, 100, fptr);
                    l = 0;
                    while((l < 100) && (file_string[l] != NULL)){
                        if(string_checker(string, file_string + l, stat-first-flag)){
                            if(command[0] == 's'){
                                fprintf(tptr, "%s : %s\n", ad_name, file_string);
                            }
                            else if(command[0] == 'c'){
                                count++;
                            }
                            else if(command[0] == 'l'){
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
    }
    if(command[0] == 'c')
        fprintf(tptr, "%d", count);
    free(string);
    free(ad_name);
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

void undo(char *command)
{
    FILE *fptr;
    for(int i = log_size; i > -1; i--){
        if(string_checker(command, log[i][0], sizeof(log[i][0]))){
            fptr = fopen(command, "r");
            if(fptr == NULL){
                printf("File doesn't exist\n");
                fclose(fptr);
                return ;
            }
            fclose(fptr);
            fptr = fopen(command, "w");
            fputs(log[i][1], fptr);
            fclose(fptr);
            return ;
        }
    }
    printf("NO history!\n");
    return ;
}

int find_most(char *string, int loc, char side)
{
    int k , mount = 0, ans = -1;
    if(side == 'l'){
        while((sting[loc+mount] != '\n') && (sting[loc+mount] != NULL) && (loc+mount >= 0) && ((string[loc+mount] != '{') || (string[loc+mount] != '}'))){
            if(string[loc+mount] != ' ')
                ans = loc+mount;
            mount--;
        }
        return ans;
    }
    else{
        while((sting[loc+mount] != '\n') && (sting[loc+mount] != NULL) && (loc+mount >= 0) && ((string[loc+mount] != '{') || (string[loc+mount] != '}'))){
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
        printf("File doesn't exist\n");
        fclose(fptr);
        free(ad_name);
        return ;
    }
    fseek(fptr, 0, SEEK_END);
    file_size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    char *string = (char *)calloc(file_size+1, sizeof(char));
    fread(string, sizeof(char), file_size, fptr);
    fclose(fptr);
    strcpy(log[log_size-1][0], ad_name);
    strcpy(log[log_size-1][1], string);
    log_size++;
    fptr = fopen(ad_name, "w");
    int l = 0, r = 0, mount, count = 0, k = 0;
    for(k < file_size){
        if(string[k] == '{'){
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
        else if(string[k] == '}'){
            l = find_most(string, k-1, 'l');
            r = find_most(string, k-1, 'r');
            for(int j = 0; j < count; j++){
                fprintf(fptr, "\t");
            }
            if(l != -1){
                fwrite(string+l, sizeof(char), r-l+1, fptr);
                fprintf(fptr, "\n");
            }
            fprintf(fptr, "}\n");
            count--;
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
    char *ad_name1 = (char *)calloc(50, sizeof(char));
    char *ad_name2 = (char *)calloc(50, sizeof(char));
    int i = 0, start = 0;
    while(!string_checker(command+i, comms[18], strlen(comms[18]))){
        ad_name1[i-start] = command[i];
        i++;
    }
    i += 2;
    start = i;
    while(i < strlen(command)){
        if(command[i] == '/'){
            command[i] = '\\';
        }
        ad_name2[i-start] = command[i];
        i++;
    }
    int line1, line2;
    FILE *fptr1 = fopen(ad_name1, "r");
    FILE *fptr2 = fopen(ad_name2, "r");
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
    char *string = (char *)calloc(file_size2+1, sizeof(char));
    fread(string, sizeof(char), file_size2, fptr2);
    line2 = line_counter(string, file_size2);
    free(string);
    int l1, r1 = -2, l2, r2 = -2, length, word_Counter1 = 0, word_Counter2 = 0, fail = 0, max_l, line = 1, left1, right1, left2, right2;
    while((!feof(fptr1)) && (!feof(fptr2))){
        char *string1 = (char *)calloc(100, sizeof(char));
        char *string2 = (char *)calloc(100, sizeof(char));
        fgets(string1, 100, fptr1);
        fgets(string2, 100, fptr2);
        length = strlen(string1) * (strlen(string1) >= strlen(string2)) + strlen(string2) * (strlen(string1) < strlen(string2));
        if(!string_checker(string1, string2, length)){
            fail = 0;
            for(int k = 0; k < length; k++){
                if((string1[k] == ' ') || ((string1[k] == NULL) && (string1[k-1] != NULL))){
                    word_Counter1++;
                    l1 = r1 + 2;
                    r1 = k-1;
                    if(word_Counter1 == word_Counter2){
                        if((r1-l1 != r2-l2) || ((r1-l1 == r2-l2) && (!string(string1, string2, r1-l1+1)))){
                            fail++;
                            if(fail == 1){
                                left1 = l1;
                                right1 = r1;
                                left2 = l2;
                                right2 = r2;
                            }
                            else if(fail > 1){
                                printf("============ #%d ============\n", line);
                                puts(string1);
                                puts(string2);
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
                        if((r1-l1 != r2-l2) || ((r1-l1 == r2-l2) && (!string(string1, string2, r1-l1+1)))){
                            fail++;
                            if(fail == 1){
                                left1 = l1;
                                right1 = r1;
                                left2 = l2;
                                right2 = r2;
                            }
                            else if(fail > 1){
                                printf("");
                                puts(string1);
                                puts(string2);
                                break;
                            }
                        }
                    }
                }
            }
        }
        if(fail == 1){
            string1[left1-1] = NULL;
            string1[right1+1] = NULL;
            string2[left2-1] = NULL;
            string2[right2+1] = NULL;
            printf("============ #%d ============\n%s >>%s<< %s\n%s >>%s<< %s", line, string1, string1+left1, string1+right1+2, string2, string2+left2, string2+right2+2);
        }
        line++;
        free(string1);
        free(string2);
    }
    if(!feof(fptr1) && feof(fptr2)){
        printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n", line+1, line2);
        while(!feof(fptr2)){
            char *string2 = (char *)calloc(100, sizeof(char));
            fgets(string2, 100, fptr2);
            puts(string2);
            free(fptr2);
        }
    }
    else if(feof(fptr1) && !feof(fptr2)){
        printf("<<<<<<<<<<<< #%d - #%d <<<<<<<<<<<<", line+1, line1);
        while(!feof(fptr1)){
            char *string1 = (char *)calloc(100, sizeof(char));
            fgets(string1, 100, fptr1);
            puts(string1);
            free(fptr1);
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    free(ad_name1);
    free(ad_name2);
    return ;
}

void listdirectory(char *dirname, int depth, int curdepth, int next_situation)
{
    if((curdepth > depth) && (depth != -1))
        return ;
    DIR *dir = opendir(dirname);
    if(dir == NULL)
        return ;
    struct dirent *subdir;
    subdir = readdir(dir);
    FILE *fptr;
    FILE *tptr = fopen("temporary.txt", "w");
    fclose(tptr);
    tptr = fopen("temporary.txt", "a");
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
        fclose(tptr);
        char *dir_name = (char *)calloc(100, sizeof(char));
        strcat(dir_name, dirname);
        strcat(dir_name, "/");
        strcat(dir_name, name);
        fptr = fopen(dir_name, "r");
        if((fptr == NULL) && !string_checker(name, ".", 1) && !string_checker(name, "..", 1)){
            listdirectory(dir_name, depth, curdepth+1, (subdir != NULL));
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
        printf("invalid depth\n");
        return ;
    }
    listdirectory("root", depth, 1, 0);
    if(arm == 0){
        FILE *tptr = fopen("temporary.txt", "r");
        fseek(tptr, 0, SEEK_END);
        int file_size = ftell(tptr);
        fseek(tptr, 0, SEEK_SET);
        char *string = (char *)calloc(file_size+1, sizeof(char));
        fread(string, sizeof(char), file_size, tptr);
        printf("%s", string);
        free(string);
        fclsoe(tptr);
    }
    else
        arman(strstr(command, comms[24]) + strlen(comms[24]));
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
        strncpy(temp, command, (size_t)(strstr(command, comms[3])-command));
        strcpy(temp, comms[2]);
        strcpy(temp, " \"");
        strcpy(temp, string);
        strcpy(temp, "\"");
        strcpy(temp, strstr(command, comms[3]));
        insert(temp + strlen(comms[1]) + 1);
    }
    else if(string_checker(command, "find", 4)){
        strcpy(temp, "find");
        strcpy(temp, comms[2]);
        strcpy(temp, " \"");
        strcpy(temp, string);
        strcpy(temp, "\"");
        strcpy(temp, command+4);
        find(command + strlen(comms[10]));
    }
    else if(string_checker(command, "replace", 7)){
        strcpy(temp, "replace");
        strcpy(temp, " -str1");
        strcpy(temp, " \"");
        strcpy(temp, string);
        strcpy(temp, "\"");
        strcpy(temp, command+7);
        replace(command + strlen(comms[27]));
    }
    else if(string_checker(command, "grep", 4)){
        strcpy(temp, "grep");
        strcpy(temp, comms[2]);
        strcpy(temp, " \"");
        strcpy(temp, string);
        strcpy(temp, "\"");
        strcpy(temp, command+4);
        grep(command + strlen(comms[16]));
    }
    free(temp);
    free(string);
    fclsoe(tptr);
}

int main()
{
    while(1){
        char *command = (char *)calloc(200, sizeof(char));
        gets(command);
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
            undo(command + strlen(comms[23]) + 1)
        else if(string_checker(command, comms[22], strlen(comms[22])))
            indent(command + strlen(comms[22] + 1))
        else if(string_checker(command, comms[19], strlen(comms[19])))
            compare(command + strlen(comms[19] + 1));
        else if(string_checker(command, comms[20], strlen(comms[20])))
            tree(command + strlen(comms[20]));
        free(command);
        break;
    }
    return 0;
}