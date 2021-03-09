


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
        this->SP[0] = 1000;
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


int main(int argc, char*argv[])
{
Processor processor_obj ;
ifstream  infile;
Memory memory_obj;


if(argc > 1)
{
    //cout<<argv[0];
   infile.open(argv[1]);

  if(!infile)
  {
      cout<<"\nCould not open file"<<argv[1];
      return EXIT_FAILURE;
  }
}
else
{
    infile.open("./sample2.txt");
}
int user_timer = 10;

if(argc == 3) // if there are three arguements give user_timer a value from the arguements
{

user_timer = atoi(argv[2]);
}

string content;
srand(time(NULL));
int pipefds1[2], pipefds2[2];

int pid;



int handler_AC = 0;
int handler_X = 0;
int handler_Y = 0;
int kernal_mode = 0;
int timer = 0;

int X = 0;

if (pipe(pipefds1) == -1)
{
    error_exit("unable to create pipe1");
}

if(pipe(pipefds2) == -1 )
{
    error_exit("unable to create pipe2");
}
int temp = -100;

int index = 0;
    pid = fork();

    if(pid == 0)
    {

      while (!infile.eof())
  {
      getline(infile,content);
      if(content != "" ) {
          if (content.at(0) == '.') //move index to populate interrupt programs
          {
              content.erase(0, 1);

              //cout << "\nContent after making changes" << content;
              istringstream parser(content);
              parser >> index;
             // cout << "\n new index " << index;
          }
          else {

              memory_obj.populateMemory(content, index);
              ++index;
          }

      }
       // cout<<"\n inside of child\n";
    }
}
    infile.close();

    while ((processor_obj.IR != 50  )  ) // once we hit instruction 50 we kill the program
    {

    if (pid != 0) {

        close(pipefds1[0]); // Close the unwanted pipe1 read side
        close(pipefds2[1]); // Close the unwanted pipe2 write side

        int port = -1000;




        switch(processor_obj.IR) {
            case 0:
                write(pipefds1[1], &processor_obj.PC, sizeof(int));// send pc to memory
                    read(pipefds2[0], &processor_obj.IR, sizeof(int)); // read instruction from memory where PC points

                break;
            case 1:


                ++processor_obj.PC; // move pc
                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // write PC to mem
                read(pipefds2[0], &processor_obj.IR, sizeof(int));// retrieve instruction at PC'S address

                processor_obj.AC = processor_obj.IR;  // load value at int AC
                ++processor_obj.PC; // move pc

                write(pipefds1[1], &processor_obj.PC, sizeof(int));// write PC to mem
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // get the new instruction


                break;
            case 2:
            ++processor_obj.PC; // move to the load address
            write(pipefds1[1], &processor_obj.PC, sizeof(int));
            read(pipefds2[0], &processor_obj.IR, sizeof(int));

              if(kernal_mode == 0 && processor_obj.IR >= 1000)
                {
                  cout<<"\n Memory violation: accessing system address "<< processor_obj.IR <<" in user mode ";
                  exit(3);
                  return(3);
                }

            write(pipefds1[1], &processor_obj.IR, sizeof(int)); // read data from load address into AC
            read(pipefds2[0], &processor_obj.AC, sizeof(int));


            ++processor_obj.PC; // go onto the next instruction
            write(pipefds1[1], &processor_obj.PC, sizeof(int));
            read(pipefds2[0], &processor_obj.IR, sizeof(int));


                break;
            case 3:
            ++processor_obj.PC; // move to the load address
            write(pipefds1[1], &processor_obj.PC, sizeof(int));
            read(pipefds2[0], &processor_obj.IR, sizeof(int));

              if(kernal_mode == 0 && processor_obj.IR >= 1000)
                {
                  cout<<"\n Memory violation: accessing system address "<< processor_obj.IR <<" in user mode ";
                  exit(3);
                  return(3);
                }
                write(pipefds1[1], &processor_obj.IR, sizeof(int)); // get the value from the address that we pulled
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // store it in IR

            write(pipefds1[1], &processor_obj.IR, sizeof(int)); // read data from load address into AC
            read(pipefds2[0], &processor_obj.AC, sizeof(int));


            ++processor_obj.PC; // go onto the next instruction
            write(pipefds1[1], &processor_obj.PC, sizeof(int));
            read(pipefds2[0], &processor_obj.IR, sizeof(int));

                break;
            case 4:
                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // getting address
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // getting address
                processor_obj.AC = processor_obj.IR + processor_obj.X; // setting address + X into AC

                write(pipefds1[1], &processor_obj.AC, sizeof(int)); // loading value at address
                read(pipefds2[0], &processor_obj.AC, sizeof(int)); // loading value at address into AC

                ++processor_obj.PC; // move PC to point to the next instruction

                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));

                break;
            case 5:
                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // getting address
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // getting address
                processor_obj.AC = processor_obj.IR + processor_obj.Y; // setting address + Y into AC

                write(pipefds1[1], &processor_obj.AC, sizeof(int)); // loading value at address
                read(pipefds2[0], &processor_obj.AC, sizeof(int)); // loading value at address into AC

                ++processor_obj.PC; // move PC to point to the next instruction

                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));

                break;
            case 6:
                processor_obj.IR = processor_obj.SP[0]; // store old SP pointer
                processor_obj.SP[0] = processor_obj.SP[0] + processor_obj.X ;  // change the SP pointer to X + SP

                write(pipefds1[1], &processor_obj.SP[0],sizeof(int) );
                read(pipefds2[0], &processor_obj.AC, sizeof(int)); // load what was in SP + X into AC

                processor_obj.SP[0] = processor_obj.IR; // restore the stack pointer

                ++processor_obj.PC; // go on to the next instruction

                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));

                break;
            case 7:
            ++processor_obj.PC; // get the address to  store data

            processor_obj.IR = processor_obj.SP[0]; // temporarily store the stack pointer in the IR Register

             write(pipefds1[1], &processor_obj.PC, sizeof(int));
             read(pipefds2[0], &processor_obj.SP[0], sizeof(int)); // store that address in to sp data holding element

            processor_obj.SP[1] = processor_obj.AC;

            write(pipefds1[1], &processor_obj.SP, sizeof(processor_obj.SP)); // write AC into the address
            processor_obj.SP[0] = processor_obj.IR; // restore SP pointer
            read(pipefds2[0], &processor_obj.IR, sizeof(int));

            ++processor_obj.PC; // go to the next instruction

            write(pipefds1[1], &processor_obj.PC, sizeof(int)); // get the next instruction
            read(pipefds2[0], &processor_obj.IR, sizeof(int));

                break;
            case 8:

                processor_obj.AC = (rand() % 100) + 1;
                if(processor_obj.PC - 1 != 0) {
                    ++processor_obj.PC; // move PC to point to the next instruction
                }
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));

                break;
            case 9:

                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &port, sizeof(int));

               if(port == 1)
                {
                    cout<<processor_obj.AC;
                } else if(port == 2)
                {
                    cout<< (char) processor_obj.AC;
                }
                else
                {
                    cout<<"\nAn error has occurred incorrect port= "<<port;
                }

                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));
              break;
            case 10:

                processor_obj.AC = processor_obj.AC + processor_obj.X; // add value in X into Ac
                ++processor_obj.PC; // move PC up one
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));

                break;
            case 11:
                processor_obj.AC = processor_obj.AC + processor_obj.Y; // add value of Y into ac
                    ++processor_obj.PC; // move PC up one
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));

                break;
            case 12:
            processor_obj.AC = processor_obj.AC - processor_obj.X;  // subtact the value in  X from AC
            ++processor_obj.PC; // move PC up one
            write(pipefds1[1], &processor_obj.PC, sizeof(int));
            read(pipefds2[0], &processor_obj.IR, sizeof(int));

                break;
            case 13:
            processor_obj.AC = processor_obj.AC - processor_obj.Y;  // subtact the value in  Y from AC
            ++processor_obj.PC; // move PC up one
            write(pipefds1[1], &processor_obj.PC, sizeof(int));
            read(pipefds2[0], &processor_obj.IR, sizeof(int));

                break;
            case 14:
                processor_obj.X = processor_obj.AC; // copy AC into X
                ++processor_obj.PC; // move Pc up one
                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // send pc to mem
                read(pipefds2[0], &processor_obj.IR, sizeof(int));// retrieve new instruction


                break;
            case 15:
                processor_obj.AC = processor_obj.X; // copy the value in X into AC

                ++processor_obj.PC; // move the pointer up one

                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // send pc to mem
                read(pipefds2[0], &processor_obj.IR, sizeof(int));// retrieve new instruction


                break;
            case 16:
                processor_obj.Y = processor_obj.AC; // copy AC into Y
                ++processor_obj.PC; // move Pc up one
                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // send pc to mem
                read(pipefds2[0], &processor_obj.IR, sizeof(int));// retrieve new instruction


                break;
            case 17:
                processor_obj.AC = processor_obj.Y; // copy Y into AC
                ++processor_obj.PC; // move PC up one

                write(pipefds1[1], &processor_obj.PC, sizeof(int)); // send pc to mem
                read(pipefds2[0], &processor_obj.IR, sizeof(int));// retrieve new instruction

                break;
            case 18:

                cout<<"\n18 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC;

                break;
            case 19:

        processor_obj.AC = processor_obj.SP[0];
            ++processor_obj.PC;
            write(pipefds1[1], &processor_obj.PC, sizeof(int)); // send pc to mem
            read(pipefds2[0], &processor_obj.IR, sizeof(int));// retrieve new instruction


                break;
            case 20:
                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));

                processor_obj.PC = processor_obj.IR; // point to new address to jump to

                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // get the instruction from that new address


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
                if(processor_obj.IR -1 == 0)
                {
                    --processor_obj.PC;
                }
                break;
            case 22:

                if(processor_obj.AC != 0)
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


                if(processor_obj.IR -1 == 0)
                {
                    --processor_obj.PC;
                }
                break;
            case 23:
                ++processor_obj.PC;
                processor_obj.SP[1]= processor_obj.PC;

                --processor_obj.SP[0]; // move the stack back one

                write(pipefds1[1], &processor_obj.SP, sizeof(processor_obj.SP)); // send the SP and the PC  to store PC into memory

                read(pipefds2[0], &processor_obj.PC, sizeof(int));// PC jumps to new address

                write(pipefds1[1],&processor_obj.PC, sizeof(int) ); // grab new instruction from jumped address
                read(pipefds2[0], &processor_obj.IR, sizeof(int));


                break;
            case 24:



                write(pipefds1[1],&processor_obj.SP[0],sizeof(int)); // get the PC previous address
                read(pipefds2[0], &processor_obj.PC,sizeof(int) );

                ++processor_obj.SP[0];

                ++processor_obj.PC; // point PC to next address to be executed

                write(pipefds1[1],&processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int)); // load new instruction to IR


                break;
            case 25:
                ++processor_obj.X; //increment X
                ++processor_obj.PC; // go to the next value
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));


                break;
            case 26:
                --processor_obj.X;
                ++processor_obj.PC;
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                read(pipefds2[0], &processor_obj.IR, sizeof(int));


                break;
            case 27:
                processor_obj.SP[1] = processor_obj.AC;
                --processor_obj.SP[0]; // move the stack back one
                write(pipefds1[1], &processor_obj.SP, sizeof(processor_obj.SP)); // send the SP and the AC to store PC into user stack memory
                read(pipefds2[0],&processor_obj.SP[1],sizeof(int) ); // receiving  the memmories write back just to unload it


                ++processor_obj.PC;// on to the next instruction
                write(pipefds1[1], &processor_obj.PC, sizeof(int) );
                read(pipefds2[0], &processor_obj.IR, sizeof(int) );


                break;
            case 28:

                write(pipefds1[1], &processor_obj.SP[1], sizeof(int)); // send SP to retrieve AC
                ++processor_obj.SP[0]; // move back the SP up to retrieve the latest value in it
                read(pipefds2[0],&processor_obj.AC, sizeof(int) ); // pop the AC from the stack
                   // --processor_obj.SP[0];

                ++processor_obj.PC; // go on to next instruction
                write(pipefds1[1], &processor_obj.PC, sizeof(int) );
                read(pipefds2[0], &processor_obj.IR, sizeof(int) );


                break;
            case 29:
           handler_X = processor_obj.X;
           handler_Y = processor_obj.Y; // handler storing other variables
           handler_AC = processor_obj.AC;
            ++processor_obj.PC;
          processor_obj.SP[1] = processor_obj.SP[0];// put the stack pointer in the element to be sent
          processor_obj.SP[0] = 1999;

          write(pipefds1[1], &processor_obj.SP, sizeof(processor_obj.SP)); // write the pc counter into the system stack
          read(pipefds2[0],&processor_obj.SP[1],sizeof(int));

           processor_obj.SP[0] = 1998;
          processor_obj.SP[1] = processor_obj.PC;
          write(pipefds1[1], &processor_obj.SP, sizeof(processor_obj.SP));
          read(pipefds2[0], &processor_obj.IR, sizeof(int)); // read instruction from memory where PC points
                                          // move PC to System intructions


                processor_obj.PC = 1500 ;

            write(pipefds1[1], &processor_obj.PC, sizeof(int));
          read(pipefds2[0], &processor_obj.IR, sizeof(int));

            kernal_mode = 1;

                break;
            case 30:
            processor_obj.SP[1] = 1998; // get the address for the PC
            write(pipefds1[1],&processor_obj.SP[1], sizeof(int));
            read(pipefds2[0], &processor_obj.PC, sizeof(int)); // restore the PC from the USER code

            processor_obj.X  = handler_X;
            processor_obj.Y  = handler_Y;
            processor_obj.AC = handler_AC;


            processor_obj.SP[1] = 1999;
            write(pipefds1[1], &processor_obj.SP[1], sizeof(int));
            read(pipefds2[0], &processor_obj.SP[0], sizeof(int)); // restore the SP pointer

            write(pipefds1[1], &processor_obj.PC, sizeof(int)); // go on to the next instruction

           read(pipefds2[0], &processor_obj.IR, sizeof(int));
            kernal_mode = 0;

                break;
            case 50:
                cout<<"\nEnding program";
                cout<<"\n50 case"<<"IR = "<<processor_obj.IR <<"PC = "<<processor_obj.PC <<"X = "<<processor_obj.X <<"AC ="<< processor_obj.AC << "Y = "<<processor_obj.Y ;

                break;

            default:
                write(pipefds1[1], &processor_obj.PC, sizeof(int));
                ++processor_obj.PC;
                read(pipefds2[0], &processor_obj.IR, sizeof(int));

                break;
                // code block
        }

