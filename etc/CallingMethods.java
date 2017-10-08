public class CallingMethods {

    public static void main(String[] args) {
        printOne();
        printTwo();
        printThree();
    }

    public static void printOne() {
        System.out.println("Vamos! Vamos Cruzeiro!\nVamos! Vamos pra ganhar!\nVou aonde voce for!\nSo pra ver voce jogar!");
    }

    public static void printTwo() {
        printOne();
        printOne();
    }

    public static void printThree() {
        printOne();
        printOne();
        printOne();
    }
}