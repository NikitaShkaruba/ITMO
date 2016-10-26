#include <functional>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <string>
#include <Vector>
#include <Array>
using namespace std;
#define Pi 3.14159f

namespace math {
	// 1. Linear systems
	bool dDominance(float** arr, size_t size) {
		for (size_t i = 0; i < size; i++) {
			double sum = 0;
			for(size_t j = 0; j < size; j++)
				if (j != i)
					sum += abs(arr[i][j]);
			
			if (abs(arr[i][i]) > sum)
				return true;
		}
		return false;
	}
	bool converge(float* first, float* second, size_t size, float precision) {
		float norm = 0;

		for (int i = 0; i < size; i++) 
			norm += (first[i] - second[i]) * (first[i] - second[i]);
		
		return (sqrt(norm) < precision);
	}
	float* GaussSeidel(float** a, float* b, size_t size, float precision) {
		// aX = b
		size_t count = 0;
		float* X = new float[size];
		for (size_t i = 0; i < size; i++)
			X[i] = 0;
		float* pastX = new float[size];
		
		do {
			for (size_t i = 0; i < size; i++)
				pastX[i] = X[i];
			
			for (int i = 0; i < size; i++) {
				double var = 0;
				for (int j = 0; j < i; j++)
					var += a[i][j] * X[j];
				for (int j = i + 1; j < size; j++)
					var += a[i][j] * pastX[j];

				X[i] = (b[i] - var) / a[i][i];
			}
			if (count++ > 10050)
				throw "Cannot compute due to dDominance";
		} while (!converge(X, pastX, size, precision));
	
		delete[] pastX;
		return X;
	}
	
	bool converge(vector<float> first, vector<float> second, float precision) {
		float norm = 0;

		for (int i = 0; i < first.size(); i++) 
			norm += powf((first[i] - second[i]), 2);
		
		return (sqrt(norm) < precision);
	}
	vector<float> GaussSeidel(vector<vector<float>> a, vector<float> b, float precision) {
		// aX = b

		size_t count = 0;
		vector<float> X(b.size());
		vector<float> pastX(X);

		do {
			pastX = X;
			
			for (int i = 0; i < b.size(); i++) {
				double var = 0;
				for (int j = 0; j < i; j++)
					var += a[i][j] * X[j];
				for (int j = i + 1; j < b.size(); j++)
					var += a[i][j] * pastX[j];

				X[i] = (b[i] - var) / a[i][i];
			}
			if (count++ > 10050)
				throw "Cannot compute due to dDominance";
		} while (!converge(X, pastX, precision));
		return X;
	}
	// 2. Integrals
	double ComputeIntegral(double(*y)(double x), double lowBound, double topBound, double atomRang) {
		if (lowBound == topBound)
			return 0;
		if (lowBound > topBound)
			swap(lowBound, topBound);

		double sum = 0;
		for (double x = lowBound; x <= topBound; x += atomRang)
			sum += y(x) * atomRang;

		return sum;
	}

	// 3. Function approximation
	struct Point {
		Point(float x, float y): x(x), y(y) {}

		string toString() {
			string s("x: ");
			return "{ " + std::to_string(x) + ", " + std::to_string(y) = " }";
		}

		const float x;
		const float y;
	};

