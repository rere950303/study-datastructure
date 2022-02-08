#include "stack.h"
#include "calculator.h"
#include <iostream>

//
// Assignment 2 : Simple calculator using Stack
//
// COSE213 Fall 2021
//
// Won-Ki Jeong (wkjeong@korea.ac.kr)
//

// stack & calculator test

int main()
{
	// Stack test
	Stack<int> s;
    	
	s.Push(23);
	s.Push(102);

	s.Print();
	printf("--\n");
	
	s.Push(345);
	s.Push(77);
	s.Print();
	printf("--\n");
	
	s.Pop();
	s.Push(678);
	s.Push(91011);
	s.Print();
	printf("--\n");
    
    for(int i=0; i<6; i++)
    {
        try {
            s.Pop();
            std::cout << "Pop() is called" << std::endl;
        }
        catch(const char* message)
        {
            std::cout << message << std::endl;
        }
    }

    // Calculator test
    char str1[] ="-10-((-2+(2+4*3))-12) + 122 * (123 + (120+888) - 300)";
    // The correct result is 101372
    double res1 = Eval(str1);
    std::cout << "Result : " << res1 << std::endl;
	
	char str2[] = "1.2 + 2.4 + 3.0*2";
	// The correct result is 9.6
	double res2 = Eval(str2);
	std::cout << "Result : " << res2 << std::endl;
    
    char str3[] = "(5*2)+(200+25)/2";
    // The correct result is 122.5
    double res3 = Eval(str3);
    std::cout << "Result : " << res3 << std::endl;
    
    char str4[] = "(3 * 2) + ((-2) / 5) + (34 * (3 - 2) * (5 - 3)) + 100";
    // The correct result is 173.6
    double res4 = Eval(str4);
    std::cout << "Result : " << res4 << std::endl;
    
    char str5[] = "(-127 + 130 * (12/3) -20 -30)*3+127";
    // The correct result is 1156
    double res5 = Eval(str5);
    std::cout << "Result : " << res5 << std::endl;
		
	return 0;
}
