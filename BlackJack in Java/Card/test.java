package Card;
public class Card {
    private String suit;
    private String rank;

    public Card(String suit, String rank) {
        this.suit = suit;
        this.rank = rank;
    }

    @Override
    public String toString() {
        return rank + " of " + suit;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        Card card = (Card) obj;
        return suit.equals(card.suit) && rank.equals(card.rank);
    }
}
public class test {
    public static void main(String[] args) {
        Card card1 = new Card("Hearts", "Ace");
        Card card2 = new Card("Spades", "King");
        Card card3 = new Card("Hearts", "Ace");

        System.out.println(card1); // Output: Ace of Hearts
        System.out.println(card2); // Output: King of Spades
        System.out.println(card3); // Output: Ace of Hearts

        System.out.println(card1.equals(card2)); // Output: false
        System.out.println(card1.equals(card3)); // Output: true
    }
}