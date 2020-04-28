#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>

int OFFSET = 4;

typedef struct binary{

    char bytes[16];
    int count;
    int buffer;   
  
} binary;


int incrementOffset(int *offset) {
	return *offset * 12;
}


int main(int argc, char *argv[]) {

    int num = 0;

    if (argc != 2) {
        printf("Error: Please enter the correct number of parameters");
        exit(-1);
    }

    binary binary;
    char *fileName = argv[1];
    int fileDesc = open(fileName, O_RDONLY);

    read(fileDesc, &binary.bytes, OFFSET);
    lseek(fileDesc, OFFSET, SEEK_SET);
    read(fileDesc, &binary.count, OFFSET);

    int offset[binary.count];

    int last = incrementOffset(&binary.count);

    lseek(fileDesc, OFFSET, SEEK_SET);

    for(int i = 0; i < last; i++){
        lseek(fileDesc, i, SEEK_SET);
        read(fileDesc, &binary.buffer, OFFSET);
        offset[num] = binary.buffer;
        binary.buffer = 0;

        num++;
    }

    printf("%s \n", binary.bytes);


    return 0;

}
