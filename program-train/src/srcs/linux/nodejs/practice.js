/*
 * Progarm Name: practice.js
 * Created Time: 2016-11-23 09:17:21
 * Last modified: 2016-11-23 14:27:04
 * @author: minphone.linails linails@foxmail.com 
 */

function print(msg)
{
    console.log(msg);
}

/*  
 * js的代码块不会创建一个新的作用域
 *
 * typeof运算符产生的值有: "number", "string", "boolean", "undefined", "function", "object"
 *      如果一个运算数量是一个数组或null，那么结果就是"object"
 *  */

print(typeof(100));
print(typeof("hello world"));

function var_print()
{
    var flight = {
        airline: "Oceanic",
        number : 815,
        departure: {
            IATA: "SYD",
            time: "2016-11-23 09:39",
            city: "Sydney"
        },
        arrival: {
            IATA: "LAX",
            time: "2016-11-22 09:39",
            city: "Los Angeles"
        }
    };

    print(flight);
    print("");
    print("flight.airline : " + flight.airline);
    print("flight.number : " + flight.number);
    print("flight['number'] : " + flight['number']);

    print("");
    print("typeof(flight.number) : " + typeof(flight.number));
    print("typeof(flight.arrival) :" + typeof(flight.arrival));
    print("typeof(flight.manifest) :" + typeof(flight.manifest));
    print("typeof(flight.toString) :" + typeof(flight.toString));
    print("typeof(flight.constructor) :" + typeof(flight.constructor));
    print("");

    /*  
     *  使用 hasOwnProperty 方法，如果对象拥有独有的属性，返回 true，此方法
     *  不检查原型链
     *  */
    print("flight.hasOwnProperty('number') : " + flight.hasOwnProperty('number'));
    print("flight.hasOwnProperty('constructor') : " + flight.hasOwnProperty('constructor'));
    print("");

    for (name in flight){
        print("properties : " + name);
    }
    print("");
}

var_print();
print(typeof(var_print));
print(typeof(100));

var value = 10;

function fun_print()
{
    print("");

    var add = function (a, b){
        return a + b;
    };

    print("add(1, 2) : " + add(1, 2));

    function minus(a, b)
    {
        return a - b;
    }

    print("minus(2, 1) : " + minus(2, 1));

    /* 
     * 每个函数接收两个附加的参数：this 和 arguments
     *
     * js 中有四种调用模式：
     *    1> 方法调用模式
     *    2> 函数调用模式
     *    3> 构造器调用模式
     *    4> apply 调用模式
     * */

    var myobj = {
        value: 0,
        increment: function (inc){
            this.value += typeof inc === 'number' ? inc : 1;
        }
    };

    myobj.increment();
    print("myobj.value : " + myobj.value);
    myobj.increment(2);
    print("myobj.value : " + myobj.value);

    myobj.double = function (){
        /* 两种都可以这里 */
        /* 
        var that = this;
        print(that);
        var helper = function (){
            that.value = add(that.value, that.value);
        };

        helper();
        return myobj.value;

         * */
        //return (this.value = add(this.value, this.value));

        var helper = function (that){
            that.value = add(that.value, that.value);
            print(that.value);
        };

        helper(this);
        return myobj.value;
    };
    print("myobj.double() : " + myobj.double());

    var dat = new Date();
    print("dat = " + dat);
}

fun_print();

/* 
 * 总结：
 *  1> javascript 的简单类型包括数字、字符串、布尔值、null值和undefined值
 *  2> 其他所有的值都是对象
 *  3> javascript 包括一个原型链特性，允许对象继承另一个对象的属性，正确
 *     地使用它能减少对象初始化的时间和内存消耗
 * */

