#include <iostream>
#include <limits>
#include <stdio.h>
#include <string.h>
#include "yojimbo.h"
using namespace std;

int setup();
Yojimbo advSetup();
int payYojimbo();
bool hasOverdrive();
int caveChoice();

int main() {
  int gameVersion = setup();
  int payment = payYojimbo();
  Yojimbo yojimbo = Yojimbo(gameVersion, payment);
  yojimbo.setOverdrive(hasOverdrive());
  yojimbo.setCF(caveChoice());
  yojimbo.attack();
  yojimbo.displayStats();
}

int setup() {
  int version = 0;
  cout << "Select your version of FFX:\n1. HD Remaster / PAL / "
          "International\n2. Original JP / Original NTSC\n";
  cin >> version;
  while (version > 2 || version < 1) {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      version = 0;
    }
    cout << "\n!! Detected an invalid input. Please try again. !!\n\n";
    cout << "Select your version of FFX:\n1. HD Remaster / PAL / "
            "International\n2. Original JP / Original NTSC\n";
    cin >> version;
  }
  return version;
}


Yojimbo advSetup(){

}

int payYojimbo(){
    int pay;
    int cap = Yojimbo().gilCap;
    cout << "How much do you wish to pay Yojimbo?\n";
    cin >> pay;
    while(pay < 0 || pay > cap || !cin){
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pay = 0;
        }
        cout << "!! Pay must be a number between 0 and " << cap << " !!\n\n";
        cout << "How much do you wish to pay Yojimbo?\n";
        cin >> pay;
    }
    return pay;
}

bool hasOverdrive(){
    char s = ' ';
    cout << "Does Yojimbo currently have Overdrive? (y/n)\n";
    cin >> s;
    while(s != 'y' && s != 'n'){
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            s = ' ';
        }
        cout << "!! Invalid response !!\n\n";
        cout << "Does Yojimbo currently have Overdrive? (y/n)\n";
        cin >> s;
    }

    if(s == 'y' || s == 'Y') return true; else return false;
}

int caveChoice(){
    int choice = 0;
    cout << "What was your choice at the Cavern of Stolen Fayth?\n"
            "1. To train as a summoner.\n"
            "2. To gain the power to destroy fiends.\n"
            "3. To defeat the most powerful of enemies.\n";
    cin >> choice;
    while(choice < 1 || choice > 3 || !cin){
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }
        cout << "!! Invalid response !!\n\n";
        cout << "1. To train as a summoner.\n"
                "2. To gain the power to destroy fiends.\n"
                "3. To defeat the most powerful of enemies.\n";
        cin >> choice;
    }

    if(choice == 1){
        int total = 0;
        cout << "What's your total gil?";
        cin >> total;
        while(!cin){
            cout << "Really, now. What's your total gil?";
            cin >> total;
        }
    }
    return choice;
}