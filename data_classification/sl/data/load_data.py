import numpy as np
import matplotlib.pyplot as plt
import torch
import torch.nn as nn
from random import randint
import pandas as pd

def load_data(data_type, train_eval):
    if data_type == "standing":
        data = pd.read_csv("./sl/data/standing_data.csv").values
        labels = np.full(data.shape[0], 0)
    elif data_type == "walking":
        data = pd.read_csv("./sl/data/walking_data.csv").values
        labels = np.full(data.shape[0], 1)
    elif data_type == "running":
        data = pd.read_csv("./sl/data/running_data.csv").values
        labels = np.full(data.shape[0], 2)
    else:
        print("Data isn't defined.")
        sys.exit(0)

    if train_eval = "train":
        return torch.from_numpy(data)[0:450], torch.from_numpy(labels).unsqueeze(1)[0:450]
    else train_eval = "test":
        return torch.from_numpy(data)[450:909], torch.from_numpy(labels).unsqueeze(1)[450:909]
    else:
        sys.exit(0)

def shuffle_in_unison(a, b):
    rng_state = np.random.get_state()
    np.random.shuffle(a)
    np.random.set_state(rng_state)
    np.random.shuffle(b)

    return a, b

if __name__ == "__main__":
    data, labels = load_data("standing")

    print(data.shape)
    print(labels.shape)


# data_standing = pd.read_csv("./standing_data.csv")
# data_standing = data_standing.values
# print(data_standing.shape[0])
# data_standing_labels = np.full(data_standing.shape[0], 0)
# data_walking = pd.read_csv("./walking_data.csv")
# data_walking = data_walking.values
# print(data_walking.shape[0])
# data_walking_labels = np.full(data_walking.shape[0], 1)
# data_running = pd.read_csv("./running_data.csv")
# data_running = data_running.values
# print(data_running.shape[0])
# data_running_labels = np.full(data_running.shape[0], 1)

# data_samples = np.concatenate([data_standing, data_walking])
# data_labels = np.concatenate([data_standing_labels, data_walking_labels])

# train_samples, train_labels = shuffle_in_unison(data_samples, data_labels)