/*
 * Progarm Name: app.js
 * Created Time: 2016-11-18 18:01:58
 * Last modified: 2016-12-09 14:49:03
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





