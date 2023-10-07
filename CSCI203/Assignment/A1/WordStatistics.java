import java.io.*;
import java.util.*;

public class WordStatistics {

    // Class to represent each word and its count
    static class WordCount implements Comparable<WordCount> {
        String word;
        int count;

        public WordCount(String word, int count) {
            this.word = word;
            this.count = count;
        }

        // Comparator to sort based on count and then alphabetically
        public int compareTo(WordCount o) {
            if (this.count != o.count) {
                return o.count - this.count; // descending count
            }
            return this.word.compareTo(o.word); // ascending lexicographically
        }
    }

    // Convert word to lowercase without using String methods
    public static String toLowerCase(String word) {
        char[] chars = word.toCharArray();
        for (int i = 0; i < chars.length; i++) {
            if (chars[i] >= 'A' && chars[i] <= 'Z') {
                chars[i] = (char) (chars[i] + 'a' - 'A');
            }
        }
        return new String(chars);
    }

    // Remove punctuation from a word without using String methods
    public static String removePunctuations(String s) {
        char[] chars = s.toCharArray();
        StringBuilder sb = new StringBuilder();
        for (char c : chars) {
            if (Character.isLetter(c)) {
                sb.append(c);
            }
        }
        return sb.toString();
    }

    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter Filename: ");
        String filename = scanner.nextLine();

        BufferedReader br = new BufferedReader(new FileReader(filename));

        HashMap<String, Integer> wordCounts = new HashMap<>();

        String line;
        while ((line = br.readLine()) != null) {
            StringTokenizer st = new StringTokenizer(line);
            while (st.hasMoreTokens()) {
                String word = removePunctuations(st.nextToken());
                word = toLowerCase(word);
                wordCounts.put(word, wordCounts.getOrDefault(word, 0) + 1);
            }
        }
        br.close();

        List<WordCount> sortedList = new ArrayList<>();
        for (String key : wordCounts.keySet()) {
            sortedList.add(new WordCount(key, wordCounts.get(key)));
        }

        Collections.sort(sortedList);

        System.out.println("First ten words:");
        for (int i = 0; i < 10 && i < sortedList.size(); i++) {
            System.out.println(sortedList.get(i).word + ": " + sortedList.get(i).count);
        }

        System.out.println("Last ten words:");
        for (int i = sortedList.size() - 1; i >= sortedList.size() - 10 && i >= 0; i--) {
            System.out.println(sortedList.get(i).word + ": " + sortedList.get(i).count);
        }

        System.out.println("Unique words:");
        for (WordCount wc : sortedList) {
            if (wc.count == 1) {
                System.out.println(wc.word);
            }
        }
    }
}
