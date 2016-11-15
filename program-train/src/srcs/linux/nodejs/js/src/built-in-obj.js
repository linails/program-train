/*
 * Progarm Name: built-in-obj.js
 * Created Time: 2016-11-14 16:57:28
 * Last modified: 2016-11-15 15:51:09
 */

/* 
 * JavaScript 包含两类对象：
 *  一类是JavaScript內建对象，即JavaScript语言本身所带的对象
 *  一类是浏览器对象，由客户端浏览器所支持
 * */

/* 
 * 会被覆盖同名函数
 * */
function built_in_obj(prt)
{
    prt("para is function ...");
    prt(" built-in-obj ...");
}
// 
// function built_in_obj()
// {
//     print("no para version ...");
// }
//


/* 
 * 定义对象
 * */
function show_book()
{
    print("book name : " + this.title);
    print("book author : " + this.author);
    print ("book publisher : " + this.publisher);

    /* 用于列出所有属性 */
    for(varil in this){
        print("this->" + varil);
    }
}

/* 直接采用类似此方式定义一个类 */
function Book(title, author, publisher)
{
    this.title  = title;
    this.author = author;
    this.publisher  = publisher;
    this.showbook   = show_book;
}

/* array */
function array_test()
{
    print("");
    print("array_test");

    /* array 对象的构造函数有三种，分别用不同的方式构造一个数组对象 
     *  1> var xx = new Array();
     *  2> var xx = new Array(length); | 即使定义了长度，也是可以动态改变长度的
     *  3> var xx = new Array(arg1, arg2, ... argN);
     * */

    order = new Array();
    print("order" + order);

    order[19] = 10;
    print("order" + order);


    var arg = new Array(20);
    print("arg : " + arg);

    arg[19] = 12;
    print("arg : " + arg);

    arg[29] = 12;
    print("arg : " + arg);


    var a = new Array(1, 2, 3, 4, 5, "nice", "to", "you");
    print("array a : " + a);


    var order = new Array();
    print("Array order : " + order);

    order[0] = new Array("shoes", "30", "$200");
    order[1] = new Array("socks", "50", "$10");
    order[2] = new Array("underwaist", "40", "$80");
    for(i=0; i<3; i++){
        print("Array order[" + i + "] : " + order[i]);
    }

    print("order[1][2] : " + order[1][2]);

    {
        document.write("<table border align = center>");
        document.write("<th>product</th><th>count</th><th>price</th>");
        for(i=0; i<order.length; i++){
            document.write("<tr>");
            for(j=0; j<order[i].length; j++){
                document.write("<td>" + order[i][j] + "</td>");
            }
            document.write("</tr>");
        }
        document.write("</table>");
    }

    {
        /* 使用 prototype 属性 */
        function pop()
        {
            if(this.length > 0){
                var last = this[this.length - 1];
                this.length--;
                return last;
            }
        }

        /* 用 prototype 属性为 array 对象指定一个新方法 pop */
        Array.prototype.pop = pop;

        var color = new Array("red", "yellow", "green", "blue");
        print("color : " + color);

        color.pop();
        print("color : " + color);
    }
    print("====================================================");
    {
        var color = new Array("red", "yellow", "green", "blue");
        print("color : " + color);
        /* concat 将参数中的元素添加到数组中，但并不改变数组原来的属性 */
        print("color.concat('gray', 'purple', 'pink') : " + color.concat('gray', 'purple', 'pink'));

        print("color.join(':') : " + color.join(':'));
        print("color.reverse() : " + color.reverse());
        /* slice(start, end) | (start, end) */
        print("color.slice(-2, -1) : " + color.slice(-2, -1));
        print("color.slice(-2) : " + color.slice(-2));
        print("color.slice(-2, -2) : " + color.slice(-2, -2));

        print("color.sort() : " + color.sort());

        print("color.toString() : " + color.toString());

        print("color.valueOf() : " + color.valueOf());
    }
    print("====================================================");
    {
        var color = ["red", "green", "gray", "black"];
        print("color : " + color);
    }
}

/* boolean object Test */
function boolean_test()
{
    print("====================================================");

    /* 
     * boolean 对象支持以下属性和方法
     *  1> prototype    : 用于在 Boolean 对象中添加新的属性和方法
     *  2> toString     : 用于返回该对象的布尔值字符串
     *  3> valueOf      : 返回对象的原始值
     * */

    function letter()
    {
        if(this == true){
            return 'T';
        }else{
            return 'F';
        }
    }

    Boolean.prototype.letter = letter;

    var b1 = new Boolean(0);

    print("b1 : " + b1);
    print("b1.letter() : " + b1.letter());
    print("b1.toString() : " + b1.toString());
    print("b1.valueOf() : " + b1.valueOf());
}

function date_test()
{
    print("");
    print("====================================================");
    print("");
    var date = new Date();
    print("date : " + date);

    date = new Date(1000);
    print("date(1000) : " + date);

    date = new Date(1989, 11, 11, 11, 11, 11, 11);
    print("date(1989, 11, 11, 11, 11, 11, 11) : " + date);

    date = new Date("15 Jul, 2016 20:20:20");
    print("date('15 Jul, 2016 20:20:20') : " + date);
}

/* 
 * 如果此函数定义在前面，也不需要做类似C的那种前向声明，
 * 只要处于一个文件，都可以进行调用
 * */
function object_test()
{
    print("");
    print("=============== --- object_test --- ================");

    array_test();

    boolean_test();

    date_test();
}


