
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner lukija = new Scanner(System.in);
    
        WordList words = new WordList("words.txt");
        Hangman hangman = new Hangman(words, 6);
    
        System.out.println("The hidden word...");
        System.out.println(hangman.getHidden());
        System.out.println("Guesses left: " + hangman.guessesLeft);
        System.out.println("Guessed letters: " + hangman.guesses);
        
        while (hangman.guessesLeft > 0 && !hangman.theEnd()) {
            System.out.print("Guess a letter: ");
            char guess = lukija.nextLine().charAt(0);
            
            if (hangman.guess(guess)) {
                System.out.println("The hidden word...");
                System.out.println(hangman.getHidden());
                System.out.println("Guesses left: " + hangman.guessesLeft);
                System.out.println("Guessed letters: " + hangman.guesses);
            } else {
                System.out.println("Incorrect guess!");
                System.out.println("The hidden word...");
                System.out.println(hangman.getHidden());
                System.out.println("Guesses left: " + hangman.guessesLeft);
                System.out.println("Guessed letters: " + hangman.guesses);
            }
        }   
        
        lukija.close();

        if (hangman.theEnd()) {
            System.out.println("Congratulations! You won!!!");
            System.out.println("The hidden word was: \"" + hangman.word + "\"");
        } else {
            System.out.println("You lost! The word was: \"" + hangman.word + "\"");
        }
    }
}
