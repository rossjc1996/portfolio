import java.util.Scanner;
public class TriangleNumbers {
	private static int n; // number of rows.
	private static int [] [] triangle; // Stores the input.

	public static void main(String [] args) {
		// Reading the input and putting it in a double dimensional array triangle.
		Scanner kb = new Scanner(System.in);
		n = kb.nextInt();
		triangle = new int[n+1][n+1]; // rows 1...n contain the input triangle. 

		for (int i = 1; i < n+1; ++i) {
			for (int j = 1; j <= i; ++j) {
				triangle[i][j] = kb.nextInt();
			}
		}
		// TODO: Please write a recursive funciton to compute the largest sum of a path from the top to the bottom row.
        int result = recur(1, 1);
        System.out.println("The largest sum obtained is " + result);
	}

    public static int recur(int row, int col)
    {
        if (row > n || col > n)
        {
            return 0;
        }
        int leftSum = triangle[row][col] + recur(row + 1, col);
        int rightSum = triangle[row][col] + recur(row + 1, col + 1);
        if (leftSum >= rightSum)
        {
            return leftSum;
        }
        return rightSum;
    }
}
