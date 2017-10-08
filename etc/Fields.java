public class Fields {

    public static String hello = "Hello, World!";

    public static void main(String[] args) {
        InnerClass inner = new InnerClass();
        System.out.println(hello);
        System.out.println(inner.publicLong);
        System.out.println(inner.publicInt);
        System.out.println(inner.getPrivateFloat());
        System.out.println(inner.getProtectedDouble());
        System.out.println(inner.finalChar);
    }

    private static class InnerClass {

        public long publicLong = 999999999999l;
        public int publicInt = 10;
        private float privateFloat = 11.1f;
        protected double protectedDouble = 5.6787;
        public final char finalChar = 'g';
        public float getPrivateFloat() {
            return privateFloat;
        }

        public double getProtectedDouble() {
            return protectedDouble;
        }
    }
}