#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

const string SECRET_WORD = "WATERMELON";
map<char, bool> guesses;
vector<char> wrong_guesses;

bool check_guess(char guess){
    for(char letter: SECRET_WORD){
        if(guess == letter)
        {
            return true;
        }
    }
    return false;
}

bool check_win(){
    for(char letter: SECRET_WORD){
        if(!guesses[letter]){
            return false;
        }
    }
    return true;
}

bool is_hanged(){
    return wrong_guesses.size() == 5;
}

int main(){

    cout << "*********************" << endl;
    cout << "*** Hangman Game ***" << endl;
    cout << "*********************" << endl;
    cout << endl;

    char guess;
    //Game end whem word was guessed or whem 
    while(!check_win() && !is_hanged()){
        cout << "Wrong guesses: ";
        for(char letter: wrong_guesses){
            cout << letter << " ";
        }
        cout << endl;
        for(char letter: SECRET_WORD){
            if(guesses[letter]){
                cout << letter << " ";
            }else{
                cout << "_ ";
            }
        }
        cout<< "\nYour guess: ";
        cin>>guess;
        guesses[guess] = true;

        if(check_guess(guess)){
            cout << "Your guess is in the word." << endl;
        }else{
            cout << "Your guess is not in the word." << endl;
            wrong_guesses.push_back(guess);
        }
        cout << endl;
    }
}