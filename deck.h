#include <cstddef>
#include <cstdlib>
#include <ctime>

#ifndef DECK
#define DECK

class Card
{
public:
	enum suit
	{
		sJoker, hearts /*♥*/, diamonds /*♦*/, spades /*♠*/, clubs /*♣*/
	};
	enum value
	{
		vJoker, A = 1, v2, v3, v4, v5, v6, v7, v8, v9, v10, J, Q, K
	};
	Card(suit, value);
private:
	const suit s;
	const value v;
};

class Deck
{
private:
	class CPH // Card placeholder
	{
	public:
		Card *data;
		CPH *next;
		CPH(Card*, CPH*);
		CPH* goDown(int);
		void destroyDeck();
	};
	CPH *top;
	
	// Initial info:
	int nSuites, nDecks, nJokersPerDeck;
public:
	Deck(int);
	Deck(int, int, int);
	~Deck();
	void shuffle();
	void shuffle(int);
	void reset();
	int defSize();
	int size();
	Card** cardAt(int);
	Card* draw();
	void shuffleIn(Card*);
};

#endif // DECK
