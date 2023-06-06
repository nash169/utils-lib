#!/usr/bin/env python
# encoding: utf-8
#
#    This file is part of utils-lib.
#
#    Copyright (c) 2020, 2021, 2022, 2023 Bernardo Fichera <bernardo.fichera@gmail.com>
#
#    Permission is hereby granted, free of charge, to any person obtaining a copy
#    of this software and associated documentation files (the "Software"), to deal
#    in the Software without restriction, including without limitation the rights
#    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#    copies of the Software, and to permit persons to whom the Software is
#    furnished to do so, subject to the following conditions:
#
#    The above copyright notice and this permission notice shall be included in all
#    copies or substantial portions of the Software.
#
#    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#    SOFTWARE.

import matplotlib.pyplot as plt
from scripts.read_file import get_data

sigmoid = get_data("outputs/sigmoid_fun.csv", "X", "Y")
gaussian = get_data("outputs/gaussian_fun.csv", "X", "Y")

fig = plt.figure()
ax = fig.add_subplot(121)
ax.plot(sigmoid["X"], sigmoid["Y"])
ax = fig.add_subplot(122)
ax.plot(gaussian["X"], gaussian["Y"])

fig.savefig("outputs/plot_from_file.png", format="png", dpi=300, bbox_inches="tight")
