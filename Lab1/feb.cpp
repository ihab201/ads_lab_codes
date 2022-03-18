#include <iostream>
#include <ctime>

using namespace std;

long feb_loop(int n);
long feb_recursive(int n);

clock_t start , end ;


int main(){
    long n = 15;
    long result;
    clock_t start;
    clock_t end;

    cout << "Type a number: \n"; 
    cin >> n;

    start  = clock(); //measure recursive implementation start time
    result = feb_recursive(n);
    end    = clock(); //measure recursive implementation end time
    cout << "feb_recursive of " << n << " is: " << result << "| time taken is: " 
         << ((float)(end - start) / CLOCKS_PER_SEC) << " seconds \n";

    start  = clock(); //measure iterative implementation start time
    result = feb_loop(n);
    end    = clock(); //measure iterative implementation end time
    cout << "feb_loop of " << n << " is: " << result << "| time taken is: " 
         << ((float)(end - start) / CLOCKS_PER_SEC) << " seconds \n";

    return 0;
}

long feb_loop(int n){

        if(n <= 1) {
			return n;
		}
		long fib = 1;
		long prevFib = 1;

		for(int i=2; i<n; i++) {
			long temp = fib;
			fib+= prevFib;
			prevFib = temp;
		}
		return fib;
}

long feb_recursive(int n){
    if(n == 0 || n== 1) return n;
    return feb_recursive(n - 1) + feb_recursive(n-2);
}
