/*
 * Compile assim: javac lookupSwitch.java -target 1.2 -source 1.2
 */
public class lookupSwitch{
    public static int chooseNear(int intOne) {
        switch (intOne) {
            case 10:
                return 1;
            case 20:
                return 2;
            case 30:
                return 3;
            default:
                return -1;
        }
    }
    public lookupSwitch(){
        System.out.println("Ops!");
    }
    public static void main(String args[]){
        System.out.println(lookupSwitch.chooseNear(-1));
        System.out.println(lookupSwitch.chooseNear(10));
        System.out.println(lookupSwitch.chooseNear(20));
        System.out.println(lookupSwitch.chooseNear(30));
    }
}
