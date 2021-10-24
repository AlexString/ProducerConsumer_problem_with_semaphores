/*
Author: AlexString
Description:
	This is a class for using the
	Producer/Consumer problem
	with semaphores
*/
#include <iostream>
// For random numbers
#include <random>
#include <ctime>
// For using sleep in Windows/Linux SOs:
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif 


class ConsumerProducer_Class{
private:
	std::string container[20]; // Items store here
	int container_counter = 0; // used by producer
	int consumer_counter = 0; // used by consumer

	// Internal usage only

	bool advancing_semaphore = true; // true = can proceed.
	bool empty_semaphore = true;
	bool full_semaphore = false;

	// togglers
	void checkFull(); // toggles full_semaphore
	void checkEmpty(); // toggles empty_semaphore

	// Process blocking/allow methods
	void wait(); // blocks advancing_semaphore
	void signal(); // allows advancing_semaphore
	
	// Main methods 
	void Producer(std::string item);
	void Consumer();

	// checkers
	bool isAvailable(); // if advancing_semaphore is available.
public:
	// Constructor/Destructor
	ConsumerProducer_Class();
	~ConsumerProducer_Class();

	// Interface methods
	void useProducer(std::string item); //Item should be template
	void useConsumer();
};
// -------- PRIVATE METHODS --------

// Process blocking/allow methods
void ConsumerProducer_Class::wait(){
	// Generating random number (0-5)
	std::srand(std::time(nullptr));
	int timing = rand() % 6;

	sleep(timing);
	advancing_semaphore = false;
}
void ConsumerProducer_Class::signal(){
	advancing_semaphore = true;
}

// Main methods 
void ConsumerProducer_Class::Producer(std::string item){
	if(isAvailable() != true)	return;
	std::cout << "Producer status: Checking if buffer is full..." << std::endl;
	wait();
	checkFull();
	if(full_semaphore == true){
		std::cout << "[Error]: Buffer is full, need to use Consumer." << std::endl;
		signal();
		return;
	}

	std::cout << "Producer status: [working]" << std::endl;
	wait(); 

	std::cout << "[working]: Accesing container..." << std::endl;
	wait();


	std::cout << "[working]: Saving item..." << std::endl;
	container[container_counter] = item;
	container_counter++;
		
	// This makes it circular
	if (container_counter == 20){ 
		container_counter = 0; 
	}

	std::cout << "[working]: Item saved." << std::endl;
	std::cout << "[working]: Process finished." << std::endl;

	std::cout << "Producer status: [sleeping]" << std::endl;

	signal(); // unblocks advance_semaphore
}
void ConsumerProducer_Class::Consumer(){
	if(isAvailable() != true) return;
	checkEmpty();
	if(empty_semaphore == true){
		std::cout << "Consumer status: [Error]: No items to consume. Use producer." << std::endl;
		return;
	}

	std::cout << "Consumer status: [working]" << std::endl;
	wait(); // blocks advancing_semaphore

	std::cout << "[working]: Accesing container..." << std::endl;

	std::cout << "[working]: Consuming item..." << std::endl;
	std::string deleted_item = container[consumer_counter];
	container[consumer_counter] = "";
	consumer_counter++;
	

	if (consumer_counter == 20){ 
		consumer_counter = 0; // This makes it circular
	}

	std::cout << "[working]: Item [ " << deleted_item << " ] consumed." << std::endl;
	std::cout << "[working]: Process finished." << std::endl;

	std::cout << "Consumer status: [sleeping]" << std::endl;

	signal(); // unblocks advance_semaphore
}

// checkers/helpers
bool ConsumerProducer_Class::isAvailable(){
	if(advancing_semaphore != true){
		std::cout<<"[Error]: Can't do that now, a procces is still going."<<std::endl;
		return false;
	}
	else return true;
}
void ConsumerProducer_Class::checkFull(){
	// If there is a memory space with ""
	// 	means is not full.
	for(int i=0; i<20; i++){
		if(container[i].size() == 0){
			full_semaphore = false;
			return;
		}
	}	
	full_semaphore = true;
}
void ConsumerProducer_Class::checkEmpty(){
	// if all memory spaces are ""
	// 	means is empty
	for(int i=0; i<20; i++){
		if(container[i].size() == 0){
			empty_semaphore = false;
			return;
		}
	}	
	empty_semaphore = true;
}
// -------- PUBLIC METHODS --------

// Constructor/Destructor
ConsumerProducer_Class::ConsumerProducer_Class(){
	for(int i=0; i<20; i++){ // All spaces empty
		container[i] = "";
	}
	std::cout << "System awake. Status: Waiting for instructions" << std::endl;
}
ConsumerProducer_Class::~ConsumerProducer_Class(){
	for(int i=0; i<20; i++){ // All spaces empty
		container[i] = "";
	}
}

// Interface methods
void ConsumerProducer_Class::useProducer(std::string item){ Producer(item); }
void ConsumerProducer_Class::useConsumer()			   { Consumer(); 	 }