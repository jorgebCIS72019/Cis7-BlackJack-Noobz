/*

Team: BlackJack Noobz
Members: Jorge Bautista & Luis Batz

CIS 7
Created on: 5/15/2019
*/

#include"Deck.h"
#include<iostream>
#include<string>


using namespace std;

int main()
{
	int choice = 0;
	int option = 0;
	bool dealer_turn = false;
	bool push = false;
	Deck deck;
	bool blackjack = false;
	int money_choice = 0;
	double money_pot = 0.0;
	bool split_is_found = false;
	bool not_enough_cards = false;
	bool dbl_is_possible = false;
	int split_score_tmp = 0;


	//deck.print_deck(); && deck.get_card_position() < 50 6
	while (choice != 2 && not_enough_cards == false) // while loop for whole game
	{
		if (push == false)
		{


			//Black Jack Menu Options
			deck.shuffle();
			cout << "<><><><><><><><><><><><><><<><>\n";
			cout << "Welcome to BlackJack!!\n";
			cout << "1) Play BlackJack\n";
			cout << "2) Exit\n";
			cout << "Choice: ";
			cin >> choice;
			cout << "******************************" << endl;

		}
		else
		{

			choice = 1;
		}


		switch (choice)
		{
		case 1: // Play game
			//Function to deal cards to player & dealer
			deck.clear_hands();
			deck.reset_ace_is_found();

			if (push == false)
			{
				if (deck.get_player_money() <= 0.0)
				{

					deck.clear_money();
					cout << "You are starting with $1000" << endl;
					deck.money_system(1000.0, 1);
				}
				else if (deck.get_player_money() > 0.0)
				{
					cout << "You have $" << deck.get_player_money() << endl;
				}
				//cout << "You are starting with $1000" << endl;
				//deck.money_system(1000.0, 1);

			}
			else
			{
				cout << "You have $" << deck.get_player_money() << endl;
				push = false;
			}

			//add function to skip this if previous result was a push and return current money
			//also add a clear money value for new game
			do
			{
				cout << "Choose how much you want to bet" << endl;
				cout << "1. $1 \t\t2. $5" << endl;
				cout << "3. $25 \t\t4. $50" << endl;
				cout << "5. $100 \t6. $500" << endl;
				cout << "7. All In" << endl;
				cout << "Enter money choice: ";
				cin >> money_choice;
				cout << endl;
				if (money_choice == 1)
				{
					money_pot = 1.0;
					deck.money_system(money_pot, 0);
					cout << "You have bet $1" << endl;
					cout << "----------------------------" << endl;
				}
				else if (money_choice == 2)
				{
					money_pot = 5.0;
					deck.money_system(money_pot, 0);
					cout << "You have bet $5" << endl;
					cout << "----------------------------" << endl;
				}
				else if (money_choice == 3)
				{
					money_pot = 25.0;
					deck.money_system(money_pot, 0);
					cout << "You have bet $25" << endl;
					cout << "----------------------------" << endl;
				}
				else if (money_choice == 4)
				{
					money_pot = 50.0;
					deck.money_system(money_pot, 0);
					cout << "You have bet $50" << endl;
					cout << "----------------------------" << endl;
				}
				else if (money_choice == 5)
				{
					money_pot = 100.0;
					deck.money_system(money_pot, 0);
					cout << "You have bet $100" << endl;
					cout << "----------------------------" << endl;
				}
				else if (money_choice == 6)
				{
					money_pot = 500.0;
					deck.money_system(money_pot, 0);
					cout << "You have bet $500" << endl;
					cout << "----------------------------" << endl;
				}
				else if (money_choice == 7)
				{
					money_pot = deck.get_player_money();
					deck.money_system(money_pot, 0);
					cout << "You have bet $" << money_pot << endl;
					cout << "----------------------------" << endl;
				}
				else
				{
					cout << "Please chooses one of the displayed options." << endl << endl;
				}
			} while (money_choice < 1 || money_choice > 7);

			//checks if not enough cards to start a new game
			if (deck.get_card_position() > 47)
			{
				not_enough_cards = true;
				break;

			}
			else
			{


				//check if a card has already been played, then incriment
				if (deck.get_card_position() > 0)
				{
					deck.incriment_card_position();
				}


				//Deals first four cards of the game <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Important
				deck.deal_cards(1);


				//if a blackjack is found in first turn of the game
				if (deck.player_score() == 21 && deck.get_plyr_hnd_size() == 2)
				{
					blackjack = true;
				}

				//checks if not enough cards to start a new game
				if (deck.get_card_position() > 51)
				{
					not_enough_cards = true;
					break;

				}

				//check if can double and enough money for double

				if (deck.get_player_money() > money_pot && deck.get_plyr_hnd_size() == 2) // fix 500 left, bet 500, can still double
				{
					dbl_is_possible = true;
				}

			}
			//While loop for - hitting or standing && dealer_turn == false
			while (deck.player_score() < 21 && not_enough_cards == false)
			{

				cout << "Choose to: " << endl;

				cout << "1) Hit\n";
				cout << "2) Stand\n";
				if ((deck.get_val_of_card(1) == deck.get_val_of_card(2)) && deck.get_dlr_hnd_size() == 2)
				{
					if (deck.get_player_money() > money_pot)
					{
						cout << "3) Split\n";
						//split_is_found = false;
					}
				}
				if (dbl_is_possible == true && deck.get_plyr_hnd_size() == 2)
				{
					cout << "4) Double\n";
				}

				cout << "Choice: ";
				cin >> option;
				cout << "******************************" << endl;
				//switch case for choosing to hit or stand
				switch (option)
				{
				case 1:
					//function to hit
					deck.deal_cards(2);

					break;
				case 2: // function to stand
					dealer_turn = true;


					break;
				case 3: //Split function
					cout << "chose to split" << endl;
					//put which hands you are using now, like "Split hand 1 and split hand 2", 
					//1. split, on first split card, autohit, then choose to hit or stand again, 
					//if stand, then go second split card, autohit, then choose to hit or stand again, if stand, then dealerturn = true.
					deck.money_system(money_pot, 0);
					deck.split();
					cout << "Split Hand - 1" << endl;
					cout << "Auto Dealing Card..." << endl;
					deck.deal_cards(2); //forced hit
					split_is_found = true;
					break;
				case 4: //Double Function
					cout << "Chose to double" << endl;
					deck.money_system(money_pot, 0);
					deck.deal_cards(2);
					dealer_turn = true;
					cout << "Money Pot: " << money_pot << endl;
					break;
				default: // if user doesn't pick 1 or 2, asks user to pick again
					cout << "Please Enter a Correct Choice" << endl;
					break;
				}
				if (dealer_turn == true)
				{
					break;
				}

			}
			if (dealer_turn == true && split_is_found == true)
			{
				dealer_turn = false;
			}

			if (dbl_is_possible == true)
			{
				dbl_is_possible = false;
			}

			//Copy of while - this is my split
			
			if (split_is_found == true) //will not split again 
			{
				cout << "Split Hand - 2" << endl;
				cout << "Auto Dealing Card..." << endl;
				split_score_tmp = deck.player_score(); // re stores score into new tmp split score
				deck.final_hand_stored();
				deck.split_clear_hand();
				deck.deal_cards(2);
				//&& dealer_turn == false
				while (deck.player_score() < 21 && not_enough_cards == false)
				{

					cout << "Choose to: " << endl;

					cout << "1) Hit\n";
					cout << "2) Stand\n";

					if (dbl_is_possible == true && deck.get_plyr_hnd_size() == 2)
					{
						cout << "4) Double\n";
					}

					cout << "Choice: ";
					cin >> option;
					cout << "******************************" << endl;
					//switch case for choosing to hit or stand
					switch (option)
					{
					case 1:
						//function to hit
						deck.deal_cards(2);

						break;
					case 2: // function to stand
						dealer_turn = true;

						break;
					case 4: //Double Function
						cout << "Chose to double" << endl;
						deck.money_system(money_pot, 0);
						deck.deal_cards(2);
						dealer_turn = true;
						cout << "Money Pot: " << money_pot << endl;
						break;
					default: // if user doesn't pick 1 or 2, asks user to pick again
						cout << "Please Enter a Correct Choice" << endl;
						break;
					}
					if (dealer_turn == true)
					{
						break;
					}

				}
			}

			//checks if it's dealers turn or if its not a black jack and player score is 21.
			if (dealer_turn == true || (blackjack == false && deck.player_score() == 21))
			{
				//displays that player has chosen to stand and that it is dealers turn.
				cout << endl;
				cout << "---------------" << endl;
				cout << "|Player Stands|" << endl;
				cout << "|-------------|" << endl;
				cout << "|Dealers Turn |" << endl;
				cout << "---------------" << endl << endl;

				//Displays dealers hand to show hidden card before it gets new card if it chooses.
				cout << "*****Dealer Hand Reveal*****" << endl;
				deck.show_dealer_hand(1);
				cout << endl;
				while (deck.dealer_score() < 17) //dealers turn
				{
					if (deck.get_card_position() < 52)
					{
						deck.deal_cards(3);
					}
					else
					{
						not_enough_cards = true;

						break;

					}
				}
				//sets dealers turn back to false(its not his turn)
				dealer_turn = false;
			}

			//runs only if split is found
			if (split_is_found == true)
			{

				//	&& deck.get_plyr_hnd_size() == 2 && split_score_tmp == 21 && split_score_tmp < 21 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>D=Fix probability
						//all the various scenarios for if you win or lose
				if (blackjack == true) // A
				{

					cout << "*****Final Hands*****" << endl;
					
					deck.print_final_hand(split_score_tmp);
					cout << endl;
					deck.show_dealer_hand(1);
					cout << endl;
					cout << "You win!!!" << endl;
					deck.money_system(money_pot, 3);
					//cout << "A\n"; // Won via black jack
					cout << "Won via BlackJack!!!!!!" << endl;
					cout << "Your money: $" << deck.get_player_money() << endl;
					blackjack = false;
				}
				else if (split_score_tmp > deck.dealer_score() && split_score_tmp < 21) //B
				{
					cout << "*****Final Hands*****" << endl;
					deck.print_final_hand(split_score_tmp);
					cout << endl;
					deck.show_dealer_hand(1);
					cout << endl;
					cout << "You Win!!!" << endl;
					deck.money_system(money_pot, 2);
					//cout << "B\n";
					cout << "Your money: $" << deck.get_player_money() << endl << endl;
				}
				else if (deck.dealer_score() > split_score_tmp && split_score_tmp < 21 && deck.dealer_score() < 21) //C
				{
					cout << "*****Final Hands*****" << endl;
					deck.print_final_hand(split_score_tmp);
					cout << endl;
					deck.show_dealer_hand(1);
					cout << endl;
					//cout << "C\n";
					cout << "You Lose, Better luck Next Time" << endl << endl;
				}
				else if (deck.dealer_score() > 21 && split_score_tmp < 21) //CH
				{
					cout << "*****Final Hands*****" << endl;
					deck.print_final_hand(split_score_tmp);
					cout << endl;
					deck.show_dealer_hand(1);
					cout << endl;
					cout << "You win!!!" << endl << endl;
					deck.money_system(money_pot, 2);
					//cout << "CH\n";
					cout << "Your money: $" << deck.get_player_money() << endl << endl;
				}
				else if (split_score_tmp > 21) //D
				{
					cout << "*****Final Hands*****" << endl;
					deck.print_final_hand(split_score_tmp);
					cout << endl;
					deck.show_dealer_hand(1);
					cout << endl;
					//cout << "D\n";
					cout << "BUST!!! You Lose, Better Luck Next Time" << endl << endl;
				}
				else if (split_score_tmp == 21 && deck.dealer_score() == 21 && deck.get_plyr_hnd_size() == 2 && deck.get_dlr_hnd_size() == 2) //Blackjack tie scenario // E
				{
					cout << "*****Final Hands*****" << endl;
					deck.print_final_hand(split_score_tmp);
					cout << endl;
					deck.show_dealer_hand(1);
					cout << endl;
					cout << "Tie by BlackJack" << endl;
					cout << "Push" << endl;
					push = true;

					cout << "Hands Cleared" << endl;
					cout << "New Hands" << endl << endl;
					//cout << "E\n";
					cout << "******************************" << endl;
					deck.money_system(money_pot, 4);

				}
				else if (split_score_tmp == deck.dealer_score()) // F
				{
					cout << "Push" << endl;
					push = true;
					cout << "Hands Cleared" << endl;
					cout << "New Hands" << endl << endl;
					//cout << "F\n";
					cout << "******************************" << endl;
					deck.money_system(money_pot, 1);


				}
				else if (split_score_tmp == 21 && deck.dealer_score() != 21) //G
				{
					cout << "*****Final Hands*****" << endl;
					deck.print_final_hand(split_score_tmp);
					cout << endl;
					deck.show_dealer_hand(1);
					cout << "You win!!!" << endl << endl;
					deck.money_system(money_pot, 2);
					//cout << "G\n";
					cout << "Your money: $" << deck.get_player_money() << endl << endl;

				}
				else if (deck.dealer_score() == 21 && split_score_tmp != 21) //H
				{
					cout << "*****Final Hands*****" << endl;
					deck.print_final_hand(split_score_tmp);
					deck.show_dealer_hand(1);
					cout << endl;
					//cout << "H\n";
					cout << "You Lose, Better Luck Next Time" << endl << endl;
				}
			}

			//always runs&& deck.get_plyr_hnd_size() == 2 && deck.player_score() == 21 && deck.player_score() < 21
			if (blackjack == true) // A
			{

				cout << "*****Final Hands*****" << endl;
				deck.show_player_hand();
				cout << endl;
				deck.show_dealer_hand(1);
				cout << endl;
				cout << "You win!!!" << endl;
				deck.money_system(money_pot, 3);
			//	cout << "A\n"; // Won via black jack
				cout << "Won via BlackJack!!!!!!" << endl;
				cout << "Your money: $" << deck.get_player_money() << endl;
				blackjack = false;
			}
			else if (deck.player_score() > deck.dealer_score() && deck.player_score() < 21) //B
			{
				cout << "*****Final Hands*****" << endl;
				deck.show_player_hand();
				cout << endl;
				deck.show_dealer_hand(1);
				cout << endl;
				cout << "You Win!!!" << endl;
				deck.money_system(money_pot, 2);
			//	cout << "B\n";
				cout << "Your money: $" << deck.get_player_money() << endl << endl;
			}
			else if (deck.dealer_score() > deck.player_score() && deck.player_score() < 21 && deck.dealer_score() < 21) //C
			{
				cout << "*****Final Hands*****" << endl;
				deck.show_player_hand();
				cout << endl;
				deck.show_dealer_hand(1);
				cout << endl;
			//	cout << "C\n";
				cout << "You Lose, Better luck Next Time" << endl << endl;
			}
			else if (deck.dealer_score() > 21 && deck.player_score() < 21) //CH
			{
				cout << "*****Final Hands*****" << endl;
				deck.show_player_hand();
				cout << endl;
				deck.show_dealer_hand(1);
				cout << endl;
				cout << "You win!!!" << endl << endl;
				deck.money_system(money_pot, 2);
				//cout << "CH\n";
				cout << "Your money: $" << deck.get_player_money() << endl << endl;
			}
			else if (deck.player_score() > 21) //D
			{
				cout << "*****Final Hands*****" << endl;
				deck.show_player_hand();
				cout << endl;
				deck.show_dealer_hand(1);
				cout << endl;
				//cout << "D\n";
				cout << "BUST!!! You Lose, Better Luck Next Time" << endl << endl;
			}
			else if (deck.player_score() == 21 && deck.dealer_score() == 21 && deck.get_plyr_hnd_size() == 2 && deck.get_dlr_hnd_size() == 2) //Blackjack tie scenario // E
			{
				cout << "*****Final Hands*****" << endl;
				deck.show_player_hand();
				cout << endl;
				deck.show_dealer_hand(1);
				cout << endl;
				cout << "Tie by BlackJack" << endl;
				cout << "Push" << endl;
				push = true;

				cout << "Hands Cleared" << endl;
				cout << "New Hands" << endl << endl;
				//cout << "E\n";
				cout << "******************************" << endl;
				deck.money_system(money_pot, 4);

			}
			else if (deck.player_score() == deck.dealer_score()) // F
			{
				cout << "Push" << endl;
				push = true;
				cout << "Hands Cleared" << endl;
				cout << "New Hands" << endl << endl;
				//cout << "F\n";
				cout << "******************************" << endl;
				deck.money_system(money_pot, 1);


			}
			else if (deck.player_score() == 21 && deck.dealer_score() != 21) //G
			{
				cout << "*****Final Hands*****" << endl;
				deck.show_player_hand();
				cout << endl;
				deck.show_dealer_hand(1);
				cout << "You win!!!" << endl << endl;
				deck.money_system(money_pot, 2);
				//cout << "G\n";
				cout << "Your money: $" << deck.get_player_money() << endl << endl;

			}
			else if (deck.dealer_score() == 21 && deck.player_score() != 21) //H
			{
				cout << "*****Final Hands*****" << endl;
				deck.show_player_hand();
				deck.show_dealer_hand(1);
				cout << endl;
				//cout << "H\n";
				cout << "You Lose, Better Luck Next Time" << endl << endl;
			}

			if (split_is_found == true)
			{
				split_is_found = false;
			}
			break;
		case 2: // Exit
			cout << "You finished with $" << deck.get_player_money() << endl;
			cout << "Thanks for playing, see you again next time" << endl << endl;;
			break;
		default: // if user didn't choose to play or exit
			cout << "Please Enter a Correct Choice." << endl;
			break;
		}
	}
	if (not_enough_cards == true)
	{
		cout << "Deck has run out cards!!" << endl;
		cout << "You finished with $" << deck.get_player_money() << endl;
		cout << "Thanks for playing, See you again next time." << endl << endl;
	}

	//just for visual studio to keep console from closing
	system("pause");
	return 0;
}