	float computePolynom(float x, vector<float> coefficients) {
		float sum = 0;

		for (size_t i = 0; i < coefficients.size(); i++)
			sum += powf(x, i)*coefficients[i];

		return sum;
	}
	function<float(float)> OrdinaryLeastSquares(vector<Point> points, size_t polynomRang = 5) {
		// Matrix system is bA = c
		// polynomRang = points.size() - 1 
		vector<vector<float>> b(polynomRang, vector<float>(polynomRang));
		vector<float> c(polynomRang);
		vector<float> coefficients(polynomRang);

		// compute b
		for (size_t k = 0; k < polynomRang; k++)
			for (size_t l = 0; l < polynomRang; l++)
				for (size_t i = 0; i < points.size(); i++)
					b[k][l] += powf(points[i].x, k+l); 

		// compute c
		for (size_t k = 0; k < polynomRang; k++)
			for (size_t i = 0; i < points.size(); i++)
				c[k] = powf(points[i].x, k) + points[i].y;
		
		// compute coefficients
		coefficients = GaussSeidel(b, c, 0.0001);
		
		// appriximated function. Don't be ashamed of lambda's
		return [coefficients](float x) -> float {
			return computePolynom(x, coefficients);
		};
	}
}
namespace tests {
	void printEquatationSystem(float** a, float* b, size_t size) {
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) 
			cout << a[i][j] << "x" << j << " ";
		cout << "= " << b[i] << endl;
	}
}
	using namespace math;
	// 1
	void runGaussSeidelTest() {
		size_t size = 3;
		float precision = 0.001;
		float** a = new float*[size] {	new float[3] {8, 4, 2}, 
										new float[3] {3, 5, 1},
										new float[3] {3, -2, 10}};
		float* b = new float[size] {10, 5, 4};
		
		printEquatationSystem(a, b, size);
		cout << "is computable? " << math::dDominance(a, size) << endl;
		float* result = math::GaussSeidel(a, b, size, precision);

		cout << "result is" << endl;
		for (size_t i = 0; i < size; i++)
			cout << "X[" << i << "]: " << result[i] << endl;
	}
	// 2
	void runComputeIntegralTests() {
		// triangle: 1\2*h*w
		double atomRang = 0.100;
		double lowBound = -3;
		double topBound = 3;
		double testResult = 0;

		// common
		testResult = ComputeIntegral([](double x) { return -abs(x) + 3; }, lowBound, topBound, atomRang);
		assert(testResult >= 9 - atomRang && testResult <= 9 + atomRang);	
		
		// reversed
		testResult = ComputeIntegral([](double x) { return -abs(x) + 3; }, topBound, lowBound, atomRang);
		assert(testResult >= 9 - atomRang && testResult <= 9 + atomRang);

		// lowBound == upBound
		testResult = ComputeIntegral([](double x) { return -abs(x) + 3; }, lowBound, lowBound, atomRang);
		assert(testResult == 0);

		// y(x) = -y(x)
		testResult = ComputeIntegral([](double x) { return x; }, topBound, lowBound, atomRang);
		assert(testResult >= 0 - atomRang && testResult <= 0 + atomRang);
	}
	// 3
	void runOrdinaryLastSquaresTests() {
		// simulate function is sin(x)
		vector<Point> v;

		// case 1
		v.push_back({-Pi, 0});
		v.push_back({-Pi/2, -1});
		v.push_back({0, 0});
		v.push_back({Pi/2, 1});
		v.push_back({Pi, 0});

		auto f = OrdinaryLeastSquares(v, 4);
		float rslt = f(2);
		// assert(abs(f(5) - 71) <= 0.1);

		// case 2
		v.push_back({-Pi/6, -sqrtf(3)/2});
		v.push_back({-Pi/4, -sqrtf(2)/2});
		v.push_back({-Pi/3, -1/2});
		v.push_back({Pi/3, 1/2});
		v.push_back({Pi/4, sqrtf(2)/2});
		v.push_back({Pi/6, sqrtf(3)/2});
		f = OrdinaryLeastSquares(v, 4);
		rslt = f(2);
		// assert(abs(f(5) + 66) <= 0.1);

		// case 3
		v.pop_back();
		v.push_back({Pi/6, 67});
		f = OrdinaryLeastSquares(v, 4);
		rslt = f(2);
		// assert(abs(f(5) + 66) <= 0.1);

		// case 4
		v.clear();
		v.push_back({-11*Pi/2, -1});
		v.push_back({-15*Pi, 0});
		v.push_back({-7*Pi/2, -1});
		v.push_back({5*Pi, 0});
		v.push_back({-3*Pi/2, -1});
		v.push_back({0, 0});
		v.push_back({3*Pi/2, 1});
		v.push_back({5*Pi, 0});
		v.push_back({7*Pi/2, 1});
		v.push_back({13*Pi, 0});
		v.push_back({11*Pi/2, 1});
		f = OrdinaryLeastSquares(v, 4);
		rslt = f(2);
		// assert(abs(f(5) + 66) <= 0.1);
	}
	// All
	void runAllTests() {
		runGaussSeidelTest();
		runComputeIntegralTests();
		runOrdinaryLastSquaresTests();
	}
}

