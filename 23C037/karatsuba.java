
public class karatsuba {

    public static long karatsubaMultiply(long x, long y) {
        if (x < 10 || y < 10) {
            return x * y;
        }
        int length = Math.max(Long.toString(x).length(), Long.toString(y).length());
        int halflength = length / 2;
        long max1 = x / (long) Math.pow(10, halflength);
        long max2 = y / (long) Math.pow(10, halflength);
        long min1 = x % (long) Math.pow(10, halflength);
        long min2 = y % (long) Math.pow(10, halflength);

        long A = karatsubaMultiply(max1, max2);
        long B = karatsubaMultiply(min1, min2);
        long C = karatsubaMultiply(max1 + min1, max2 + min2) - A - B;

        return A * (long) Math.pow(10, halflength * 2) + C * (long) Math.pow(10, halflength) + B;

    }

    public static void main(String[] args) {
        int x = 1234;
        int y = 5678;
        System.out.println(karatsubaMultiply(x, y));
    }

}
