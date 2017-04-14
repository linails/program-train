#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-09-09 20:34:41
#

import sys
import csv
import time

print "platform :", sys.platform
print "sys.argv[0] :", sys.argv[0] #argv[0] is python script name

def get_unit(line, bodylist):
    head = line[ : line.find(':') ]
    body = line[ line.find(':')+1 : line.find('\r\n')]
    bodylist += body.split(',')
    return head

def write2csv():
    print "called function : write2csv"
    with open("/home/minphone/github/wordlib/wordembeding_recovered/wordembeding.csv", 'wb') as csvfile:
        spamwriter = csv.writer(csvfile, dialect='excel')
        for line in filecontent:
            body    = []

            head = get_unit(line, body)

            csvunit = (head, body)
            print "head :", head
            print "csvunit :", csvunit[0]

            spamwriter.writerow(csvunit[0])
            spamwriter.writerow(csvunit[1])
            print "\n", csvunit[1]

            time.sleep(1)
            #time.sleep(0.01) # delay 0.01s

fn = "/home/minphone/github/wordlib/wordembeding_recovered/wordembeding.txt"

filecontent = open(fn, 'r')

from xlwt import *
def write2xls():
    print "called function : write2xls"

    book2save = []

    for index, line in enumerate(filecontent):

        book2save.append(line)

        if False ==  ((index + 1) % 5000):
            print "index :", index + 1

            book = Workbook()
            sheet1 = book.add_sheet('wordembeding')

            al = Alignment()
            al.horz = Alignment.HORZ_CENTER
            al.vert = Alignment.VERT_CENTER

            for sindex, sline in enumerate(book2save):
                body    = []

                head = get_unit(sline, body)

                csvunit = (head, body)

                sheet1.write(sindex, 0, csvunit[0].decode("utf8"))

                for idx, value in enumerate(csvunit[1]):
                    sheet1.write(sindex, idx+1, value)

            index_begin = index - 5000 + 2
            index_end = index + 1
            book.save("/home/minphone/github/wordlib/wordembeding_recovered/wordembeding-(%d-%d).xls" % (index_begin, index_end))

            book2save[:] = []

    if len(book2save) > 0:
        print "len(book2save) :", len(book2save)
        book = Workbook()
        sheet1 = book.add_sheet('wordembeding')

        for sindex, sline in enumerate(book2save):
            if sindex > 4437: break # 4437行后格式有错误
            print "sindex = %d -- %s " % (sindex, sline.decode("utf8"))
            body    = []

            head = get_unit(sline, body)
            print "head :", head

            csvunit = (head, body)
            sheet1.write(sindex, 0, csvunit[0].decode("utf8"))

            for idx, value in enumerate(csvunit[1]):
                sheet1.write(sindex, idx+1, value)

        book.save("/home/minphone/github/wordlib/wordembeding_recovered/wordembeding-(500001-).xls")


def main():
    write2xls()
    #write2csv()

if __name__ == "__main__":
    main()


