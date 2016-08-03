/*
 * Progarm Name: container_test.cpp
 * Created Time: 2015-11-13 07:53:08
 * Last modified: 2016-08-02 10:44:00
 * @author: minphone.linails linails@foxmail.com 
 */

#include "container_test.h"
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cstdlib>
#include <map>
#include <typeinfo>
#include <bitset>
#include <list>
#include <queue>
#include <deque>
#include <tuple>


/*c++中的标准库的包含了c标准库的头文件，
 *并且在c的头文件中添加一个c，就可以把.h去掉，内容相同*/
#include <cctype>// = #include<ctype.h> 
#include <cstdio>

using namespace std;

/*string test func*/
static void string_test(void);

/*vector test func*/
static void vector_test(void);

/*map test func*/
static void map_test(void);

/*iterator test func*/
static void iterator_test(void);

/*bitset_test func*/
static void bitset_test(void);

/*list test func*/
static void list_test(void);

/*deque test func*/
static void deque_test(void);

/*adaptor_stack_test func*/
static void adaptor_stack_test(void);

/*adaptor_queue_test func*/
static void adaptor_queue_test(void);

/*adaptor_priority_queue_test func*/
static void adaptor_priority_queue_test(void);

/*container_test func*/
void container_test(void)
{
	cout<<"container test start..."<<endl;
	string_test();

	vector_test();

    map_test();
	
	iterator_test();

	bitset_test();

    list_test();

    /*queue test func*/
    void queue_test(void);
    queue_test();

    deque_test();
    adaptor_stack_test();
    adaptor_queue_test();
    adaptor_priority_queue_test();
	cout<<"---------------------------"<<endl;
    void unordered_container(void);
    unordered_container();
}

//----------------------------------------------------------