++timer; // increment timer by one
        if(kernal_mode == 0 && timer % user_timer == 0)
        {

           handler_X = processor_obj.X;
           handler_Y = processor_obj.Y; // handler storing other variables
           handler_AC = processor_obj.AC;

          processor_obj.SP[1] = processor_obj.SP[0];// put the stack pointer in the element to be sent
          processor_obj.SP[0] = 1999;

          write(pipefds1[1], &processor_obj.SP, sizeof(processor_obj.SP)); // write the pc counter into the system stack
          read(pipefds2[0],&processor_obj.SP[1],sizeof(int));

           processor_obj.SP[0] = 1998;
          processor_obj.SP[1] = processor_obj.PC;
          write(pipefds1[1], &processor_obj.SP, sizeof(processor_obj.SP));
          read(pipefds2[0], &processor_obj.IR, sizeof(int)); // read instruction from memory where PC points
                                          // move PC to System intructions


                processor_obj.PC = 1000 ;

            write(pipefds1[1], &processor_obj.PC, sizeof(int));
          read(pipefds2[0], &processor_obj.IR, sizeof(int));

            kernal_mode = 1;


        }


    } else {

        close(pipefds1[1]); // Close the unwanted pipe1 write side
        close(pipefds2[0]); // Close the unwanted pipe2 read side
        int  readMsg[] = {-1000, -1000};

        read(pipefds1[0], &readMsg, sizeof(readMsg)); // value from Parent proccess PC register gets stored into X
        int Y = 0;
        if(readMsg[1] != -1000) // if we are  writing to memory
            {

                memory_obj.list[readMsg[0]] = to_string(readMsg[1]);

                string temp = memory_obj.list[readMsg[1]]; //

                istringstream parser(temp);

                parser >> Y;


                write(pipefds2[1], &Y, sizeof(int));

            }
            else { // if we are just reading from memory
                string temp = memory_obj.list[readMsg[0]]; //

                istringstream parser(temp);

                parser >> Y;


                write(pipefds2[1], &Y, sizeof(int));
            }

    }
}

    return 0;
}

void error_exit(string s)
{
    fprintf(stderr,"\nERROR: %s - bye!\n", s.c_str());
    exit(1);
}
