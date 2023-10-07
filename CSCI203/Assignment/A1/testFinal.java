import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class testFinal {
    public static int sum;
    public static void main(String[] args) {
        WordCount wordCount = new WordCount();
        Scanner input = new Scanner(System.in);
        System.out.print("Enter the name of the text file here: ");
        String fileName = input.nextLine();

        try {
            FileReader fileReader = new FileReader(fileName);

            int character;
            char[] word = new char[100];
            char c;
            int wordLength = 0;
            boolean insideWord = false;

            while ((character = fileReader.read()) != -1) {

                if (character >= 65 && character <= 90) {
                    character += 32;
                }
                c = (char) character;

                if (Character.isLetterOrDigit(c)) {
                    insideWord = true;
                    word[wordLength] = c;
                    wordLength++;
                } else if (insideWord) {
                    wordCount.addWord(word, wordLength);
                    wordLength = 0;
                    insideWord = false;
                }
            }

            // Check if there was a word at the end
            if (insideWord) {
                wordCount.addWord(word, wordLength);
            }

            fileReader.close();
            wordCount.printWords(); // Print the words and their counts

        } catch (IOException e) {
            e.printStackTrace();
        }

        input.close();
    }
}

class WordCount {
    private final int maxWords = 50000;
    private char[][] words = new char[maxWords][];
    private int[] counts = new int[maxWords];
    private int wordCount = 0;
    private int totalWords = -1; 

    public void addWord(char[] word, int wordLength) {
        totalWords++;  // Increment total words whenever a word is added
        for (int i = 0; i < wordCount; i++) {
            if (isEqual(words[i], word, wordLength)) {
                counts[i]++;
                return;
            }
        }

        words[wordCount] = new char[wordLength];
        System.arraycopy(word, 0, words[wordCount], 0, wordLength);
        counts[wordCount] = 1;
        wordCount++;
    }

    private boolean isEqual(char[] word1, char[] word2, int length) {
        if (word1.length < length) {
            return false;
        }

        for (int i = 0; i < length; i++) {
            if (word1[i] != word2[i]) {
                return false;
            }
        }
        return true;
    }

    public void printWords() {
        for (int i = 0; i < wordCount; i++) {
            System.out.println(new String(words[i]) + ": " + counts[i]);
        }
        // Print the total words at the end
        System.out.println("Total words: " + totalWords);
    }
}

