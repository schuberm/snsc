#include <iostream>

int main(){
	float sum =0.0000000001;
	float increm = 0.0000000001;
	float corr = 0.0;
	float y,t;
	for (int i = 0 ; i<=1000000000-1; i++){
		sum=sum+increm;
		//y = increm - corr;
		//t = sum + y;
		//corr = (t-sum)-y;
		//sum = t;
	}
	std::cout.precision(15);
	std::cout << std::fixed << sum +1 << std::endl;
}

//Kahan summation algorithm
