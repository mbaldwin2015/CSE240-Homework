#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
	string line, name, attr1, attr2, move, temp;
	int hp, str, def, speed;
	ifstream file("Pokedex.csv"); // object 'file' of class ifstream

	if (file.is_open())
	{
		getline(file, line); // in this case, we need to ignore the first line

		while (getline(file, line, '\n'))
		{
			istringstream iss(line);

			getline(iss, name, ',');

			getline(iss, temp, ',');
			hp = stoi(temp); // stoi = string to integer

			getline(iss, temp, ',');
			str = stoi(temp);
			
			getline(iss, temp, ',');
			def = stoi(temp);
			
			getline(iss, temp, ',');
			speed = stoi(temp);
			
			getline(iss, move, ',');

			getline(iss, attr1, ',');
			if (attr1.compare("Electric")) cout << "Hello world!" << endl; // these attributes need to be an object or something
			// so we need string compare to figure it out

			getline(iss, attr2, ',');
		}

		file.close();
	}
	else
	{
		cout << "ERROR READING FILE" << endl;
	}
}