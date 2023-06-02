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

import matplotlib as mpl
import matplotlib.pyplot as plt
from io_utils import get_data

# Load data
data = get_data("outputs/check_derivative.csv", "gradient", "hessian")

mpl.rcParams['text.usetex'] = True
mpl.rcParams['font.family'] = 'JetBrains'

# Gradient Check Plot
fig = plt.figure()
ax = fig.add_subplot()
ax.plot(data["gradient"][:, 0], data["gradient"][:, 1], 'k', label=r'$\log(E(t))$')
ax.plot(data["gradient"][:, 0], 2*data["gradient"][:, 0], 'r--', label=r'$2 \log(t)$')
ax.scatter(data["gradient"][20:30, 0], data["gradient"][20:30, 1], label=r'$\log(E(t_{20:30}))$')
ax.axes.get_yaxis().set_visible(False)
ax.set_title('Gradient Check', fontsize=20)
ax.axis('square')
ax.set_xlabel(r'$\log(t)$', fontsize=20)
ax.legend(fontsize=20, loc='lower right')
ax.set_xticks([])
fig.tight_layout()
fig.savefig("outputs/check_gradient.png", format="png", dpi=300, bbox_inches="tight")

# Hessian Check Plot
fig = plt.figure()
ax = fig.add_subplot()
ax.plot(data["hessian"][:, 0], data["hessian"][:, 1], 'k', label=r'$\log(E(t))$')
ax.plot(data["hessian"][:, 0], 3*data["hessian"][:, 0], 'r--', label=r'$3 \log(t)$')
ax.scatter(data["hessian"][20:30, 0], data["hessian"][20:30, 1], label=r'$\log(E(t_{20:30}))$')
ax.axes.get_yaxis().set_visible(False)
ax.set_title('Hessian Check', fontsize=20)
ax.axis('square')
ax.set_xlabel(r'$\log(t)$', fontsize=20)
ax.legend(fontsize=20, loc='lower right')
ax.set_xticks([])
fig.tight_layout()
fig.savefig("outputs/check_hessian.png", format="png", dpi=300, bbox_inches="tight")
