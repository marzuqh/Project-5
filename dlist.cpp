template <typename T>
bool Dlist<T>::isEmpty() const
{
	//if first and last don't point to NULL then the list is empty
	if(first && last) return false;
	else return true;
}

template <typename T>
void Dlist<T>::insertFront(T *o)
{
	node *ptr = new node;
	//creates a pointer to a new node

	if(isEmpty())
	//if it is an empty list, this creates the first node
	{
		ptr->next = NULL;
		//first pointers next pointer points at nothing, hence NULL
		
		ptr->prev = NULL;
		//first pointers prev pointer points at nothing, hence NULL
		
		ptr->o = o;
		//gives the pointer its value

		first = ptr;//makes the new node the first node
		last = ptr;//makes the new mode the last node
	}

	else
	{
	//the general dealio

	ptr->next = first;
	
	//assigns new pointers next to point to the original first
	ptr->prev = NULL;
	
	//assigns the new points prev to NULL because its first always
	//points to NULL
	
	ptr->o = o;

	first->prev = ptr;
	//changes the original first node's prev pointer to point to 
	//the new node. This changes last->prev as well because they were
	//pointing to the same node
	
	first = ptr;
	//makes the new node the first node
	
	}
}

template <typename T>
void Dlist<T>::insertBack(T *o)
{
	//is similar to insertFront();
	node *ptr = new node;

	if(isEmpty())
	{
		ptr->next = NULL;
		ptr->prev = NULL;
		ptr->o = o;

		first = ptr;
		last = ptr;
	}

	else
	{
		ptr->next = NULL;
		//the next pointer for the new last should point to NULL
		
		ptr->prev = last;
		//sets new pointer's prev pointer to point to old last node

		ptr->o = o;

		last->next = ptr;
		//sets old last node's next to point to new node
		//also changes first->next to point to new node

		last = ptr;
	}
}

template <typename T>
T* Dlist<T>::removeFront()
{
	if(isEmpty())
	//if the list is empty you can't remove anything, so an instance 
	//of emptyList is thrown
	{
		emptyList e;
		throw e;
	}
	
	else if(first->next == NULL && last->prev == NULL)
	//if there is only one node in the list then
	{
		T *ptr = first->o;
		//stores its val to returned

		delete first;
		//deletes node and first->o

		makeEmpty();

		return ptr;
		//returns a pointer to its value
	}

	else
	//general case
	{
		node *temp = first;
		//creates a temp node pointer to point to "soon to be 
		// deleted" node

		T *foo = temp->o;
		//store its val to return 

		first = first->next;
		//make first point to next node in the list

		first->prev = NULL;
		//make the next node in the list's prev point to NULL

		delete temp;
		//delete where first was pointing to

		return foo;
		//return the held value
	}
}

template <typename T>
T* Dlist<T>::removeBack()
{
	//Similiar to removeFront()

	if(isEmpty())
	{
		emptyList e;
		throw e;
	}
	
	else if(first->next == NULL && last->prev == NULL && first->o)
	{
		T *ptr = last->o;
		//store the value that last is holding

		delete last;
		//delete the node

		makeEmpty();

		return ptr;//
		//return a pointer to its value
	}
	
	else
	{
		node *temp = last;
		//makes a new pointer to point to the "soon to be deleted"
		//old last node

		T* foo = temp->o;
		//store the value to be returned held by the old last node

		last = last->prev;
		//make the prev node the new last node
		last->next = NULL;
		//set the new last node's next to NULL

		delete temp;
		//delete the old last node

		return foo;
		//return the value of the old last node
	}
}

template <typename T>
Dlist<T>::Dlist()
{
	makeEmpty();
}

template <typename T>
Dlist<T>::~Dlist()
{
	removeAll();
}

template <typename T>
Dlist<T>::Dlist(const Dlist &l)
{
	makeEmpty();
	copyAll(l);
}

template <typename T>
Dlist<T>& Dlist<T>::operator=(const Dlist &l)
{
	if(this != &l)
	{
		removeAll();
		copyAll(l);
	}
	return *this;
}

template <typename T>
void Dlist<T>::makeEmpty()
{
	first = NULL;
	last = NULL;
}

template <typename T>
void Dlist<T>::removeAll()
{
	while(!isEmpty())
	{
		T* op = removeFront();
		delete op;
	}
}

template <typename T>
void Dlist<T>::copyAll(const Dlist &l)
{
	node *place = l.first;
	//creates a place pointer to point to where the first node in 
	//the passed Dlist is

	while(place)
	{
		//while place isn't pointing to NULL, or the end of 
		//the list

		T* op = new T(*place->o);

		insertBack(op);
		//insert the value of place into the new Dlist

		place = place->next;
		//move onto the next node in the passed Dlist		
	}
}
