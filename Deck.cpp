#include"Deck.h"
#include<random>
#include<iostream>
#include<time.h>
#include<vector>

using namespace std;

Deck::Deck()
{
	//initialize card_position/ player score / dealer score  at 0
	card_position = 0;

	ps = 0;
	ds = 0;
	pm = 0.0;
	needed_val_to_win = 0;

	player_ace_is_found = false;
	dealer_ace_is_found = false;

	//gets cards with suit and rank
	for (int i = 1; i < 5; i++)
	{
		for (int j = 1; j < 14; j++)
		{
			deck.push_back(Card(j, i));
		}
	}
}

//shffles deck using rand
void Deck::shuffle()
{
	unsigned seed = time(0);
	srand(seed);
	random_shuffle(deck.begin(), deck.end());
}

//displays deck, used to check if deck is shuffling
void Deck::print_deck()
{
	for (int i = 0; i < deck.size(); i++)
	{
		deck[i].print_card();
	}
}

//deals card funcion
void Deck::deal_cards(int scenario)
{

	switch (scenario)
	{
	case 1: // start by giving out all 4 cards, 2 to player and 2 to dealer
		//First Cards player

		if (card_position == 0)
		{
			player_hand.push_back(deck[card_position]);


		}
		else
		{
			player_hand.push_back(deck[card_position++]);
		}

		if (player_hand.back().get_rank() == 1)
		{
			player_ace_is_found = true;

		}

		ps += player_hand.back().get_val();
		//****************************************************
		//Second Cards dealer
		dealer_hand.push_back(deck[card_position++]);

		if (dealer_hand.back().get_rank() == 1)
		{
			dealer_ace_is_found = true;
		}

		ds += dealer_hand.back().get_val();
		//****************************************************
		//Third Card player

		player_hand.push_back(deck[card_position++]);

		if (player_hand.back().get_rank() == 1)
		{
			if (player_ace_is_found == true)
			{
				player_hand.back().set_val(1);
			}
			else if (player_ace_is_found == false)
			{
				player_ace_is_found = true;
			}

		}

		ps += player_hand.back().get_val();
		//****************************************************
		//Fourth Card dealer

		dealer_hand.push_back(deck[card_position++]);

		if (dealer_hand.back().get_rank() == 1)
		{
			if (dealer_ace_is_found == true)
			{
				dealer_hand.back().set_val(1);
			}
			else if (dealer_ace_is_found == false)
			{
				dealer_ace_is_found = true;
			}
		}

		ds += dealer_hand.back().get_val();
		//****************************************************



	//displays the hands
		/*
		cout << "<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
		cout << "Deck has run out of cards" << endl;
		cout << ">>>>>>>>>>>>>>>>>>>>>>>>>" << endl; */
		show_player_hand();
		cout << endl;

		show_dealer_hand(0);
		cout << endl;

		break;

	case 2: // if player chose to hit give player another card

		player_hand.push_back(deck[card_position++]);

		if (player_hand.back().get_rank() == 1)
		{
			if (player_ace_is_found == true || ps > 10)		//ps holds player score		
			{
				player_hand.back().set_val(1);
			}
			else
			{
				player_ace_is_found = true;

			}

		}
		else
		{
			if (ps + player_hand.back().get_val() > 21 && player_ace_is_found == true)
			{
				ps -= 10;
				player_ace_is_found = false;
			}
		}

		ps += player_hand.back().get_val();
		show_player_hand();
		cout << endl;


		show_dealer_hand(0);
		cout << endl;

		break;
	case 3: // if dealer chose to hit give dealer another card
		cout << "***Dealer chooses to Hit***\n\n";
		show_player_hand();
		cout << endl;

		dealer_hand.push_back(deck[card_position++]);

		////////////////////
		if (dealer_hand.back().get_rank() == 1)
		{
			if (dealer_ace_is_found == true || ds > 10)		//ps holds player score		
			{
				dealer_hand.back().set_val(1);
			}
			else
			{
				dealer_ace_is_found = true;

			}

		}
		else
		{
			if (ds + dealer_hand.back().get_val() > 21 && dealer_ace_is_found == true)
			{
				ds -= 10;
				dealer_ace_is_found = false;
			}
		}

		///////////////////////////


		ds += dealer_hand.back().get_val();
		show_dealer_hand(1);
		cout << endl;
		cout << "******************************" << endl;

		break;

	}
}

void Deck::show_player_hand() // displays players hand and value
{
	cout << "Player Hand: \n";
	cout << "---------------" << endl;
	for (int i = 0; i < player_hand.size(); i++)
	{
		player_hand[i].print_card();

	}

	cout << "Player Hand Value: " << ps << endl;
	cout << "Probability of drawing card needed to Win: " << get_win_prob() << "%" << endl;
	//cout << "Card Position: " << card_position << endl;
	//cout << "Deck Size: " << deck.size() << endl;
}

