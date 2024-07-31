#include <iostream>
#include<string>

  using namespace std;

const int states_max = 100;
const int input_max = 100;

struct MOORE_STRUCT {
    int states;
    int state_count;
    int input;
    int new_state[states_max][input_max]; // new_state table
    int output[states_max][input_max]; // Output table
    int inc_states[states_max];
    int outno[states_max];
    
};

struct MEALY_STRUCT {
    int states;
    int input;
    int new_state[states_max][input_max]; // new_state table
    int output[states_max][input_max]; // Output table

};

void mealy2moore(const MEALY_STRUCT& mealy, MOORE_STRUCT & moore) {
  moore.states = mealy.states;
  moore.input = mealy.input;

  // Initialize Moore machine new_state table
  for (int i=0; i < moore.states; ++i) {
    for (int j=0; j < moore.input; ++j) {
      moore.new_state[i][j] = mealy.new_state[i][j]; // Copy new_states
      moore.output[i][j] = mealy.output[i][j];
    }
  }

  
  
  
  for (int i=0; i < moore.states; ++i) {


    moore.inc_states[i] = -1;
    moore.outno[i] = -1;
  }
  
  
  
  moore.state_count = moore.states;

  for (int i=0; i < moore.states; ++i) {
    for (int j=0; j < moore.input; ++j) {
      if (moore.inc_states[moore.new_state[i][j]] == -1) {
      	
        moore.inc_states[moore.new_state[i][j]] = mealy.output[i][j];
        

      } else if (moore.inc_states[moore.new_state[i][j]] == mealy.output[i][j]) {
        
        

      } else if (moore.inc_states[moore.new_state[i][j]] != mealy.output[i][j]&&moore.inc_states[moore.new_state[i][j]] !=-1) {
      	moore.outno[moore.new_state[i][j]]=1;
        moore.state_count++;
        

      }

    }
  }


}


void MooreToMealy( MEALY_STRUCT& mealy, const MOORE_STRUCT&  moore) {

  mealy.states = moore.states;
  mealy.input = moore.input;

  // Initialize Moore machine new_state table
  for (int i=0; i < mealy.states; ++i) {
    for (int j=0; j < mealy.input; ++j) {
      mealy.new_state[i][j] = moore.new_state[i][j]; // Copy new_states
    }
  }

  // Initialize Moore machine output table
  for (int i=0; i<mealy.states;++i) {
    for (int j=0;j< mealy.input;++j) {

      mealy.output[i][j]=moore.output[i][j];
    }
  }


}







const std:: string RESET_COLOR = "\033[0m";
const std:: string RED_COLOR = "\033[31m";
const std:: string GREEN_COLOR = "\033[32m";
const std:: string YELLOW_COLOR = "\033[33m";
const std:: string BLUE_COLOR = "\033[34m";

int main() {
  // Print a welcome message with colored text
  std:: cout << "\033[36m";
  cout << "\t\t\t\t\t\t*****************************" << std:: endl;
  cout << RED_COLOR << " \t\t\t\t\t\t\t   WELCOME TO          " << std:: endl;
  cout << RED_COLOR << "\t\t\t\t\t\t\tMACHINE CONVERTER    " << std:: endl;
  std:: cout << "\033[36m";
  cout << "\t\t\t\t\t\t*****************************" << std:: endl;

  // Reset text color
  cout << RESET_COLOR;

  start:
	
	int choice;
  cout << BLUE_COLOR << "\n\n\t\t\t\t ENTER :\n\t\t\t\t\t 1: Mealy to Moore\n\n\t\t\t\t\t 2: Moore to Mealy\n\n\t\t\t\t\t 3: Exit\n\n  ";
  cin >> choice;
  cout << RESET_COLOR;
  cout << "\033[36m";
  if (choice == 1) {
	
	
    MEALY_STRUCT mealy1;
    MOORE_STRUCT moore1;

    // Input Mealy machine
    cout << GREEN_COLOR << "Enter the number of states in the Mealy machine: ";
    cin >> mealy1.states;
    cout << "Enter the number of input symbol in the Mealy machine: ";
    cin >> mealy1.input;

    cout  <<BLUE_COLOR<< "Enter the Mealy machine Transition function(only input two outputs):\n";
    for (int i=0; i < mealy1.states; ++i) {
      for (int j=0; j < mealy1.input; ++j) {
        cout << "From state Q" << i << " --- " << char('a' + j) << "/ ";
        cin >> mealy1.output[i][j];
        cout << "-->  Q";
        cin >> mealy1.new_state[i][j];
      }
    }



    // Convert Mealy to Moore
    mealy2moore(mealy1, moore1);

    // Output Moore machine
    cout << GREEN_COLOR << "\nEquivalent Moore machine:\n";
     cout << "\033[36m";
    cout << "No of States: " << moore1.state_count << endl;
    cout << "No of input symbols: " << moore1.input << endl;
    cout << "Transition function:\n";
    for (int i=0; i < moore1.states; ++i) {
      for (int j=0; j < moore1.input; ++j) {
      	if(moore1.outno[i]==-1){
      		cout << "From state Q" << i <<"/"<<moore1.inc_states[i]<< " --" << char('a' + j) << " --> Q" << moore1.new_state[i][j] << "/" << moore1.output[i][j] << endl;
		  }else if(moore1.outno[i]== 1)
		  {
		  	cout << "From state Q" << i <<"/0 --"<< char('a' + j) << " --> Q" << moore1.new_state[i][j] << "/" << moore1.output[i][j] << endl;
		  	cout << "From state Q" << i <<"/1 --"<< char('a' + j) << " --> Q" << moore1.new_state[i][j] << "/" << moore1.output[i][j] << endl;
		  }

        

      }
    }goto start;
  } else if (choice == 2) {
  		
    MEALY_STRUCT mealy;
    MOORE_STRUCT moore;

    cout << GREEN_COLOR << "Enter the number of states in the Moore machine: ";
    cin >> moore.states;
    cout << "Enter the number of input symbol in the Moore machine: ";
    cin >> moore.input;

    cout <<BLUE_COLOR << "Enter the Moore machine Transition function:\n";
    for (int i=0; i < moore.states; ++i) {
      for (int j=0; j < moore.input; ++j) {
        cout << "From state Q" << i << " --- " << char('a' + j) << "--> Q";
        cin >> moore.new_state[i][j];
        cout << "/";
        cin >> moore.output[i][j];
      }
    }


    // Convert MOORE TO MEALY
    MooreToMealy(mealy, moore);

    // Output Moore machine
    cout << GREEN_COLOR << "\nEquivalent Mealy machine:\n";
     cout << "\033[36m";
    cout << "No. Of States: " << mealy.states << endl;
    cout << "No. of Input Symbols: " << moore.input << endl;
    cout << "Transition function:\n";
    for (int i=0; i < mealy.states; ++i) {
      for (int j=0; j < mealy.input; ++j) {

        cout << "From state Q" << i << " --" << char('a' + j) << "/" << moore.output[i][j] << " --> Q" << moore.new_state[i][j] << endl;

      }
    }
goto start;


  } else if (choice == 3) {
  	
return 0;

  } else {
cout<<RED_COLOR<<"/n/nINCORRECT CHOICE\n";
goto start;
    
  }

  return 0;
}
