#include "deck.h"

Card::Card(suit s, value v)
: s(s), v(v)
{}

Deck::CPH::CPH(Card *data, Deck::CPH *next)
: data(data), next(next)
{}

Deck::CPH* Deck::CPH::goDown(int i)
{
	if(i <= 0)
		return this;
	return next->goDown(i - 1);
}

void Deck::CPH::destroyDeck()
{
	if(next != NULL)
		next->destroyDeck();
	delete data;
	delete this;
}

Deck::Deck(int nJokers)
: Deck(4, 1, nJokers)
{}

Deck::Deck(int nSuites, int nDecks, int nJokersPerDeck)
: nSuites(nSuites), nDecks(nDecks), nJokersPerDeck(nJokersPerDeck)
{
	reset();
}

Deck::~Deck()
{
	top->destroyDeck();
}

void Deck::shuffle()
{
	shuffle(500);
}

void Deck::shuffle(int nSwaps)
{
	std::srand(std::time(0));
	for(int i = 0; i < nSwaps; i++)
	{
		Card **a = cardAt(rand() % size());
		Card **b = cardAt(rand() % size());
		Card *tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

void Deck::reset()
{
	top = NULL;
	for(int i = 0; i < nDecks; i++)
	{
		switch(nSuites)
		{
		case 4:
			for(int j = 1; j <= 13; j++)
				top = new CPH(new Card(Card::diamonds, (Card::value) j), top);
		case 3:
			for(int j = 1; j <= 13; j++)
				top = new CPH(new Card(Card::clubs, (Card::value) j), top);
		case 2:
			for(int j = 1; j <= 13; j++)
				top = new CPH(new Card(Card::hearts, (Card::value) j), top);
		default:
			for(int j = 1; j <= 13; j++)
				top = new CPH(new Card(Card::spades, (Card::value) j), top);
		}
		for(int j = 0; j < nJokersPerDeck; j++)
			top = new CPH(new Card(Card::sJoker, Card::vJoker), top);
	}
	shuffle();
}

int Deck::defSize()
{
	return nDecks * (nSuites * 13 + nJokersPerDeck);
}

int Deck::size()
{
	int n = 1;
	for(CPH* c = top; c->next != NULL; c = c->next)
		n++;
	return n;
}

Card** Deck::cardAt(int i)
{
	return &top->goDown(i)->data;
}

Card* Deck::draw()
{
	CPH *oldTop = top;
	top = oldTop->next;
	Card *c = oldTop->data;
	delete oldTop;
	return c;
}

void Deck::shuffleIn(Card* c)
{
	std::srand(std::time(0));
	CPH* prev = top->goDown(std::rand() % size());
	CPH* newCPH = new CPH(c, prev->next);
	prev->next = newCPH;
}
