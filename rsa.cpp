#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <string>
#include <fstream>

using namespace std;

// int gcd(int a, int b) {
// 	if (b == 0) {
// 		return a;
// 	}
// 	if (a < b) {
// 		swap(a, b);
// 	}
// 	return gcd(b, a % b);
// }

bool contains(int n, const vector<int> v) {
	for (int i = 0; i < v.size(); ++i) {
		if (v.at(i) == n) {
			return true;
		}
	}
	return false;
}

bool isPrime(int n) {
	for (int i = 2; i < sqrt(n); ++i) {
		// cout << n << " mod " << i << " is " << n % i << endl;
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

int inverseMod(int a, int b) {
	vector<int> A;
	vector<int> B;
	int x = a;
	int y = b;
	int multiple = 1;

	//if 'a' isn't in vector 'B' AND if 'b' isn't in vector 'A',
	//push back into respective vectors
	while (!contains(a, B) && !contains(b + 1, A)) {
		A.push_back(a);
		// cout << "Pushing " << a << " into A" << endl;
		B.push_back(b+1);
		// cout << "Pushing " << b + 1 << " into B" << endl;

		a += x;
		b += y;
		++multiple;
	}
	return multiple;
}

int powerModulo(int b, int exp, int n) {
	int exp2 = 0;
	int c = 1;

	while (exp2 < exp) {
		++exp2;
		c = (b * c) % n;
	}

	return c;
}

void readData(const string &name, vector<int> &v) {
	ifstream inFS;
	int n = 0;

	//Opening file
	inFS.open(name.c_str());
    if (!inFS.is_open()) {
        cout << "Error opening " << name << endl;
        exit(1);
    }

    while (inFS >> n) {
        v.push_back(n);
    }
    inFS.close();
}

//Public key = (e, n) = (13, 77)

int main() {
	double n = 0;
	int phi = 0;
	int e = 0;
	int p = 0;
	int q = 0;
	int userNum = 0;
	int modExp = 0;
	bool result = false;
	vector<int> init;
	queue<int> RSA;
	string filename;
	char keys[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
				'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
				'W', 'X', 'Y', 'Z', ' '};

	// cout << "Checking if num is prime" << endl;
	// if (isPrime(12)) {
	// 	cout << "12 is prime" << endl;
	// }
	// else {
	// 	cout << "12 is not prime" << endl;
	// }

	cout << "Enter filename: " << endl;
	cin >> filename;
	readData(filename, init);

	cout << "Enter 'e' for Public key = (e, n)" << endl;
	cin >> e;
	cout << "Enter 'n' for Public key = (e, n)" << endl;
	cin >> n;

	while (!result) {
		cout << "Enter 2 distinct prime factors of 'n' (Product MUST equal n)" << endl;
		cin.ignore();
		cin >> p;
		cin.ignore();
		cin >> q;
		cin.ignore();
		if (p * q != n) {
			cout << "Product of p and q does not equal n" << endl;
		}
		else if (!isPrime(p) || !isPrime(q)) {
			cout << "p and/or q is not prime" << endl;
		}
		else {
			result = true;
		}
	}

	n = p * q; //n = 77
	phi = (p - 1) * (q - 1);

	// cout << phi << endl;

	int multiNum = inverseMod(e, phi);

	// cout << e << "^-1 (mod " << phi << ") = " << multiNum << endl;

	for (int i = 0; i < init.size(); ++i) {
		modExp = powerModulo(init.at(i), multiNum, n);
		cout << "Pushing " << modExp << " to RSA queue" << endl;
		RSA.push(modExp);
	}

	while (!RSA.empty()) {
		cout << keys[RSA.front() - 2];
		RSA.pop();
	}
	cout << endl;

	return 0;
}