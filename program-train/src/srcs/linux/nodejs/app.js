/*
 * Progarm Name: app.js
 * Created Time: 2016-11-18 18:01:58
 * Last modified: 2016-12-13 14:17:06
 * @author: minphone.linails linails@foxmail.com 
 */

function printf(msg)
{
    console.log(msg + "\n");
}

function draw(data)
{
    printf("data = " + data);
}

d = [1, 2, 3, 4, 5, 6, 7, 8];

draw(d);

d[0] = 10

draw(d);

function callback()
{
    printf("I'm callback ...");
}

function do_cb(cb)
{
    printf("I'm do_cb ...");
    cb();
}

do_cb(callback);

printf("------------------------------------------------------------");

function jsmap()
{
    /* 
     * map() 方法返回一个由原数组中的每个元素调用一个指定方法后的返回值组成的新数组
     * */

    /*
    var a = map.call("Hello world", function(x){ return x.charCodeAt(0); });
    printf("a = " + a);
     * */

    var blok = {
        "coo":1,
        "rou":2,
        "end":3
    }

    printf("blok" + blok);
    //printf("blok + " + JSONstringify(blok));

    tf = ["coo", "rou", "end"].map(function(d){
        return {type:d , device:blok[d]};
    });

    printf("tf.coo" + tf.coo);
}

jsmap();




