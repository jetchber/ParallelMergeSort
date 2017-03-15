#include <iostream>
#include <math.h>
#include <fstream>
#include "mpi.h" // message passing interface
using namespace std;

// Do this ONCE when you start up thomas
// module load openmpi-x86_64

// New compile and run commands for MPI!
// mpicxx -o Sort ParallelMergeSort.cpp
// mpirun -np 32 Sort

int * inputArray;
int * outputArray;

int Rank(int, int, int, int *);

int main (int argc, char * argv[]) {

	int my_rank;			// my CPU number for this process
	int p;					// number of CPUs that we have
	int source;				// rank of the sender
	int dest;				// rank of destination
	int tag = 0;			// message number
	char Message[100];		// message itself
	MPI_Status status;		// return status for receive
	
	// Start MPI
	MPI_Init(&argc, &argv);
	
	// Find out my rank!
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	// Find out the number of processes!
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	// THE REAL PROGRAM IS HERE
	if(my_rank == 0){
		cout << "Start" << endl;
		
		int * A = new int[5];
		int * B = new int[5];
		outputArray = new int[5];
		
		A[0] = 9;
		A[1] = 4;
		A[2] = 1;
		A[3] = 7;
		A[4] = 6;
		B[0] = 3;
		B[1] = 4;
		B[2] = 2;
		B[3] = 7;
		B[4] = 1;
		
		cout << "Arrays Created" << endl;
		
		for(int i = 0; i < 5; i++){
			cout << A[i];
		}
		
		for(int i = 0; i < 5; i++){
			outputArray[i] = Rank(B[i], 0, 4, A);
			cout << "One Iteration" << endl;
		}
		
		for(int i = 0; i < 5; i++){
			cout << outputArray[i] + " ";
		}
	}
	
	// Shut down MPI
	MPI_Finalize();

	return 0;
}

int Rank(int value, int first, int last, int * array){
	int M = (int)ceil(last / 2);
	if(first > last)
		return 0;
	else if(last == 1){
		if(value < array[0])
			return 0;
		else
			return 1;
	}
	else if(value < array[M]){
		return Rank(value, first, M-1, array);
	}
	else{
		return M - first + Rank(value, M+1, last, array);
	}
}
