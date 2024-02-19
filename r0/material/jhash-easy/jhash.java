public class jhash {

    public static int hash(char[] key, int len) {
        int h = 8388617;

        for (int i = 0; i < len; i++) {
            h = ( (h << 1 | h >> 30) & 0x7fffffff ) ^ key[i];
        }
        return h;
    }
    

    public static void main(String[] args){
        char[] key = {'j', 'h', 'a', 's', 'h'};
        System.out.println(hash(key, 5));
    }
}
