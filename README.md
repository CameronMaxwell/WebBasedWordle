# WebBasedWordle

This C++ wordle game runs on a remote Wt server. The player gets 6 chances to guess a 5 letter word. With every guess, the player is given hints toward the target word through highlighting letters on the guessed word based on it's correctness. 

Running the game:
1. To setup the environment, install C++ compiler tools, CMake, Boost, and Wt.
2. While on your computers terminal, run the command make while within the application's folder
3. Once the application has been compiled, run the command ./wordle --docroot . --http-listen 0.0.0.0:8080
4. Load up the server link on your browser to start playing the game!
