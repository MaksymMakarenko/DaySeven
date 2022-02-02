#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Positions {
private:
	int value;
	int count;
public:
	Positions(int value) {
		this->value = value;
		count = 1;
	}
	int getValue() {
		return value;
	}
	int getCount() {
		return count;
	}
	void addCount() {
		count++;
	}
};

void addValue(std::vector<Positions>& values, int value) {
	bool inclusions = false;
	for (auto& val : values) {
		if (val.getValue() == value) {
			val.addCount();
			inclusions = true;
			break;
		}

	}
	if (!inclusions) {
		values.push_back(value);
	}
}

int maxValue(std::vector<Positions> values) {
	int max_value = 0;
	for (auto value : values) {
		if (max_value < value.getValue()) {
			max_value = value.getValue();
		}
	}
	return max_value;
}

long int amountOfFuelNSteps(int n) {
	if (n == 1) {
		return 1;
	}
	else if (n == 0) {
		return 0;
	} 
	else {
		return n + amountOfFuelNSteps(n - 1);
	}
}

long int countFuelQuantity(std::vector<Positions> values, int value) {
	long int fuel_quantity = 0;
	for (auto val : values) {
		fuel_quantity += amountOfFuelNSteps(abs(val.getValue() - value)) * val.getCount();
	}
	return fuel_quantity;
}

void minAmountOfFuel(std::vector<long int> fuel) {
	long int min = INT_MAX;
	for (auto value : fuel) {
		if (min > value) {
			min = value;
		}
	}
	std::cout << min << "\n";
}


std::vector<int>  splitStringComma(std::string str) {
	int iter = 0;
	std::vector<int> values;
	std::string value;
	while (iter < str.length()) {
		if (str[iter] != ',') {
			value += str[iter];
		}
		else {
			values.push_back(stoi(value));
			value = "";
		}

		iter++;
	}
	values.push_back(stoi(value));
	return values;
}



int main()
{
	std::string path("inputSeven.txt");

	std::ifstream in(path); 
	std::string line;
	std::vector<int> values;
	std::vector<Positions> submarine_position;
	int max_value;


	if (in.is_open())
	{
		while (getline(in, line))
		{
			values = splitStringComma(line);
		}
	}
	else std::cout << "File not found";
	in.close();    

	for (auto value : values)
	{
		addValue(submarine_position, value);
	}

	max_value = maxValue(submarine_position);
	std::vector<long int> fuel(max_value, 0);

	for (int i = 0; i < max_value; i++) {
		fuel[i] = countFuelQuantity(submarine_position, i);
	}

	minAmountOfFuel(fuel);

	system("pause");
	return 0;
}