/*
 * Progarm Name: formatParsing.cpp
 * Created Time: 2016-05-15 12:14:11
 * Last modified: 2016-12-18 22:17:06
 * @author: minphone.linails linails@foxmail.com 
 */

#include "formatParsing.h"
#include <iostream>
#include <map>
#include <cstdio>
#include <cstdlib>
#include "regex_common.h"
#include "stringTools.h"
#include <cstring>
#include <cassert>

using std::map;
using std::cout;
using std::endl;

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
    auto print_units = [](vector<string> &us){
        cout << "us.size() : " << us.size() << endl;
        for(auto &u : us){
            cout << "us : " << u << endl;
        }
    };


    /* get wc.word */
    regex_common_c0x("^[\\w\\W][^`<\\s]+", s, this->m_wc.word);


    /* get wc.attr */
    {
        vector<string> units;

        regex_common_c0x("`\\d`[\\W\\w][^\\(]*", s, units);
        assert(units.size() == 1);

        regex_common_c0x("`\\d`[\\W\\w][^`<]*", units[0], this->m_wc.attr);
    }


    /* get units */
    {
        vector<string> units;
        //regex_common_c0x("(\\(\\d\\)){1}.+?(?=>\\(\\d\\))|\\(\\d\\).*", s, units);

#if 0
        stringTools st(s);

        st.match("([1-9])-[([1-9])|$]", units);
#else
        this->regex_split(s, units);
#endif

    //    print_units(units);

        vector<string> subunits;
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

    }
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
 * <br><font size=3 color=purple>【英文】parently love<br>
 *                              【故事】东汉末年，曹操进攻刘备，在斜谷界口驻扎，陷于进退两难境地，
 *                                部将夏侯淳询问夜间口令，曹操随口说鸡肋。杨修认为是曹操退兵的意思，
 *                                叫士兵打点行装，曹操借口杀了杨修。后见到骨瘦如柴的杨修父亲杨彪，
 *                                问为何？杨彪说有舐犊之爱\n
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
 * list :  ①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮
 *
 * “左”倾机会主义	
 *      <font size=+2 color="red">[“左”倾机会主义]</font>zuǒqīnɡjīhuìzhǔyì见627页〖机会主义〗。\n
 *
 *
 * 一下	
 *      <font size=+2 color="red">[一下]</font>yīxià(～儿)
 *      ①<font size=+1 color="green">数</font>量词。用在动词后面，表示做一次或试着做：看～儿｜打听～｜研究～。
 *      ②<font size=+1 color="green">副</font>表示短暂的时间：灯～儿又亮了｜这天气，～冷，～热。‖也说一下子。\n
 *
 * 
 * 一	*
 *      <font size=+2 color="red">一</font>1yī
 *      ①<font size=+1 color="green">数</font>最小的正整数。参看1271页〖<font size=+1 color="green">数</font>字〗。
 *      ②<font size=+1 color="green">数</font>表示同一：咱们是～家人｜你们～路走｜这不是～码事。
 *      ③<font size=+1 color="green">数</font>表示另一：番茄～<font size=+1 color="green">名</font>西红柿。
 *      ④<font size=+1 color="green">数</font>表示整个；全：～冬｜～生｜～路平安｜～屋子人｜～身的汗。
 *      ⑤表示专一：～心～意。
 *      ⑥<font size=+1 color="green">数</font>表示动作是一次，或表示动作是短暂的，或表示动作是试试的。
 *          a)用在重叠的动词(多为单音)中间：歇～歇｜笑～笑｜让我闻～闻。
 *          b)用在动词之后，<font size=+1 color="green">动</font>量词之前：笑～声｜看～眼｜让我们商量～下。
 *      ⑦<font size=+1 color="green">数</font>用在动词或动量词前面，表示先做某个动作(下文说明动作结果)：
 *          ～跳跳了过去｜～脚把它踢开｜他在旁边～站，再也不说什么。
 *      ⑧<font size=+1 color="green">数</font>与“就”配合，表示两个动作紧接着发生：～请就来｜～说就明白了。
 *      ⑨一旦；一经：～失足成千古恨。
 *      ⑩〈书〉<font size=+1 color="green">助</font>用在某些词前加强语气：～何速也｜为害之甚，～至于此!
 *          ‖注意“一”字单用或在一词一句末尾念阴平，如“十一、一一得一”，在去声字前念阳平，
 *          如“一半、一共”，在阴平、阳平、上声字前念去声，如“一天、一年、一点”。
 *          本词典为简便起见，条目中的“一”字，都注阴平。\n
 *
 *
 * 好	*
 *      <font size=+2 color="red">好</font>hǎo 
 *      ①<font size=+1 color="green">形</font>优点多的；使人满意的(跟“坏”相对)：～人｜～东西｜～事情｜～脾气｜庄稼长得很～。
 *      ②<font size=+1 color="green">形</font>合宜；妥当：初次见面，不知跟他说些什么～。
 *      ③用在动词前，表示使人满意的性质在哪方面：～看｜～听｜～吃。
 *      ④<font size=+1 color="green">形</font>友爱；和睦：友～｜～朋友｜他跟我～。
 *      ⑤<font size=+1 color="green">形</font>(身体)健康；(疾病)痊愈：体质～｜身子比去年～多了|他的病～了。
 *      ⑥<font size=+1 color="green">形</font>用于套语：～睡｜您～走。
 *      ⑦<font size=+1 color="green">形</font>用在动词后，表示完成或达到完善的地步：计划订～了｜功课准备～了｜外边太冷，穿～了衣服再出去｜坐～吧，要开会了。
 *      ⑧<font size=+1 color="green">形</font>表示赞许、同意或结束等语气：～，就这么办｜～了，不要再说了。
 *      ⑨<font size=+1 color="green">形</font>反话，表示不满意：～，这一下可麻烦了。
 *      ⑩<font size=+1 color="green">形</font>容易(限用于动词前)：那个歌儿～唱｜这问题很～回答。
 *      ○11动便于：地整平了～种庄稼｜告诉我他在哪儿，我～找他去。
 *      ○12〈方〉<font size=+1 color="green">动</font>应该；可以：我～进来吗?｜时间不早了，你～走了。
 *      ○13副用在形容词、<font size=+1 color="green">数</font>量词等前面，表示多或久：～多｜～久｜～几个｜～一会儿｜～半天。
 *      ○14副用在形容词、<font size=+1 color="green">动</font>词前，表示程度深，并带感叹语气：～冷｜～香｜～漂亮｜～面熟｜～大的工程｜原来你躲在这儿，害得我～找!
 *      ○15〈方〉<font size=+1 color="green">副</font>用在形容词前面问数量或程度，用法跟“多”相同：哈尔滨离北京～远?\n
 *
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

int  formatTool::regex_split(string &s, vector<string> &units)
{
    int ret = 0;

    char *ptr = new char[s.size() + 1];

    if(nullptr != ptr){

        size_t len = 0;
        vector<string> last;

        regex_common_c0x("(\\(\\d\\)).+?(?=\\(\\d\\))", s, units);
        if(0 != units.size()){

            memcpy(ptr, s.c_str(), s.size());
            ptr[s.size()] = '\0';

            for(auto &u : units) len += u.size();

            if(len < s.size()){
                string sptr = &ptr[len];
                regex_common_c0x("(\\(\\d\\)).+$", sptr, last);

                if(last.size() > 0){
                    units.push_back(last[0]);
                }
                //cout << "last[0] : " << last[0] << endl;
            }
        }else{
            units.push_back(s);
        }

        delete [] ptr;
    }else{
        ret = -1;
        cout << "[Error] new failed !" << endl;
    }

    return ret;
}

int  formatTool::get_wordcell(WordCell_t &wc)
{
    wc = this->m_wc;

    return 0;
}
