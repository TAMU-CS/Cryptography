/* Notes on Pollard p-1 algorithm
	-the goal is to find a factor of an integer N
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//fast powering algorithm , time = O(logy)
long long int fastPower(long long int x, long long int y, long long int p);
//Greated common divisor- recursive with euclidian algorithm
long long int GCD(long long int x, long long int y);
//Pollard P-1 algorithm
long long int Pollard(long long int N);

int main() {
	
	//setup file
	ofstream ofile("OutputPollard.txt");
	ifstream ifile("TestNums.txt");

	//read in from test file
	long long int N;
	while (ifile >> N) {
		long long int factorD = Pollard(N);
		long long int OtherFactor = N / factorD;

		ofile << N << " = " << factorD << " * " << OtherFactor << endl;

		if (factorD * OtherFactor != N) {
			cout << "ERROR: test epic fail\n";
			return 0;
		}
	}

	ofile.close();
	ifile.close();
	return 0;
}

//fast powering
long long int fastPower(long long int x, long long int y, long long int p)
{
	int result = 1; //start with 1

	//take the exponent and iterate through it's binary values
	while (y > 0) {

		//check least significant bit
		if (y & 1) {
			result = (result * x) % p; //x = x^2 mod p
		}

		//shift y over 1 bit, as the previous bit was already processed
		y = y >> 1;

		//set x = x^2 mod p, x = originalX ^ (2,4,8,16, etc.) mod p
		x = (x * x) % p;
	}

	return result;
}

//greatest common divisor with Euclidian algorithm
long long int GCD(long long int x, long long int y) {
	//base case
	int val = x % y;
	if (val == 0) {
		return y;
	}
	else {
		return GCD(y, val);
	}
}

//Pollard alg
long long int Pollard(long long int N) {
	//1. set a = 2
	long long int a = 2;

	//2. loop through j = 2, 3, 4, ... to some bound
	bool found = false;
	int j = 2;
	while (j <= N) { //limit to N for now, but j bound should be a smooth number

		//a = a^j mod N
		a = fastPower(a, j, N);

		//comput d = gcd(a-1, N)
		long long d = GCD(a - 1, N);

		if (1 < d && d < N) { //factor found
			return d;
		}

		j++; //increment j
	}

	return N; //no factors found
}