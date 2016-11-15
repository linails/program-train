# readme.txt
# Created Time: 2016-11-14 10:08:33
# Last modified: 2016-11-14 17:50:45
#

1. 注释
   <!xxx>
2. 引用外部脚本
   使用 SCRIPT 标记符的 SRC 属性来指定外部文件
   这种方式下，浏览器只使用在外部文件中的脚本，并忽略了任何位于 SCRIPT 标记符之间的脚本
3. 为了防止所有格式控制符被当作空格，需要使用预格式化标记<PRE>
4. javascript 未定义的变量自动作为全局变量
5. === 严格等于 , 此运算符先不进行类型转换再测试是否相等
   !== 严格不等于 , 不进行类型转换直接测试是否相等
   >>> 无符号右移
6. typeof 运算符返回表示操作数类型的字符串值，eg  typeof true 返回 boolean
7. 
   /* 其他程序结构均同C语言 */
   with(object)
      statement;
   for(variable in object){
      statement;
   }
8. 七个全局函数
   escape()     : 参数指定的字符串中的所有非字母字符被替换成以xx%表示的等价数字
   eval()       : 将通过参数传入的一个包含JavaScript语句的字符串作为一个js源代码执行 , 返回执行 JavaScript 语句的返回值
   isFinite()   : 用于确定一个变量是否有界，如果有界返回true，否则返回false
   isNaN()      :
   parseFloat() : 将字符串开头的整数或浮点数分解出来，若字符串不是以数字开头，则返回NaN
   parseInt()   : 同上
   unescape()   : 与escape相反
9. javascript 中分别包含两个运算符和两条语句，专门用于对象操作，分别是
   1> new 语句      : 实例化对象
   2> delete 语句   : 从对象中删除属性或方法或从数组中删除元素
   3> with 语句
   4> for in 语句   : 用于遍历一个对象中的所有属性



