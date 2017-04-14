#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-11-03 15:58:23
# Last modified: 2016-11-03 17:35:39
# 

import mayavi.mlab as mlab
from traits.api import HasTraits, Str, Int
from traitsui.api import View, Item

class Employee(HasTraits):
    name        = Str
    department  = Str
    salary      = Int
    bonus       = Int

    view = View(
            Item("department", label="department"),
            Item("name", label="name"),
            Item("salary", label="salary"),
            Item("bonus", label="bonus"),
            title = "employees", width=250, height=150
            )

Employee().configure_traits()


