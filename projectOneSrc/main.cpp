


#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>


using namespace std;

void error_exit(string s);


class Processor {
public:
    int PC ;
    int SP[2]  ;
    int IR ;
    int AC ;
    int X ;
    int Y ;
    Processor(){
        this->PC = 0;
        this->SP[0] = 999;
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
infile.open("./sample2.txt");
string content;
srand(time(NULL));
int pipefds1[2], pipefds2[2];

int pid;

int index = 0; //debugging purposes



    int X = 0;
    int Y = 0;





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

    if(pid == 0)
    {
        while (!infile.eof())
        {
            getline(infile,content);
            if(content != "") {
                memory_obj.populateMemory(content, index);
                ++index;
            }
        }
       // cout<<"\n inside of child\n";
    }
    index = 0;
    while ((processor_obj.IR != 50  )  ) {

    if (pid != 0) {
     ++index;
        close(pipefds1[0]); // Close the unwanted pipe1 read side
        close(pipefds2[1]); // Close the unwanted pipe2 write side

        int port = -1000;

       //cout<<"\ninside of the parent\n";





        switch(processor_obj.IR) {
            case 0:
                write(pipefds1[1], &processor_obj.PC, sizeof(int));// send pc to memory
                //++processor_obj.PC;// increase PC by One
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // read instruction from memory where PC points

              //  cout<<"\nzero case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;
                break;
            case 1:


                ++processor_obj.PC; // move pc
                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // write PC to mem
                read(pipefds2[0], &processor_obj.IR, sizeof(int));// retrieve instruction at PC'S address

                processor_obj.AC = processor_obj.IR;  // load value at int AC
                ++processor_obj.PC; // move pc

                write(pipefds1[1], &processor_obj.PC, sizeof(int));// write PC to mem
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // get the new instruction

              //  cout<<"\nOnecase"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC<<"Y = "<<processor_obj.Y;

                // code block
                break;
            case 2:

                //cout<<"\n 2  case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                // code block
                break;
            case 3:

             //   cout<<"\n 3 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 4:
                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // getting address
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // getting address
                processor_obj.AC = processor_obj.IR + processor_obj.X; // setting address + X into AC
            //    cout<<"\nCase FOUR AC address "<<processor_obj.AC;

                write(pipefds1[1], &processor_obj.AC, sizeof(int)); // loading value at address
                read(pipefds2[0], &processor_obj.AC, sizeof(int)); // loading value at address into AC

                ++processor_obj.PC; // move PC to point to the next instruction

                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));
             //   cout<<"\nFour case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 5:
                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // getting address
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // getting address
                processor_obj.AC = processor_obj.IR + processor_obj.Y; // setting address + Y into AC
             //   cout<<"\nCase FIVE AC address "<<processor_obj.AC;

                write(pipefds1[1], &processor_obj.AC, sizeof(int)); // loading value at address
                read(pipefds2[0], &processor_obj.AC, sizeof(int)); // loading value at address into AC

                ++processor_obj.PC; // move PC to point to the next instruction

                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));
             //   cout<<"\nFive case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC<<"Y ="<<processor_obj.Y;

                break;
            case 6:
                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // getting address
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // getting address
                processor_obj.AC = processor_obj.IR + processor_obj.Y; // setting address + Y into AC
             //   cout<<"\nCase FIVE AC address "<<processor_obj.AC;

                write(pipefds1[1], &processor_obj.AC, sizeof(int)); // loading value at address
                read(pipefds2[0], &processor_obj.AC, sizeof(int)); // loading value at address into AC

