#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-10-02 20:23:15
#

import tushare as ts
from pprint import pprint
import pandas as pd

print ts.__version__

def get_rongxing():
    data = ts.get_hist_data("002123")

    print "type(data) :", type(data)

    pprint(data)

    data.to_excel("/home/minphone/share/temp/002123.xlsx")

def download_all_stock_history_k_line():
    print "download all stock k-line"
    try :
        df = pd.DataFrame.from_csv(cm.DownloadDir + cm.TABLE_STOCKS_BASIC + '.csv')
        pool = ThreadPool(processes = 10)
        pool.map(download_stock_kline, df.index)
        pool.close()
        pool.join()
    except Exception as e:
        print str(e)


if __name__ == '__main__':
    print "do main"
    #download_all_stock_history_k_line()

