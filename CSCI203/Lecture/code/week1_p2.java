package Lecture.code;

public class week1_p2 {
    public static void main(String[] args) {
        int[][] matrix = {
            {10, 8, 10, 10},
            {14, 13, 12, 11},
            {15, 9, 11, 21},
            {16, 17, 19, 20}
        };

        int[] peak = find2DPeak(matrix);

        if (peak != null) {
            System.out.println("Peak found at position (" + peak[0] + "," + peak[1] + ") with value " + matrix[peak[0]][peak[1]]);
        } else {
            System.out.println("No peak found in the matrix.");
        }
    }

    public static int[] find2DPeak(int[][] matrix) {
        int startCol = 0;
        int endCol = matrix[0].length - 1;

        while (startCol <= endCol) {
            int midCol = (startCol + endCol) / 2;
            
            // Find the maximum in the middle column
            int maxVal = Integer.MIN_VALUE;
            int maxRow = -1;
            for (int i = 0; i < matrix.length; i++) {
                if (matrix[i][midCol] > maxVal) {
                    maxVal = matrix[i][midCol];
                    maxRow = i;
                }
            }

            // Compare with the left column, if exists
            if (midCol > 0 && matrix[maxRow][midCol] < matrix[maxRow][midCol - 1]) {
                endCol = midCol - 1;
            }
            // Compare with the right column, if exists
            else if (midCol < matrix[0].length - 1 && matrix[maxRow][midCol] < matrix[maxRow][midCol + 1]) {
                startCol = midCol + 1;
            } else {
                return new int[]{maxRow, midCol}; // peak found
            }
        }

        return null; // No peak found
    }
}

// public class PeakFinding2D {
//     public static void main(String[] args) {
//         int[][] matrix = {
//             {10, 8, 10, 10},
//             {14, 13, 12, 11},
//             {15, 9, 11, 21},
//             {16, 17, 19, 20}
//         };

//         int[] peak = find2DPeak(matrix);

//         if (peak != null) {
//             System.out.println("Peak found at position (" + peak[0] + "," + peak[1] + ") with value " + matrix[peak[0]][peak[1]]);
//         } else {
//             System.out.println("No peak found in the matrix.");
//         }
//     }

//     public static int[] find2DPeak(int[][] matrix) {
//         int startCol = 0;
//         int endCol = matrix[0].length - 1;

//         while (startCol <= endCol) {
//             int midCol = (startCol + endCol) / 2;

//             int maxRow = findMaxInColumn(matrix, midCol);

//             // Compare with the left column, if exists
//             if (midCol > 0 && matrix[maxRow][midCol] < matrix[maxRow][midCol - 1]) {
//                 endCol = midCol - 1;
//             }
//             // Compare with the right column, if exists
//             else if (midCol < matrix[0].length - 1 && matrix[maxRow][midCol] < matrix[maxRow][midCol + 1]) {
//                 startCol = midCol + 1;
//             } else {
//                 return new int[]{maxRow, midCol}; // peak found
//             }
//         }

//         return null; // No peak found
//     }

//     private static int findMaxInColumn(int[][] matrix, int col) {
//         int maxVal = Integer.MIN_VALUE;
//         int maxRow = -1;

//         for (int i = 0; i < matrix.length; i++) {
//             if (matrix[i][col] > maxVal) {
//                 maxVal = matrix[i][col];
//                 maxRow = i;
//             }
//         }

//         return maxRow;
//     }
// }

