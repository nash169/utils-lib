#! /usr/bin/env python
# encoding: utf-8

import numpy as np
import matplotlib.pyplot as plt
import sys

from matplotlib import cm
from io_utils import get_data

data = get_data(sys.argv[1], "X", "Y")

fig = plt.figure()
ax = fig.add_subplot(111)
ax.plot(data["X"], data["Y"])


plt.show()
