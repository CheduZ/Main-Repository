
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class WordList {
    private List<String> wordList = new ArrayList<>();
    
    public WordList(String filename) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = reader.readLine()) != null) {
                wordList.add(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public List<String> giveWords() {
        return wordList;
    }
    public WordList theWordsOfLength(int length) {
        WordList newList = new WordList("");
        for (String word : wordList) {
            if (word.length() == length) {
                newList.wordList.add(word);
            }
        }
        return newList;
    }
    
    public WordList theWordsWithCharacters(String someString) {
        WordList newList = new WordList("");
        for (String word : wordList) {
            if (word.length() == someString.length()) {
                boolean match = true;
                for (int i = 0; i < someString.length(); i++) {
                    if (someString.charAt(i) != '_' && someString.charAt(i) != word.charAt(i)) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    newList.wordList.add(word);
                }
            }
        }
        return newList;
    }
}
