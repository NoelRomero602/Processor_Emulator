


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

int index = 0; //debugging purposes



    int X = 0;
    int Y = 0;

    while (!infile.eof())
    {
        getline(infile,content);
        if(content != "") {
            memory_obj.populateMemory(content, index);
            ++index;
        }
    }



if (pipe(pipefds1) == -1)
{
    error_exit("unable to create pipe1");
}

if(pipe(pipefds2) == -1 )
{
    error_exit("unable to create pipe2");
}
int temp = -100;


index = 0;
    pid = fork();
    while ((processor_obj.IR != 50) && index <= 160 ) {

    if (pid != 0) {
     ++index;
        close(pipefds1[0]); // Close the unwanted pipe1 read side
        close(pipefds2[1]); // Close the unwanted pipe2 write side
        cout << "\n inside of parent";
        int port = -1000;





        switch(processor_obj.IR) {
            case 0:
                write(pipefds1[1], &processor_obj.PC, sizeof(int));// send pc to memory
                ++processor_obj.PC;// increase PC by One
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // read instruction from memory where PC points

                cout<<"\nzero case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;
                break;
            case 1:

                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // write PC to mem
                read(pipefds2[0], &processor_obj.IR, sizeof(int));// retrieve instruction at PC'S address

                processor_obj.AC = processor_obj.IR;  // load value at int AC
                ++processor_obj.PC; // move pc

                write(pipefds1[1], &processor_obj.PC, sizeof(int));// write PC to mem
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // get the new instruction

              //  cout<<"\nOne case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                // code block
                break;
            case 2:

              //  cout<<"\n 2  case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                // code block
                break;
            case 3:

               // cout<<"\n 3 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 4:
                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // getting address
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // getting address
                processor_obj.AC = processor_obj.IR + processor_obj.X; // setting address + X into AC
              //  cout<<"\nCase FOUR AC address "<<processor_obj.AC;

                write(pipefds1[1], &processor_obj.AC, sizeof(int)); // loading value at address
                read(pipefds2[0], &processor_obj.AC, sizeof(int)); // loading value at address into AC

                ++processor_obj.PC; // move PC to point to the next instruction

                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));
              //  cout<<"\nFour case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 5:
                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // getting address
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // getting address
                processor_obj.AC = processor_obj.IR + processor_obj.Y; // setting address + Y into AC
              //  cout<<"\nCase FIVE AC address "<<processor_obj.AC;

                write(pipefds1[1], &processor_obj.AC, sizeof(int)); // loading value at address
                read(pipefds2[0], &processor_obj.AC, sizeof(int)); // loading value at address into AC

                ++processor_obj.PC; // move PC to point to the next instruction

                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));
            //    cout<<"\nFive case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC<<"Y ="<<processor_obj.Y;

                break;
            case 6:
                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // getting address
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // getting address
                processor_obj.AC = processor_obj.IR + processor_obj.Y; // setting address + Y into AC
              //  cout<<"\nCase FIVE AC address "<<processor_obj.AC;

                write(pipefds1[1], &processor_obj.AC, sizeof(int)); // loading value at address
                read(pipefds2[0], &processor_obj.AC, sizeof(int)); // loading value at address into AC

                ++processor_obj.PC; // move PC to point to the next instruction

                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));
              //  cout<<"\nSix case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 7:

              //  cout<<"\nSeven case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;


                break;
            case 8:

              //  cout<<"\n eight case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;
                break;
            case 9:

                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &port, sizeof(int));

