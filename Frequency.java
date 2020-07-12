import java.util.Scanner;
import java.io.*;

public class Frequency
{
    public static void main(String [] args)
    {
        File fi = new File("LOTR-words");
        Scanner scan = new Scanner(fi);
        scan = new Scanner(System.in);
        countWord(scan.next());
    }
    public static void countWord(String word)
    {
        
    }
    public int HashFunction(char[] word)  
    {
        int value = 0;
        for (int i = 0; i < word.length; i++)
        {
            value = value + word[i]^i;
        }
        return value;
    }
}
