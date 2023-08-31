package Lecture.code;
import java.util.*;

public class week1_p1 {
    public static void main(String[] arg) {
        int[] array = { 1, 2, 3, 4, 7, 8, 6, 5, 10, 9 };

        // Method 1: the maximum algorithms
        /*  
        int position =0;
        int maximum = array[0];
        for (int i = 1; i <10; i++) {
            if (array[i]>maximum) {
                maximum = array[i];
                position = i;
            }
        } */
        // System.out.println("The maximum value is " + maximum + " at position " + position);

        // Method 2: Linear Search
        /*
        for (int i =0; i<9; i++) {
            if (array[i] >= array[i+1]) {
                System.out.println("there is a peak with value " + array[i] + " at position " + i);
            break;
            }
        } */
        // System.out.println("There is a peak with value " + array[9] + " at position " + 9);
         

        // Method 3: Binary Search
    /*  int start = 0;
        int end = array.length -1;
        boolean check = true;

        while (check) {
            int mid = (int) (((start + end) / 2));
            if (array[mid] < array[mid - 1]) {
                end = mid - 1;
            } else if (array[mid] < array[mid + 1]) {
                start = mid + 1;
            } else {
                System.out.println("peak found at position " + mid + " with value " + array[mid]);
                check = false;
                break;
            }

        } */
        
    //Method 3a: Binary search with test for termination
    // int start = 0;
    // int end = array.length -1;
    // while (start <=end) {
    //     int mid = (int)(((start+end)/2)+0.5);
    //     if (array[mid] <array[mid -1]) {
    //         end = mid -1;
    //     } else if (array[mid] <array[mid+1]) {
    //         start = mid +1;
    //     } else {
    //         System.out.print("Peak found at position " + mid + " with value " + array[mid]);
    //         break;
    //     }
    // }
    
/*--------------------end_main--------------------- */
    }
}