//                write(pipefds1[1], &processor_obj.AC, sizeof(int)); // loading value at address
//                read(pipefds2[0], &processor_obj.AC, sizeof(int)); // loading value at address into AC
                if(port ==1)
                {
                    cout<<"\n port 1: "<<processor_obj.AC;
                } else if(port == 2)
                {
                    cout<<"\nport 2"<< (char) processor_obj.AC;
                }
                else
                {
                    cout<<"An error has occurred";
                }

                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));
              //  cout<<"\nNine case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 10:

                processor_obj.X = processor_obj.AC + processor_obj.X; // add ac to value in x
                ++processor_obj.PC; // move PC up one
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));
            //    cout<<"\n 11 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC<<"Y = "<<processor_obj.Y;


             //   cout<<"\nTen case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;
                break;
            case 11:
                    processor_obj.Y = processor_obj.AC + processor_obj.Y; // add ac to value in y
                    ++processor_obj.PC; // move PC up one
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));
              //  cout<<"\n 11 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC<<"Y = "<<processor_obj.Y;

                break;
            case 12:
              //  cout<<"\n 12 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 13:
              //  cout<<"\n13 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 14:
                processor_obj.X = processor_obj.AC; // copy AC into X
                ++processor_obj.PC; // move Pc up one
                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // send pc to mem
                read(pipefds2[0], &processor_obj.IR, sizeof(int));// retrieve new instruction

              //  cout<<"\n14 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 15:

              //  cout<<"\n15 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC<<"Y ="<<processor_obj.Y;

                break;
            case 16:
                processor_obj.Y = processor_obj.AC; // copy AC into Y
                ++processor_obj.PC; // move Pc up one
                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // send pc to mem
                read(pipefds2[0], &processor_obj.IR, sizeof(int));// retrieve new instruction

              //  cout<<"\n16 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 17:

              //  cout<<"\n17 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 18:

             //   cout<<"\n18 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 19:

              //  cout<<"\n19 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 20:
                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));

                processor_obj.PC = processor_obj.IR; // point to new address to jump to

                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // get the instruction from that new address

              //  cout<<"\n20 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 21:
                if(processor_obj.AC == 0)
                {
                    ++processor_obj.PC;
                    write(pipefds1[1], &processor_obj.PC, sizeof(int));
                    read(pipefds2[0], &processor_obj.IR, sizeof(int));
                    processor_obj.PC = processor_obj.IR;

                    write(pipefds1[1], &processor_obj.PC, sizeof(int));
                    read(pipefds2[0], &processor_obj.IR, sizeof(int));
                    ++processor_obj.PC;
                }
                else
                {
                    processor_obj.PC = processor_obj.PC +2;
                    write(pipefds1[1], &processor_obj.PC, sizeof(int));
                    read(pipefds2[0], &processor_obj.IR, sizeof(int));

                }
             //   cout<<"\n21 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 22:
              //  cout<<"\n22 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 23:

             //   cout<<"\n23 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 24:

              //  cout<<"\n24 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 25:
                ++processor_obj.X; //increment X
                ++processor_obj.PC; // go to the next value
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));

             //   cout<<"\n25 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 26:

              //  cout<<"\n26 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 27:

              //  cout<<"\n27 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 28:

            //    cout<<"\n28 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 29:

           //     cout<<"\n29 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 30:

            //    cout<<"\n30 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 50:
              //  cout<<"\nEnding program";
              //  cout<<"\n50 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;

            default:
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                ++processor_obj.PC;
                read(pipefds2[0], &processor_obj.IR, sizeof(int));
                cout<<"\ndefault case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
                // code block
        }



        //printf("\n At parent this is message from child %d   and PC is %d", processor_obj.IR, processor_obj.PC);






    } else {

        close(pipefds1[1]); // Close the unwanted pipe1 write side
        close(pipefds2[0]); // Close the unwanted pipe2 read side
        char readmessage[20];


        read(pipefds1[0], &X, sizeof(int)); // value from Parent proccess PC register gets stored into X
        // cout<<"\n work plz"<< memory_obj.index;
       // printf("\n At the child value returned from parent is: %c ", X);
        string temp = memory_obj.list[X]; //

        istringstream parser(temp);

        parser >> Y;
       // cout<<"\n At child value in the array to be returned: "<<Y ;


        write(pipefds2[1], &Y, sizeof(int));

    }
}



infile.close();


    return 0;
}



void error_exit(string s)
{
    fprintf(stderr,"\nERROR: %s - bye!\n", s.c_str());
    exit(1);
}




