#ifndef CARD_H
#define CARD_H



class Card
{
private:
	int suit; // holds suit
	int rank; // holds rank(1-13)
	int val; // holds values (1-11)

public:
	Card(int, int); // card constructor
	void print_card(); // print card function
	int get_suit() const; // get suit function
	int get_rank() const; // get rank function
	int get_val() const; // get value function
	void set_val(int); // sets value
};

#endif