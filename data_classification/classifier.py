import numpy as np
from sklearn.datasets import make_moons
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
import torch
import torch.nn as nn
from random import randint
import pandas as pd

train_samples = []
train_labels = []

test_samples = []
test_labels = []

def shuffle_in_unison(a, b):
    rng_state = np.random.get_state()
    np.random.shuffle(a)
    np.random.set_state(rng_state)
    np.random.shuffle(b)

    return a, b

def randomFunction(train_samples, train_labels):

    train_subsamples = []

    for i in range(3000):

        random_red = randint(180, 255)
        train_subsamples.append(random_red)
        random_green = randint(0,150)
        train_subsamples.append(random_green)

        train_samples.append(train_subsamples)
        train_labels.append(0)

        train_subsamples = []

        random_red = randint(0,150)
        train_subsamples.append(random_red)
        random_green = randint(180, 255)
        train_subsamples.append(random_green)

        train_samples.append(train_subsamples)
        train_labels.append(1)

        train_subsamples = []


    return train_samples, train_labels

# train_samples, train_labels = randomFunction(train_samples, train_labels)
# test_samples, test_labels = randomFunction(test_samples, test_labels)
# train_samples = np.array(train_samples)
# train_labels = np.array(train_labels)
# test_samples = np.array(test_samples)
# test_labels = np.array(test_labels)


# print(train_samples)
# print(train_labels)

data_standing = pd.read_csv("./standing_data.csv")
data_standing = data_standing.values
print(data_standing.shape[0])
data_standing_labels = np.full(data_standing.shape[0], 0)
data_walking = pd.read_csv("./walking_data.csv")
data_walking = data_walking.values
print(data_walking.shape[0])
data_walking_labels = np.full(data_walking.shape[0], 1)
data_running = pd.read_csv("./running_data.csv")
data_running = data_running.values
print(data_running.shape[0])
data_running_labels = np.full(data_running.shape[0], 1)

data_samples = np.concatenate([data_standing, data_walking])
data_labels = np.concatenate([data_standing_labels, data_walking_labels])

train_samples, train_labels = shuffle_in_unison(data_samples, data_labels)

print(data_samples.shape)
print(data_labels.shape)

class Network():
    
    def __init__(self, X, Y, n_hidden=10, learning_rate=0.8e-2, device='cpu'):
        self.device = device
        self.X = X
        self.Y = Y.reshape(-1,1)
        self.Y_t = torch.FloatTensor(self.Y).to(device=self.device)
        self.n_input_dim = X.shape[1]
        self.n_output = 1
        self.learning_rate = learning_rate
        self.n_hidden = n_hidden
        
        # Build network
        self.net = nn.Sequential(
            nn.Linear(self.n_input_dim, self.n_hidden), 
            nn.ELU(),
            nn.Linear(self.n_hidden, self.n_output),
            nn.Sigmoid())
        
        if self.device == 'cuda':
            self.net.cuda()
        
        self.loss_func = nn.BCELoss()
        self.optimizer = torch.optim.Adam(self.net.parameters(), 
                                          lr=self.learning_rate)
        
    def predict(self, X):
        # Function to generate predictions based on data
        X_t = torch.FloatTensor(X).to(device=self.device)
        return self.net(X_t)
    
    def calculate_loss(self, y_hat):
        return self.loss_func(y_hat, self.Y_t)
    
    def update_network(self, y_hat):
        self.optimizer.zero_grad()
        loss = self.calculate_loss(y_hat)
        loss.backward()
        self.optimizer.step()
        self.training_loss.append(loss.item())
        
    def calculate_accuracy(self, y_hat_class, Y):
        return np.sum(Y.reshape(-1,1)==y_hat_class) / len(Y)
        
    def train(self, n_iters=10000):
        self.training_loss = []
        self.training_accuracy = []
        
        for i in range(n_iters):
            print("Iter" + str(i))
            y_hat = self.predict(self.X)
            self.update_network(y_hat)
            y_hat_class = np.where(y_hat<0.5, 0, 1)
            accuracy = self.calculate_accuracy(y_hat_class, self.Y)
            self.training_accuracy.append(accuracy)
            
    def plot_training_results(self):
        fig, ax = plt.subplots(2, 1, figsize=(12,8))
        ax[0].plot(self.training_loss)
        ax[0].set_ylabel('Loss')
        ax[0].set_title('Training Loss')

        ax[1].plot(self.training_accuracy)
        ax[1].set_ylabel('Classification Accuracy')
        ax[1].set_title('Training Accuracy')

        plt.tight_layout()
        plt.show()
        
    def plot_testing_results(self, X_test, Y_test):
        # Pass test data
        y_hat_test = self.predict(X_test)
        y_hat_test_class = np.where(y_hat_test<0.5, 0, 1)
        print("Test Accuracy {:.2f}%".format(
            self.calculate_accuracy(y_hat_test_class, Y_test) * 100))

        # Plot the decision boundary
        # Determine grid range in x and y directions
        x_min, x_max = self.X[:, 0].min()-0.1, self.X[:, 0].max()+0.1
        y_min, y_max = self.X[:, 1].min()-0.1, self.X[:, 1].max()+0.1

        # Set grid spacing parameter
        spacing = min(x_max - x_min, y_max - y_min) / 100

        # Create grid
        XX, YY = np.meshgrid(np.arange(x_min, x_max, spacing),
                       np.arange(y_min, y_max, spacing))

        # Concatenate data to match input
        data = np.hstack((XX.ravel().reshape(-1,1), 
                          YY.ravel().reshape(-1,1)))

        # Pass data to predict method
        db_prob = self.predict(data)

        clf = np.where(db_prob<0.5,0,1)

        Z = clf.reshape(XX.shape)

        plt.figure(figsize=(12,8))
        plt.contourf(XX, YY, Z, cmap=plt.cm.Accent, alpha=0.5)
        plt.scatter(X_test[:,0], X_test[:,1], c=Y_test, 
                    cmap=plt.cm.Accent)
        plt.show()

# data = np.loadtxt('standing_data.csv')
# print(data)




net = Network(train_samples, train_labels)
net.train()
print(net.predict(train_samples))
print(train_labels)
net.plot_training_results()
net.plot_testing_results(train_samples, train_labels)

