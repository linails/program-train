/*
 * Progarm Name: formatParsing.cpp
 * Created Time: 2016-05-15 12:14:11
 * Last modified: 2016-12-15 22:56:53
 * @author: minphone.linails linails@foxmail.com 
 */

#include "formatParsing.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>
#include "regex_common.h"

using namespace std;

//---------------------------------------------------------

int formatPrint(string fname,string line)
{
    int ret = 0;

    formatTool ftool(fname,line);

    return ret;
}

/*
 亶1
    `1` 亶1 `2`dǎn
    <br>(1)
        <br>(形声。本义:谷多)
    <br>(2)
        <br>同本义 [full of grains]
        <br>亶,多谷也。――《说文》
        <br>择三有事,亶侯多藏。――《诗·小雅·十月之交》
    <br>(3)
        <br>厚道;忠实 [kind and sincere]
        <br>亶,信也;又,诚也。――《尔雅》
        <br>不实于亶。――《诗·大雅·板》
    <br>(4)
        <br>又如:亶厚(忠厚,淳厚);亶诚(真诚)
    <br>(5)
        <br>平坦;广大 [smooth]。如:亶亶(平坦。通“坦坦”)
    <br>(6)
        <br>姓
 亶2	
    `1` 亶2 `2`dàn
    <br>通“但”。仅,只 [only]
    <br>非亶倒县(悬)而已。――《汉书·贾谊传》
    <br>另见 dǎn

 伡	
    `1`伡`2`
        (1)
        <br>俥
        <br>chē
    <br>
        (2)
        <br>――用于“大伡”。见“大车”

 怅	
    `1`怅`2`
        (1)
        <br>悵
        <br>chàng
    <br>
        (2)
        <br>(形声。从心,长声。本义:因失意而不痛快) 同本义 [disappointed]
        <br>恨,望恨也。――《说文》
        <br>陈涉少时,尝与人佣耕,辍耕之垄上,怅恨久之:“苟富贵,无相忘。”――《史记·陈涉世家》
        <br>怅寥廓,向苍茫大地,谁主沉浮。――毛泽东《沁园春·长沙》
    <br>
        (3)
        <br>又如:惆怅(伤感;失意);怅况(恍惚);怅触(惆怅感触)

 * */

/*format parsing for xinhuazidian*/
void formatTool::formatParsing_xhzd(string &s)
{
    cout << "s : " << s << endl;
    cout << "s.length() : " << s.length() << endl;
    cout << "sizeof(WordCell_t) : " << sizeof(WordCell_t) << endl;

    regex_common_c0x("^[^`]{0,5}", s, this->m_wc.word);

    regex_common_c0x("`\\d`[^<]{0,4}", s, this->m_wc.attr);

    vector<string> units;
    vector<string> subunits;
    regex_common_c0x("(\\(\\d\\)){1}.+?(?=>\\(\\d\\))|\\(\\d\\).*", s, units);
    for(auto iter = units.begin();
             iter!= units.end(); iter++){
        regex_common_c0x("<br>[^<]+", *iter, subunits);
        if(false == subunits.empty()){
            for(auto iiter = subunits.begin();
                     iiter!= subunits.end(); iiter++){
                iiter->erase(0, iiter->find_first_not_of("<br>"));
            }
            this->m_wc.contents.push_back(subunits);
        }
        subunits.clear();
    }

#if 1
    cout << "print wc info" << endl;
    cout << "word : " << this->m_wc.word << endl;
    for(auto iter = this->m_wc.attr.begin();
             iter!= this->m_wc.attr.end(); iter++){
        cout << "attr : " << *iter << endl;
    }
    for(auto iter = this->m_wc.contents.begin();
             iter!= this->m_wc.contents.end(); iter++){
        cout << "   -------" << endl;
        for(auto iiter = iter->begin();
                 iiter!= iter->end(); iiter++){
            cout << "contents : " << *iiter << endl;
        }
    }
#endif

}

