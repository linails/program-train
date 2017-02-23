/*
 * Progarm Name: bt-test.cpp
 * Created Time: 2017-02-22 14:26:43
 * Last modified: 2017-02-23 17:45:32
 * @author: minphone.linails linails@foxmail.com 
 */

#include "bt-test.hpp"
#include <iostream>
#include "binditem-tetris.hpp"

using std::cout;
using std::endl;

int ctrl_trigger(int gid, int status)
{
    cout << "[Outter Trigger] gid = " << gid << " - status = " << status << endl;
    return 0;
}

int bt_test(void)
{
    BindItemTetris bit(ctrl_trigger);

    /* init Testing data */
    BindItem_t item;
    vector<BindItem_t> items;
    {
        item.id = 1; item.gateway = "gw01"; item.devid = 1; items.push_back(item);
        item.id = 1; item.gateway = "gw01"; item.devid = 2; items.push_back(item);
        item.id = 1; item.gateway = "gw01"; item.devid = 3; items.push_back(item);
        item.id = 1; item.gateway = "gw01"; item.devid = 4; items.push_back(item);

        bit.add_item_group(items); items.clear();

        item.id = 2; item.gateway = "gw02"; item.devid = 5; items.push_back(item);
        item.id = 2; item.gateway = "gw02"; item.devid = 6; items.push_back(item);
        item.id = 2; item.gateway = "gw02"; item.devid = 7; items.push_back(item);
        item.id = 2; item.gateway = "gw02"; item.devid = 8; items.push_back(item);
    }

    bit.add_item_group(items);
    cout << "---------------------------" << endl;
    {
        string scb = "cb 001";
        auto cb = [&scb](int gid, int status) -> int{
            cout << "[Outter Trigger] gid = " << gid << " - status = " << status;
            cout << " - scb : " << scb << endl;
        };

        bit.register_ctrl_trigger(cb);

        bit.push_ctrl_status(1, 1); bit.print_info(1);
        bit.push_report_status("gw01", 1, 0); bit.print_info(1);
        bit.push_report_status("gw01", 1, 1); bit.print_info(1);

        bit.push_report_status("gw01", 2, 1); bit.print_info(1);
        bit.push_report_status("gw01", 3, 1); bit.print_info(1);
        bit.push_report_status("gw01", 4, 1); bit.print_info(1);

    }
    cout << "---------------------------" << endl;
    {
        item.id = 1; item.gateway = "gw01"; item.devid = 5;
        bit.add_item(item); bit.print_info(1);

        auto cb = [&item](int gid, int status) -> int{
            cout << "[Outter Trigger] gid = " << gid << " - status = " << status;
            cout << " - item.id = " << item.id << " - (gateway, devid) : (" 
                 << item.gateway << " : " << item.devid << ")" << endl;
        };
        bit.register_ctrl_trigger(cb);

        bit.push_report_status("gw01", 5, 0); bit.print_info(1);
        bit.push_report_status("gw01", 1, 0); bit.print_info(1);
        bit.push_report_status("gw01", 2, 0); bit.print_info(1);
        bit.push_report_status("gw01", 3, 0); bit.print_info(1);
        bit.push_report_status("gw01", 4, 0); bit.print_info(1);
    }
    cout << "---------------------------" << endl;
    {
        bit.register_ctrl_trigger(ctrl_trigger); cout << "register_ctrl_trigger Line : " << __LINE__ << endl;
#if 1
        bit.del_item(1, "gw01", 5); bit.print_info(1);
#else
        items.clear();
        item.id = 1; item.gateway = "gw01"; item.devid = 1; items.push_back(item);
        item.id = 1; item.gateway = "gw01"; item.devid = 2; items.push_back(item);
        item.id = 1; item.gateway = "gw01"; item.devid = 3; items.push_back(item);
        item.id = 1; item.gateway = "gw01"; item.devid = 4; items.push_back(item);

        bit.del_item_group(1);
        cout << "del -> add " << endl;
        bit.add_item_group(items); bit.print_info(1);
#endif

        bit.push_ctrl_status(1, 0); bit.print_info(1);
        bit.push_report_status("gw01", 1, 0); bit.print_info(1);
        bit.push_report_status("gw01", 2, 0); bit.print_info(1);
        bit.push_report_status("gw01", 3, 0); bit.print_info(1);

        bit.push_ctrl_status(1, 0); bit.print_info(1);
        bit.push_ctrl_status(1, 1); bit.print_info(1);
        bit.push_ctrl_status(1, 0); bit.print_info(1);

        bit.push_report_status("gw01", 3, 1); bit.print_info(1);
        bit.push_report_status("gw01", 3, 0); bit.print_info(1);
        bit.push_report_status("gw01", 3, 1); bit.print_info(1);
        bit.push_report_status("gw01", 3, 0); bit.print_info(1);
        bit.push_report_status("gw01", 3, 1); bit.print_info(1);

        bit.push_report_status("gw01", 1, 0); bit.print_info(1);

        #if 1
        bit.push_report_status("gw01", 4, 1); bit.print_info(1);
        #else
        bit.push_report_status("gw01", 4, 0); bit.print_info(1);
        #endif
    }
    cout << "---------------------------" << endl;

    return 0;
}

