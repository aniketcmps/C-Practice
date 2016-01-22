#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <sstream>
#include <omp.h>
#include <chrono>
using namespace std;

#define GETMICROS() chrono::system_clock::now().time_since_epoch() / chrono::microseconds(1) //To calculate time

class Name
{
    //Class Name with functions Start, End, InsertionSort, Average, Select
     public:
        int *fitnessdata;
        int size; //will store the size of array
        int sort; //to check if array is sorted or not
        string name;
        int endname;
        int *sortedData; //store sorted array
        int compare; //store number of comparisons.
        int swap; //Store number of sorts.

        Name()
        {
            size=0;
            sort=0;
            name="";
            endname=1;
            compare=0;
            swap=0;
        }

        void reinitialise(string input)
        {
            sort=1;
            compare=0;
            swap=0;

            sortedData=new int[size];
            for(int i=0;i<size;i++)
            {
                sortedData[i]=fitnessdata[i]; //Store the sorted data
            }

            input=input.append(".txt"); //append ".txt" to define the extension of file to be read
            ifstream file;
            file.open( input.c_str(),ios::in);
            if (file.is_open())
            {
                file >> size; //read total no of inputs
                fitnessdata= new int[size]; //reinitialize array with the size
                for(int i=0;i<size;i++)
                {
                    file >> fitnessdata[i];
                }
                file.close();
            }
        }

        void start(string input)
        {
            if(endname==0)
            {
                cout<<"Invalid Start \n"; //Give error for consequtive start
            }
            else if(endname==1)
            {
                name=input;
                input=input.append(".txt"); //append ".txt" to define the extension of file to be read
                ifstream file;
                file.open( input.c_str(),ios::in);
                if (file.is_open())
                {
                    endname=0;
                    cout << "Processing fitness data of: " << name << "\n";
                    file >> size; //read total no of inputs
                    fitnessdata= new int[size]; //initialize array with the size
                    for(int i=0;i<size;i++)
                    {
                        file >> fitnessdata[i];//store input values in the array

                    }
                    file.close();
                }
                else cout << "Unable to open file. \n"; //gives error if file not found
            }
        }

        void end(string input)
        {
            if(input.compare(name) == 0)
            {
                cout << "End of processing fitness data for: " << name << "\n";
                size=0; //deallocating memory
                sort=0;
                delete[] fitnessdata;
                delete[] sortedData;
                name="";
                endname=1;
                compare=0;
                swap=0;
            }
            else
            {
                cout<< "Invalid End. \n"; //if user tries to end different name
            }
        }

        void insertionSort()
        {
            long time=0;
            time=GETMICROS();

            int key;

            for(int i=1;i<size;i++) //Insertion Sort
            {
                key=fitnessdata[i];
                int j=i-1;
                while(j>=0 && fitnessdata[j]>key)
                {
                    compare++;

                    fitnessdata[j+1]=fitnessdata[j];
                    j=j-1;
                    swap++;//increment swap when we place the element in proper position
                }
                compare++; //increment compare when fitnessdata[j]>key is false
                fitnessdata[j+1]=key;
            }

            time=GETMICROS()-time;

            cout<< "Number of comparisons made by insertion sort: " << compare << "\n";
            cout<< "Number of swaps made by insertion sort: " << swap << "\n";
            cout<< "Time to run insertion sort (ms): " << (double) time / 1000  << "\n";
        }

        void merge(int data[], int start, int mid, int end)
        {
            int sortedList[size];
            for(int i=0;i<size;i++)
            {
                sortedList[i]=data[i]; //store array in temp file for reference
            }
            int i=start;
            int j=mid+1;
            int z=start;

            while(i<=mid && j<=end)
            {
                compare++;
                //swap++;

                if(sortedList[i]<=sortedList[j])
                {
                    data[z]=sortedList[i];
                    i++;
                }
                else
                {
                    data[z]=sortedList[j];
                    j++;
                    swap++;
                }
                z++;
            }
            if(i<=mid)
            {
                for(int k=z;k<=end;k++)
                {
                    data[k]=sortedList[i];  //If left array is not traveresed completely
                    i++;
                }
            }
            else if(j<=end)
            {
                for(int k=z;k<=end;k++)
                {
                    data[k]=sortedList[j]; //If right array is not traveresed fully
                    j++;
                }
            }
        }

        void parallelMergeSort(int data[], int start, int end)
        {
            int mid;
            if(start<end)
            {
                #pragma omp parallel num_threads(2) //parallel function will work on Left and Right array at same time
                {
                    mid=((start+end)/2);
                    #pragma omp sections
                    {
                        #pragma omp section
                        mergeSort(data, start, mid); //mergesort on Left part of array
                        #pragma omp section
                        mergeSort(data, mid+1, end); //mergesort on Right part of array
                    }
                    merge(data, start, mid, end);
                }
            }
        }

        void mergeSort(int data[], int start, int end)
        {
            int mid;
            if(start<end)
            {
                mid=((start+end)/2);
                parallelMergeSort(data, start, mid); //mergesort on Left part of array
                parallelMergeSort(data, mid+1, end); //mergesort on Right part of array
                merge(data, start, mid, end);
            }
        }

