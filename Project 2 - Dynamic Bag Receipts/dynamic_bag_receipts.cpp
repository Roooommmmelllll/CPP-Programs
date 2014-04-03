// FILE: bag_receipts.cpp
// INVARIANT for the bag class:
//   1. The number of items in the bag is in the member variable used;
//   2. For an empty bag, we do not care what is stored in any of data; for a
//      non-empty bag the items in the bag are stored in data[0] through
//      data[used-1], and we don't care what's in the rest of data.

#include <algorithm> // Provides copy function
#include <cassert>   // Provides assert function
#include <iostream>
#include <random>
#include <time.h>
#include "dynamic_bag_receipts.h"
using namespace std;

int generateReceipt(){
	srand(time(NULL));
	int randNum = rand()%8999+1000;
	return randNum;
}

bag::bag(size_type initial_capacity){
	data = new value_type[initial_capacity];
	receipt = new int[initial_capacity];
	capacity = initial_capacity;
	used = 0;
}

bag::bag(const bag& source){
	data = new value_type[source.capacity];
	capacity = source.capacity;
	used = source.used;
	copy(source.data, source.data + used, data);
}

bag::~bag( ){
	delete [ ] data;
	delete [ ] receipt;
}

void bag::reserve(size_type new_capacity){
	value_type *larger_bag;
	int *larger_receipt;

	if (new_capacity == capacity){
		return; // The allocated memory is already the right size.
	}
	if (new_capacity < used){
		new_capacity = used; // Can’t allocate less than we are using.
	}
	larger_bag = new value_type[new_capacity];
	larger_receipt = new int[new_capacity];
	copy(data, data + used, larger_bag);
	copy(receipt, receipt + used, larger_receipt);
	delete [ ] data;
	delete [ ] receipt;
	data = larger_bag;
	receipt = larger_receipt;
	capacity = new_capacity;
}

bool bag::erase_one(const value_type& target){
	size_type index; // The location of target in the data array 
	bool checkReceipt = false;
	int receiptNumber;

	// First, set index to the location of target in the data array,
	// which could be as small as 0 or as large as used-1. If target is not
	// in the array, then index will be set equal to used.
	index = 0; 
	while ((index < used) && (data[index] != target)){
		++index;

		if (index == used){
			return false; // target isn’t in the bag, so no work to do.
		}
	}
	// When execution reaches here, target is in the bag at data[index].
	// So, reduce used by 1 and copy the last item onto data[index].
	// Check for receipt before deletion.
	while (checkReceipt == false){
		cout << "Value: " << data[index] << endl << "Please enter receipt number for deletion." << endl
			<< "Or enter 0 (zero) to exit the delete process." << endl;
		cin >> receiptNumber;
		if (cin.fail()){
			cin.clear();
			cin.ignore();
			cout << "Unexpected input, please try again." << endl << endl;
		}
		else if (receiptNumber != receipt[index]){
			cout << "That is not the valid receipt for this data." << endl;
		}
		else if (receiptNumber == 0){
			return false;
		}
		else{
			--used;
			data[index] = data[used]; 
			receipt[index] = receipt[used];
			cout << "Receipt Accepted." << endl;
			return true;
		}
	}
}

bag::size_type bag::erase(){
	size_type index = 0;
	size_type many_removed = 0;

	while (index < used){
		if (erase_one(data[index]) == true){
			++many_removed;
		}
		else{
			++index;
		}
	}
	return many_removed;
}

int bag::insert(const value_type& entry){ 
	int newReceipt = generateReceipt();
	if (used == capacity){
		reserve(used+1);
		data[used] = entry;
		receipt[used] = generateReceipt();
		++used;
	}
	else{
		data[used] = entry;
		receipt[used] = newReceipt;
		++used;
	}
	return newReceipt;
}

void bag::printMe(){
	for (int i = 0;i < used;i++){
		cout << data[i] << " ";
	}
	cout << endl;
}

bag::size_type bag::count(const value_type& target) const{
	size_type answer;
	size_type i;

	answer = 0;
	for (i = 0; i < used; ++i){
		if (target == data[i])
			++answer;
	}
	return answer;
}
