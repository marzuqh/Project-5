#include <iostream>
#include <cstdlib>
#include <string>
#include "dlist.h"

using namespace std;

struct Caller
{
	//Caller struct that details each caller

	unsigned int timestamp;
	string name;
	string status;
	unsigned int duration;
};

Caller Pop(Dlist<Caller> &l)
{
	//REQUIRES: A well-formed Dlist<Caller>
	//EFFECTS:  Returns first caller from the dlist
	//MODIFIES: l
	
	Caller *foo;
	Caller Serving;
	
	foo = l.removeFront();
	Serving = *foo;

	delete foo;
	return Serving;
}

void PushF(Dlist<Caller> &l, Caller c)
{
	//REQUIRES: A well-formed Dlist<Caller>
	//EFFECTS:  Places a Caller at top of the dlist
	//MODIFIES: l

	Caller *foo = new Caller(c);
	l.insertFront(foo);
}

void Calling(Dlist<Caller> &l, const unsigned int time)
{
	//REQUIRES: A well-formed Dlist<Caller>
	//EFFECTS:  Checks to see if top caller on dlist is calling at the 
	//given tick
	//MODIFIES: l

	bool listNotEmpty = false;
   
	Dlist<Caller> temp;
	//A temporary dlist to hold instance where multiple callers from 
	//same list call at the same time

	Caller c;
	
	bool moreCalls = true;

	while(moreCalls)
	{
		//While there are people who are calling at this time...

		if(!l.isEmpty())
		{
			//while the list is not empty...
      
         		c = Pop(l);//check the top Caller on the list
         		listNotEmpty = true;
      		}
      		if(listNotEmpty)
      		{
      			if(c.timestamp == time && c.status != "none")
      			{
      				//if the caller's time is the same 
      				//as the current time and he isn't 
      				//a regular member

      				cout << "Call from " << c.name << " a "; 
      				cout << c.status << " member" << endl;

      				listNotEmpty = false;
      				//assumes that he was the last caller
         		}
		 	else if(c.timestamp == time)
		 	{
		 		//if this person is a regular member

		 		cout << "Call from " << c.name;
		 		cout << " a regular member" << endl;

		 		listNotEmpty = false;
		 	}

		 	if(c.timestamp > time)
		 	{
		 	//if the caller's time is after the current time 
		 	//then there is nobody else who is calling at 
		 	//this time and we have to push him back to the top
		 	//of the list
		 
		    		moreCalls = false;
		   		PushF(l,c);
		 	}
      		}
     	else moreCalls = false;
      	//if the list is empty then there is no more calls left
   	}
}

void Evaluate(Dlist<Caller> &l, const unsigned int time, unsigned int &until, bool &busy, const Caller &c)
{
	//REQUIRES: A well-formed Dlist<Caller>
	//EFFECTS: checks first to see if the teller is busy, and if not, 
	//answers a call from the list if there is someone on hold
	//MODIFIES: l
	   
	if(c.timestamp <= time && !busy)
	{
	   	//Someone calls or is on hold + the teller isn't busy
	   
	      	busy = true;//he is busy now
	      	
	      	until = time + c.duration;//he will be busy until...
	      	
	      	cout << "Answering call from " << c.name << endl;
      		//announces who he is answering
   	}
   	else
   	{
   		PushF(l,c);//Otherwise leave the list unchanged
   	}
   
}

int main(void)
{
	//Created 4 Dlist<Caller> for each status and one for the in order 
	//file list

	Dlist<Caller> callLog;
	Dlist<Caller> Plat;
	Dlist<Caller> Gold;
	Dlist<Caller> Silv;
	Dlist<Caller> None;
	   
	int events;//How many events to read into the files
	int count = 0;
   
	cin >> events;

	while(events > count)
	{
		//While all of the events haven't been read...

		Caller *a = new Caller;
		//creates a new caller on the heap
		//Assign the caller its characteristics

		cin >> a->timestamp;
		cin >> a->name;
		cin >> a->status;
		cin >> a->duration;

		Caller *b = new Caller(*a);
		//the pointer to Callers in the callLog
		//Assigns each caller to their respective lists as well as
		// the callLog
		if(a->status == "platinum")
		{
			Plat.insertBack(a);
			callLog.insertBack(b);
		}
	
		else if(a->status == "gold")
		{
			Gold.insertBack(a);
			callLog.insertBack(b);
		}
	
		else if(a->status == "silver")
		{
			Silv.insertBack(a);
			callLog.insertBack(b);
		}
		else
		{
			None.insertBack(a);
			callLog.insertBack(b);
		}

		count++;//An event has been added    
	}

	unsigned int time = 0;
	//time starts at 0
	
	bool busy = false;
	//The teller has just opened shop
	
	unsigned int until = 1000;
	//sets it arbitrarily to 1000 so it pasts first if-statement  

	while(events > 0)
	{
		cout << "Starting tick #" << time << endl;
		//Tells the user what time it is

		if(time == until)
		{
			//If the teller is finishing up with a caller

			busy = false;
			//he isn't busy anymore

			events--;
			//he is finished with one event
		}
      
		//Checks the callLog and sees if anyone is calling at this
		// time

		Calling(callLog, time);

		//Checks every list in order of priority to see if there 
		// is someone who needs to be answered while the teller is 
		//not busy.

		if(!Plat.isEmpty())
		{
			Caller plat = Pop(Plat);
			Evaluate(Plat, time, until, busy, plat);
		}

		if(!Gold.isEmpty())
		{
			Caller gold = Pop(Gold); 
         		Evaluate(Gold, time, until, busy, gold);       
         	}

         	if(!Silv.isEmpty())
		{
			Caller silv = Pop(Silv); 
         		Evaluate(Silv, time, until, busy, silv);       
         	}

         	if(!None.isEmpty())
		{
			Caller none = Pop(None); 
         		Evaluate(None, time, until, busy, none);       
         	}

         	time++;//time just goes on by
         }
	return 0;
}
