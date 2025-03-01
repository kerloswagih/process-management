#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
 
struct student {
    int midterm;
    int final;
 };

 int main(int argc,char *argv[])      // as in file handling using c lab 
 {
    struct student * student;
    FILE * fileptr;
    if(argc!=4)    // if the number of arguments is not equal to 4 we terminate the program as it read wrong number of arguments
    {
        printf("Usage: %s filename\n",argv[0]);
        exit(1);
    }
    char * filepath = argv[1];    // atoi converts string to integer
    int N_of_TAs = atoi(argv[2]);        
    int min_pass_grade = atoi(argv[3]);        
    fileptr = fopen(filepath,"r"); // read only access
    if(fileptr == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    int number_of_students;    
    fscanf(fileptr,"%d",&number_of_students);
    student = malloc(number_of_students*sizeof(struct student));  // here we want to allocate memory for the number of students i have in the first line of the file dynamic using malloc
    for (int i = 0; i < number_of_students; i++)
    {
        fscanf(fileptr,"%d %d",&student[i].midterm,&student[i].final);
    }
fclose(fileptr);
int students_each_ta=number_of_students / N_of_TAs;
int the_remaining=number_of_students % N_of_TAs;
int array[N_of_TAs];

for(int i=0;i<N_of_TAs;i++)
{
int pid=fork();
if(pid==-1)
{
    perror("error in fork");
}
else if(pid==0)
{
    int start_place,end_place;
    start_place = i * students_each_ta;
    end_place = start_place + students_each_ta;
    if(i==N_of_TAs-1) // remainig students added to the last TA 
    {
        end_place += the_remaining;
    }
    int count=0;
    for(int j=start_place;j<end_place;j++)
    {
        if(student[j].midterm + student[j].final >= min_pass_grade)
        {
            count++;       // count students who passed for each TA
        }
    }
    free(student);
    exit(count);     // we termeinate child process and return the count of students who passed as exit code
    }
  
}
for(int i=0;i<N_of_TAs;i++)
{
    int stat_loc;
    wait(&stat_loc);    // i used this as blocking call to wait until child process terminates
    if(!(stat_loc & 0xFF))
    {
        array[i]= (stat_loc >> 8) & 0xFF;  // i used this to get the exit code of the child process that is equal to count 
    }
}
for(int i=0;i<N_of_TAs;i++)
{
    printf("%d ", array[i]);
}
printf("\n");
return 0;
}
