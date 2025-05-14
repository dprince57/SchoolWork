#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    for(int i=0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    if(argc <= 1){
        printf("Usage: ./exec 'Word1' 'Word2' .... 'LastWord'\n");
        printf("Highest: \nLowest: \n");
        return 0;
    }
    //Set our vars to empty before starting.
    char *smallest = argv[2];
    char *biggest = argv[2];

    int all_ok = 1;
    for(int i=2; i < argc; i++) {
        if(strcmp(argv[i], smallest) < 0)smallest = argv[i];
        if(strcmp(argv[i], biggest) > 0)biggest = argv[i];
        if(strcmp(argv[i], argv[i-1]) < 0){
            printf("Not in order, %s should be after %s.\n",
            argv[i-1], argv[i]);
            all_ok = 0;
        }
    }
    if(argc == 1)all_ok = 0;
    if (all_ok) printf("In alphabetical order\n");
    printf("Highest: %s\nLowest: %s\n",biggest,smallest);
    return 0;
}
