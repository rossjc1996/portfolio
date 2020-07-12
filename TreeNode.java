
public class TreeNode {
	public int key;
	public TreeNode left;
	public TreeNode right;

	public TreeNode(int k) {
		key = k;
		left = right = null;
	}	

	public TreeNode(int k, TreeNode l, TreeNode r) {
		key = k;
		left = l;
		right = r;
	}
}
