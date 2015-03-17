#include <iostream>
#include <cstdlib>
#include <string>
#include "dlist.h"

using namespace std;

double operations(double first, double second, double (*fn)(double, double))
//REQUIRES: a valid fn that does a mathematical calculation using two
//          doubles and returns a double
//EFFECTS: computes the mathematical calculation desired and return 
//         the results
{
	return fn(first, second);
}

double add(double i, double j)
//EFFECTS: returns addition of two numbers
{
	return i + j;
}

double sub(double i, double j)
//EFFECTS: returns subtraction of first number from second number
{
	return j-i;
}

double mult(double i, double j)
//EFFECTS: returns multiplication of two numbers
{
	return i*j;	
}

double div(double i, double j)
//EFFECTS: returns the division of second number by first number
{
	return j/i;
}

double Pop(Dlist<double> &l)
//REQUIRES: a well-formed Dlist<double>
//EFFECTS: returns a double for the first number in the stack
//MODIFIES: l
{
	double *ptr;//a pointer to a double
	double value;//a double to hold the value of the return

	ptr = l.removeFront();
	//have a pointer point to the returned double
	
	value = *ptr;
	//dereferences the point and assigns its value to "value"

	delete ptr;
	//delete dynamic memory of where the object was in the heap

	return value;
	//returns the value it held
}

void Push(Dlist<double> &l, double d)
//REQUIRES: a well-formed Dlist<double>
//EFFECTS: pushes a double value onto the top of the stack
//MODIFIES: l
{
	double *foo = new double(d);
	l.insertFront(foo);
}

int main(void)
{
	Dlist<double> calc;

	bool inUse = true;

	int count = 0;
	//counter of how many values are in the stack

	while(inUse)
	//while the calculator is still running
	{
		string input;

		double result;
		double number;
		double *ptr;
		double *ptr2;

		cin >> input;

		//NOTE: for all mathematical calcs, count goes down by 1
		// b/c you pop 2 numbers off and only push one numbers back

		if(input == "+" && count >= 2)
		//ADDITION
		{
			result = operations(Pop(calc), Pop(calc), add);
			Push(calc, result);

			count--;
		}
		
		else if(input == "*" && count >= 2)
		//MULTIPLICATION
		{
			result = operations(Pop(calc), Pop(calc), mult);
			Push(calc, result);

			count--;
		}

		else if(input == "-" && count >= 2)
		//SUBTRACTION
		{
			double first = Pop(calc);
			double second = Pop(calc);

			result = operations(first, second, sub);
			Push(calc, result);

			count--;
		}

		else if(input == "/" && count >= 2)
		//DIVISION
		{
			double first = Pop(calc);
			double second = Pop(calc);

			if(first == 0)
			//divide by zero error
			{
				cout << "Divide by zero" << endl;
				Push(calc, second);//leaves stack unchanged
				Push(calc, first);
			}
			else
			{
				result = operations(first, second, div);
				Push(calc, result);

				count--;
			}
		}
		
		else if(input == "d" && !calc.isEmpty())
		//DUPLICATION: Only case I can't use Push fn
		{
			ptr = new double(Pop(calc));
			calc.insertFront(ptr);

			ptr2 = new double(*ptr);
			calc.insertFront(ptr2);

			count++;
			//Duplicate pops one number off and pushes two
			// numbers in
			
		}
		
		else if(input == "r" && count >=2)
		//REVERSE
		{
			double first;
			double second;

			first = Pop(calc);
			second= Pop(calc);

			Push(calc, first);
			Push(calc, second);
		}
		
		else if(input == "c")
		//CLEAR ALL
		{
			while(!calc.isEmpty())
			{
				Pop(calc);
			}

			count = 0;
			//clears all numbers from the stack
		}
		
		else if(input == "a")
		//PRINT ALL
		{
			Dlist<double> temp;
			//a temp Dlist<double> to hold the values of calc

			while(!calc.isEmpty())
			//while there are still items in calc
			{
				ptr = new double(Pop(calc));
				//pop them off

				cout << *ptr << endl;
				//display them

				temp.insertBack(ptr);
				//push them back in the reverse order to
				// keep calc unchanged
			}

			calc = temp;
			//Return calc to its original store
		}

		else if(input == "n" && !calc.isEmpty())
		//NEGATION
		{
			result = Pop(calc)*(-1);
			Push(calc, result);
		}
		
		else if(input == "p" && !calc.isEmpty())
		//PRINT FIRST
		{
			ptr = new double(Pop(calc));
			cout << *ptr << endl;

			calc.insertFront(ptr);
		}
		
		else if(input == "q")
		//QUIT
		{
			inUse = false;
		}
		
		else if((input[0] >= '0' && input[0] <= '9') 
		&& (input[input.size() - 1] >= '0' 
		&& input[input.size() - 1] <= '9' 
		&& input[input.size() - 1] != '.'))
		//checks to see if the input is a valid number before
		// putting it into calc
		{
		number = atof(input.c_str());
		//converts string into a  c_str and returns a double to it

		Push(calc, number);
		count++;
		}
		
		else
		{
			if(input == "+" || input == "-" || input == "/" ||
			 input == "*" || input == "d" || input == "r" ||
			  input == "n" || input == "p")
			{
			//if one of the valid operations was entered but
			// couldn't be run

			cout << "Not enough operands" << endl;
			}
			else cout << "Bad Input" << endl;
			//anything else is considered this
		}
	}
return 0;
}
