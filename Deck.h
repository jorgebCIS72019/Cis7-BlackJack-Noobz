#ifndef DECK_H
#define DECK_H

#include"Card.h"
#include<vector>

using namespace std;

class Deck
{
private:
	//attribuites for deck functions
	vector<Card> deck;
	vector<Card> player_hand;
	vector<Card> dealer_hand;
	int card_position; // holds position to be able to deal cards
	int ps; // will hold player score
	int ds; // will hold dealer score
	double pm; //will hold player money value
	bool player_ace_is_found;
	bool dealer_ace_is_found;
	double win_prob; // will hold winning probabity percent
	int needed_val_to_win;
	vector<Card> split_hand_tmp;
	vector<Card> final_hand;
	
public:
	Deck(); // default constructor
	void shuffle(); // shuffles deck
	void print_deck(); // displays deck
	void deal_cards(int); // deals the cards
	void show_player_hand(); // displays player hand
	void show_dealer_hand(int); // displays dealer hand
	int player_score() const; //holds player score
	int dealer_score() const; // holds dealer score
	void clear_hands(); // clears hands after a push(black jack term)
	int get_plyr_hnd_size() const; // gets player hand size
	int get_val_of_card(int) const; // gets value of a card

	double get_player_money() const;
	void money_system(double, int);
	int get_dlr_hnd_size() const;
	void clear_money();
	int get_card_position() const;
	void incriment_card_position();
	void reset_ace_is_found();
	double get_win_prob();
	int get_val_of_card_dealer(int) const;
	void split();
	void split_clear_hand();
	void final_hand_stored();
	void print_final_hand(int);
};



#endif