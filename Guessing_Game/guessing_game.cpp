#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    
    //Print the start message
    cout<<"*************************************"<<endl;
    cout<<"* Welcome to the guessing game *"<<endl;
    cout<<"*************************************"<<endl;

    cout<< "Choose your difficulty level: "<<endl;
    cout<<"Easy (E), Medium (M) or Hard (H)"<<endl;

    //Difficulty choice
    char difficulty;
    cin >> difficulty;

    int number_of_attempts;

    if(difficulty == 'E'){
        number_of_attempts = 15;
    }
    else if (difficulty == 'M')
    {
        number_of_attempts = 10;
    }
    else{
        number_of_attempts = 5;
    }
    
    //Generating random number between 0 and 100
    srand(time(NULL));
    const int SECRET_NUMBER = rand() % 100;

    int attempts = 0;
    bool guessed = false;
    int guess;
    
    double score = 1000.0;
    double lost_score = 0;

    for(attempts = 1; attempts <= number_of_attempts; attempts++)
    {
        cout<<"Attempts "<< attempts<<endl;
        cout<<"What's your guess?"<<endl;
        cin>>guess;

        lost_score = abs(guess - SECRET_NUMBER)/2.0;
        score-=lost_score;

        cout<< "Your guess's value is: " << guess << endl;
        

        if(guess == SECRET_NUMBER)
        {
            guessed = true;
            cout<<"Congratulations! You guessed the secret number!" << endl;
            break;
        }
        else if(guess > SECRET_NUMBER)
        {
            cout<<"Your number is greater than the secret number!"<<endl;
        }
        else
        {
            cout<<"Your number is smaller than the secret number!"<<endl;
        }
    }
    cout<<"End of the game!"<<endl;
    
    if(!guessed)
    {
        cout << "You lost! Try again!" << endl;
    }
    else{
        cout<< "You guessed the number correctly in "<< attempts << " attempts" <<endl;
        cout.precision(2);
        cout << fixed;
        cout<< "Your score was: " << score << "."<<endl;
    }

    return 0;
}