/*string test func*/
void string_test(void)
{
	string s1;
	cout<<"s1 = "<<s1<<endl;
	cout<<"is s1 empty:"<<s1.empty()<<endl;
	string s2("s2 hello");
	cout<<"s2 = "<<s2<<endl;
	string s3(s2);
	cout<<"s3 = "<<s3<<endl;
	string s4 = "s4 hello";
	cout<<"s4 = "<<s4<<endl;
	string s5(6,'s');
	cout<<"s5 = "<<s5<<endl;
	string s6 = s2 + s4;
	cout<<"s6 = "<<s6<<endl;
	cout<<"s6[0] = "<<s6[0]<<endl;
	cout<<"s6[6] = "<<s6[6]<<endl;
	cout<<"size of s6 = "<<s6.size()<<endl;

    /*string::size_type 的类型值是string长度返回值专用的
     * 不能赋值给int变量*/
	string::size_type str_len;
	str_len = s6.size();
	cout<<"size_type of s6 = "<<str_len<<endl;
	printf("hello world\n");

	string s7("s is same");
	string s8("s is same");
	cout<<"s7 :"<<s7<<endl;
	cout<<"s8 :"<<s8<<endl;
	if(s7 == s8){
		cout<<"s7 = s8"<<endl;
	}else{
		cout<<"s7 != s8"<<endl;
	}

    string str("hello string -> c string\n");
    printf("%s",str.c_str());

	//for(int i=0;i<3;i++){
	//	cout<<"input your line:";
	//	/*getline()函数返回时会丢弃换行符*/
	//	getline(cin,s1);
	//	cout<<"get line:"<<s1<<endl;
	//}

    string ss("hello world ss");
    string *ps = NULL;
    string &rs = ss;
    ps = &ss;
    cout << "rs[1] = " << rs[1] << endl;
    cout << "(*ps)[1] = " << (*ps)[1] << endl;
    cout << "*ps = " << *ps << endl;
    const char *cs = ps->c_str();
    printf("cs = 0x%x\n%s\n",cs,cs);
    //printf("cs = 0x%x\n",reinterpret_cast<unsigned>(const_cast<char *>(cs)));
    *ps = "n89798989jkhiujkjkjihjk\
           jkjihgoieuljlkajglkjdlk\
           jkjkjkjkjkj000000000000\
           00000000000000000000000\
           00000000000000000000000\
           00000000000000000000000\
           00000000000000000000000\
           00000000000000000000000\
           00000000000000000000000\
           00000000000000000000000";
    const char *cs1 = ps->c_str(); //string内部的存储区更换了，因此返回的地址变了
    printf("cs1 = 0x%x\n",cs1);
    cout << "*ps = " << *ps << endl;

	cout<<"---------------------------"<<endl;
    string content01("name:%s,hello");
    char buf[64];
    sprintf(buf,content01.c_str(),"xiaolin");
    string content = content01 + buf;
    cout << "content :" << content << endl;

	cout<<"---------------------------"<<endl;
    {
        string sa("nice");
        string sb(sa);

        cout << "sa : " << sa << endl;
        cout << "sb : " << sb << endl;
        printf("sa addr : 0x%x - 0x%x\n",&sa,sa.c_str());
        printf("sb addr : 0x%x - 0x%x\n",&sb,sb.c_str());

        sa[0] = 'N';
        sb[0] = 'M';

        cout << "sa : " << sa << endl;
        cout << "sb : " << sb << endl;
        printf("sa addr : 0x%x - 0x%x\n",&sa,sa.c_str());
        printf("sb addr : 0x%x - 0x%x\n",&sb,sb.c_str());

        string sc = sa;
        cout << "sa : " << sa << endl;
        cout << "sc : " << sb << endl;
        printf("sa addr : 0x%x - 0x%x\n",&sa,sa.c_str());
        printf("sc addr : 0x%x - 0x%x\n",&sb,sc.c_str());

        sa[0] = 'N';
        sc[0] = 'M';

        cout << "sa : " << sa << endl;
        cout << "sc : " << sc << endl;
        printf("sa addr : 0x%x - 0x%x\n",&sa,sa.c_str());
        printf("sc addr : 0x%x - 0x%x\n",&sb,sc.c_str());
    }
	cout<<"---------------------------"<<endl;
    {
        char temp[] = "hello string!";
        char temp1[4] = {'0','1','2','4'};
        char temp2[4] = {0,1,2,4};
        string s=temp1;

        cout << "s = " << s << endl;
        cout << "s length : " << s.length() << endl;
        printf("%x%x%x%x\n",s[0],s[1],s[2],s[3]);

        string s2=temp2;

        cout << "s2 = " << s2 << endl;
        cout << "s2 length : " << s2.length() << endl;
        printf("%x%x%x%x\n",s2[0],s2[1],s2[2],s2[3]);
    }
	cout<<"---------------------------"<<endl;
    {
        string s("怅	`1`怅`2`(1)<br>悵<br>chàng<br>(2)<br>(形声。从心,长声。本义:因失意而不痛快) 同本义 ");

        string is(s.substr(0,s.find(")<br>")));
        cout << "is : " << is << endl;
        is = s.substr(0,s.find(")<br>"));
        cout << "is : " << is << endl;
        is = s.substr(s.find(")<br>"),s.find("<br>("));
        cout << "is : " << is << endl;
        is = s.substr(s.find(")<br>"),s.find("<br>("));
        cout << "is : " << is << endl;

        for(auto iter = is.begin();
                 iter!= is.end(); iter++){
            printf("%c ",*iter);
        }
        cout << endl;
    }
	cout<<"---------------------------"<<endl;
    {
        string s("(1)<br>chàng<br>(2)<br>");
        cout << "s.length() : " << s.length() << endl;

        string::size_type pos1 = s.find(")<br>");
        string::size_type pos2 = s.find("<br>(");
        printf("pos1 = %d - pos2 = %d\n",pos1,pos2);

        string is;
        is = s.substr(pos1,pos2);
        cout << "is : " << is << endl;
        cout << "is.length() : " << is.length() << endl;
    }
	cout<<"---------------------------"<<endl;
    {
        char buf[128] = {0,};
        string s("hello buffer");
        char *p = buf;

        for(auto iter = s.begin();
                 iter!= s.end(); iter++){
            *p++ = *iter;
        }
        cout << "buf : " << buf << endl;
    }
	cout<<"---------------------------"<<endl;
}

struct cell_t{
	char cell[3];
};