void main() {
	// tests::runOrdinaryLastSquaresTests();
	// tests::runAllTests();
	using namespace math;
	char command;

	while (true) {
		cout << "Which method do you want to run?" << endl;
		cout << "1. Gauss-Seidel method\n2. Reqtangle method(integrals)\n3. Ordinary Least Squares(approximation)\n4.\n5.\n0 - exit" << endl;
		cout << endl << "Command: ";
		
		cin >> command;
		switch (command) {
		case '1': {
			cout << "Gauss-Seidel method for linear system solving" << endl;
			float precision = 0;
			int N = 0;

			// creating matrix model
			cout << "input matrix size(N*N): ";
			cin >> N; 
			float** arr = new float*[N];		// Didn't optimized for readability
			for (size_t i = 0; i < N; i++)		// That's a hard shit(code), maan.
				arr[i] = new float[N];
			float* b = new float[N];

			//  inputting all the coefficients
			for (size_t i = 0; i < N; i++) {
				for (size_t j = 0; j < N; j++) {
					cout << "input an a[" << i << "][" << j << "] coefficient: ";
					cin >> *arr[i + j]; 
				}
			}
			for (size_t i = 0; i < N; i++) {
				cout << "input b[" << i << "]: ";
				cin >> b[i];
			}
			cout << "input precition: ";
			cin >> precision;

			// printing al the statistic
			tests::printEquatationSystem(arr, b, N);
			cout << "precision: " << precision << endl;
			cout << "Computing..." << endl << endl;
			float* result = math::GaussSeidel(arr, b, N, precision);
			cout << "result is: " << endl;
			for (size_t i = 0; i < N; i++)
				cout << "X[" << i << "] = " << result[i] << endl;

			// prolog
			for (size_t i = 0; i < N*N; i++)
				delete[] arr[i];
			delete[] arr;
		} break;
		case '2': {
			cout << "Reqtangle method for computing integrals" << endl;
			float atomRang = 0;
			float lowBound = 0;
			float upBound = 0;
			double (*function)(double x) = nullptr;

			cout << "choose f(x) function: \n1. y = x^2\n2. y = 1/x^2\n3. y = 4*x\n4. y = e^x\n5. y = sin(3*x)\n\n0. - exit";
			cout << endl << "Command: ";
			cin >> command;
			switch (command) {
				case '1': function = [](double x) { return pow(x, 2); }; break;
				case '2': function = [](double x) { return 1/pow(x, 2); }; break;
				case '3': function = [](double x) { return 4 * x; }; break;
				case '4': function = [](double x) { return exp(x); }; break;
				case '5': function = [](double x) { return sin(3 * x); }; break;

				case '0': break; break;
				default: cout << "Wrong number. Try a number(1-5)/n 0 to exit." << endl; break; continue;
			}

			cout << "input lower bound:";
			cin >> lowBound;
			cout << "input upper bound:";
			cin >> upBound;
				
			cout << "input positive(!) precision == atom rang(maximum deta(x)): ";
			cin >> atomRang;
			if (atomRang <= 0)
				break;

			double I = ComputeIntegral(function, lowBound, upBound, atomRang);
			cout << endl << "*************results:\nI = " << I << endl;
			cout << "Amount of divisions = " << abs(lowBound - upBound) / atomRang << endl;
			cout << "Error == " << abs(I - ComputeIntegral(function, lowBound, upBound, atomRang/2))/3 << endl;
			cout << "*************" << endl << endl;
		} break;
		case '3': {
			vector<Point> points;
			size_t polynomRank = 0;

			cout << "Ordinary Least Squares method" << endl;
			cout << "Input points:";
			do {
				cout << endl;
				float x, y;
				cout << "x: "; 
				cin >> x;
				cout << "y: ";
				cin >> y;
				points.push_back({ x, y });
				cout << "'q' - exit; other key - continue. command: ";
			} while (cin >> command && command != 'q');

			cout << endl;
			cout << "Input expexted polynom rank or 'q' if you don't know it: ";
			cin >> command;
			if (command == 'q')
				polynomRank = points.size() - 1;
			polynomRank = atoi(&command);
			cout << endl;

			function<float(float)> approximation = OrdinaryLeastSquares(points, polynomRank);
			// use reflextion power, son
			cout << "input 'q' to exit, or if you want to calculate y, inout x: ";
			if (command == 'q')
				break;
			cout << endl << "y: " << approximation(atof(&command));
		} break;
		case '4': throw "NotImplementedException"; break;
		case '5': throw "NotImplementedException"; break;
		default: cout << "Wrong number. Try a number(1-5)" << endl;
		}
	}
}