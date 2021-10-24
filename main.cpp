/*
Author: AlexString
Description:
	This file demonstrates the use of 
	ConsumerProducer_Class
*/

#include <iostream>
#include <limits>
#include "ConsumerProducer.h"

using namespace std;

int menu(){
	int desition;
	cout << "--Menu--" << endl;
	cout << "1) Producer"
			"\n2) Consumer"
			"\n3) Exit." << endl;
	cin >> desition;
	return desition;
}

int main(){
	ConsumerProducer_Class consumer_producer;
	cout << "Producer / Consumer demonstration using Semaphores" << endl;
	
	while(1){
		int select = menu();
		switch(select){
		case 1:{
			cin.ignore(numeric_limits<streamsize>::max(),'\n');

			string item;
			cout << "Insert item:" << endl;
			getline(cin, item); 
			std::cout << "Sending [ "<< item << " ] to producer." << std::endl;
			consumer_producer.useProducer(item);
			}
		break;
		case 2:
			consumer_producer.useConsumer();
		break;

		default:
			exit(0);
		break;
		}
	}
	return 0;
}