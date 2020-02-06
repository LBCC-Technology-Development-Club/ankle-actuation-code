import numpy as np
import torch
import torch.nn as nn
import argparse
import pickle
import sys

class Net(nn.Module):
    def __init__(self, input_nodes=9, output_nodes=1):
        super(Net, self).__init__()
        self.layer = nn.Linear(input_nodes, output_nodes)

    def forward(self, x):
        x = self.layer(x)
        x = torch.sigmoid(x)
        return x
