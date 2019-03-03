#include "vector-main.h"
#include "vector-test.h"
int main(){
	//test0();
	//test0DimVect();
	//test1();
	//test2();
	//test3();
	//test4();
	std::string input;
	bool success = true;
	unsigned int dimensions[2];
	do{
		std::cout << "Enter 2 positive whole numbers as dimensions of the vectors: ";
		std::getline(std::cin, input);
		success = getUnsignedInt(dimensions, 2, input);
		if(dimensions[0] == 0 || dimensions[1] == 0)
			success = false;
	} while(!success);
	Vector v1(dimensions[0]), v2(dimensions[1]);
	unsigned int decision = -1;
	do{
		std::cout << "Current values: " << "v1: " << v1 << ", v2: " << v2 << std::endl << "Choose an option: \n"
			<< "[1] - read one value from vector\n"
			<< "[2] - set one field to a new value\n"
			<< "[3] - load vector from input\n"
			<< "[4] - add vectors\n"
			<< "[5] - subtract vectors\n"
			<< "[6] - dot product of vectors\n"
		        << "[7] - compare vectors\n"
			<< "[8] - print vector\n"
			<< "[0] - quit: "; 
		success = true;
		do{
			std::getline(std::cin, input);
			success = getUnsignedInt(&decision, 1, input);
			if(decision > 8)
				success = false;
		} while(!success);
		unsigned int whichVect = 0;
		if(decision == 1 || decision == 2 || decision == 3 || decision == 8){
			std::cout << "Which vector? [1 OR 2]: ";
			do{
				std::getline(std::cin, input);
				success = getUnsignedInt(&whichVect, 1, input);
				if(whichVect > 2 || !whichVect)
					success = false;
			} while(!success);
		}
		Vector *vChosen = NULL;
		whichVect == 1 ? vChosen = &v1 : vChosen = &v2;
		unsigned int whichElement = 0;
		if(decision == 1 || decision == 2){
			std::cout << "Which element? [0 - " << vChosen->getDimension() - 1 << "]: ";
			do{
				std::getline(std::cin, input);
				success = getUnsignedInt(&whichElement, 1, input);
				if(whichElement >= vChosen->getDimension() || !whichElement)
					success = false;
			} while(!success);
		}
		unsigned int whichToUpdate = 0;
		if(decision == 4 || decision == 5){
			std::cout << "In which vector to store the result? [1 OR 2]: ";
			do{
				std::getline(std::cin, input);
				success = getUnsignedInt(&whichToUpdate, 1, input);
				if(whichToUpdate > 2 || !whichToUpdate)
					success = false;
			} while(!success);
		}
		Vector *resultHere = NULL;
		whichToUpdate == 1 ? resultHere = &v1 : resultHere = &v2;
		if(decision == 1)
			readValue(*vChosen, whichElement);
		else if(decision == 2)
			setValue(*vChosen, whichElement);
		else if(decision == 3)
			loadVector(*vChosen);
		else if(decision == 4)
			addVectors(v1, v2, *resultHere);
		else if(decision == 5)
			subtractVectors(v1, v2, *resultHere);
		else if(decision == 6)
			dotProduct(v1, v2);
		else if(decision == 7)
			compareVectors(v1, v2);
		else if(decision == 8)
			printVector(*vChosen);
	} while(decision); 
}
void readValue(const Vector& vect, const unsigned int& n){
	std::cout << "v: " << vect << ", v[" << n << "] = " << vect.getNthValue(n) << std::endl;
}
void setValue(Vector& vect, const unsigned int &n){
	bool success = true;
	std::string input;
	double newValue;
	do{
		std::cout << "Enter new value: ";
		getline(std::cin, input);
		success = getDouble(&newValue, 1, input);
	} while(!success);
	vect.setNthValue(n, newValue);
	std::cout << "Vector updated to " << vect << std::endl;
}
void loadVector(Vector &vect){
	std::cout << "Enter new vector: ";
	std::cin >> vect;
	std::cout << "Vector updated to " << vect << std::endl;
}
void addVectors(Vector &v1, Vector &v2, Vector &result){
	std::cout << v1 << " + " << v2 << " = " << v1 + v2 << std::endl;
	result = v1 + v2;
}
void subtractVectors(Vector &v1, Vector &v2, Vector &result){
	bool success = true;
	std::string input;
	unsigned int option = 0;	
	do{
		std::cout << "[1] => v1 - v2\n[2] => v2 - v1:";
		std::getline(std::cin, input);
		success = getUnsignedInt(&option, 1, input);
		if(option > 2 || !option)
			success = false;
	} while(!success);
	if(option == 1){
		std::cout << v1 << " - " << v2 << " = " << v1 - v2 << std::endl;
		result = v1 - v2;
	}
	else{
		std::cout << v2 << " - " << v1 << " = " << v2 - v1 << std::endl;
		result = v2 - v1;
	}
}
void dotProduct(const Vector& v1, const Vector &v2){
	std::cout << v1 << " * " << v2 << " = " << v1 * v2 << std::endl;
}
void compareVectors(const Vector& v1, const Vector &v2){
	if(v1 == v2)
		std::cout << "Vectors are equa\n";
	else
		std::cout << "Vectors are not equal\n";
}
void printVector(const Vector& vect){
	std::cout << vect << std::endl;
}
void cantGetError(){
	std::cout << "An error occurred while reading data. Try again.\n";
}
bool getUnsignedInt(unsigned int* data, const unsigned int& howMany, const std::string& input){
	std::stringstream inputStream(input);
	bool success = true;
	for(int i = 0; i < howMany; ++i){
		inputStream >> data[i];
		if(inputStream.fail()){
			success = false;
			break;
		}
	}
	if(!success)
		cantGetError();
	return success;
}
bool getDouble(double* data, const unsigned int& howMany, const std::string& input){
	std::stringstream inputStream(input);
	bool success = true;
	for(int i = 0; i < howMany; ++i){
		inputStream >> data[i];
		if(inputStream.fail()){
			success = false;
			break;
		}
	}
	if(!success)
		cantGetError();
	return success;
}
