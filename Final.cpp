#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <time.h> 

using namespace std;

void rollDice();
bool checkDice(int);
int trackInitiative();
string generateName();
int errorBD();

int main() {
  int input;

  //Hello and WElcome to my code :D
  //as we can see, i have this little header that is outside od the main loop.
  //so after the little splash screen, everything else can run as long as the user wants
  cout << "Welcome to Adams Handy Helper D&D App!" << endl;
  do{
    cout << "----------------------------------------" << endl;
    cout << "Please Select the option that suites you the most" << endl;
    cout << "1. Roll Dice\n2. initiative Tracker\n3. Generate Name\n0. Exit App" << endl;
    cout << "----------------------------------------" << endl;
    cin >> input;
    //here is the main switch statment. each takes us to the sub-main for each function
    switch(input){
      case 1 : rollDice(); break;
      case 2 : trackInitiative(); break;
      case 3 : generateName(); break;
    }

  //do thus until the user wants out
  }while(input != 0);
  //and that is it for my Main!
}

void rollDice(){
  //here is where we roll dice.
  int amt,type,mod,diceDis;
  bool isValid;
  char input, rusure;
  //here is the main part of the function, first we prompt the user how how many dice they want to roll
  do{
    cout << "----------------------------------------" << endl;
    //every time this is run the random seed is changed
    srand(time(NULL));

    cout << "How many dice are you rolling? . .";
    //get the amount of dice to roll
    cin >> amt;

    while(cin.fail()){
      errorBD();
      cout << "How many dice are you rolling? . .";
      cin >> amt;
    }

    while(amt > 999){
      if(amt >= 1000000){
        cout << "Are you sure you want to roll " << amt << " dice? This can take a long time" << endl;
      }else{
        cout << "Are you sure you want to roll " << amt << " dice?" << endl;
      }
      cout << "(y/n) ";
      cin >> rusure;
      if(rusure == 'y' || rusure == 'Y' ){
        break;
      }

      if(rusure == 'n' || rusure == 'N' ){
        cout << "How many dice are you rolling? . .";
        cin >> amt;
      }

    }

    cout << "You are rolling " << amt << "d";
    cin >> type;

    while(cin.fail()){
      errorBD();
      cout << "You are rolling " << amt << "d";
      cin >> type;
    }
    
    isValid = checkDice(type);

    while(isValid == false){
      cout << "You are rolling " << amt << "d";
      cin >> type;
      isValid = checkDice(type);
    };
    cout << "----------------------------------------" << endl;
    //now that we have the amount and the type, we see if there is a modifier that should be added to the rolls
    cout << "What is your ability check modifier? +";
    cin >> mod;

    while(cin.fail()){
      errorBD();
      cout << "What is your ability check modifier? +";
      cin >> mod;
    }

    //here i where the dice are actually rolled, and the code is repeated untill the amount inputed above have ben rolled
    cout << "\n----------------------------------------" << endl;
    do{
     cout << (rand() % type+1) +mod << " ";
      amt--;
    }while(amt != 0);
    
    cout << "\n----------------------------------------" << endl;
    cout << "\nWould you like to roll again?(y/n). .";
    cin >> input;
  }while(input == 'y' || input == 'Y');
  cout << "\n";
}

bool checkDice(int d){
  bool isVal = false;
  //here we are simple cheking if the dice the user wishes to roll is an actuall dice, be default it is not, only when the dice is correct do we pass the true value back to the rolling code
  switch(d){
    case 4 : isVal = true; break;
    case 6 : isVal = true; break;
    case 8 : isVal = true; break;
    case 10 : isVal = true; break;
    case 12 : isVal = true; break;
    case 20 : isVal = true; break;
    case 100 : isVal = true; break;
  }

   if(isVal == false){
        cout << "Please Make sure that you are entering one of the fallowing :\n4,6,8,10,12,20,100" << endl;
      }

  return isVal;
  //d4,d6,d8,d10,d12,d20,d100
}

int trackInitiative(){
  int input, ini, arrNum;
  int temp = 0;
  int count = 0;
  int player = 1;
  bool isDoneSorting = false;

  string name, tempName;

  //here is somehting a little sly. here we see how many charecters will be in this order, and then make an array based on that number. Simple i know but it makes me feel cool for thinking of it :D
  cout << "----------------------------------------" << endl;
  cout << "How many characters are in this iniative?(players + NPC's) . .";
  cin >> arrNum;
  while(cin.fail()){
    errorBD();
    cout << "How many characters are in this iniative?(players + NPC's) . .";
    cin >> arrNum;
  }

  int initiative[arrNum];
  string names[arrNum];
  //a paired name array is also made so there can be personalized names
  
  do{
    cout << "Please Enter Character " << player << "'s  Name" << endl;
    cin >> name;
    cout << "Now Enter " << name << "'s initiative" << endl;
    cin >> ini;

    while(cin.fail()){
      errorBD();
      cout << "Now Enter " << name << "'s initiative" << endl;
      cin >> ini;
    } 

    initiative[count] = ini;
    names[count] = name;
    count++;
    player++;
    
  }while(count < arrNum);

  cout << "\nSorting. . ." << endl;
  //here we sort the list high > low
  while(isDoneSorting == false){
    //if the IF never runs, then we are sorted, and are done
    isDoneSorting = true;
    for(int i = 0; i < (arrNum-1); i++){
      //here we cycle through the array(s) element by element seeing if element+1 is greater then the elemant being checked If it is move it up the list

      if(initiative[i] < initiative[i+1]){
        temp = initiative[i];
        initiative[i] = initiative[i+1];
        initiative[i+1] = temp;
        //if we get to this point we need to make sure we look at the list again
        isDoneSorting = false;
        tempName = names[i];
        names[i] = names[i+1];
        names[i+1] = tempName;
      } 
    }
  }

  cout << "\nThe order is. . ." << endl;

  for(int i = 0;  i < arrNum; i++){
    cout << names[i] << ":" << initiative[i] << endl;
  }

  cout << "\n";

  return 0;
}

string generateName(){
  srand(time(NULL));
  ifstream firstName ("FirstNames.txt");
  ifstream lastName ("LastNames.txt");
  string line,first,last;
  int totalFNLines = 0, totalLNLines = 0;
  int randFN, randLN;
  char input = 'y';
  //get random first name
  //thnaks to stack overflow for this code idea
  
  vector<string> FNline;
  vector<string> LNline;

   while(getline(firstName,line)){
    totalFNLines++;
    FNline.push_back(line);
  }

  while(getline(lastName,line)){
    totalLNLines++;
    LNline.push_back(line);
  }

  do{
    randFN = (rand()%totalFNLines);
    first = FNline[randFN];

    randLN = (rand()%totalLNLines);
    last = LNline[randFN];

    cout << "----------------------------------------" << endl;

    cout << first << " " << last << endl;

    cout << "----------------------------------------" << endl;

      cout <<"would you like to Generate another name?(y/n)" << endl;
      cin >> input;
  }while(input == 'y' || input == 'Y');

  return line;
}

int errorBD(){
  //this code is called when the user trys to input bad data
  //just kind of makes sure that the code dosn't crap itself
  cout << "----------------------------------------" << endl;
  cout << "ERROR : Bad input! Please Try again\n";
  cout << "----------------------------------------" << endl;
  cin.clear();
  cin.ignore();

  return 0;
}

/*
4/7/20 : Started work on the app, got the rolling dice part working as intended, promtes user to keep rolling untill the decide to stop.
Also came up with NAme #1
*/
