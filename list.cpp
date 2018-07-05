//============================================================================
// Name        : 22C.cpp
// Author      : Li Gu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename T>
class List;

template <typename T>
class Node
{
private:
	T item;
	Node<T>* next;

public:
	Node(T data)
	{
		item = data;
		next = nullptr;
	}

	~Node() {}

    friend class List<T>;
};

template <typename T>
class ListInterface
{
protected:
	Node<T>* head;
	Node<T>* tail;

public:
	virtual bool isEmpty() const = 0;
	virtual bool add(T newEntry) = 0;
	virtual bool remove(T anEntry) = 0;
	virtual void clear() = 0;
	virtual bool search(T anEntry) const = 0;
	virtual ~ListInterface(){};
};

template <typename T>
class List : public ListInterface<T>
{
private:
	int itemCount;

public:
	List()
	{
		this->head = nullptr;
		this->tail = nullptr;
		itemCount = 0;
	}

	~List()
	{
		if (itemCount != 0)
		{
			clear();
		}
	}

	// Sees whether this list is empty.
	// return True if the list is empty, or false if not.
	bool isEmpty() const
	{
		return (this->head == nullptr);
	}

	//  Adds a new entry to the list.
	// post  If successful, newEntry is stored in the list and
	// the count of items in the list has increased by 1.
	// param newEntry:  The object to be added as a new entry.
	// return  True if addition was successful, or false if not.
	bool add(T newEntry)
	{
		if (search(newEntry))
		{
			return false;
		}

		Node<T>* temp = new Node<T>(newEntry);
		if (isEmpty())
		{
			this->head = temp;
			this->tail = temp;
			itemCount++;
			return true;
		}

		this->tail->next = temp;
		this->tail = temp;
		itemCount++;
		return true;
	}

	// Searches for anEntry in the list
	// param anEntry  The entry to be found.
	// return  The entry was found or not.
	bool search(T anEntry) const
	{
		Node<T>* temp = this->head;
		while (temp != nullptr)
		{
			if (temp->item == anEntry)
			{
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	// Removes one occurrence of a given entry from this list, if possible.
	// post  If successful, anEntry has been removed from the list and the count of
	// items in the list has decreased by 1.
	// param anEntry  The entry to be removed.
	// return  True if removal was successful, or false if not.
	bool remove(T anEntry)
	{
		Node<T>* temp = this->head;

		if (isEmpty())
		{
			return false;
		}

		if (this->head->item == anEntry)
		{
			this->head = this->head->next;
			if (this->head == nullptr)
			{
				this->tail = nullptr;
			}
			delete temp;
			itemCount--;
			return true;
		}

		while (temp->next != nullptr && temp->next->item != anEntry)
		{
			temp = temp->next;
		}

		if (temp->next == nullptr)
		{
			return false;
		}

		Node<T>* temp2 = temp->next;
		temp->next = temp2->next;
		delete temp2;

		if (temp->next == nullptr)
		{
			this->tail = temp;
		}
		itemCount--;
		return true;
	}

// Removes all entries from this list.
// post  List contains no items, and the count of items is 0.
	void clear()
	{
		while (this->head != nullptr)
		{
			Node<T>*temp = this->head;
			this->head = this->head->next;
			delete temp;
			itemCount--;
		}
		this->head = nullptr;
		this->tail = nullptr;
	}

	friend ostream& operator<<(ostream& out, const List<T>& linkedList)
	{
		Node<T>*temp = linkedList.head;

		while(temp != nullptr)
		{
			out << temp->item << " ";
			temp = temp->next;
		}
		cout << endl;
		return out;
	}

	int lengthOfList()
	{
		return itemCount;
	}

	void creatListFromFile(const string &fileName)
	{
		ifstream ifs;
		ifs.open(fileName);

		if (!ifs.good())
		{
			cout << "Unable to open: " << fileName << endl;
		}

		cout << "Creating a list by adding the items:" << endl;
		T buffer;
		while (!ifs.eof())
		{
			ifs >> buffer;
		    add(buffer);
		}
		ifs.close();
	}

};

int main()
{
	List<string> linkedList;

	linkedList.creatListFromFile( "Words.txt");
    cout << linkedList;

	if (!linkedList.isEmpty())
	{
		cout << "The linked list is not empty." << endl;
	}
	else
	{
		cout << "The linked list is empty." << endl;
	}

	cout << "Enter a word and try to find it in this linked list: ";
	string word;
	cin >> word;
    if (linkedList.search(word) != 0)
    {
    	cout << "Founded." << endl;
    	cout << "Let's remove it from the linked list: " << endl;
    	if (linkedList.remove(word) != 0)
    	{
    	    cout << word <<" has been removed and the number of the items is " << linkedList.lengthOfList() << "." << endl;
    	}
    	/*
    	else
    	{
    	    cout << "Fail to remove " << word << "you typed." << endl;
    	}
    	*/
    }
    else
    {
    	cout << "Not founded." << endl;
    }

    cout << "Now clear the linked list." << endl;
    linkedList.clear();

    cout << "The number of items in linked list is: " << linkedList.lengthOfList() << endl;
    //cout << L;

	return 0;
}
