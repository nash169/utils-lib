#! /usr/bin/env python
# encoding: utf-8

import numpy as np
import matplotlib.pyplot as plt
import sys

from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from utils import get_data

data = get_data("rsc/check_derivative.csv", "gradient")

fig = plt.figure()
ax = fig.add_subplot()
ax.plot(data["gradient"][:, 0], data["gradient"][:, 1],
        data["gradient"][:, 0], 2*data["gradient"][:, 0], 'r--')

plt.show()
