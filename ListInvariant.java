
public class ListInvariant {
    static ListNode curNode; 
    static int preKey;
    static int count;

	public static void main(String [] args) {
		MyList L = new MyList();
		ListNode head = L.getHead();

		// TODO: call your recursive function check_invariant here. 
 
        curNode = head;
        preKey = 0;
        count = 0;
        reWrapper();
    }
    public static void reWrapper()
    {
        if (curNode != null){
            if (!check_invariant(curNode, preKey)){
                count = 0;
                reWrapper();
            }
        }
    }
    public static boolean check_invariant(ListNode node, int key)    
    {
        if (node == null){
            return true;
        }
        if(count >= 5000)
        {
            curNode = node;
            preKey = key;
            return false;
        }
        if ((node.next != null && node.key > node.next.key && node.key > key) 
            || (node.next == null && node.key > key)){
            System.out.println(node.key); 
        }
        count++;
        return check_invariant(node.next, node.key);
    }
}