/*vector test func*/
void vector_test(void)
{
	/*几种初始化vector对象的方式*/
	//vector<T> v1;			vector保存类型为T的对象，默认构造函数v1为空
	//vector<T> v2(v1);		v2是v1的一个副本
	//vector<T> v3(n,i);	v3包含n个值为i的元素
	//vector<T> v4(n);		v4含有值初始化的元素的n个副本
	//
    
    /*vector 不是一种数据类型，而只是一个类模板
     * 可以用来定义任意多种数据类型
     * vector<int> & vector<string> 算数据类型*/

	/*vector is class template*/
	vector<int> v1;//定义了类型是vector<int>
	/*虽然可以对给定元素个数的vector对象预先分配内存，
     * 但更有效的方法是先初始化一个空vector对象，
	 * 然后再动态地增加元素*/
	vector<int> fvec(10);//10 elements ,each initialized to 0
	vector<string> svec;//10 elements,each an empty string
	if(fvec.empty()){
		cout<<"fvec is empty"<<endl;
	}else{
		cout<<"fvec is full"<<endl;
	}

	cout<<"sizeof svec(10):"<<svec.size()<<endl;
	//vector类型总是包括vector的元素类型
	vector<string>::size_type sv_size;
	sv_size = svec.size();
	cout<<"sizeof svec(10):"<<sv_size<<endl;
	string s1("hello");
	string s2("world");
	if(svec.empty()){
		cout<<"svec is empty"<<endl;
	}else{
		cout<<"svec is full"<<endl;
	}
	svec.push_back(s1);
	svec.push_back(s2);
	cout<<svec[0]<<endl;
	cout<<svec[1]<<endl;
	svec[1] = "niceto";
	for(vector<string>::size_type sv_len = 0;
			sv_len < svec.size();//c++程序员习惯于优先选用！=而不是<来编写循环判断条件
			sv_len++){
		cout<<"svec["<<sv_len<<"]="<<svec[sv_len]<<endl;
	}

	vector<cell_t> cell_vec(1);
	char p[4] = "你";
	cell_vec[0].cell[0] = p[0];
	cell_vec[0].cell[1] = p[1];
	cell_vec[0].cell[2] = p[2];
	printf("%.2x %.2x %.2x \n",p[0],p[1],p[2]);
	printf("%.2x %.2x %.2x \n",cell_vec[0].cell[0],cell_vec[0].cell[1],cell_vec[0].cell[2]);
	cout<<"cell_vec size : "<<cell_vec.size()<<endl;
	cout<<"cell_vec length : "<<sizeof(cell_vec[0])<<endl;

	char p1[4] = "是";
	cell_t c1;
	c1.cell[0] = p1[0];
	c1.cell[1] = p1[1];
	c1.cell[2] = p1[2];
	cell_vec.push_back(c1);
	cout<<"cell_vec size : "<<cell_vec.size()<<endl;

    vector<int>::iterator iter_int;
    vector<int> vint(10);
    for(vector<int>::iterator iter_int = vint.begin();
            iter_int != vint.end();
            ++iter_int){
        *iter_int = 0;
    }
    /* 两个类比如下
     * vector<int>::const_iterator  和 const vector<int>::iterator
     * int const *p                 和  int * const p
     * */
    for(vector<int>::const_iterator coniter_int = vint.begin();
            coniter_int != vint.end();
            ++coniter_int){
        cout << *coniter_int << endl;
    }


    //-----------------------------------------
    vector<cell_t> vcell;

    c1.cell[0] = 0x01;
    c1.cell[1] = 0x02;
    c1.cell[2] = 0x03;
    vcell.push_back(c1);
    c1.cell[0] = 0x04;
    c1.cell[1] = 0x05;
    c1.cell[2] = 0x06;
    vcell.push_back(c1);

    for(vector<cell_t>::const_iterator coniter_cell = vcell.begin();
            coniter_cell != vcell.end();
            ++coniter_cell){
        printf("cell[0] = 0x%.2x,cell[1] = 0x%.2x,cell[2] = 0x%.2x\n",
               coniter_cell->cell[0],coniter_cell->cell[1],coniter_cell->cell[2]);
               //coniter_cell[0].cell[0],coniter_cell[0].cell[1],coniter_cell[0].cell[2]);
    }

    for(vector<cell_t>::size_type vcellsize = vcell.size();
            vcellsize>0;
            vcellsize--){
        
        printf("cell[0] = 0x%.2x,cell[1] = 0x%.2x,cell[2] = 0x%.2x\n",
               vcell[vcellsize-1].cell[0],vcell[vcellsize-1].cell[1],vcell[vcellsize-1].cell[2]);
    }

	cout<<"---------------------------"<<endl;
    vector<char *> pcvec;
    char *cp0 = (char *)0x01;
    pcvec.push_back(cp0);
    printf("pcvec :%d\n",pcvec[0]);

	cout<<"---------------------------"<<endl;
    const vector<int> cvi(10);
    /* 新定义的时候，vector内分配的内存的容量是指定数量，并没有扩大
     * 只有做了push_back()的操作后，vector的容量会扩大*/
    vector<int> ncvi(10);
    //cvi[0] = 10;
    //cvi.push_back();
    cout << "const vector size :" << cvi.size() << endl;
    cout << "const vector capacity :" << cvi.capacity() << endl;
    cout << "const vector max size :" << cvi.max_size() << endl;
    ncvi.push_back(11);
    cout << "vector size :" << ncvi.size() << endl;
    cout << "vector capacity :" << ncvi.capacity() << endl;
    cout << "vector max size :" << ncvi.max_size() << endl;
//    cvi.push_back(11);

	cout<<"---------------------------"<<endl;

    vector<float> flvec;
    flvec.push_back(0.1234);
    flvec.push_back(1.2343);
    flvec.push_back(-0.3445);

    cout << "flvec[0] = " << flvec[0] << endl;
    cout << "flvec[1] = " << flvec[1] << endl;
    cout << "flvec[2] = " << flvec[2] << endl;

    vector<float> flvec2;
    flvec2 = flvec;
    cout << "flvec2[0] = " << flvec2[0] << endl;
    cout << "flvec2[1] = " << flvec2[1] << endl;
    cout << "flvec2[2] = " << flvec2[2] << endl;

    vector<vector<float> *> parry_vec;
    parry_vec.push_back(&flvec);
    parry_vec.push_back(&flvec2);

    cout << "parry_vec[0][0] = " << (*parry_vec[0])[0] << endl;
    cout << "parry_vec[0][1] = " << (*parry_vec[0])[1] << endl;
    cout << "parry_vec[0][2] = " << (*parry_vec[0])[2] << endl;

	cout<<"---------------------------"<<endl;
    {
        vector<unsigned char> ucvec;
        ucvec.push_back(0x01);
        ucvec.push_back(0x02);
        ucvec.push_back(0x03);
        ucvec.push_back(0x04);

        for(int i=0; i<ucvec.size(); i++){
            printf("ucvec[%d] = 0x%.2x \n",i,ucvec[i]);
        }
    }
	cout<<"---------------------------"<<endl;
    {
        vector<unsigned char> ucvec;
        vector<unsigned char>::iterator iter;
        ucvec.push_back(0x03);
        iter = ucvec.begin();

        printf("*iter = 0x%.2x\n",*iter);

        vector<unsigned char>::const_iterator iter2;
        iter2 = ucvec.begin();

        printf("*const_iterator = 0x%.2x\n",*iter);
    }
	cout<<"---------------------------"<<endl;

}

