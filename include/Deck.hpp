#pragma once

#include <memory>
#include <vector>

namespace deck_of_cards
{
/**
 * @brief Enumeration representing the four suits in a standard deck of playing cards.
 */
enum class Suit
{
  Club = 0,
  Diamond,
  Heart,
  Spade
};

/**
 * @brief A constexpr initializer list containing all the suits in a standard deck of playing cards.
 *
 * This list can be used to iterate over all available suits.
 */
constexpr std::initializer_list<Suit> Suits = { Suit::Club, Suit::Diamond, Suit::Heart, Suit::Spade };

/**
 * @brief Enumeration representing the values of cards in a standard deck of playing cards.
 */
enum class Value
{
  Ace = 1,
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King
};

/**
 * @brief A constexpr initializer list containing all the values in a standard deck of playing cards.
 *
 * This list can be used to iterate over all available card values.
 */
constexpr std::initializer_list<Value> Values = { Value::Ace,  Value::Two,   Value::Three, Value::Four, Value::Five,
                                                  Value::Six,  Value::Seven, Value::Eight, Value::Nine, Value::Ten,
                                                  Value::Jack, Value::Queen, Value::King };

class Card
{
public:
  /**
   * @brief Deleted default constructor.
   *
   * This constructor is deleted to prevent the creation of a Card
   * object without specifying its suit and value.
   */
  Card() = delete;

  /**
   * @brief Constructs a Card with the specified suit and value.
   *
   * @param suit The suit of the card (e.g., hearts, diamonds, clubs, spades).
   * @param value The value of the card (e.g., Ace, 2, 3, ..., King).
   */
  Card(Suit suit, Value value);

  /**
   * @brief Deleted copy constructor.
   *
   * This constructor is deleted to prevent copying of Card objects.
   */
  Card(const Card&) = delete;

  /**
   * @brief Deleted move constructor.
   *
   * This constructor is deleted to prevent moving of Card objects.
   */
  Card(Card&&) = delete;

  /**
   * @brief Default destructor.
   *
   * Cleans up the Card object. This destructor is defaulted and does not
   * perform any special actions.
   */
  ~Card() = default;

  /**
   * @brief Deleted copy assignment operator.
   *
   * This operator is deleted to prevent copying of Card objects.
   *
   * @return Reference to this object.
   */
  Card& operator=(const Card&) = delete;

  /**
   * @brief Deleted move assignment operator.
   *
   * This operator is deleted to prevent moving of Card objects.
   *
   * @return Reference to this object.
   */
  Card& operator=(Card&&) = delete;

  /**
   * @brief Equality operator for Card
   *
   * Two Card objects are considered equal if they have the same suit and value.
   *
   * @param other The other Card object to compare with.
   * @return True if the two Card objects are equal, false otherwise.
   */
  bool operator==(const Card& other) const
  {
    return m_suit == other.m_suit && m_value == other.m_value;
  };

  /**
   * @brief Gets the suit of the card.
   *
   * @return The suit of the card as a Suit type.
   *
   * This function is marked as noexcept, indicating that it does not throw exceptions.
   */
  Suit suit() const noexcept
  {
    return m_suit;
  };

  /**
   * @brief Gets the value of the card.
   *
   * @return The value of the card as a Value type.
   *
   * This function is marked as noexcept, indicating that it does not throw exceptions.
   */
  Value value() const noexcept
  {
    return m_value;
  };

private:
  Suit m_suit;    ///< The suit of the card.
  Value m_value;  ///< The value of the card.
};

class Deck
{
public:
  /**
   * @brief Constructs a Deck object.
   *
   * This constructor initializes a new deck of cards, typically containing
   * a standard set of playing cards.
   */
  Deck();

  /**
   * @brief Deleted copy constructor.
   *
   * This constructor is deleted to prevent copying of Deck objects.
   */
  Deck(const Deck&) = delete;

  /**
   * @brief Deleted move constructor.
   *
   * This constructor is deleted to prevent moving of Deck objects.
   */
  Deck(Deck&&) = delete;

  /**
   * @brief Default destructor.
   *
   * Cleans up the Deck object. This destructor is defaulted and does not
   * perform any special actions.
   */
  ~Deck() = default;

  /**
   * @brief Deleted copy assignment operator.
   *
   * This operator is deleted to prevent copying of Deck objects.
   *
   * @return Reference to this object.
   */
  Deck& operator=(const Deck&) = delete;

  /**
   * @brief Deleted move assignment operator.
   *
   * This operator is deleted to prevent moving of Deck objects.
   *
   * @return Reference to this object.
   */
  Deck& operator=(Deck&&) = delete;

  /**
   * @brief Shuffles the deck of cards.
   *
   * This function randomizes the order of the cards in the deck using the
   * Fisher-Yates algorithm.
   */
  void shuffle();

  /**
   * @brief Deals a card from the deck.
   *
   * @return A shared pointer to a Card object, representing the dealt card.
   *
   * If there are no cards left in the deck, this function may return a null
   * pointer or throw an exception, depending on the implementation.
   */
  std::shared_ptr<Card> deal_card();

  /**
   * @brief Gets the number of cards remaining in the deck.
   *
   * @return The number of cards remaining in the deck.
   */
  std::size_t num_cards() const noexcept
  {
    return m_cards.size();
  };

  void reset()
  {
    m_cards = m_original_cards;
  }

private:
  std::vector<std::shared_ptr<Card>> m_cards;           ///< A vector containing the cards in the deck.
  std::vector<std::shared_ptr<Card>> m_original_cards;  ///< A vector containing the original cards in the deck.
};

// Hash function for Card
class CardHash
{
public:
  std::size_t operator()(const std::shared_ptr<Card>& card) const
  {
    return std::hash<int>()(static_cast<int>(card->suit())) ^ std::hash<int>()(static_cast<int>(card->value()));
  };
};

// Equality operator for Card
class CardEqual
{
public:
  bool operator()(const std::shared_ptr<Card>& lhs, const std::shared_ptr<Card>& rhs) const
  {
    return *lhs == *rhs;
  };
};

}  // namespace deck_of_cards
