#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

//const string SECRET_WORD = "WATERMELON";
string SECRET_WORD;
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

void game_header(){
    cout << "*********************" << endl;
    cout << "*** Hangman Game ***" << endl;
    cout << "*********************" << endl;
    cout << endl;
}

void print_wrong_guesses(){
    cout << "Wrong guesses: ";
    for(char letter: wrong_guesses){
        cout << letter << " ";
    }
    cout << endl;
}

/// @brief Read a file with words to play an return a random word.
vector<string> read_wfile(){
    ifstream file;
    file.open("words.txt");
    unsigned int num_words = 0;
    file >> num_words;

    vector<string> words_list;
    for(int i = 0;i<num_words;i++){
        string word;
        file>>word;
        words_list.push_back(word);
    }
    return words_list;
}

string random_word_selection(){
    vector<string> words_list = read_wfile();
    srand(time(NULL));
    return words_list[rand()%words_list.size()];
}

void print_dashes(){
    for(char letter: SECRET_WORD){
        if(guesses[letter]){
            cout << letter << " ";
        }else{
            cout << "_ ";
        }
    }
}

void take_guess(){
    char guess;
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
int main(){

    game_header();
    SECRET_WORD = random_word_selection();
    //Game end whem word was guessed or whem 
    while(!check_win() && !is_hanged()){

        print_wrong_guesses();
        print_dashes();
        take_guess();
    }

    cout<< "The secret word was: "<< SECRET_WORD << endl;
    if(check_win()){
        cout << "Congratulations! You guessed the secret word!" << endl;
    }else{
        cout << "Game Over! try again!" << endl;
    }
}