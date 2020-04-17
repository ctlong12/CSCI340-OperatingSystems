
int check(char string[]){

    int length = strlen(string);
    //int test_i;

    //printf("%d\n", length);

    for(int walk = 0; walk <= length; walk++){
        //test_i = isdigit(string[walk]);
        //printf("walk: %d char: %c test_i: %d\n", walk, string[walk], test_i);
        if(isdigit(string[walk]) == 0 && string[walk] != '\0'){
            
            return 0;
        }
    }
    
    return 1;
}