                ++processor_obj.PC; // move PC to point to the next instruction

                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));
             //   cout<<"\nSix case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 7:

            //   cout<<"\nSeven case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;


                break;
            case 8:

                processor_obj.AC = (rand() % 100) + 1;
                if(processor_obj.PC - 1 != 0) {
                    ++processor_obj.PC; // move PC to point to the next instruction
                }
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));
             //   cout<<"\n8 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;


                break;
            case 9:

                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &port, sizeof(int));

               if(port ==1)
                {
                    cout<<processor_obj.AC;
                } else if(port == 2)
                {
                    cout<< (char) processor_obj.AC;
                }
                else
                {
                    cout<<"An error has occurred incorrect port";
                }

                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));
           //     cout<<"\nNine case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC<< "Y = "<<processor_obj.Y;

                break;
            case 10:

                processor_obj.AC = processor_obj.AC + processor_obj.X; // add value in X into Ac
                ++processor_obj.PC; // move PC up one
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));

             //   cout<<"\nTen case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;
                break;
            case 11:
                processor_obj.AC = processor_obj.AC + processor_obj.Y; // add value of Y into ac
                    ++processor_obj.PC; // move PC up one
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));
            //    cout<<"\n 11 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC<<"Y = "<<processor_obj.Y;

                break;
            case 12:
             //   cout<<"\n 12 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 13:
            //    cout<<"\n13 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 14:
                processor_obj.X = processor_obj.AC; // copy AC into X
                ++processor_obj.PC; // move Pc up one
                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // send pc to mem
                read(pipefds2[0], &processor_obj.IR, sizeof(int));// retrieve new instruction

            //    cout<<"\n14 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 15:
                processor_obj.AC = processor_obj.X; // copy the value in X into AC

                ++processor_obj.PC; // move the pointer up one

                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // send pc to mem
                read(pipefds2[0], &processor_obj.IR, sizeof(int));// retrieve new instruction

           //     cout<<"\n15 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC<<"Y ="<<processor_obj.Y;

                break;
            case 16:
                processor_obj.Y = processor_obj.AC; // copy AC into Y
                ++processor_obj.PC; // move Pc up one
                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // send pc to mem
                read(pipefds2[0], &processor_obj.IR, sizeof(int));// retrieve new instruction

          //      cout<<"\n16 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC<<"Y = "<<processor_obj.Y;

                break;
            case 17:

          //      cout<<"\n17 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 18:

          //      cout<<"\n18 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 19:

         //       cout<<"\n19 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 20:
                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));

                processor_obj.PC = processor_obj.IR; // point to new address to jump to

                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // get the instruction from that new address

         //       cout<<"\n20 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

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
         //       cout<<"\n21 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;
                if(processor_obj.IR -1 == 0)
                {
                    --processor_obj.PC;
                }
                break;
            case 22:

                if(processor_obj.AC != 0)
                {

                    processor_obj.PC = processor_obj.PC +2;
                    write(pipefds1[1], &processor_obj.PC, sizeof(int));
                    read(pipefds2[0], &processor_obj.IR, sizeof(int));




                }
                else
                {

                    ++processor_obj.PC;
                    write(pipefds1[1], &processor_obj.PC, sizeof(int));
                    read(pipefds2[0], &processor_obj.IR, sizeof(int));
                    processor_obj.PC = processor_obj.IR;

                    write(pipefds1[1], &processor_obj.PC, sizeof(int));
                    read(pipefds2[0], &processor_obj.IR, sizeof(int));
                    ++processor_obj.PC;

                }


           //     cout<<"\n22 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC <<"SP"<<processor_obj.SP[0]<<" : "<<processor_obj.SP[1];
                if(processor_obj.IR -1 == 0)
                {
                    --processor_obj.PC;
                }
                break;
            case 23:
                ++processor_obj.PC;
                processor_obj.SP[1]= processor_obj.PC;
                write(pipefds1[1], &processor_obj.SP, sizeof(processor_obj.SP)); // send the SP and the PC  to store PC into memory
                --processor_obj.SP[0]; // move the stack back one
                read(pipefds2[0], &processor_obj.PC, sizeof(int));// PC jumps to new address

                write(pipefds1[1],&processor_obj.PC, sizeof(int) ); // grab new instruction from jumped address
                read(pipefds2[0], &processor_obj.IR, sizeof(int));

               // cout<<"\n23 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC << "Y = "<<processor_obj.Y <<"SP = "<<processor_obj.SP[0]<<" : "<<processor_obj.SP[1];

                break;
            case 24:


                ++processor_obj.SP[0];
                write(pipefds1[1],&processor_obj.SP[0],sizeof(int)); // get the PC previous address
                read(pipefds2[0], &processor_obj.PC,sizeof(int) );


                ++processor_obj.PC; // point PC to next address to be executed

                write(pipefds1[1],&processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // load new instruction to IR

         //       cout<<"\n24 case"<<"IR = "<<processor_obj.IR <<": PC = "<<processor_obj.PC <<": X = "<<processor_obj.X <<": AC ="<< processor_obj.AC << ": Y = "<<processor_obj.Y <<": SP = "<<processor_obj.SP[0]<<" : "<<processor_obj.SP[1];

                break;
            case 25:
                ++processor_obj.X; //increment X
                ++processor_obj.PC; // go to the next value
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));

          //      cout<<"\n25 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 26:
                --processor_obj.X;
                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));
         //       cout<<"\n26 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC << ": Y = "<<processor_obj.Y <<": SP = "<<processor_obj.SP[0]<<" : "<<processor_obj.SP[1];


                break;
            case 27:
                processor_obj.SP[1] = processor_obj.AC;
                write(pipefds1[1], &processor_obj.SP, sizeof(processor_obj.SP)); // send the SP and the AC to store PC into user stack memory
                read(pipefds2[0],&processor_obj.SP[1],sizeof(int) ); // receiving  the memmories write back just to unload it
                --processor_obj.SP[0]; // move the stack back one

                ++processor_obj.PC;// on to the next instruction
                write(pipefds1[1], &processor_obj.PC, sizeof(int) );
                read(pipefds2[0], &processor_obj.IR, sizeof(int) );


         //       cout<<"\n27 case"<<"IR = "<<processor_obj.IR <<": PC = "<<processor_obj.PC <<": X = "<<processor_obj.X <<": AC ="<< processor_obj.AC << ": Y = "<<processor_obj.Y <<": SP = "<<processor_obj.SP[0]<<" : "<<processor_obj.SP[1];
                break;
            case 28:
                ++processor_obj.SP[0]; // move back the SP up to retrieve the latest value in it
                write(pipefds1[1], &processor_obj.SP[1], sizeof(int)); // send SP to retrieve AC
                read(pipefds2[0],&processor_obj.AC, sizeof(int) ); // pop the AC from the stack


                ++processor_obj.PC; // go on to next instruction
                write(pipefds1[1], &processor_obj.PC, sizeof(int) );
                read(pipefds2[0], &processor_obj.IR, sizeof(int) );

          //      cout<<"\n28 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC << " : Y = "<<processor_obj.Y<<": SP = "<< processor_obj.SP[0] << " : "<< processor_obj.SP[1];

                break;
            case 29:

        //       cout<<"\n29 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 30:

         //       cout<<"\n30 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 50:
             //   cout<<"\nEnding program";
              //  cout<<"\n50 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC << "Y = "<<processor_obj.Y ;

                break;

            default:
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                ++processor_obj.PC;
                read(pipefds2[0], &processor_obj.IR, sizeof(int));
             //   cout<<"\ndefault case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
                // code block
        }


    } else {

        close(pipefds1[1]); // Close the unwanted pipe1 write side
        close(pipefds2[0]); // Close the unwanted pipe2 read side
        int  readMsg[] = {-1000, -1000};


        read(pipefds1[0], &readMsg, sizeof(readMsg)); // value from Parent proccess PC register gets stored into X
            if(readMsg[1] != -1000)
            {

                memory_obj.list[readMsg[0]] = to_string(readMsg[1]);

                string temp = memory_obj.list[readMsg[1]]; //

                istringstream parser(temp);

                parser >> Y;


                write(pipefds2[1], &Y, sizeof(int));

            }
            else {
                string temp = memory_obj.list[readMsg[0]]; //

                istringstream parser(temp);

                parser >> Y;


                write(pipefds2[1], &Y, sizeof(int));
            }

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




