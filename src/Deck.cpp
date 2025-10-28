#include "Deck.hpp"

#include <time.h>

#include <cstdlib>

using namespace deck_of_cards;

deck_of_cards::Card::Card(Suit suit, Value value)
  : m_suit(suit)
  , m_value(value)
{
}

deck_of_cards::Deck::Deck()
  : m_cards(std::vector<std::shared_ptr<deck_of_cards::Card>>())
{
  srand(time(NULL));  // set random seed
  // build our deck of cards
  for (const auto suit : Suits)  // loop over the four suits
  {
    for (const auto value : Values)  // loop over the thirteen face values
    {
      std::shared_ptr<Card> card = std::make_shared<Card>(suit, value);
      m_cards.push_back(card);
    }
  }

  m_original_cards = m_cards;
}

void deck_of_cards::Deck::shuffle()
{
  // Fisher-Yates shuffle algorithm
  // iterate over the entire deck, swapping each card with a randomly selected card
  // this ensures that every card has an equal chance of being dealt
  for (size_t i = m_cards.size() - 1; i > 0; --i)
  {
    // generate a random index between i and m_cards.size() - 1
    int j = rand() % (i + 1);
    std::iter_swap(m_cards.begin() + i, m_cards.begin() + j);
  }
}

std::shared_ptr<deck_of_cards::Card> deck_of_cards::Deck::deal_card()
{
  if (m_cards.size() > 0)
  {
    const auto card = m_cards.back();
    m_cards.pop_back();

    return card;
  }

  return nullptr;
}