/*map test func*/
void map_test(void)
{
    string s1("s1"),s2("s2"),sv1("123"),sv2("423");
    map<string ,string> map_is;
    if(map_is.empty()){
        cout << "map_is is empty" << endl;
    }
    map_is.insert(map<string,string>::value_type(s1,sv1));
    map_is.insert(map<string,string>::value_type(s2,sv2));

#if 0
    if(!map_is.empty()){
        cout << "map size() : " << map_is.size() << endl;
        map<string,string>::const_iterator map_it = map_is.begin();
        cout << "map :" << map_it->first << " - " << map_it->second << endl;
        map_is.erase(map_it);
        cout << "map size() : " << map_is.size() << endl;

        map_it = map_is.begin();
        cout << "map :" << map_it->first << " - " << map_it->second << endl;
        map_is.erase(map_it);
        cout << "map size() : " << map_is.size() << endl;
    }
#endif


    pair<string,string> p1("p1","123"),p2("p2","234");

    map<string,pair<string,string> > map_sm;
    if(map_sm.empty()){
        cout << "map_sm is empty " << endl;
    }
#if 0
    map_sm.insert(map<string,pair<string,string> >::value_type("name",p1));
    map_sm.insert(map<string,pair<string,string> >::value_type("addr",p2));
#else 
    map_sm.insert(map<string,pair<string,string> >::value_type("name",make_pair("p1","123")));
    map_sm.insert(map<string,pair<string,string> >::value_type("addr",make_pair("p2","234")));
#endif

    if(!map_sm.empty()){
        cout << "map_sm size :" << map_sm.size() << endl;
        //map<string,pair<string,string> >::const_iterator map_sm_it = map_sm.begin();
        auto map_sm_it = map_sm.begin();

        if(map_sm_it->first == "name"){
            cout << "cmp map_sm_it->first is ok , is name" << endl;
        }else if(map_sm_it->first == "addr"){
            cout << "cmp map_sm_it->first is ok , is addr" << endl;
        }

        cout << "map : " << map_sm_it->first << " - (" 
            << map_sm_it->second.first << "," << map_sm_it->second.second << ")" << endl; 
        map_sm.erase(map_sm_it);
        cout << "map_sm size :" << map_sm.size() << endl;

        map_sm_it = map_sm.begin();
        cout << "map : " << map_sm_it->first << " - (" 
            << map_sm_it->second.first << "," << map_sm_it->second.second << ")" << endl; 
        map_sm.erase(map_sm_it);
        cout << "map_sm size :" << map_sm.size() << endl;
    }

    cout<<"---------------------------"<<endl;

    typedef union{
        int a;
        struct{
            char b;
            char c;
        };
    }udata_t;
    udata_t ud1;
    ud1.a = 10;

    pair<bool,udata_t> pair01(true,ud1);
    if(pair01.first == true){
        cout << "ud1 = " << pair01.second.a << endl;
    }

	cout<<"---------------------------"<<endl;
    map<int,int> m_nc;
    m_nc.insert(map<int,int>::value_type(make_pair(10,20)));
    const map<int ,int> m_c(m_nc);
    cout << "sizeof const map<int,int> :" << sizeof(m_c) << endl;
    cout << "const map<int,int> size :" << m_c.size() << endl;
    //auto iter_mc = m_c.begin();
    map<int,int>::const_iterator iter_mc = m_c.begin();
    //iter_mc->second = 21; //-->false
    cout << "m_c[10] = " << iter_mc->second << endl;

    map<string,int> m_nsi;
    m_nsi.insert(map<string,int>::value_type("hello",15));
    const map<string,int> m_ncsi(m_nsi);
    cout << "sizeof const map<string,int> :" << sizeof(m_nsi) << endl;
    cout << "const map<string,int> size :" << m_nsi.size() << endl;
    auto iter_mncsi = m_ncsi.begin();
    //iter_mncsi->first += "nice"; //-->false
    //iter_mncsi->second = 21; //-->false
    cout << "m_nsi.first :" << iter_mncsi->first  << iter_mncsi->second << endl;
    auto iter_mnsi = m_nsi.begin();
    iter_mnsi->second = 20;

    map<string,string> m_nss;
    m_nss.insert(map<string,string>::value_type("name","lin"));
    //m_nss["name"] = "ming"; //-->can work
    const map<string,string> m_cnss(m_nss);
    cout << "sizeof const map<string,string> :" << sizeof(m_cnss) << endl;
    cout << "const map<string,string> size :" << m_cnss.size() << endl;
    auto iter_mcnss = m_cnss.begin();
    cout << "typeid : iter_mcnss :" << typeid(iter_mcnss).name() << endl;
    auto iter_mnss = m_nss.begin();
    cout << "typeid : iter_mnss :" << typeid(iter_mnss).name() << endl;
    //m_cnss["name"] = "ming"; //-->false


	cout<<"---------------------------"<<endl;
    map<int,vector<int> > m_iv;
    vector<int> iv;
    m_iv.insert(map<int,vector<int> >::value_type(1,iv));
    m_iv.insert(map<int,vector<int> >::value_type(2,iv));
    m_iv.insert(map<int,vector<int> >::value_type(3,iv));

    iv.push_back(10);
    iv.push_back(11);
    iv.push_back(12);

    int i=12;
    for(auto iter_miv = m_iv.begin();
            iter_miv != m_iv.end(); iter_miv++){
        iter_miv->second.push_back(i++);
        iter_miv->second.push_back(i++);
        iter_miv->second.push_back(i++);
    }

    if(!m_iv.empty()){
        for(auto iter_miv = m_iv.begin();
                iter_miv != m_iv.end(); iter_miv++){
            cout << "map[" << iter_miv->first << "]" ;
            cout << " -> vector size :" << iter_miv->second.size() << " vals :"; 
            cout << " " << iter_miv->second[0];
            cout << " " << iter_miv->second[1];
            cout << " " << iter_miv->second[2] << endl;
        }
    }


	cout<<"---------------------------"<<endl;
    {

    map<int,int> iimap;
    iimap.insert(make_pair(2,4));
    auto iter = iimap.begin();
    cout << "iimap.first : " << iter->first << endl;
    }

    {
    bitset<20> b("1");

    vector<bitset<20>> bitvec;
    bitvec.push_back(b);

    map<bitset<20>*,int> bitmap;
    bitmap.insert(make_pair(&bitvec[0],3));

    auto iter = bitmap.begin();
    cout << "*bitmap->first = " << *iter->first << " bitmap->second = " << iter->second << endl;
    }
	cout<<"---------------------------"<<endl;
    {
        map<int,string> ismap;
        
        ismap.insert(map<int,string>::value_type(1,"nice"));
        ismap.insert(map<int,string>::value_type(2,"hello"));
        ismap.insert(map<int,string>::value_type(3,"you"));

        cout << "ismap[1] : " << ismap[1] << endl;




        bitset<20> b("1");
        vector<bitset<20> > bitvec;
        bitvec.push_back(b<<0);
        bitvec.push_back(b<<1);
        bitvec.push_back(b<<2);

        map<vector<bitset<20> >::size_type,string> bsmap;

        bsmap.insert(map<vector<bitset<20> >::size_type,string>::value_type(0,"first bitset"));
        bsmap.insert(map<vector<bitset<20> >::size_type,string>::value_type(1,"second bitset"));
        bsmap.insert(map<vector<bitset<20> >::size_type,string>::value_type(2,"third bitset"));

        cout << "bsmap[0] : " << bsmap[0] << endl;
        auto iter = bsmap.find(2);
        cout << "bsmap[2] : " << iter->second << endl;
        auto niter = bsmap.find(3);
        auto end = bsmap.end();
        auto begin = bsmap.begin();

        printf("begin : 0x%x\n",begin);
        printf("niter : 0x%x\n",niter);
        printf("end : 0x%x\n",end);

        if(niter != end){
            cout << "niter is exist" << endl;
        }else{
            cout << "niter is NULL" << endl;
        }

    }
	cout<<"---------------------------"<<endl;
    {
        map<pair<float,float>,float> mfff;
        mfff.insert(make_pair(make_pair(0.0001,0.0002),0.0001));
        mfff.insert(make_pair(make_pair(0.0002,0.0002),0.0001));
        mfff.insert(make_pair(make_pair(0.0003,0.0002),0.0001));

        for(auto iter = mfff.begin();
                 iter!= mfff.end(); iter++){
            cout << "map<pair<float,float>,float> : " << iter->first.first << " " << iter->first.second
                 << " " << iter->second << endl;
        }
        /*此用法错误*/
        //cout << map[(0.0001,0.0002)] << endl;
    }
	cout<<"---------------------------"<<endl;
}

