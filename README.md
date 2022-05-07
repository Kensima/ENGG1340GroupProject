# ENGG1340GroupProject
Group Number: 226

Group member: **Yukun Sima**, **Haoyu Sun**

UID: 3035946124, 3035856044

Problem statement:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
Our inspiration for designing this game comes from an ordinary board game party. Since Blackjack is a very simple card game, everyone is familiar with its rules. But in fact, the very simple Blackjack rule is easy to be boring, and everyone can't agree to play other card games (because of the number limit or difficulty). Therefore, in order to meet everyone's needs, I temporarily add several rules (such as mutual attack and defense between players) for blackjack, which are the same as the code game we create today, so as to make the whole game more playable. For other card games, blackjack is more popular. Basically everyone knows how to play it, but its rules are too simple and easy to make people feel bored. Most other card games (such as blood stained clock tower, landlords, Texas poker, etc.) have more interesting game rules, but some are less popular and difficult to start; Some have strict number limits, otherwise they will lose the fun of the game. Therefore, I designed this upgraded version of blackjack.

First of all, it adds more abundant playing methods to the original rules, and because it is similar to the original blackjack, it can be accepted by the public when it is not difficult to start; Not only that, the game will not last for a long time, which can also enable people to play during recess.
Short game introduction: Our group designed a card game similar to Blackjack but with different rules and more playing methods.

Game Description: 
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

In our upgraded version of Black Jack game, you will fight three AI players.

Before the game starts, you will see the directory, which includes three options: 1: difficulty setting, 2: Game reading, and 3: starting a new game. When you select the difficulty setting (enter 1), you will enter the difficulty setting interface. You can adjust the game difficulty between "simple" and "normal".

Game file reading (enter 2): the game file reading function is used to read the progress of the previously unfinished game and continue the unfinished game.

Start a new game (enter 3): this option will start a new game.

Basic rules of the game:

**Step 1**: at the beginning of the game, the system will prompt the player to enter a number, which is the maximum number of rounds of the game. In other words, when the game round equals this number and the game continues, the game will automatically end and enter settlement.

**Step 2**: next, the new round starts and enters the licensing stage. The player and the three AI will be assigned a card with random points (with decor). At this stage, players can only see their own cards, but can't see other AI cards.

**Step 3**: after seeing the amount of cards and gold coins they hold, players can choose to launch one of the following three skills (attack an AI, defend, or remain neutral). When a player chooses to attack an AI and that AI chooses to launch a skill other than defense, your opponent will receive a random card because of being attacked. When multiple people attack one person at the same time, the attacker receives the same number of cards equal to the number of people for attack. When multiple person attacks take effect, the attacker receives the same number of card points. When players or AI choose to defend, they are immune to any attack. When a player or AI chooses to remain neutral or attack, it cannot be immune to attack.

(AI will randomly launch its own skills)

The amount of gold coins obtained by different skills launched by players is also different:

1: **Attack** - 100 gold coins for success, 0 gold coins for failure, and 50 gold coins will be lost if the player is attacked.

2: **Defense** - fixed at 50 gold coins.

3: **Neutral** - fixed at 150 gold coins.

(step 3 only appears in games with ordinary difficulty, while step 3 does not exist in games with simple difficulty)

**Step4**: after the above game steps are completed, the system will ask the player whether to continue the game. If the player selects "Y", the game will directly enter the current round of settlement. If the player selects "n", the game will be suspended, and the system will cycle whether the player saves the game progress (you can cancel the game directly without saving the game progress); if the player selects "s", it will enter the store.

In the store, players can buy function cards with different attributes with gold coins (which must be used immediately after purchase), and there is only one chance to use the function card in each round. Function cards include: peeping into other people's hands, exchanging a hand with others, discarding one of your own cards, and giving one of your own cards to another player.

(exit the store after the store session, and the system will ask the player whether to continue the game (only y and N options)

**Step 5**: after entering the current round of settlement, the system will judge the total number of AI and players' hand points. Those with more than 21 points will be declared eliminated and will no longer participate in the rest of the game.

When any of the following situations occurs, the game will end directly:

1: The player's hand is equal to or greater than 21 points

2: All AI have been eliminated except players

3: Except for players, the hand points of any AI are equal to 21 points.

(if the game is not over, go to the next round, repeating step 2 - step 5)

If the game is over, enter the final settlement - the system will disclose everyone's hand and hand points, and inform players of their final ranking.

Description of implementations (satisfy requirements):
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

**1: Generation of random game sets or events** --- Since this is a card game, the cards distributed by all players in the game in each round are random. We use srand and rand() to generate cards with different points in several functions like "void SendCard".

**2: Data structures for storing game status** --- in this case we create FileIO.cpp and FileIO.h in order to save game progress; Players can enter "n" during the game to pause the game and save it. When players re run the file, they can select the file reading function in the directory to play the unfinished game. (read file and save file function call is in 1340Gp_main.cpp)

**3: Dynamic memory management** --- We use dynamic array in the game, that is, the card library of players and three AI, to ensure that the number of cards in the hands of four people can be changed at will and do not need to maintain the same number of cards as others.

**4: File input/output** (e.g., for loading/saving game status) --- we use "SaveFile" and "ReadFile" functions to loading and saving game status, this including use "fout" or "fin" command to put necessary data in a new file and output necessary data from the saved file.

**5: Program codes in multiple files** --- we have one main file as 1340Gp_main.cpp (has main()), two function file (FileIO.cpp to loading and saving game status)(Store.cpp for player to buy and use special cards) and two header file of FileIO and Store. Last but not the least--- the "Makefile".

**6: Creative points**: Different from the simple touch mechanism of traditional blackjack, our card game has the following innovations.

First: The maximum round can be set. When the maximum round is less, the player's strategy will change (for example, if the maximum round is three rounds, it is difficult for the player to be eliminated in three rounds, then the player can be deliberately attacked by others, but his hand points are larger, and finally win)

Second: The new three skills that can be used once per round, such as attack, defense and neutrality, make the game more interesting and random. Players can be eliminated through different operations. In the traditional blackjack, there is no interaction between players.

Third: New store system and currency mechanism, which gives players the privilege to use functional cards. This enriches the player's strategy and game experience (for example, when a player buys a handling over card, he can reduce his hand points while increasing the hand points of other players, so as to eliminate other players) 

(peeping card can enable the player to see the hands of other AI, so as to specify the next strategy). 

(the exchange card allows players to exchange cards with large numbers for cards with small numbers when they don't have enough gold coins, so as to reverse their own dangerous situation)

List of non-standard C/C++ libraries:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include < iostream >
    
#include < string > 
  
#include < fstream > --- FileIO
  
#include < iomanip > --- set precision of output
  
#include < cstdlib > --- "new" and dymamic array establishment
  
#include < ctime > --- generate unsigned time for random generation of cards
  
#include < algorithm > --- to use swap() function
  
#include "FileIO.h"
  
#include "Store.h"
  
Compilation and execution instructions:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
 make 1340Gp_main ---- Compilation
  
 ./1340Gp_main   ---- Execution
  
 When the game start: 
  
 Enter "3" to start game, enter "2" to continue saved and unfinished game, enter"1" to change difficulty.
 

