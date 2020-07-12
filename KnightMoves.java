import java.util.Scanner;

public class KnightMoves
{
    private static int[][] chessBoard;
    
    public static void main(String[] args)
    {
        Scanner Scan = new Scanner(System.in);
        int size = Scan.nextInt();
        int startRow = Scan.nextInt();
        int startCol = Scan.nextInt();
        chessBoard = new int[size][size];

        for(int i = 0; i < size; i++)
            for(int j = 0; j < size; j++)
                chessBoard[i][j] = size;
        chessBoard[startRow-1][startCol-1] = 0;
        recur(size, startRow - 1, startCol - 1, 0);
        print(size);
    }

    private static void print(int size)
    {
        for (int i = size - 1; i >= 0; i--)
        {
            for (int j = 0; j < size; j++)
                System.out.print(chessBoard[i][j] + " ");
            System.out.println();
        }
    }

    private static void recur(int size, int row, int col, int count)
    {
        count++;
        //System.out.println(count);
        if (row + 2 < size)
        {
            if (col + 1 < size)
            {
                if(chessBoard[row + 2][col + 1] > count)
                {
                    //System.out.println("R2 C1");
                    chessBoard[row + 2][col + 1] = count;
                    recur(size, row + 2, col + 1, count);
                }
            }
            if (col - 1 >= 0)
            {
                if(chessBoard[row + 2][col - 1] > count)
                {
                    //System.out.println("R2 C0");
                    chessBoard[row + 2][col - 1] = count;
                    recur(size, row + 2, col - 1, count);
                }
            }
        }
        if (row - 2 >= 0)
        {
            if (col + 1 < size)
            {
                if(chessBoard[row - 2][col + 1] > count)
                {
                    chessBoard[row - 2][col + 1] = count;
                    recur(size, row - 2, col + 1, count);
                }
            }
            if (col - 1 >= 0)
            {
                if(chessBoard[row - 2][col - 1] > count)
                {
                    chessBoard[row - 2][col - 1] = count;
                    recur(size, row - 2, col - 1, count);
                }
            }
        }
        if (col + 2 < size)
        {
            if (row + 1 < size)
            {
                if(chessBoard[row + 1][col + 2] > count)
                {
                    chessBoard[row + 1][col + 2] = count;
                    recur(size, row + 1, col + 2, count);
                }
            }
            if (row - 1 >= 0)
            {
                if(chessBoard[row - 1][col + 2] > count)
                {
                    chessBoard[row - 1][col + 2] = count;
                    recur(size, row - 1, col + 2, count);
                }
            }
        }
        if (col - 2 >= 0)
        {
            if (row + 1 < size)
            {
                if(chessBoard[row + 1][col - 2] > count)
                {
                    chessBoard[row + 1][col - 2] = count;
                    recur(size, row + 1, col - 2, count);
                }
            }
            if (row - 1 >= 0)
            {
                if(chessBoard[row - 1][col - 2] > count)
                {
                    chessBoard[row - 1][col - 2] = count;
                    recur(size, row - 1, col - 2, count);
                }
            }
        }
    }
}
