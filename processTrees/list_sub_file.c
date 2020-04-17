#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "Numeric_checker.c"

/*
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
*/

typedef struct node{
    int pid;
    int ppid;
    char final[100];
    int vsize;
    int visted;

    struct node *sub_p;
} node;


struct node* print_process_tree(struct node * rt, int tab, struct node* head) {

    struct node* temp = head;


    while (temp != NULL) {
        if(temp->visted == 0){
        
            //printf("tempppid<%d>, rtpid<%d>\n", temp->ppid, rt->pid);            
            
            if(temp->ppid == 0){ // base node 
                temp->visted = 1;
                tab = 0;

                //get rid of the '(' at the start or each string and print the nessceary info from each node
                int length = strlen(temp->final) - 2;
                printf("(%d) %.*s, %d kb\n",
                       temp->pid, length, temp->final + 1, temp->vsize);

                //go find any other node with ppid 0
                print_process_tree(temp, tab, head);
                //look for all the children of this node
                return print_process_tree(temp, tab + 1, head);
            }
        
            //find all the parents children
                if(temp->ppid == rt->pid){
                temp->visted = 1;

                //find all the childs(now new parents) chidlren
                print_process_tree(rt, tab, head);    

                // this just adds the approriate number of tabs for the given line
                for(int j = 0; j < tab +1 ; j++) 
                    printf("  ");                


                //get rid of the '(' at the start or each string and print the nessceary info from each node
                int length = strlen(temp->final) - 2;
                printf("(%d) %.*s, %d kb\n",
                       temp->pid, length, temp->final + 1, temp->vsize);
                
                tab++;
                return print_process_tree(temp, tab + 1, head);
            }
        }
        
        //move to the next node in the linked list
        temp = temp->sub_p;
    }

    // return your root node
    return rt;
}



int main(void)
{
    struct dirent *de; 
   
    DIR *dr = opendir("/proc");

    struct node *head = NULL;
    struct node *n_prev = NULL;

    while ((de = readdir(dr)) != NULL){
        if(check(de->d_name) >= 1){ // make sure each directory only has numbers in the name
            char file_n[] = "/proc/";   //make a string with the file you want to open
            strcat(file_n, de->d_name);
            strcat(file_n, "/stat"); 
        

            FILE *fp; //create a file data type so you can pass somthing to fopen
        
            //info on each file
            int pid; //this files pid
            int ppid;  // this files ppid
            char executable[100];  //this files name of its executable 
            int Vsize; // this files vsize

            
            fp= fopen(file_n, "r"); // open and read from file

            
            if(fp == NULL){
            }
            else{
                fscanf(fp, "%d %s %*s %d %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d", &pid, executable, &ppid, &Vsize);
                fclose(fp); 
            } 
            
            //make nodes for trees
            struct node *n_new = malloc(sizeof(struct node));
            
            // add all member info for each node
            n_new->pid = pid;
            n_new->ppid = ppid;
            n_new->vsize = Vsize;
            n_new->visted = 0; // a variable to track to see if recursion has already printed said node
            strcpy(n_new->final, executable); 
            n_new->sub_p = NULL;


            //make a ll of nodes
            if (head == NULL)
                    head = n_new;
                else
                    n_prev->sub_p = n_new;
                    
             // Save nodes addy
             n_prev = n_new;

        }

    }

    //create a root node to pass to recursive funciton make it null to start
    struct node *rt = NULL;
    
    print_process_tree(rt, 0, head);// recurisive print call
    
    closedir(dr);     
    return 0;
}

