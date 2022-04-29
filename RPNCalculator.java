import java.util.ArrayDeque;
import java.util.Scanner;

public class RPNCalculator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        String[] operations = input.split(" ");
        ArrayDeque<Integer> stack = new ArrayDeque<>();
        for (String operation : operations) {
            try {
                int number = Integer.parseInt(operation);
                stack.push(number);
            } catch (NumberFormatException e) {
                int second = stack.pop();
                int first = stack.pop();
                switch (operation) {
                    case "+" -> stack.push(first + second);
                    case "-" -> stack.push(first - second);
                    case "*" -> stack.push(first * second);
                    case "/" -> stack.push(first / second);
                    case "%" -> stack.push(first % second);
                    default -> {
                        System.out.printf("ERROR: Unhandled operation : %s", operation);
                        throw new IllegalArgumentException();
                    }
                }
            }
        }
        while (!stack.isEmpty()) {
            System.out.printf("%d ", stack.pop());
        }
    }
}