/*标准库为每一种标准容器定义了一种迭代器类型，所有的标准库容器都定义了相应的迭代器类型，
 *而只有少数的容器支持下标操作*/
/*iterator test func*/
void iterator_test(void)
{
	/*每个标准库容器类型都定义了一个名为iterator的成员*/
    vector<int>::iterator iter;
    vector<int> ivec(4,1);
    ivec[1] = 2;
    ivec[2] = 3;
    ivec[3] = 4;
    iter = ivec.begin();
    cout<<"iter = "<<*iter<<endl;
    iter++;
    cout<<"iter = "<<*iter<<endl;

	/*语句的定义必然是分号
	 * 因此for(int i=0,int b=0;i<10;i++)是错误的*/
	int i = 0;
	for(vector<int>::iterator index = ivec.begin(); index != ivec.end(); index++,i++)
		*index = i ;
	/*const_iterator 是只读的，不可以进行改变其容器的值*/
	for(vector<int>::const_iterator index = ivec.begin(); index != ivec.end(); index++){
		cout<<"index = "<<*index<<endl;
	}
	/*任何改变vector长度的操作都会使已存在的迭代器失效*/

	cout<<"---------------------------"<<endl;

    {
        vector<int> ivec;
        ivec.push_back(1);
        ivec.push_back(2);
        ivec.push_back(3);

        vector<int>::iterator iter = ivec.begin();
        vector<int>::iterator end = ivec.end();

        printf("iter = 0x%x\n",iter);
        printf("end = 0x%x\n",end);

        if(iter != end){
            cout << "iter != end" << endl;
        }
    }

	cout<<"---------------------------"<<endl;
    {
        vector<int> ivec;
        ivec.push_back(1);
        ivec.push_back(2);

        cout << "ivec.size : " << ivec.size() << endl;
        for(auto iter = ivec.begin();
                 iter!= ivec.end(); iter++){
            printf("iter : 0x%x - *iter = %d\n",iter,*iter);
        }

        //ivec.insert();
    }
	cout<<"---------------------------"<<endl;
    /*
     * for vector<>
     *
     * reference at(int pos); 返回pos位置元素的引用
     * reference front();返回首元素的引用
     * reference back();返回尾元素的引用
     * iterator begin();返回向量头指针，指向第一个元素
     * iterator end();返回向量尾指针，不包括最后一个元素，在其下面
     * reverse_iterator rbegin();反向迭代器，最后一个元素迭代指针
     * reverse_iterator rend();反向迭代器，第一个元素之前的迭代指针
     * */
	cout<<"---------------------------"<<endl;
}

