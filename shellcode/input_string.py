from root_numpy import root2array, tree2array
from ROOT import TH2D, TH1D
from root_numpy import fill_hist
import numpy as np

#input file
from optparse import OptionParser
parser = OptionParser()
parser.add_option('-f', action = 'store', dest='filename', type='string',help='targe host', default = "defult")
(options, args) = parser.parse_args()

filename = options.filename

print("filepath : ",filename)
print("string":, args[0])

print("-----successful run-----")
