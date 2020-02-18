/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Ethan Feng
 * USC email: eyfeng@usc.edu
 * Comments (you want us to know):
 *
 *
 ******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib> 

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);
void compare(int playerValue, int dealerValue);
bool playAgain();

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  /******** You complete ****************/
  for(int i=NUM_CARDS-1; i>0; i--){
      int temp, j = rand()%(i+1);
      temp = cards[j];
      cards[j]= cards[i];
      cards[i]= temp;
  }
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
  /******** You complete ****************/
    cout << type[id%13] << "-" << suit[id/13];
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
  /******** You complete ****************/
    return value[id%13];
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
    for(int i=0; i<numCards-1; i++){
        printCard(hand[i]);
        cout << " ";
    }
    printCard(hand[numCards-1]);
    cout << endl;
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/
    int sum=0, count=0;
    for(int i=0; i<numCards; i++){
        sum += cardValue(hand[i]);
        if(cardValue(hand[i])==11){
            count++;
        }
    }
    
    while(count--){
        if(sum >21){
            sum-=10;
        }
    }
    return sum;
}

void result(int playerValue, int dealerValue){
    if(playerValue > 21){
        cout << "Player Busts" << endl;
        cout << "Lose " << playerValue 
                    << " " << dealerValue << endl;
    }else if(dealerValue>21){
        cout << "Dealer Busts" << endl;
        cout << "Win " << playerValue 
                    << " " << dealerValue << endl;
    }else if(playerValue == dealerValue){
        cout << "Tie " << playerValue 
                    << " " << dealerValue << endl;
    }else if(playerValue < dealerValue){
        cout << "Lose " << playerValue 
                    << " " << dealerValue << endl;
    }else{
        cout << "Win " << playerValue 
                    << " " << dealerValue << endl;
    }
}

bool playAgain(){
    char r;
    cout << "Play again? [y/n]" << endl;
    cin >> r;
    if(r !='y'){
        return false;
    }
    return true;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
   char respond;
   int pvalue, dvalue, pdeck=0, ddeck=0, deck=0;
   bool play=true; 
    
    while(play){
        pdeck=0;
        ddeck=0;
        deck=0;
        play = false;
        
        //Initialize
        for(int i=0; i< NUM_CARDS; i++){
            cards[i]=i;
        }
        shuffle(cards);

        //Give out cards
        for(int i=0; i<4; i++){
            if(i%2==0){
                phand[pdeck] = cards[i];
                pdeck++;
            }else{
                dhand[ddeck] = cards[i];
                ddeck++;
            }
            deck++;
        }
    
        //Ask to hit or not
        cout << "Dealer: ? "; 
        printCard(dhand[1]);
        cout << endl;
        cout << "Player:";
        printHand(phand, pdeck);
        cout << "Type 'h' to hit and 's' to stay:" << endl;

        dvalue = getBestScore(dhand, ddeck);
        pvalue = getBestScore(phand, pdeck);

        //if player gets 21
        if(pvalue==21){
            while(dvalue<17){
                dhand[ddeck] = cards[deck];
                deck++;
                ddeck++;
                dvalue = getBestScore(dhand, ddeck);
            }        
            printHand(dhand, ddeck);
            
            result(pvalue, dvalue);
            play=playAgain();
            if(!play){
                return 0;
            }
        }

        //hit or stay 
        if(!play){
            cin >> respond;
            while(respond != 's' && !play){
                if(respond == 'h'){
                    phand[pdeck] = cards[deck];
                    pdeck ++;
                    deck++;
                    pvalue = getBestScore(phand, pdeck);
                    printHand(phand, pdeck);

                    if(pvalue>21){
                        result(pvalue, dvalue);
                        play = playAgain();
                        if(!play){
                            return 0;
                        }
                    }else if(pvalue==21){
                        while(dvalue<17){
                            dhand[ddeck] = cards[deck];
                            deck++;
                            ddeck++;
                            dvalue = getBestScore(dhand, ddeck);
                        }        
                        result(pvalue, dvalue);
                        play = playAgain();
                        if(!play){
                            return 0;
                        }
                    }else{
                        cout << "Type 'h' to hit and 's' to stay:" << endl;
                        cin >> respond;
                    }
                }else{
                    return 0;
                }
            }
        }

        if(!play){
            while(dvalue<17){
                dhand[ddeck] = cards[deck];
                deck++;
                ddeck++;
                dvalue = getBestScore(dhand, ddeck);
            }        
            printHand(dhand, ddeck);

            if(dvalue>21){
                result(pvalue, dvalue);
                play = playAgain();
                if(!play){
                    return 0;
                }
            }
            //Win or Not                     
            result(pvalue, dvalue);
            play = playAgain();
            if(!play){
                return 0;
            }
        }
    }
    return 0;
}
    

