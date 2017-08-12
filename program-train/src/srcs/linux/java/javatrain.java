/*
 * Progarm Name: javatrain.java
 * Created Time: 2017-06-15 16:30:11
 * Last modified: 2017-06-18 17:56:29
 * @author: minphone.linails linails@foxmail.com 
 */

import java.io.*;
import java.util.Arrays;

public class javatrain
{
    public static void main(String[] args)
    {
        System.out.printf("\n");
        System.out.print("javatrain ...\n\n");

        //------------------------------------------------------------

        javatrain jt = new javatrain();

        jt.datatype();

        jt.auto_conversion();

        jt.control_flow();

        jt.array_type();
    }

    void datatype()
    {
        {
            byte a = 56;
            System.out.printf("a = %d\n", a);

            /* 
             * ! long 数据类型需要做后面添加一个L，否则编译出错, 因为默认使用 int 存储
             * */
            long bigValue = 8786786786675667868L;
            System.out.printf("bigValue = %d\n", bigValue);

            char c = 'a';
            System.out.printf("c = %c\n", c);
            System.out.printf("c = %d\n", (int)c);

            int  ci  = 97;
            char i2c = (char)ci;
            System.out.printf("i2c = %c\n", i2c);
        }
        System.out.println("------------------------------------------------------------");
        {
            float af = 4.52335533f;
            System.out.printf("af = ");
            System.out.println(af);

            double a = 0.0;
            System.out.printf("a = ");
            System.out.println(a);

            double pi = 3.14_15_926_54;
            System.out.printf("pi = ");
            System.out.println(pi);

            int binval = 0b0000_0000_0000_0000_0000_0000_0000_0001;
            System.out.printf("binval = %d\n", binval);
        }
        System.out.println("------------------------------------------------------------");
        {
            /*
             * boolean 类型的值只能说 true / false，不能用 0 或 非0
             * 其他数据类型的值不能转换成 boolean
             * */

            boolean b1 = true;

            /* 
             * 一个 boolean 值和字符串进行连接，则 boolean 会自动转换为字符串
             * */
            String str = b1 + " ...";
            System.out.printf("str = ");
            System.out.println(str);
        }
        System.out.println("------------------------------------------------------------");
        {
            /*
             * 基本类型 + "" ，就可以把基本类型的值转换为字符串
             * */
            String str1 = 5 + "";
            System.out.printf("str1 = ");
            System.out.println(str1);

            System.out.println(3 + 4 + "hello!");   // 7hello!
            System.out.println("hello!" + 3 + 4);   // hello!34
        }
        System.out.println("------------------------------------------------------------");
    }

    void auto_conversion()
    {
        {
            int a = 6;
            float f = a;
            System.out.printf("f = ");
            System.out.println(f);

            System.out.println("f = " + f);
        }
        System.out.println("------------------------------------------------------------");
    }

    void control_flow()
    {
        {
            int age = 10;

            if(age > 20){
                System.out.println("age > 20");
            }else{
                System.out.println("age < 20");
            }
        }
        System.out.println("------------------------------------------------------------");
        {
            String season = "summer";

            switch(season){
                case "spring" :
                    System.out.println("spring !");
                    break;
                case "summer" :
                    System.out.println("summer !");
                    break;
                case "autumn" :
                    System.out.println("autumn !");
                    break;
                case "winter" :
                    System.out.println("winter !");
                    break;
            }
        }
        System.out.println("------------------------------------------------------------");
        {
            for(int i=0; i<10; i++){
                if (i >= 2){
                    System.out.println(" i >= 2");
                    break;
                }
            }
        }
        System.out.println("------------------------------------------------------------");
        {
            int flag = 0;


            if(flag != 0){
                System.out.println("flag != 0");
            }else{
                outer:
                for(int i=0; i<10; i++){
                    for(int j=0; j<10; j++){
                        if(j > 2){
                            System.out.println(" j>2 ");
                            flag = 1;
                            break outer;
                        }
                    }
                }
            }
        }
        System.out.println("------------------------------------------------------------");
        {
            outer:
            for(int i=0; i<10; i++){
                for(int j=0; j<10; j++){
                    if(j == 2){
                        System.out.println("i = " + i + " j = " + j);
                        continue outer;
                    }

                    System.out.println("  j = " + j);
                }
            }
        }
        System.out.println("------------------------------------------------------------");
    }

    void array_type()
    {
        {
            int[] a;

            a = new int[]{1, 2, 3, 9, 8, 4, 3, 1, 4, 8, 0};

            for(int i=0; i<a.length; i++){
                System.out.printf("a[%d] = %d\n", i, a[i]);
            }
        }
        System.out.println("------------------------------------------------------------");
        {
            int[] a; 

            /* 
             * 动态初始化，只定义长度，系统会负责初始化为初始值
             *  1> 整形类型(byte/short/int/long)，则数组元素值初始化为 0
             *  2> 浮点类型(float/double)，则数组元素值初始化为 0.0
             *  3> 字符类型(char)，则数组元素值初始化为 '\u0000'
             *  4> 布尔类型(boolean)，则数组元素值初始化为 false
             *  5> 引用类型(类/接口/数组)，则数组元素值初始化为 null
             * */
            a = new int[10];

            System.out.println("a.length = " + a.length);
            for(int i=0; i<a.length; i++){
                System.out.printf("a[%d] = %d\n", i, a[i]);
            }

            for(int u : a){ System.out.println("u = " + u); }
        }
        System.out.println("------------------------------------------------------------");
        {
            /*
             * 数组变量名，只是引用，可以互相交换和赋值
             * */
            int[] a = {3, 4, 5};
            int[] b = new int[4];

            System.out.println("a.length = " + a.length);
            System.out.println("b.length = " + b.length);

            int[] c = b;

            b = a;
            a = c;
            c = null;

            System.out.println("a.length = " + a.length);
            System.out.println("b.length = " + b.length);
        }
        System.out.println("------------------------------------------------------------");
        {
            int [][] a;

            a = new int[4][];
            for(int[] u : a){ System.out.println("int[] u = " + u); }

            int[] sa = {3, 4, 5};
            a[0] = sa;
            for(int u : a[0]){ System.out.println("int u = " + u); }

            int [][] b = new int[3][4];
            System.out.println("b.length = " + b.length);
            System.out.println("b[0].length = " + b[0].length);
        }
        System.out.println("------------------------------------------------------------");
        {
            int [][] a = new int[][]{new int[3], new int[]{3, 4}};

            System.out.println("a.length = " + a.length);
            System.out.println("a[0].length = " + a[0].length);
            System.out.println("a[1].length = " + a[1].length);
        }
        System.out.println("------------------------------------------------------------");
        {
            int[] a = new int[]{1, 4, 7, 2, 5, 2, 9, 0};
            for(int u : a) System.out.printf("%d ", u); System.out.println("");

            Arrays.sort(a);
            for(int u : a) System.out.printf("%d ", u); System.out.println("");

            System.out.println("a[i] = 2 | i = " + Arrays.binarySearch(a, 0));
            System.out.println("a[i] = 2 | i = " + Arrays.binarySearch(a, 1));
            System.out.println("a[i] = 2 | i = " + Arrays.binarySearch(a, 2));
            System.out.println("a[i] = 2 | i = " + Arrays.binarySearch(a, 7));
        }
        System.out.println("------------------------------------------------------------");
        {
        }
        System.out.println("------------------------------------------------------------");
    }
}

