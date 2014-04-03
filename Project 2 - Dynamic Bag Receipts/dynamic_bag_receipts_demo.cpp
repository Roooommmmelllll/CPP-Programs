#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include "dynamic_bag_receipts.cpp"
using namespace std;

void get_count(bag&);
void get_input(bag&);
void remove_input(bag&);

int main( ){
	int looper = 1, command = 2;
	bag b1;
	
	//Controls the testing done by the user.
	while (looper == 1){
		cout << "You can manipulate the bag with receipts using the following commands:" << endl
			<< "1) Add a value into the bag, and receive a receipt." << endl
			<< "2) Check the current size of the bag." << endl
			<< "3) Check for the occurence of a single value in the bag." << endl
			<< "4) Print all values in the bag." << endl
			<< "5) Remove a single value from the bag." << endl
			<< "6) Remove all values from the bag." << endl
			<< "0) Exit the program" << endl
			<< "Please input a command..." << endl << endl;
		cin >> command;
		if (cin.fail()){
			cin.clear();
			cin.ignore();
			cout << "Unexpected input, please try again." << endl << endl;
		}
		else if (command < 0 || command > 6){
			cout << "The value you entered is either above "
				<< "or below the values expected, please try again." << endl;
		}
		else{
			//Actions taken based on the choice of the user.
			cout << endl << endl;
			switch(command){
				case 0:
					command = 0;
					break;
				case 1:	
					get_input(b1);
					break;
				case 2:	
					cout << "The bag currently has " << b1.size() << " values." << endl;
					break;
				case 3:
					get_count(b1);
					break;
				case 4:
					b1.printMe();
					break;
				case 5:
					remove_input(b1);
					break;
				case 6:
					b1.erase();
			};
			if (command == 0){
			break;
			}
		}
	}
	
	cin.ignore();
	cin.get();
	return EXIT_SUCCESS;
}

void get_count(bag& currentBag){
	bag::value_type user_input;

    cout << "Please enter a value to count from the bag." << endl;	
    cin >> user_input;
    cout << "That value is found " << currentBag.count(user_input) << " times in the bag." << endl;
}

void get_input(bag& currentBag){
    bag::value_type user_input;
	int receiptNumber;

    cout << "Please enter a value to enter into the bag." << endl;	
    cin >> user_input;
    receiptNumber = currentBag.insert(user_input);
	cout << endl << "This is your receipt: " << receiptNumber << endl;
	cout << "----PLEASE KEEP TRACK OF YOUR RECEIPTS!----" << endl << endl;
}

void remove_input(bag& currentBag){
    int user_input;

    cout << "Please enter the value to remove from the bag."<< endl;
    cin >> user_input;
	currentBag.erase_one(user_input);
}