        int select(string input)
        {
            long time=0;

            if(sort==0) //check if array is sorted
            {
                cout<< "Unable to select from an unsorted array. \n"; //error if array is not sorted
            }
            else
            {
                int i;
                time=GETMICROS();
                if(input.compare("min") == 0)
                {
                    i=0; //smallest value i.e. first data item
                }
                else if(input.compare("max") == 0)
                {
                    i=size-1; //largest value i.e. last data item
                }
                else if(input.compare("median") == 0)
                {
                    if(size%2==0) //if the array contains even numbers
                    {
                        i=size/2;
                        float median=(sortedData[i]+sortedData[i-1]);
                        time=GETMICROS()-time;

                        cout<< "Selecting item: " << median/2 << "\n"; //median is mean (average) of the two middlemost numbers
                        cout<< "Time to run the selection (ms): " << (double) time / 1000 << "\n";
                        return 0;
                    }
                    else
                        i=size/2; //if the array contains odd number
                }
                else
                {
                    istringstream buffer( input.c_str() ); //convert string into integer
                    buffer >> i;
                    if(i<1 || i>size) //check if input is greater than or less than size of array
                    {
                        cout<< "Invalid input. \n"; //prints error if input greater than size of array
                        return 0;
                    }
                    i--;
                    cout<<i;
                }
                time=GETMICROS()-time;

                cout<< "Selecting item: " << sortedData[i] << "\n";
                cout<< "Time to run the selection (ms): " << (double) time / 1000 << "\n";
                return 0;
            }
        }

        void average()
        {
            long time=0;
            time=GETMICROS();

            float avg=0;
            for(int i=0;i<size;i++)
            {
                avg+=fitnessdata[i]; //sum of all elements in array
            }
            avg=avg/size; //divide by the total number of elements to get average
            time=GETMICROS()-time;

            cout<< "Average number of steps: " << avg << "\n";
            cout<< "Time to run the average (ms): " << (double) time / 1000 << "\n";
        }

        //#pragma omp
        void parallelAverage()
        {
           long time=0;
            time=GETMICROS();
            int siz=size;
            int temp[siz];
            for (int i=0;i<siz;i++)
                temp[i]=fitnessdata[i];

            float avg=0;
            #pragma omp parallel for shared(siz,temp,avg) num_threads(4)//parallel function to split into 2 threads
            for(int i=0;i<size;i++)
                avg+=temp[i]; //sum of all elements in array
            avg=avg/size; //divide by the total number of elements to get average
            time=GETMICROS()-time;

            cout<< "Average number of steps: " << avg << "\n";
            cout<< "Time to run the average (ms): " << (double) time / 1000 << "\n";
        }
        void exit()
        {
            cout<< "Program terminating. \n";
        }
}; //End of Class

int main()
{
    string input,command;
    Name n1;
    do
    {
        cout<<"Enter the command. \n"; //Take input from user
        cin>>command;
        if(command.compare("Start")==0) // If command is Start call Start function.
        {
            cin>>input;
            n1.start(input);
        }
        else if(command.compare("InsertionSort")==0) // If command is InsertionSort call InsertionSort function.
        {
            n1.insertionSort();
            n1.reinitialise(n1.name); //reinitialise the array
        }
        else if(command.compare("MergeSort")==0) // If command is InsertionSort call InsertionSort function.
        {
            long time=0;
            time=GETMICROS();
            n1.mergeSort(n1.fitnessdata,0,(n1.size-1));
            time=GETMICROS()-time;

            cout<< "Number of comparisons made by merge sort: " << n1.compare<< "\n";
            cout<< "Number of swaps made by merge sort: " << n1.swap << "\n";
            cout<< "Time to run insertion sort (ms): " << (double) time / 1000  << "\n";
            n1.reinitialise(n1.name); //reinitialise the array
        }
        else if(command.compare("ParallelMergeSort")==0) // If command is InsertionSort call InsertionSort function.
        {
            long time=0;
            time=GETMICROS();
            n1.parallelMergeSort(n1.fitnessdata,0,(n1.size-1));
            time=GETMICROS()-time;

            cout<< "Number of comparisons made by merge sort: " << n1.compare << "\n";
            cout<< "Number of swaps made by merge sort: " << n1.swap << "\n";
            cout<< "Time to run insertion sort (ms): " << (double) time / 1000  << "\n";
            n1.reinitialise(n1.name); //reinitialise the array
        }
        else if(command.compare("Select")==0) // If command is Select call Select function.
        {
            cin>>input;
            int temp=n1.select(input);
        }
        else if(command.compare("Average")==0) // If command is Average call Average function.
        {
            n1.average();
        }
        else if(command.compare("ParallelAverage")==0) // If command is InsertionSort call InsertionSort function.
        {
            n1.parallelAverage();
        }
        else if(command.compare("End")==0) // If command is End call End function.
        {
            cin>>input;
            n1.end(input);
        }
        else if(command.compare("Exit")==0) // If command is Exit call Exit function.
        {
            n1.exit();
        }
        else
            cout<< "Invalid command. \n";
    }while(command.compare("Exit")!=0); //End when command is Exit.

    return 0;
}
