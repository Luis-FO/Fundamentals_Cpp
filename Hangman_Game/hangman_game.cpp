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

///  @brief Check if the guess is part of the secret word
bool check_guess(char guess){
    for(char letter: SECRET_WORD){
        if(guess == letter)
        {
            return true;
        }
    }
    return false;
}

/// @brief Check if the word was guessed
bool check_win(){
    for(char letter: SECRET_WORD){
        if(!guesses[letter]){
            return false;
        }
    }
    return true;
}

/// @brief Check if the attempts are over.
bool is_hanged(){
    return wrong_guesses.size() == 5;
}

/// @brief Print the game intro
void game_header(){
    cout << "*********************" << endl;
    cout << "*** Hangman Game ***" << endl;
    cout << "*********************" << endl;
    cout << endl;
}

/// @brief Shows wrong guesses up to now
void print_wrong_guesses(){
    cout << "Wrong guesses: ";
    for(char letter: wrong_guesses){
        cout << letter << " ";
    }
    cout << endl;
}

/// @brief Read a word bank file.
vector<string> read_wfile(){
    ifstream file;
    file.open("words.txt");
    if(file.is_open()){
        unsigned int num_words = 0;
        file >> num_words;

        vector<string> words_list;
        for(int i = 0;i<num_words;i++){
            string word;
            file>>word;
            words_list.push_back(word);
        }
        file.close();
        return words_list;
    }else{
        cout<<"Unable to access word bank!"<<endl;
        exit(0);
    }

}
/// @brief Select a random word to play
void random_word_selection(){
    vector<string> words_list = read_wfile();
    srand(time(NULL));
    SECRET_WORD = words_list[rand()%words_list.size()];
}

/// @brief Print the dashes with the correct guesses up to now.
void print_dashes(){
    for(char letter: SECRET_WORD){
        if(guesses[letter]){
            cout << letter << " ";
        }else{
            cout << "_ ";
        }
    }
}

/// @brief Take the player's guess
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
void save_file(vector<string> words_list){
    ofstream file;
    file.open("words.txt");
    if(file.is_open()){
        file << words_list.size() << endl;
        for(string word: words_list){
            file << word << endl;
        }
        file.close();
    }else{
        cout<<"Unable to access word bank!"<<endl;
        exit(0);
    }
}
void add_new_word(){
    cout<<"Enter a new word (with capital letters): ";
    string new_word;
    cin >> new_word;

    vector<string> words_list = read_wfile();
    words_list.push_back(new_word);
    save_file(words_list);

}

int main(){

    game_header();
    random_word_selection();
    //Game end whem word was guessed or whem 
    while(!check_win() && !is_hanged()){

        print_wrong_guesses();
        print_dashes();
        take_guess();
    }

    cout<< "The secret word was: "<< SECRET_WORD << endl;
    if(check_win()){
        cout << "Congratulations! You guessed the secret word!" << endl;
        cout<< "Do you want to add a new word to the bank?(Y/N)"<<endl;
        char op;
        cin>>op;
        if(op == 'Y'){
            add_new_word();
        }
    }else{
        cout << "Game Over! try again!" << endl;
    }
}