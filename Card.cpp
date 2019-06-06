#include"Card.h"
#include<string>
#include<iostream>


using namespace std;


//Default constructor where I initialize all variables, the private attributes from the Card class;
Card::Card(int r, int s)
{
	rank = r; // holds rank
	suit = s; // holds suit
	switch (rank) // gives rank values if its not the same as rank ex. jack rank = 11 but value is 10.
	{
	case 1:
		val = 11;
		break;
	case 11:
		val = 10;
		break;
	case 12:
		val = 10;
		break;
	case 13:
		val = 10;
		break;
	default:
		val = rank;
	}

}

void Card::print_card() // gives cards, their suits and rank names
{
	string suits[] = { "Hearts", "Diamonds", "Spades", "Clubs" };
	string ranks[] = { "Ace", "Jack", "Queen", "King" };
	string card_name = "";

	if (rank == 1) //ranks their name
	{
		card_name += ranks[0];
	}
	else if (rank > 10 && rank < 14)
	{
		for (int i = 0; i < 3; i++)
		{
			if (rank == (11 + i))
				card_name += ranks[1 + i];
		}
	}
	else
	{

		card_name += to_string(rank);
	}

	//appends " of "
	card_name += " of ";

	for (int i = 0; i < 4; i++) // gives suit names loop
	{
		if (suit == (i + 1))
		{
			card_name += suits[i];
		}
	}

	cout << card_name << endl;
}

int Card::get_suit() const // return suit
{
	return suit;
}

int Card::get_rank() const // return rank
{
	return rank;
}

int Card::get_val() const // return value
{
	return val;
}

void Card::set_val(int v) //set new value
{
	val = v;
}
