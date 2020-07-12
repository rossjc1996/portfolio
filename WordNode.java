public class WordNode
{
	public int key;
    public String word;
    public int count;
	public WordNode left;
	public WordNode right;

	public WordNode(int k, String w, int c) {
		key = k;
		left = right = null;
        word = w;
        count = c;
	}	
    public void inccount()
    {
        count++;
    }
	public WordNode (int k, WordNode l, WordNode r, String w, int c) {
		key = k;
		left = l;
		right = r;
        count = c;
        word = w;
	}
}

