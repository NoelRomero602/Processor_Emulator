


#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include <algorithm>
#define N 3

using namespace std;

int  add_vector(int v[]);
void error_exit(string s);


class Processor {
public:
    int PC ;
    int SP ;
    int IR ;
    int AC ;
    int X ;
    int Y ;
    Processor(){
        this->PC = 0;
        this->SP = 0;
        this->IR = 0;
        this->AC = 0;
        this->X  = 0;
        this->Y  = 0;
    }

};

class Memory {
public:
    string list [2000];
    int index;
    Memory(){
        index = 0;
    }

    void populateMemory(string str, int index)
    {

            istringstream parser(str);

            parser >> list[index];


    }

    string getListValueAtIndex()
    {
        return this->list[this->index];
    }

    int getIndex() const {
        return index;
    }

    void setIndex(int index) {
        Memory::index = index;
    }

};


int main()
{
Processor processor_obj ;
ifstream  infile;
Memory memory_obj;
infile.open("./sample1.txt");
string content;

int pipefds1[2], pipefds2[2];

int pid;

int index = 0;


    while (!infile.eof())
    {
        getline(infile,content);
        if(content != "") {
            memory_obj.populateMemory(content, index);
            ++index;
        }
    }


    for(int i = 0; i< index ; i++)
    {
        cout<<"\n"<<memory_obj.list[i];
    }

if (pipe(pipefds1) == -1)
{
    error_exit("unable to create pipe1");
}

if(pipe(pipefds2) == -1 )
{
    error_exit("unable to create pipe2");
}

    pid = fork();

  if(pid != 0)
  {
      close(pipefds1[0]); // Close the unwanted pipe1 read side
      close(pipefds2[1]); // Close the unwanted pipe2 write side
      cout<<"\n inside of parent";

      char readmessage[20];

      write(pipefds1[1], &processor_obj.PC,sizeof(int));

      read(pipefds2[0],readmessage,sizeof(readmessage));

      printf("\n At parent this is message from child %s  ", readmessage);

  }
  else
  {
      close(pipefds1[1]); // Close the unwanted pipe1 write side
      close(pipefds2[0]); // Close the unwanted pipe2 read side

      read(pipefds1[1],&memory_obj.index,sizeof(int) );

      printf("\n At the child value returned from parent is: %d ", memory_obj.index);
      printf("\n value in the array to be returned: %s", memory_obj.getListValueAtIndex().c_str());

      write
  }


  //  printf("\n%s",String.c_str());

infile.close();


//    int a[N][N] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}},
//            i, row_sum, sum =0,
//            pd[2];                              /* pipe descriptors */
//
//    if (pipe(pd) == -1)                    /* create a pipe */
//        error_exit("pipe() failed");
//
//    for (i=0; i < N; i++)
//    {
//        if (fork() == 0)                    /* child process */
//        {
//            row_sum = add_vector(a[i]);
//            if (write(pd[1], &row_sum, sizeof(int)) == -1)
//               error_exit("write() failed");
//            _exit(0);                       /* exit from child */
//        }
//    }
//
//    for (i = 0;  i < N; ++i)
//    {
//        if (read(pd[0], &row_sum, sizeof(int)) == -1)
//           error_exit("read() failed");
//        sum += row_sum;
//    }
//
//    for (i = 0;  i < N; ++i)
//        waitpid(-1, NULL, 0);
//
//    printf("Sum of the array = %d\n", sum);

    return 0;
}

int add_vector(int v[])
{
    int i, vector_sum=0;

    for (i = 0; i < N;  ++i)
        vector_sum += v[i];

    return vector_sum;
}


void error_exit(string s)
{
    fprintf(stderr,"\nERROR: %s - bye!\n", s.c_str());
    exit(1);
}



