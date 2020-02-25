import numpy as np
import matplotlib.pyplot as plt
import torch
import torch.nn as nn
import pandas as pd
import pickle
from random import randint

from sl.net.classifier_9_1_sigmoid import Net
from sl.data.load_data import load_data, shuffle_in_unison


if __name__ == "__main__":

    data_standing, labels_standing = load_data("standing")
    data_walking, labels_walking = load_data("walking")

    data = np.concatenate([data_standing, data_walking])[1500:1803]
    labels = np.concatenate([labels_standing, labels_walking])[1500:1803]

    data, labels = shuffle_in_unison(data, labels)
    data, labels = torch.from_numpy(data), torch.from_numpy(labels)

    model = pickle.load(open("./sl/trained_models/standing_walking_MSELoss_Adam_5e-5_1000epochs_100bs.p", "rb"))
    criterion = nn.MSELoss()

    for data_points in range(0, data.shape[0]):

        output = model(data[data_points].float()) 

        loss = criterion(output, labels[data_points].float())

        print(' loss: ', loss.item()) 