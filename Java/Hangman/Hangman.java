
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.HashSet;
import java.util.Set;

public class Hangman{
    public String word;
    public int guessesLeft;
    public Set<Character> guesses;
    public WordList wordList;

    public Hangman(WordList wordlist, int guesses){
        this.wordList = wordlist;
        this.word = word();
        this.guesses = new HashSet<>();
        this.guessesLeft = guesses;
    }

    public boolean guess(Character c) {
        guesses.add(Character.toLowerCase(c));
        if (word.toLowerCase().indexOf(Character.toLowerCase(c)) != -1) {
            return true;
        } else {
            guessesLeft--;
            return false;
        }
    }

    public List<Character> guesses() {
        return new ArrayList<>(guesses);
    }

    public int guessesLeft() {
        return guessesLeft;
    }

    public String word(){
        List<String> words = wordList.giveWords();
        Random rand = new Random();
        return words.get(rand.nextInt(words.size()));
    }

    public boolean theEnd() {
        for (int i = 0; i < word.length(); i++) {
            if (!guesses.contains(Character.toLowerCase(word.charAt(i)))) {
                return false;
            }
        }
        return true;
    }

    public String getHidden() {
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            if (guesses.contains(c)) {
                builder.append(c).append(" ");
            } else {
                builder.append("* ");
            }
        }
        return builder.toString().trim();
    }

    public WordList theWordsOfLength(int length) {
        return wordList.theWordsOfLength(length);
    }
    
    public WordList theWordsWithCharacters(String someString) {
        return wordList.theWordsWithCharacters(someString);
    }
}