/*bitset_test func*/
void bitset_test(void){
	/*几种初始化bitset对象的方法*/
	//bitset<n> b;			b有n位，每位都为0
	//bitset<n> b(u);		b是unsigned long型u的一个副本
	//bitset<n> b(s);		b是string对象s中含有的位串的副本
	//bitset<n> b(s,pos,n);	b是s中从位置pos开始的n个位的副本

	cout<<"-------------- bitset_test -------------"<<endl;

    {
        bitset<20> b(1);
        cout << "b = 0b" << b.to_string() << endl;
        bitset<20> c(~b);
        cout << "c = 0b" << c.to_string() << endl;
#if 0
        /*这种定义是错误的，不能定义！操作*/
        bitset<20> d(!b);
        cout << "d = 0b" << d.to_string() << endl;
#endif
    }
    cout << "-----------------------------------------" << endl;
    {
        bitset<20> b(0x0101);
        cout << "b = 0b" << b.to_string() << endl;
        cout << "count : " << b.count() << endl;
        b.reset();
        cout << "b = 0b" << b.to_string() << endl;
        cout << "count : " << b.count() << endl;
        bitset<20> c(0x3171);
        cout << "c = 0b" << c.to_string() << endl;
        cout << "count : " << c.count() << endl;
        bitset<10> d(0x00);
        bitset<5> e(0x0f);
        cout << "d = 0b" << d.to_string() << endl;
        //cout << "d|e = 0b" << d.to_string() << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
        bitset<10> b(0x00);
        if(b.any()){
            cout << "true" << endl;
            cout << "b = 0b" << b.to_string() << endl;
        }else{
            cout << "false" << endl;
            cout << "b = 0b" << b.to_string() << endl;
        }
        b |= 0x01;
        if(b.any()){
            cout << "true" << endl;
            cout << "b = 0b" << b.to_string() << endl;
        }else{
            cout << "false" << endl;
            cout << "b = 0b" << b.to_string() << endl;
        }
        b ^= 0x01;
        if(b.any()){
            cout << "true" << endl;
            cout << "b = 0b" << b.to_string() << endl;
        }else{
            cout << "false" << endl;
            cout << "b = 0b" << b.to_string() << endl;
        }
        if(b.none()){
            cout << "b is none" << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    {
        bitset<10> b1(0x01);
        bitset<10> b2(0x02);
        pair<bitset<10>,bitset<10> > pair1(b1,b2);
        cout << "pair1<b1,b2> : " << pair1.first.to_string() << " - " << pair1.second.to_string() << endl;

        pair<bitset<10>,bitset<10> > pair2(0x02,0x04);
        cout << "pair2<b1,b2> : " << pair2.first.to_string() << " - " << pair2.second.to_string() << endl;
        pair2.first |= 0x08;
        pair2.second |= 0x08;
        cout << "pair2<b1,b2> : " << pair2.first.to_string() << " - " << pair2.second.to_string() << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
        bitset<10> b1(0x03);
        bitset<10> b2(0x07);
        bitset<10> b3;

        b3 = ~(b1 | ~b2);
        cout << "b1 = 0b" << b1.to_string() << endl;
        cout << "b2 = 0b" << b2.to_string() << endl;
        cout << "b3 = 0b" << b3.to_string() << endl;

        b1 = 0x05;
        b2 = 0x77;
        b3 = ~(b1 | ~b2);
        cout << "b1 = 0b" << b1.to_string() << endl;
        cout << "b2 = 0b" << b2.to_string() << endl;
        cout << "b3 = 0b" << b3.to_string() << endl;

        if(b1 == b2){
            cout << "b1 = b2" << endl;
        }else{
            cout << "b1 != b2" << endl;
        }

        b2 = 0x05;
        if(b1 == b2){
            cout << "b1 = b2" << endl;
        }else{
            cout << "b1 != b2" << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    {
        vector<pair<pair<bitset<10>,bitset<10> >,float> > vb;

        vb.push_back(make_pair(make_pair(0x01,0x02),0.0001));
        vb.push_back(make_pair(make_pair(0x01,0x03),0.0001));
        vb.push_back(make_pair(make_pair(0x01,0x04),0.0001));

        for(auto iter = vb.begin();
                 iter!= vb.end(); iter++){
            cout << "vb : " << iter->first.first.to_string() << " "
                 << iter->first.second.to_string() << " "
                 << iter->second << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    {
        bitset<10> b1;
        cout << "b1 = " << b1.to_string() << endl;
        b1 = 0x01 << 0;
        cout << "0x01 << 0 ; b1 = " << b1.to_string() << endl;
        b1 = 0x01 << 1;
        cout << "0x01 << 1 ; b1 = " << b1.to_string() << endl;
        b1 = 0x01 << 4;
        cout << "0x01 << 4 ; b1 = " << b1.to_string() << endl;

        bitset<10> b2(0xf0);
        cout << "b2 : " << b2.to_string() << endl;

        if((b1 & b2) == b1){
            cout << "b1 exist" << endl;
        }
    }
}

/*list test func*/
void list_test(void)
{
    cout << "------------- list test -------------" << endl;
    {
        list<int> ilist;
        ilist.push_back(1);
        ilist.push_back(2);

        for(auto iter = ilist.begin();
                 iter!= ilist.end(); iter++){
            cout << "ilist : " << *iter << endl;
        }

        list<string> slist;
        slist.push_back("hello 01");
        slist.push_back("hello 02");
        slist.push_back("hello 03");
        slist.push_back("hello 04");
        slist.push_back("hello 05");

        /* 此种写法不行
        auto begin = slist.begin();
        cout << "slist[3] = " << *(begin+2) << endl;
         * */

        auto begin = slist.begin();
        begin++;
        auto begin2 = slist.begin();
        begin2++;

        auto begin3 = begin2;

        if(begin == begin2) cout << "begin = begin2" << endl;
        if(begin3 == begin) cout << "begin = begin3" << " *begin3 = " << *begin3 << endl;
    }
}

/*queue test func*/
void queue_test(void)
{
    cout << "------------- queue test -------------" << endl;
}

/*deque test func*/
void deque_test(void)
{
    cout << "------------- deque test -------------" << endl;
    {
        deque<char> cd;
        cd.push_back(0x01);
        cd.push_back(0x02);
        cd.push_back(0x03);

        do{
            if(cd.empty() == false){
                char &c = cd.front();
                printf("pop : 0x%.2x\n",c);
                cd.pop_front();
            }
        }while(cd.empty() == false);
    }
    cout << "--------------------------------------" << endl;
    {
        struct demo{
            char a;
            int b;
            int c;
        };
        deque<struct demo> sdd;

        struct demo d1 = {0x01,1,2};
        struct demo d2 = {0x02,3,4};
        struct demo d3 = {0x03,4,5};
        sdd.push_back(d1);
        sdd.push_back(d2);
        sdd.push_back(d3);

        do{
            if(sdd.empty() == false){
                struct demo &tmp = sdd.front();

                printf("tmp.a : 0x%.2x\n",tmp.a);
                printf("tmp.b : %d\n",tmp.b);
                printf("tmp.c : %d\n",tmp.c);
                sdd.pop_front();
            }
        }while(sdd.empty() == false);
    }
}

//-----------------adaptor---------------------------------
//适配器是个通用概念，包含：容器适配器、迭代器适配器、函数适配器

/*adaptor_stack_test func*/
void adaptor_stack_test(void)
{
}

/*adaptor_queue_test func*/
void adaptor_queue_test(void)
{
}

/*adaptor_priority_queue_test func*/
void adaptor_priority_queue_test(void)
{
}

//----------------- unordered-container ---------------------------------

#include <unordered_map>

struct key{
    string first;
    string second;
};

struct keyhash{
    size_t operator()(const key& k) const
    {
        size_t ret = (hash<string>()(k.first) ^ (hash<string>()(k.second) << 1));
        cout << "size_t : " << ret << endl;
        return ret;
    }
};

struct keyequal{
    bool operator()(const key& lhs, const key& rhs) const
    {
        bool ret =  lhs.first == rhs.first && lhs.second == rhs.second;
        cout << "operator() : " << ret << endl;
        return ret;
    }
};

void unordered_container(void)
{
    /* 1.map和set内部是红黑树，在插入元素时会自动排序
     * 2.unordered_container内部是散列表(Hash Table),通过哈希(Hash),
     *   而不是排序来快速操作元素，使得效率更高*/
    cout << "func : " << __FUNCTION__ << endl;
    {
        unordered_map<string, string> m1;
        cout << "m1.size : " << m1.size() << endl;
    }
    cout << "---------------------------" << endl;
    {
        /* 对于基本类型，不需要提供hash函数和比较函数 
         * 和map/set一样*/
        unordered_map<int, string> m2 = {
            {1, "foo"},
            {2, "bar"},
            {3, "baz"}
        };
        cout << "m2.size : " << m2.size() << endl;
        
        for(auto iter = m2.begin(); 
                 iter!= m2.end(); iter++){
            cout << "iter->first : " << iter->first;
            cout << " - second : "  << iter->second << endl;
        }
        for(auto n : m2){
            cout << "n.first : " << n.first;
            cout << " - second : "  << n.second << endl;
        }

        unordered_map<int, string> m4 = move(m2);
        cout << "m4.size() : " << m4.size() << endl;
        cout << "m2.size() : " << m2.size() << endl;
    }
    cout << "---------------------------" << endl;
    {
        vector<pair<bitset<8>, int> >v = {
            {0x12, 1},
            {0x01,-1}
        };
        unordered_map<bitset<8>, double> m5(v.begin(), v.end());

        for(auto n : m5){
            printf("n.first : 0x%.2x , second : %f\n",n.first, n.second);
        }
    }
    cout << "---------------------------" << endl;
    {
        unordered_map<key, string, keyhash, keyequal> m6 = {
            {{"John", "Doe"}, "example"},
            {{"Mary", "Sue"}, "another"}
        };

        cout << "m6.size() : " << m6.size() << endl;
        for(auto n : m6){
            cout << "n.first.first : " << n.first.first << " n.first.second : " << n.first.second << endl;
        }
    }
    cout << "---------------------------" << endl;
    {
        unordered_map<int, string> m2 = {
            {1, "foo"},
            {2, "bar"},
            {3, "baz"}
        };

        cout << "m2.size() : " << m2.size() << endl;
        m2.clear();
        cout << "m2.size() : " << m2.size() << endl;

        cout << "insert : " << m2.insert(unordered_map<int, string>::value_type(1, "one")).second << endl;
        cout << "insert : " << m2.insert(unordered_map<int, string>::value_type(1, "ones")).second << endl;
        m2.insert(unordered_map<int, string>::value_type(2, "sec"));
        m2.insert(unordered_map<int, string>::value_type(3, "thi"));

        for(auto &u : m2){
            cout << u.first << " - " << u.second << endl;
        }
    }
    cout << "---------------------------" << endl;
    {
        unordered_map<int, tuple<int, string> > um;

        um.insert(unordered_map<int, tuple<int, string> >::value_type(1, make_tuple(1, "first")));

        cout << "um.size() : " << um.size() << endl;
    }
}


