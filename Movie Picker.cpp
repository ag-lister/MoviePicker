//Andy Lister, aglister@dmacc.edu, 11/19/19
//This program displays a menu to a user and allows them to pick a number.
//The program then takes that number, and based on that number, opens the appropriate
//text file. It then counts how many lines are in that file and then rolls a random number
//between 1 and how many lines there are. It then re-opens that file and counts down the appropriate number
//of lines and returns a random movie for the user to watch.

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>	//used for random number
#include <ctime>	//used for random number
using namespace std;

#define LINEOUT(str) cout << #str << endl

//Prototypes
void Menu();
string MoviePicker(fstream &, string);
void MovieAdd(fstream &);
string coinFlip();
int menuChoice();

int main(){
	Menu();
	int choice = 0;
	choice = menuChoice();
	fstream movieFile;
	string fileName = "";
	
	while(choice != 999){
	
	
	//Rolls random movie and saves it to a string to be used later
	string randomMovie = "";
	switch (choice){
		case 1:
			randomMovie = MoviePicker(movieFile, "All.txt");
			cout << randomMovie;
			cout << endl;
			break;
		case 2:
			randomMovie = MoviePicker(movieFile, "Action.txt");
			cout << randomMovie;
			cout << endl;
			break;
		case 3:
			randomMovie = MoviePicker(movieFile, "Adventure.txt");
			cout << randomMovie;
			cout << endl;
			break;
		case 4:
			randomMovie = MoviePicker(movieFile, "Animated.txt");
			cout << randomMovie;
			cout << endl;
			break;
		case 5:
			cout << MoviePicker(movieFile, "Comedy.txt");
			cout << endl;
			break;
		case 6:
			cout << MoviePicker(movieFile, "DC.txt");
			cout << endl;
			break;
		case 7:
			cout << MoviePicker(movieFile, "Disney.txt");
			cout << endl;
			break;
		case 8:
			cout << MoviePicker(movieFile, "Drama.txt");
			cout << endl;
			break;
		case 9:
			cout << MoviePicker(movieFile, "Fantasy.txt");
			cout << endl;
			break;
		case 10:
			cout << MoviePicker(movieFile, "Historical.txt");
			cout << endl;
			break;
		case 11:
			cout << MoviePicker(movieFile, "Marvel.txt");
			cout << endl;
			break;
		case 12:
			cout << MoviePicker(movieFile, "Old.txt");
			cout << endl;
			break;
		case 13:
			cout << MoviePicker(movieFile, "Romance.txt");
			cout << endl;
			break;
		case 14:
			cout << MoviePicker(movieFile, "SiFi.txt");
			cout << endl;
			break;
		case 222: //Allows for the adding of a movie
			system("cls");
			MovieAdd(movieFile);
			break;
		case 555:
			cout << coinFlip();
			cout << endl;
			break;
		default:
			cout << "Please enter a number thats on the menu." << endl;	
	}
	
	//Prompts user outside switch statement to either roll again or,
	//if the user has rolled too many times to see the menu anymore,
	//prompts the user to clear the screen and show the menu
	if(choice == 222){
		system("cls");
		Menu();
		choice = menuChoice();
	} else {
	
	LINEOUT(Enter a menu number to roll again:);
	LINEOUT((Enter 111 to clear screen and show menu));
	choice = menuChoice();
	
	}
	
	if(choice == 111){
		system("cls");
		Menu();
		choice = menuChoice();
	}
	}//end of while loop
	
	LINEOUT(Enjoy your movie!);
	
return 0;
}

//This function provides some much needed input validation for if the user enters letters
//when they should be entering numbers
int menuChoice(){
	int choice = 0;
	while(!(cin >> choice)){
		cout << "Please enter only numbers for the menu." << endl;
		cout << "Please try again" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
	}
	return choice;
}

//This function randomly generates a number, sees if it can be divided evenly by 2, and then
//depending on the result returns either heads or tails. In this case it will either return either
//my name, or my wife's name.
string coinFlip(){
	unsigned seed = time(0);
	srand(seed);
	int randomNum = (rand() % (100 - 1 + 1)) + 1;	//Generates a number 1-100
	string heads = "Andy";
	string tails = "Amanda";
	string result = "";
	
	if(randomNum % 2 == 0){
		result = heads;
	} else {
		result = tails;
	}
	
	return result;
}

//This function provides a menu for the movie picker in an easy to call function
void Menu(){
	LINEOUT(Lets pick a movie!);
	LINEOUT(Enter the number for the catagory you want and let the movie picker work its magic!);
	cout << endl;
	LINEOUT(1-All	2-Action	3-Adventure	4-Animated	5-Comedy	6-DC	7-Disney);
	LINEOUT(8-Drama	9-Fantasy	10-Historical 11-Marvel	12-Old	13-Romance	14-SiFi);
	LINEOUT((999 to close - 222 to add new movie - 555 to flip a coin));
	cout << endl;
	return;
}

