import numpy as np
import torch
import torch.nn as nn
import argparse
import pickle
import sys

class Net(nn.Module):
    def __init__(self, input_nodes=9, hidden_nodes=1000, output_nodes=1):
        super(Net, self).__init__()
        self.fc1 = nn.Linear(input_nodes, hidden_nodes)
        self.fc2 = nn.Linear(hidden_nodes, hidden_nodes)
        self.fc3 = nn.Linear(hidden_nodes, output_nodes)

    def forward(self, x):
        x = self.fc1(x)
        x = torch.relu(x)
        x = self.fc2(x)
        x = torch.tanh(x)
        x = self.fc3(x)
        x = torch.sigmoid(x)
        return x
