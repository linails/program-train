/*
 * Progarm Name: hw.js
 * Created Time: 2016-11-18 17:58:16
 * Last modified: 2016-12-08 13:21:50
 * @author: minphone.linails linails@foxmail.com 
 */

console.log("hello world!");
hw();

function hw()
{
    console.log("hw ... ");
}

function printf(msg)
{
    console.log(msg + "\n");
}

/* For Test variable */
function A()
{
    var a = 10;

    printf("a = " + a);

    function C(){
        printf("b = " + b);
    }

    function B(){
        var b = 20;
        return b;
    }

    C();
    var b = B();
    C();
}

A();

printf("----------------------------------------");

function pA()
{
    function pB(){
        var pb = 10;
        return pb;
    }

    function pC(){
        var pc = 20;
        return pc;
    }

    function pD(){
        var pd = 30;
        printf("pb = " + pb);
        printf("pc = " + pc);
        return pd;
    }

    var pb = pB();
    var pc = pC();
    var pd = pD();
}

pA();

//function fun(a, b=10)     illegal !
function fun(a, b)
{
    printf("a = " + a);
    printf("b = " + b);
}

