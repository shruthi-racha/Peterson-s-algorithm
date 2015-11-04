#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void file_access(int n)
{
    FILE *fptr;
    char c = ' ';
    switch(n)
    {
             case 1:fptr = fopen("resource.txt","r");
                    if(fptr == NULL)
                    {
                            printf("\nERROR:File doesn't exist");
                            return; 
                    }
                    while((c = fgetc(fptr))!=EOF)
                    {
                        printf("%c",c);
                    } 
                    fclose(fptr);
                    break;  
             case 0:fptr = fopen("resource.txt","a+");
                    if(fptr == NULL)
                    {
                            printf("\nERROR:File doesn't exist");
                            return; 
                    }
                    printf("\nEnter text to be written into file,press z to terminate\n");
                    scanf("%c",&c);  
                              
                    while(c != 'z')
                    {
                        fprintf(fptr,"%c",c);
                        scanf("%c",&c);
                    } 
                    fclose(fptr);
                    break;                              
    }
    return;
}

void new_process(int process_num)
{
     int n,r;
     switch(process_num)
     {
            case 1:printf("\n--------------------------------------");
                   printf("\nEntry in Critical Section of Process 1");
                   printf("\n\nContents of File resource.txt");
                   file_access(1);
                   printf("\n\nExit from Critical Section of Process 1");
                   printf("\n---------------------------------------\n");
                   break;
            case 0:printf("\n--------------------------------------");
                   printf("\nEntry in Critical Section of Process 2");
                   printf("\n\nWrite into File resource.txt\n");
                   file_access(0);
                   printf("\n\nExit from Critical Section of Process 2");
                   printf("\n---------------------------------------\n");
                   break;
     }
                        
}


main()
{
      int turn,select,loopv;
      int flag[2]={0,0};
      int i=1,j=2;
      i=rand();
      if(i==0) 
               j=1;
      else
              { j=0;i=1;}
    
     do
      {
      printf("\nProcess 1:Read and display a file named resource.txt\n\nProcess 2:Write into a file named resource.txt");
      printf("\n\nEnter the Process to run first ");
      scanf("%d",&select);
      
      //Peterson's Algorithm
      
        flag[i]=1;
        turn=j;
        while(flag[j] && turn == j )
        {
        //check to see if the flag is set for the other process, 
        //if yes then execute that process first
             printf("\nPlease Wait till the current process completes\n");
             new_process(j);
             flag[j]=0;
        //this executes the other process and clears the flag 
        //allowing the selected process to execute
        };
        //critical section
        {
             new_process(i);   //Run the process selected   
        }
          
          flag[i]=0;    //clear the flag allowing the next process to execute
        //remainder section
        {
             new_process(j);
             flag[j]=0;
             printf("\nDo you want to continue? Press 1 to Continue 0 to Exit: ");
             scanf("%d",&loopv);
             i=i+j;
             j=i-j;
             i=i-j;
        }
                
      }while(loopv);
}
