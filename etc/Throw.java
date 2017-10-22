public class Throw {
    public class Test_Deprecated {
        @Deprecated
        public void doSomething() {
            System.out.println("Testing annotation name: 'Deprecated'");
        }
    }

   public static void main(String args[]) {
      String input = "invalid input";
      try {
         if (input.equals("invalid input")) {
            throw new RuntimeException("throw demo");
         } else {
            System.out.println(input);
         }
         System.out.println("After throwing");
      } catch(RuntimeException e){
         System.out.println("Exception caught: " + e);
      }
   }
}
