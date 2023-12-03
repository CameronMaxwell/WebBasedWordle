
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

// Defines the Wordle class
class WordleApplication : public Wt::WApplication {
public:
    // Wordle constructor, takes in Wt::WEnvironment argument
    WordleApplication(const Wt::WEnvironment& env);

private:
    // private functions
    void playWordle();
    void compareWords(const std::string& guessedWord);
    void readWordsFromFile(const std::string& filename);
    std::vector<std::string> wordList_;
    std::string targetWord_;
    std::string selectRandomWord(const std::vector<std::string>& words);
    int attempts_;
    Wt::WLineEdit* input_;
    Wt::WText* feedback_;
    
    
};