/*
 * 佹得佹失 
 * </font><font size=5 color=red>佹得佹失
 * <br></font><font size=3 color=green>guǐ  dé  guǐ  shī<br>
 * <br><font size=3 color=blue>【解释】佹：出于偶然的。指得失出于偶然。
 * <br><font size=3 color=black>【出处】《列子·力命》：“佹佹成者，俏成者也，初非成也。佹佹败者，俏败者也，初非败也。”
 * <br><font size=3 color=brown>【示例】
 * <br><font size=3 color=yellow>【拼音码】gdgs
 * <br><font size=3 color=blue>【近义词】有得有失<br>【反义词】
 * <br><font size=3 color=red>【歇后语】<br>【灯谜面】
 * <br><font size=3 color=green>【用法】联合式；作谓语；指得失出于偶然
 * <br><font size=3 color=purple>【英文】<br>【故事】\n
 *
 * 偭规错矩	
 * </font><font size=5 color=red>偭规错矩
 * <br></font><font size=3 color=green>miǎn  guī  cuò  jǔ<br> 
 * <br><font size=3 color=blue>【解释】偭：违背；规、矩：标准、法则和习惯。指违背改变正常的法则
 * <br><font size=3 color=black>【出处】战国·楚·屈原《楚辞·离骚》：“固时俗之工巧兮，偭规矩而改错。”
 * <br><font size=3 color=brown>【示例】清·薛福成《分别教案治本治标之计疏》：“西洋习俗如此，教士～，亦犹中国僧道之不能尽守戒律。”
 * <br><font size=3 color=yellow>【拼音码】mgcj
 * <br><font size=3 color=blue>【近义词】<br>【反义词】
 * <br><font size=3 color=red>【歇后语】<br>【灯谜面】
 * <br><font size=3 color=green>【用法】联合式；作谓语、定语；含贬义
 * <br><font size=3 color=purple>【英文】<br>【故事】\n
 *
 * 舐犊情深	
 * </font><font size=5 color=red>舐犊情深
 * <br></font><font size=3 color=green>shì  dú  qíng  shēn 
 * <br> <br><font size=3 color=blue>【解释】比喻对子女的慈爱。
 * <br><font size=3 color=black>【出处】《后汉书·杨彪传》：“犹怀老牛舐犊之爱。”
 * <br><font size=3 color=brown>【示例】
 * <br><font size=3 color=yellow>【拼音码】sdqs
 * <br><font size=3 color=blue>【近义词】舐犊之爱<br>【反义词】
 * <br><font size=3 color=red>【歇后语】<br>【灯谜面】
 * <br><font size=3 color=green>【用法】联合式；作谓语、定语；含褒义
 * <br><font size=3 color=purple>【英文】parently love<br>【故事】东汉末年，曹操进攻刘备，在斜谷界口驻扎，陷于进退两难境地，部将夏侯淳询问夜间口令，曹操随口说鸡肋。杨修认为是曹操退兵的意思，叫士兵打点行装，曹操借口杀了杨修。后见到骨瘦如柴的杨修父亲杨彪，问为何？杨彪说有舐犊之爱\n
 *
 * */

/*format parsing for chengyucidian*/
void formatTool::formatParsing_cycd(string &s)
{
}

/*format parsing for chengyucidiandaquan*/
void formatTool::formatParsing_hycddq(string &s)
{
}

/*format parsing for hanyutongyicifanyicicidian*/
void formatTool::formatParsing_hytycfyccd(string &s)
{
}

/* 
 * “左”倾机会主义	<font size=+2 color="red">[“左”倾机会主义]</font>zuǒqīnɡjīhuìzhǔyì见627页〖机会主义〗。\n
 *
 * 一下	<font size=+2 color="red">[一下]</font>yīxià(～儿)①<font size=+1 color="green">数</font>量词。用在动词后面，表示做一次或试着做：看～儿｜打听～｜研究～。②<font size=+1 color="green">副</font>表示短暂的时间：灯～儿又亮了｜这天气，～冷，～热。‖也说一下子。\n
 * */

/*format parsing for xiandaihanyucidian*/
void formatTool::formatParsing_xdhycd(string &s)
{
}

//---------------------------------------------------------

const char *formatTool::fnameList[] = {
    "cycd.txt",
    "hycddq.txt",
    "hytycfyccd.txt",
    "xdhycd.txt",
    "xhzd.txt"
};

void (formatTool::* formatTool::formatParsingList[])(string &) = {
    &formatTool::formatParsing_cycd,
    &formatTool::formatParsing_hycddq,
    &formatTool::formatParsing_hytycfyccd,
    &formatTool::formatParsing_xdhycd,
    &formatTool::formatParsing_xhzd
};

formatTool::formatTool(std::string fname,std::string line)
    :m_fname(&fname[fname.rfind('/') + 1])
    ,m_line(line)
{
    for(int i = 0; i < (int)(sizeof(fnameList)/sizeof(*fnameList)); i++){
        if(0 == this->m_fname.compare(fnameList[i])){
            (this->*formatParsingList[i])(this->m_line);
            break;
        }
    }
}

formatTool::~formatTool()
{
}


