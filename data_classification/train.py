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

    data = np.concatenate([data_standing, data_walking])
    labels = np.concatenate([labels_standing, labels_walking])

    data, labels = shuffle_in_unison(data, labels)
    data, labels = torch.from_numpy(data), torch.from_numpy(labels)

    model = Net()
    criterion = nn.MSELoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=5e-5)
    num_epochs = 1000
    batch_size = 100
    
    for epoch in range(1000):

        permutation = torch.randperm(data.shape[0])

        for data_points in range(0, data.shape[0], batch_size):

            optimizer.zero_grad()

            indices = permutation[data_points:data_points+batch_size]
            batch_x, batch_y = data[indices], labels[indices]

            output = model(batch_x.float()) 
            loss = criterion(output, batch_y.float())

            print('epoch: ', epoch, 'data: ', data_points,' loss: ', loss.item()) 
            
            loss.backward()
            optimizer.step()

        pickle.dump(model, open("./sl/trained_models/standing_walking_MSELoss_Adam_5e-5_1000epochs_100bs.p", "wb"))