void Deck::show_dealer_hand(int scenario) //displays dealers hand and value
{

	if (scenario == 1) //displays all of dealers cards
	{
		cout << "Dealer Hand: \n";
		cout << "---------------" << endl;

		for (int i = 0; i < dealer_hand.size(); i++)
		{
			dealer_hand[i].print_card();
		}
		cout << "Dealer Hand Value: " << ds << endl;
	}
	else // displays dealers cards with one card hidden as well as its value hidden
	{
		cout << "Dealer Hand: \n";
		cout << "---------------" << endl;

		cout << "Hidden" << endl;
		dealer_hand[1].print_card();

		cout << "Dealer Hand Value: " << ds - dealer_hand[0].get_val() << endl;
	}
}

int Deck::player_score() const // returns player score
{
	return ps;
}

int Deck::dealer_score() const // returns dealers score
{
	return ds;
}

void Deck::clear_hands() // clears hands and sets scores back to 0
{
	player_hand.clear();
	dealer_hand.clear();
	ps = 0;
	ds = 0;
}



int Deck::get_plyr_hnd_size() const // returns players hand size
{
	return player_hand.size();
}

double Deck::get_player_money() const
{
	return pm;
}

void Deck::money_system(double money, int money_scenarios)
{
	switch (money_scenarios)
	{
	case 0: pm -= money; // scenario 0 subtracts money
		break;
	case 1: pm += money; // scenario 1 adds money
		break;
	case 2: pm += money * 2; // doubles money
		break;
	case 3: pm += money * 2.5; // gives player 1.5 times for black jack win
		break;
	case 4: pm += money * 3.5; // gives palyer 2.5 times for black jack tie
		break;
	} //This ones are wrong think i need to fix them, should be 2.5 and 3.5 why though and are the others affected.
}

int Deck::get_dlr_hnd_size() const
{
	return dealer_hand.size();
}

void Deck::clear_money()
{
	pm = 0;
}

int Deck::get_val_of_card(int val_of_card) const // only for player's hand
{
	if (val_of_card == 1)
	{

		return player_hand[0].get_val();
	}
	else if (val_of_card == 2)
	{

		return player_hand[1].get_val();
	}


}

int Deck::get_card_position() const
{
	return card_position;
}

void Deck::incriment_card_position()
{
	card_position++;
}

void Deck::reset_ace_is_found()
{
	player_ace_is_found = false;
	dealer_ace_is_found = false;
}

double Deck::get_win_prob()
{
	/*if (get_card_position() < 48)
	{*/
	//Will return probability of winning with each draw
	int tmp1 = 0; // total number of cards with value needed in whole deck
	int tmp2 = 0; //keeps track of how many cards are left in the deck

	//what card do you need to win
	needed_val_to_win = 21 - player_score();


	//how many cards do you have in your deck of the card that you need
	if (needed_val_to_win == 1)
	{
		for (int i = card_position; i < deck.size(); i++, tmp2++)
		{
			if (deck[i].get_val() == 11)
			{
				tmp1++;
			}
		}
	}
	else if (needed_val_to_win < 12)
	{
		//This goes through the deck starting from where i'm at
		for (int i = card_position; i < deck.size(); i++, tmp2++)
		{

			if (deck[i].get_val() == needed_val_to_win)
			{
				tmp1++;
			}

		}
	}
	else
	{
		win_prob = 0.0;
		return win_prob;
	}
	//tmp1 // total number of cards with value needed in whole deck
	//tmp2 //keeps track of how many cards are left in the deck
	win_prob = ((double)tmp1 / (double)tmp2) * 100.0;

	return win_prob;
}

int Deck::get_val_of_card_dealer(int dlr_val_of_card) const
{
	if (dlr_val_of_card == 1) // might not use because it is hidden at first
	{

		return dealer_hand[2].get_val();
	}
	else if (dlr_val_of_card == 2)
	{

		return dealer_hand[3].get_val();
	}
}

void Deck::split()
{
	split_hand_tmp.push_back(player_hand[1]);
	player_hand.pop_back();
	ps = player_hand[0].get_val();
}

void Deck::split_clear_hand()
{
	ps = 0;
	player_hand.clear();
	player_ace_is_found = false;


	player_hand = split_hand_tmp;
	ps = player_hand[0].get_val();

}

void Deck::final_hand_stored()
{
	final_hand = player_hand;
}

void Deck::print_final_hand(int new_score)
{
	cout << "Player Hand: \n";
	cout << "---------------" << endl;
	for (int i = 0; i < final_hand.size(); i++)
	{
		final_hand[i].print_card();

	}

	cout << "Player Hand Value: " << new_score << endl;
	
}