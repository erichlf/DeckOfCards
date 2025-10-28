#include <gtest/gtest.h>

#include <Deck.hpp>
#include <boost/math/distributions/chi_squared.hpp>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <vector>

class ChiSquaredTest
{
public:
  // Constructor to initialize the expected frequency
  ChiSquaredTest(int num_categories, double expected_frequency)
    : m_dofs(num_categories - 1)  // Number of degrees of freedom for the chi-squared test
    , m_observed(num_categories, 0)
    , m_expected(expected_frequency)
    , m_chi_squared_dist(m_dofs)
    , m_chi_squared(0.0)
    , m_threshold(0.0)
  {
  }

  // Add observed frequency for a specific category
  void add_observation(int category)
  {
    if (category < 0 || category >= m_observed.size())
    {
      throw std::out_of_range("Category index out of range");
    }
    m_observed[category]++;
  }

  // Check if the chi-squared statistic is below the threshold
  bool passes_test(double alpha)
  {
    // calculates m_chi_squared statistic
    calculate();

    // Calculate the critical value
    m_threshold = boost::math::quantile(m_chi_squared_dist, 1 - alpha);

    return m_chi_squared < m_threshold;
  }

  double chi_squared() const
  {
    return m_chi_squared;
  }

  double threshold() const
  {
    return m_threshold;
  }

private:
  // Calculate the chi-squared statistic
  void calculate()
  {
    // reset the chi-squared statistic to zero and calculate it again from the observed frequencies
    m_chi_squared = 0.0;
    for (const auto& count : m_observed)
    {
      if (m_expected > 0)
      {  // Avoid division by zero
        m_chi_squared += std::pow(count - m_expected, 2) / m_expected;
      }
    }
  }

  int m_dofs;                   // Degrees of freedom
  std::vector<int> m_observed;  // Observed frequencies
  double m_expected;            // Expected frequency for each category
  boost::math::chi_squared_distribution<> m_chi_squared_dist;
  double m_chi_squared;
  double m_threshold;
};

// Function to get the unique category for a card based         double threshold on its suit, value, and position
int get_category(deck_of_cards::Suit suit, deck_of_cards::Value value, int position)
{
  // Calculate the suit index and value index
  int suit_index = static_cast<int>(suit);
  int value_index = static_cast<int>(value);
  int num_values = deck_of_cards::Values.size();
  int num_suits = deck_of_cards::Suits.size();
  int num_cards = num_suits * num_values;  // Assuming num_cards is 52

  // Calculate the card index
  int card_index = (suit_index * num_values) + (value_index - 1);  // 0 to 51

  // Combine with position to create a unique category
  return (card_index * num_cards) + position;  // Assuming num_cards is 52
}

TEST(DeckTest, CardCreateTest)
{
  using namespace deck_of_cards;
  Card card(Suit::Club, Value::Ace);

  EXPECT_EQ(card.value(), Value::Ace);
  EXPECT_EQ(card.suit(), Suit::Club);
}

TEST(DeckTest, DeckDealTest)
{
  using namespace deck_of_cards;
  Deck deck;

  EXPECT_NE(deck.deal_card(), nullptr);
}

TEST(DeckTest, DeckOverDealTest)
{
  using namespace deck_of_cards;
  Deck deck;

  for (size_t i = 0; i < 52; ++i)
  {
    deck.deal_card();
  }

  EXPECT_EQ(deck.deal_card(), nullptr);
}

TEST(DeckTest, DeckResetTest)
{
  using namespace deck_of_cards;
  Deck deck;

  for (size_t i = 0; i < 52; ++i)
  {
    deck.deal_card();
  }

  EXPECT_EQ(deck.deal_card(), nullptr);
  deck.reset();
  EXPECT_NE(deck.deal_card(), nullptr);
}

TEST(DeckTest, ShuffleStatisticalTest)
{
  using namespace deck_of_cards;

  Deck deck;

  const int num_cards = deck.num_cards();  // Number of cards in the deck
  const int num_shuffles = 1000;           // Number of shuffles to perform

  // we have num_cards spots to put each card so the degrees of freedom is num_cards * num_cards
  const int dofs = num_cards * num_cards;
  const float alpha = 0.05;  // Significance level

  // Create an instance of ChiSquaredTest
  ChiSquaredTest chi_squared(dofs, static_cast<double>(num_shuffles) / num_cards);

  for (int i = 0; i < num_shuffles; ++i)
  {
    deck.reset();
    deck.shuffle();

    // Store the new order of cards after shuffling
    std::vector<std::shared_ptr<Card>> shuffled_order;
    for (int j = 0; j < num_cards; ++j)
    {
      shuffled_order.push_back(deck.deal_card());
    }

    // Count occurrences of each card in each position
    for (int j = 0; j < num_cards; ++j)
    {
      auto card = shuffled_order[j];
      int index = get_category(card->suit(), card->value(), j);
      chi_squared.add_observation(index);
    }
  }

  // Check if the chi-squared test passes
  ASSERT_TRUE(chi_squared.passes_test(alpha))
      << "chi-squared: " << chi_squared.chi_squared() << " >= threshold: " << chi_squared.threshold();
}
