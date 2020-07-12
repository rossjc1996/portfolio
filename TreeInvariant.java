
public class TreeInvariant {

	public static void main(String [] args) {
		MyTree T = new MyTree();
		TreeNode root = T.getRoot();

		// TODO: call your check_invariant function here.
       check_invariant(root);
    }

        /*curNode = root;
        count = 0;
        reWrapper():
    }
    public static void reWrapper()
    {
        if (curNode != null){
            if (!check_invariant(curNode)){
                count = 0;
                reWrapper();
            }
        }
	}*/
    public static boolean check_invariant(TreeNode node)
    {
        if (node == null)
            return true;
        if ((node.right != null && node.key >= node.right.key)
            || (node.left != null && node.key < node.left.key))
        {
            System.out.println(node.key);
        }
        check_invariant(node.left);
        check_invariant(node.right);
        return false;
    }
}
