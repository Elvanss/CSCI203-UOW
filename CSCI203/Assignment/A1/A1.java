import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner; 

/* This program was written in BST Data Structure and Quick Sort algorithm (CSCI203 lecture slides in week 1 & 4) 
 * External documents:
 * https://www.geeksforgeeks.org/quick-sort/ (Quicksort algorithm)
 * https://www.geeksforgeeks.org/insertion-in-binary-search-tree/?ref=lbp (Binary Insertion)
 * https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/ (Searching in BST)
 * https://www.freecodecamp.org/news/binary-search-tree-traversal-inorder-preorder-post-order-for-bst/ (Traversal orders)
*/

//Create a Node class which will be used in BST
class Node {
    String data;
    int count;
    Node left, right;

    public Node(String data) {
        //node data
        this.data = data;
        //counter
        this.count = 1;
        //position (left, right)
        this.left = null;
        this.right = null;
    }
}

public class A1 {
    private static Node root;

    //Compare the String (lexicographical & length word by word)
    private int stringLength(String str1, String str2) {
        char[] string1 = str1.toCharArray();
        char[] string2 = str2.toCharArray();
        int index = 0;

        while (index < string1.length && index < string2.length) {
            // check the compare the lexicographical order
            if (string1[index] < string2[index]) {
                return -1;
            } else if (string1[index] > string2[index]) {
                return 1;
            }
            index++;
        }
        // compare the length of word
        if (string1.length < string2.length) {
            return -1;
        } else if (string1.length > string2.length) {
            return 1;
        }
        return 0;
    }

    //Add node into BST (left and right); either count if strings are equal in comparison
    private void addNode(Node node, String data) {
        if (stringLength(data, node.data) == 0) {
            node.count++;
        } else if (stringLength(data, node.data) < 0) {
            if (node.left == null) {
                node.left = new Node(data);
            } else {
                addNode(node.left, data);
            }
        } else {
            if (node.right == null) {
                node.right = new Node(data);
            } else {
                addNode(node.right, data);
            }
        }
    }

    //Insert data into node from root of BST
    public void insert(String data) {
        if (root == null) {
            root = new Node(data);
        } else {
            addNode(root, data);
        }
    }

    // Traversal a BST into a list 
    public List<Node> collectNodesToList() {
        List<Node> nodeList = new ArrayList<>();
        collectNode(root, nodeList);
        return nodeList;
    }

    //collect nodes from BST
    private void collectNode(Node node, List<Node> nodeList) {
        if (node != null) {
            nodeList.add(node);
            collectNode(node.left, nodeList);
            collectNode(node.right, nodeList);
        }
    }

    //implement the quicksort logic
    public int partition(List<Node> nodeList, int lowest, int highest) {
        int pivotCount = nodeList.get(highest).count;
        int i = lowest - 1;
        int swapCount;
        String swapData;
        //sort word by count in decreasing order
        for (int j = lowest; j < highest; j++) {
            if (nodeList.get(j).count > pivotCount) {
                i++;

                swapCount = nodeList.get(i).count;
                nodeList.get(i).count = nodeList.get(j).count;
                nodeList.get(j).count = swapCount;
    
                swapData = nodeList.get(i).data;
                nodeList.get(i).data = nodeList.get(j).data;
                nodeList.get(j).data = swapData;
                
            //In case the count of each word are similarity, sorting by alphabetical
            } else if (nodeList.get(j).count == pivotCount) {
                if (nodeList.get(j).data.compareTo(nodeList.get(highest).data) < 0) {
                    i++;

                    swapCount = nodeList.get(i).count;
                    nodeList.get(i).count = nodeList.get(j).count;
                    nodeList.get(j).count = swapCount;

                    swapData = nodeList.get(i).data;
                    nodeList.get(i).data = nodeList.get(j).data;
                    nodeList.get(j).data = swapData;
                }
            }
        }
        //swap the count position
        swapCount = nodeList.get(i + 1).count;
        nodeList.get(i + 1).count = nodeList.get(highest).count;
        nodeList.get(highest).count = swapCount;
        
        //swap the data as the same time
        swapData = nodeList.get(i + 1).data;
        nodeList.get(i + 1).data = nodeList.get(highest).data;
        nodeList.get(highest).data = swapData;
    
        return i + 1;
    }

    //Quicksort method
    public void quickSort(List<Node> nodeList, int begin, int end) {
        if (begin < end) {
            //call the partition method
            int partition = partition(nodeList, begin, end);
            quickSort(nodeList, begin, partition-1);
            quickSort(nodeList, partition+1, end);
        }
    }

    //Display the tree with sorted nodes
    public void Display() {
        List<Node> nodeList = collectNodesToList();
        //set the begin and end
        int begin = 0;
        int end = nodeList.size()-1;

        String line = "------------------------------";
        //variable for the sum of words and the total of unique word(equal to 1)
        int sum = 0;
        int unique =0;
        quickSort(nodeList, begin, end);

        //print the total words
        for (int i = 0; i < nodeList.size(); i++) {
            sum += nodeList.get(i).count;
        }
        System.out.println(">>-----The total words: " + sum + "-----<");

        System.out.println(line); 
        
        // print the first 10 words including counter:
        System.out.println("The first 10 words:");
        for (int i = 0; i < nodeList.size() && i < 10; i++) {
            System.out.printf("%-17s: %d%n", nodeList.get(i).data, nodeList.get(i).count);
        } 
        
        System.out.println(line);  

        System.out.println("The last 10 words:");
        // print the last 10 words including counter:
        for (int i = nodeList.size() - 10; i < nodeList.size(); i++) {
            System.out.printf("%-17s: %d%n", nodeList.get(i).data, nodeList.get(i).count);
        }

        System.out.println(line);
        
        //print the total words which only have 1 word
        for (int i = 0; i< nodeList.size(); i++) {
            if (nodeList.get(i).count ==1) {
                unique++;
            }
        }
        System.out.println("The total unique words: " + unique);
    }

    //Make all the lower by each character in a string by utilizing ASCII theories
    public static String lowerCase(String word) {
        char[] words = word.toCharArray();
        for (int i = 0; i < words.length; i++) {
            if (words[i] >= 65 && words[i] <= 90) {
                words[i] = (char) (words[i] + 32);
            }
        }
        return new String(words);
    }

    // Remove all the punctuation of given consequence in the text file
    public static String removePunctuation(String word) {
        return word.replaceAll("[^a-zA-Z0-9\\s]", "");
    }

    //combining two methods into String function
    public static String stringCheck(String word) {
        word = removePunctuation(word);
        word = lowerCase(word);
        return word;
    }

    public static void main(String[] args) {
        // Create a Binary Tree object
        A1 BinaryTree = new A1();
        try (
            Scanner info = new Scanner(System.in)) {
            // get file name from user input 
            System.out.print("Enter the file name: ");
            String fileInput = info.nextLine();
            try {
            //Method of reading file word by word
                Scanner readFile = new Scanner(new FileReader(fileInput));
                while (readFile.hasNext()) {
                    String word = readFile.next();
                    word = stringCheck(word);
                    //Insert each word to the BST
                    BinaryTree.insert(word);
                }
                // BinaryTree.display();
                BinaryTree.Display();
                //Close the file
                readFile.close();
            } catch (IOException e) {
                System.out.print("The file name " + fileInput + " could not open!");
            }
        }
    }
}
