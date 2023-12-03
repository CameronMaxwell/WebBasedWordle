// Header files and C++ libraries
#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <Wt/WText.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "WordleApplication.h"

// Constructor for the Wordle class, takes Wt::WEnvironment argument
WordleApplication::WordleApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env), targetWord_(), attempts_(0) {
    // Web title of application
    setTitle("Wordle");

    // Read words from file, randomly select and store the answer word
    readWordsFromFile("words.txt");
    targetWord_ = selectRandomWord(wordList_);

    // Add prompt to enter guess
    root()->addWidget(std::make_unique<Wt::WText>("Enter guess, 5 letters maximum: "));
    // Create input field box for user guesses
    input_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    input_->setPlaceholderText("Enter guess");
    // Create button for user guess
    Wt::WPushButton* guessButton = root()->addWidget(std::make_unique<Wt::WPushButton>("Submit"));
    // Create empty text field for output
    feedback_ = root()->addWidget(std::make_unique<Wt::WText>(""));
    // Connect the button click to playWordle function
    guessButton->clicked().connect(this, &WordleApplication::playWordle);
}

// Function to read the words from the text file
void WordleApplication::readWordsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    // Check if the file opened properly
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        exit(1); 
    }
    // Read the words from the file line by line, add each word to the word list
    std::string word;
    while (std::getline(file, word)) {
        wordList_.push_back(word);
    }

    file.close();
}
// Function for selecting a random word from the word list 
std::string WordleApplication::selectRandomWord(const std::vector<std::string>& words) {
    // Check if word list is empty
    if (words.empty()) {
        std::cerr << "Error: No words available." << std::endl;
        exit(1); 
    }
    //  Select a random word from the word list
    std::srand(static_cast<unsigned int>(std::time(nullptr))); 
    int randomIndex = std::rand() % words.size();
    return words[randomIndex];
}

// Function for the wordle logic
void WordleApplication::playWordle() {
    std::string guessedWord = input_->text().toUTF8();

    // Remove white spaces from the guess 
    guessedWord.erase(std::remove_if(guessedWord.begin(), guessedWord.end(), ::isspace), guessedWord.end());

    // Convert guess to all lowercase
    std::transform(guessedWord.begin(), guessedWord.end(), guessedWord.begin(), ::tolower);
    // Checks if there's any numbers in the guess, if so then output an invalid guess statement
    if (std::any_of(guessedWord.begin(), guessedWord.end(), ::isdigit)) {
        feedback_->setText("<br /> Invalid guess. The word should not contain numbers.");
        return;
    }
    // Checks if the guess is 5 letters long, if not then output an invalid guess statement
    if (guessedWord.length() != targetWord_.length())  {
        feedback_->setText("<br />Invalid guess. The word length should be " + std::to_string(targetWord_.length()) + " letters.");
        return;
    }
    // Call function to compare the guess and answer words
    compareWords(guessedWord);
    // If the guess matches the answer, print out success statement
    if (guessedWord == targetWord_) {
        feedback_->setText("<br />Congratulations! You guessed the word.");
    } else {
        // If it's a missed guess, add to the attempts counter and output message if user runs out of guesses.
        attempts_++;
        if (attempts_ >= 6) {
            feedback_->setText("<br />Out of attempts. The word was: " + targetWord_);
        }
    }
    input_->setText("");
}

// Function to compare the guess and answer words
void WordleApplication::compareWords(const std::string& guessedWord) {
    std::string feedbackText;
    // Loop through all letters in word
    for (int i = 0; i < targetWord_.length(); ++i) {
        // If the guess letter is the same and in the correct spot, change letter to green
        if (guessedWord[i] == targetWord_[i]) {
            feedbackText += "<span style='color: green;'>" + std::string(1, guessedWord[i]) + "</span>";
        // If the guess letter is present but in the wrong spot, change letter to red
        } else if (targetWord_.find(guessedWord[i]) != std::string::npos) {
            feedbackText += "<span style='color: red;'>" + std::string(1, guessedWord[i]) + "</span>";
        } else {
            // Leave letter colour if not present in answer word
            feedbackText += guessedWord[i];
        }
    }
    // Set the output text
    feedback_->setText(feedback_ ->text() + "<br />" + feedbackText);
}








