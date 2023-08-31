package Lab.Wk2;
import java.io.FileReader;
import java.util.Scanner;
import java.io.IOException;

public class main {
    static String[] stack = new String[50];
    static int wordIndex = -1;
    public static void main(String[] args) {
        try (Scanner info = new Scanner(System.in)) {
            System.out.print("Enter the file name: ");
            String file_int = info.nextLine();
            try {
                Scanner readFile = new Scanner(new FileReader (file_int));
                while (readFile.hasNext()) {
                    String word = readFile.next();
                    push(word);
                }
                readFile.close();  

                while (!isEmpty()) {
                    System.out.print(top() + " ");
                    pop();
                }           
            } 
            catch (IOException e) {
                System.out.print("The file name" + file_int + "could not open!");
            }
        }
    } 

    public static void pop() {
        if (isEmpty()) {
            System.out.println("STACK EMPTY");
            System.exit(1);
          }
        wordIndex = wordIndex -1;
    }

    public static void push(String word) {
        wordIndex = wordIndex +1;
        stack[wordIndex] = word;
    }

    private static boolean isEmpty() {
        return wordIndex == -1;
    }

    public static String top () {
        return stack[wordIndex];
    }
} 