//This function provides the randomly rolled movie to the user. It counts how many lines there are
//in a movie genre txt file and then rolls a random number between 1 and that many lines. It then
//returns a string to the user that contains a randomly rolled movie.
string MoviePicker(fstream &file, string fileName){
	//Opens file
	file.open(fileName, ios :: in);
	
	//Counts how many lines are in the file, allowing dynamic random number rolling
	//for when more movies get added to files
	int count = 1;
	string line = "";
	getline(file, line);
	while(!file.eof()){
		getline(file, line);
		count++;
	}
	file.close();
	
	
	//Rolls a random number between 1 and count, then spits out the movie on that line
	unsigned seed = time(0);
	srand(seed);
	int randomNum = (rand() % (count - 1 + 1)) + 1;
	//cout << count << endl; //Use this to check how many movies are in that txt file
	count = 1;
	file.open(fileName, ios ::in); //Opens file again
	getline(file, line);
	while(count != randomNum){
		count++;
		getline(file, line);
	}
	file.close();
	
	return line;
}


//This function takes care of adding a movie. It captures a title from the user and adds
//it to the All.txt file, then it prompts users to see if the movie needs to be added to any of the other
//genre txt files.
void MovieAdd(fstream &File){
	string title = "";
	int choice = 0;
	
	//Takes care of grabbing title and adding it to all.txt
	LINEOUT(Please enter the title of the movie you would like to add:);
	cin.ignore();
	getline(cin, title);
	File.open("All.txt", ios :: app);
	File << endl;
	File << title;
	File.close();
	
	//Prompts user if there are other genres that the movie should be added to
	cout << endl;
	LINEOUT(Your movie is automatically added to the All.txt file.);
	LINEOUT(Please enter another genre txt file that it should go into.);
	cout << endl;
	LINEOUT(2-Action	3-Adventure	4-Animated	5-Comedy	6-DC	7-Disney);
	LINEOUT(8-Drama	9-Fantasy	10-Historical 11-Marvel	12-Old	13-Romance	14-SiFi);
	LINEOUT((999 to close));
	cin >> choice;
	
	while(choice != 999){
		switch (choice){
			case 2:
				File.open("Action.txt", ios :: app);
				File << endl;
				File << title;
				cout << "It has been added to the Action.txt file." << endl;
				File.close();
				break;
			case 3:
				File.open("Adventure.txt", ios :: app);
				File << endl;
				File << title;
				cout << "It has been added to the Adventure.txt file." << endl;
				File.close();
				break;
			case 4:
				File.open("Animated.txt", ios :: app);
				File << endl;
				File << title;
				cout << "It has been added to the Animated.txt file." << endl;
				File.close();
				break;
			case 5:
				File.open("Comedy.txt", ios :: app);
				File << endl;
				File << title;
				cout << "It has been added to the Comedy.txt file." << endl;
				File.close();
				break;
			case 6:
				File.open("DC.txt", ios :: app);
				File << endl;
				File << title;
				cout << "It has been added to the DC.txt file." << endl;
				File.close();
				break;
			case 7:
				File.open("Disney.txt", ios :: app);
				File << endl;
				File << title;
				cout << "It has been added to the Disney.txt file." << endl;
				File.close();
				break;
			case 8:
				File.open("Drama.txt", ios :: app);
				File << endl;
				File << title;
				cout << "It has been added to the Drama.txt file." << endl;
				File.close();
				break;
			case 9:
				File.open("Historical.txt", ios :: app);
				File << endl;
				File << title;
				cout << "It has been added to the Historical.txt file." << endl;
				File.close();
				break;
			case 10:
				File.open("Marvel.txt", ios :: app);
				File << endl;
				File << title;
				cout << "It has been added to the Marvel.txt file." << endl;
				File.close();
				break;
			case 11:
				File.open("Old.txt", ios :: app);
				File << endl;
				File << title;
				cout << "It has been added to the Old.txt file." << endl;
				File.close();
				break;
			case 12:
				File.open("Romance.txt", ios :: app);
				File << endl;
				File << title;
				cout << "It has been added to the Romance.txt file." << endl;
				File.close();
				break;
			case 13:
				File.open("SiFi.txt", ios :: app);
				File << endl;
				File << title;
				cout << "It has been added to the SiFi.txt file." << endl;
				File.close();
				break;
			default:
				cout << "Please enter a number for a genre or 999 to exit." << endl;
		}
		cout << endl;
		cout << "Enter another genre number or enter 999 to exit:" << endl;
		cin >> choice;
	}
	
}
